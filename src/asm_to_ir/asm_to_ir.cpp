#include <charconv>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <boost/hana/functional/overload.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive/unordered_set.hpp>

#include <format>
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

namespace asm_repr {

using RegVal_t = uint32_t;
using RegId_t = uint8_t;
using Bits_t = uint8_t;

struct RegValue {
  RegId_t reg_id;
};

struct ImmValue {
  uint64_t value;
};

using Value = std::variant<ImmValue, RegValue>;

namespace {
struct ParseError : std::runtime_error {
  using std::runtime_error::runtime_error;
};

template<typename T>
T parseNumber(std::string_view sv, int base = 10) {
  if (sv.empty())
    throw ParseError("parseNumber: empty input");

  if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
    T value{};
    auto first = sv.data();
    auto last = sv.data() + sv.size();

    auto [ptr, ec] = std::from_chars(first, last, value, base);
    if (ec == std::errc::invalid_argument)
      throw ParseError("parseNumber: invalid integer");
    if (ec == std::errc::result_out_of_range)
      throw ParseError("parseNumber: integer out of range");
    if (ptr != last)
      throw ParseError("parseNumber: trailing characters");

    return value;
  } else {
    static_assert(!sizeof(T), "parseNumber<T>: T must be an integral (non-bool)");
  }
}

Value parseNumberOrRegValue(std::string_view sv, size_t bits) {
  if (sv[0] == 'r') {
    return RegValue{parseNumber<RegId_t>(sv.substr(1))};
  }
  auto n = parseNumber<uint64_t>(sv);
  return ImmValue{n};
  // if (bits == 8) {
  //   return (uint8_t) n;
  // } else if (bits == 16) {
  //   return (uint16_t) n;
  // } else if (bits == 32) {
  //   return (uint32_t) n;
  // }
  // return n;
}

std::string_view removeSpaces(std::string_view v) {
  auto is_space = [](unsigned char c) { return std::isspace(c); };

  while (!v.empty() && is_space(v.front())) v.remove_prefix(1);
  return v;
}

std::string_view takeUntil(std::string_view s, char delim) {
  auto pos = s.find(delim);
  return (pos == std::string_view::npos) ? s : s.substr(0, pos);
}

std::string_view getTokenUntilWhitespace(std::string_view s) {
  size_t i = 0;
  while (i < s.size() && !std::isspace((unsigned char) s[i])) ++i;
  std::string_view tok = s.substr(0, i);
  s.remove_prefix(i);
  while (!s.empty() && std::isspace((unsigned char) s.front()))
    s.remove_prefix(1);

  return tok;
}

std::string_view consumeUntilWhitespace(std::string_view &s) {
  size_t i = 0;
  while (i < s.size() && !std::isspace((unsigned char) s[i])) ++i;
  std::string_view tok = s.substr(0, i);
  s.remove_prefix(i);
  while (!s.empty() && std::isspace((unsigned char) s.front()))
    s.remove_prefix(1);

  return tok;
}

std::string_view &expectSymbol(std::string_view &s, char expected) {
  if (s.at(0) == expected) {
    s.remove_prefix(1);
    return s;
  }
  throw std::runtime_error(std::format("Expected '{}' but get '{}' here: \"{}\"", expected, s[0], s.substr(0, 10).data()));
}

std::string_view &expectString(std::string_view &s, const char *expected) {
  size_t len = strlen(expected);
  if (s.substr(0, len) == expected) {
    s.remove_prefix(len);
    return s;
  }
  throw std::runtime_error(std::format("Expected '{}' but get '{}' here: \"{}\"", expected, s.substr(0, len), s.substr(0, len + 10).data()));
}
}// namespace

struct Function;

constexpr inline size_t kIsaRegFileSize = 16;
constexpr inline std::string kRegFileName = "regFile";

template<size_t REG_FILE_SIZE = kIsaRegFileSize>
struct Registers {
  std::array<RegVal_t, REG_FILE_SIZE> REG_FILE = {};
};

struct Instruction {
  virtual void translateToIR(llvm::Module &module, llvm::IRBuilder<> &builder, Function &f) = 0;
  virtual ~Instruction() = default;
};

struct AddInstruction : Instruction {
  using AddInstructionPtr = std::unique_ptr<AddInstruction>;

  Bits_t bits;
  RegValue res_reg;
  RegValue arg1_reg;
  Value arg2;

  AddInstruction(Bits_t bits_, RegValue res, RegValue arg1, Value arg2_)
      : bits(bits_), res_reg(res), arg1_reg(arg1), arg2(arg2_) {}

  void translateToIR(llvm::Module &module, llvm::IRBuilder<> &builder, Function &) override {
    auto *regs = module.getGlobalVariable(kRegFileName);
    auto *arg1_ir = builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, arg1_reg.reg_id);
    auto *arg2_ir = std::visit(boost::hana::overload(
                                   [&](ImmValue v) {
                                     // TODO: think about different int types
                                     return static_cast<llvm::Value *>(builder.getInt32(v.value));
                                   },
                                   [&](RegValue v) {
                                     return builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, v.reg_id);
                                   }),
                               arg2);
    auto *res_ir = builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, res_reg.reg_id);
    builder.CreateStore(builder.CreateAdd(arg1_ir, arg2_ir), res_ir);
  }

  static AddInstructionPtr parse(std::string_view &in) {
    in = removeSpaces(in);
    auto bits_sv = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto res = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto arg1 = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto arg2 = consumeUntilWhitespace(in);
    auto bits = parseNumber<Bits_t>(bits_sv);
    return std::make_unique<AddInstruction>(
        bits,
        RegValue{parseNumber<RegId_t>(res)},
        RegValue{parseNumber<RegId_t>(arg1)},
        parseNumberOrRegValue(arg2, bits));
  }

  ~AddInstruction() override = default;
};

struct MulInstruction : Instruction {
  using MulInstructionPtr = std::unique_ptr<MulInstruction>;

  Bits_t bits;
  RegValue res_reg;
  RegValue arg1_reg;
  Value arg2;

  MulInstruction(Bits_t bits_, RegValue res, RegValue arg1, Value arg2_)
      : bits(bits_), res_reg(res), arg1_reg(arg1), arg2(arg2_) {}

  static MulInstructionPtr parse(std::string_view &in) {
    in = removeSpaces(in);
    auto bits_sv = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto res = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto arg1 = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto arg2 = consumeUntilWhitespace(in);
    auto bits = parseNumber<Bits_t>(bits_sv);
    return std::make_unique<MulInstruction>(
        bits,
        RegValue{parseNumber<RegId_t>(res)},
        RegValue{parseNumber<RegId_t>(arg1)},
        parseNumberOrRegValue(arg2, bits));
  }

  void translateToIR(llvm::Module &module, llvm::IRBuilder<> &builder, Function &) override {
    auto *regs = module.getGlobalVariable(kRegFileName);
    auto *arg1_ir = builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, arg1_reg.reg_id);
    auto *arg2_ir = std::visit(boost::hana::overload(
                                   [&](ImmValue v) {
                                     // TODO: think about different int types
                                     return static_cast<llvm::Value *>(builder.getInt32(v.value));
                                   },
                                   [&](RegValue v) {
                                     return builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, v.reg_id);
                                   }),
                               arg2);
    auto *res_ir = builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, res_reg.reg_id);
    builder.CreateStore(builder.CreateMul(arg1_ir, arg2_ir), res_ir);
  }

  ~MulInstruction() override = default;
};

struct MovInstruction : Instruction {
  using MovInstructionPtr = std::unique_ptr<MovInstruction>;

  Bits_t bits;
  RegValue res_reg;
  Value arg1;

  MovInstruction(Bits_t bits_, RegValue res, Value arg1_)
      : bits(bits_), res_reg(res), arg1(arg1_) {}

  static MovInstructionPtr parse(std::string_view &in) {
    in = removeSpaces(in);
    auto bits_sv = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto res = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto arg1 = consumeUntilWhitespace(in);
    auto bits = parseNumber<Bits_t>(bits_sv);
    return std::make_unique<MovInstruction>(
        bits,
        RegValue{parseNumber<RegId_t>(res)},
        parseNumberOrRegValue(arg1, bits));
  }

  void translateToIR(llvm::Module &module, llvm::IRBuilder<> &builder, Function &) override {
    auto *regs = module.getGlobalVariable(kRegFileName);
    auto *arg1_ir = std::visit(boost::hana::overload(
                                   [&](ImmValue v) {
                                     // TODO: think about different int types
                                     return static_cast<llvm::Value *>(builder.getInt32(v.value));
                                   },
                                   [&](RegValue v) {
                                     return builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, v.reg_id);
                                   }),
                               arg1);
    auto *res_ir = builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, res_reg.reg_id);
    builder.CreateStore(arg1_ir, res_ir);
  }

  ~MovInstruction() override = default;
};

struct RetInstruction : Instruction {
  using RetInstructionPtr = std::unique_ptr<RetInstruction>;

  Bits_t bits;
  Value arg1;

  RetInstruction(Bits_t bits_, Value arg1_)
      : bits(bits_), arg1(arg1_) {}

  static RetInstructionPtr parse(std::string_view &in) {
    in = removeSpaces(in);
    auto bits_sv = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto res = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto arg1 = consumeUntilWhitespace(in);
    auto bits = parseNumber<Bits_t>(bits_sv);
    return std::make_unique<RetInstruction>(
        bits,
        parseNumberOrRegValue(arg1, bits));
  }

  void translateToIR(llvm::Module &module, llvm::IRBuilder<> &builder, Function &) override {
    auto *regs = module.getGlobalVariable(kRegFileName);
    auto *arg1_ir = std::visit(boost::hana::overload(
                                   [&](ImmValue v) {
                                     // TODO: think about different int types
                                     return static_cast<llvm::Value *>(builder.getInt32(v.value));
                                   },
                                   [&](RegValue v) {
                                     return builder.CreateConstGEP2_32(regs->getValueType(), regs, 0, v.reg_id);
                                   }),
                               arg1);
    builder.CreateRet(arg1_ir);
  }

  ~RetInstruction() override = default;
};

struct BasicBlock : public boost::intrusive::list_base_hook<>, public boost::intrusive::unordered_set_base_hook<> {
 public:
  using BasicBlockPtr = std::unique_ptr<BasicBlock>;
  using BasicBlockId = uint32_t;

  static BasicBlockPtr parse(std::string_view in) {
    auto bb = std::make_unique<BasicBlock>();
    while (true) {
      in = removeSpaces(in);
      auto label = getTokenUntilWhitespace(in);
      if (in[label.size()] == ':') {
        // read next function
        return bb;
      }
      if (label.at(0) == '.') {
        // read next basic block
        return bb;
      }
      if (label == "add") {
        bb->instrs.push_back(AddInstruction::parse(in));
      } else if (label == "mul") {
        bb->instrs.push_back(MulInstruction::parse(in));
      } else if (label == "mov") {
        bb->instrs.push_back(MovInstruction::parse(in));
      } else if (label == "ret") {
        bb->instrs.push_back(RetInstruction::parse(in));
      } else {
        throw std::runtime_error(std::format("Unknown instruction {}", label.data()));
      }
    }
  }

  std::vector<std::unique_ptr<Instruction>> instrs;
};

struct Function {
  using FunctionPtr = std::unique_ptr<Function>;

  static FunctionPtr parse(std::string_view &in) {
    auto f = std::make_unique<Function>();
    while (true) {
      in = removeSpaces(in);
      if (in.at(0) == '.') {
        expectSymbol(in, '.');
        auto label = consumeUntilWhitespace(in);
        f->bbs[std::string(label)] = BasicBlock::parse(in);
      } else {
        break;
      }
    }
    return f;
  }

  std::unordered_map<std::string, std::unique_ptr<BasicBlock>> bbs;
};

class Parser {
 public:
  void parse(std::string_view input) {
    while (!input.empty()) {
      input = removeSpaces(input);
      auto function_name = takeUntil(input, ':');
      functions[std::string(function_name)] = Function::parse(input);
    }
  }

 private:
  std::unordered_map<std::string, std::unique_ptr<Function>> functions;
};

}// namespace asm_repr

int main(int argc, char *argv[]) {
}
