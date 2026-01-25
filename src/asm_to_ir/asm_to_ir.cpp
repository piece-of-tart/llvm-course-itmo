#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <boost/intrusive/list.hpp>
#include <boost/intrusive/unordered_set.hpp>

#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

// using namespace llvm;

//////////////////////////////
// All instructions
//////////////////////////////

enum InsnId_t {
  EXIT, // 0
  PUSH, // imm
  POP,  // 1r
  ADD_S,// 0
  SUB_S,// 0
  MUL_S,// 0
  DIV_S,// 0
  NEG,  // 1r
  ADD,  // 3r
  SUB,  // 3r
  MUL,  // 3r
  DIV,  // 3r
  ADDI, // 2r imm
  SUBI, // 2r imm
  MULI, // 2r imm
  DIVI, // 2r imm
  B,    // imm
  RET,  // 0
  BL,   // imm
  BEQ,  // 2r imm
  BNE,  // 2r imm
  BGE,  // 2r imm
  BLT,  // 2r imm
  READ, // 1r
  WRITE // 1r
};

//////////////////////////////
// Model for simulation
//////////////////////////////

using RegId_t = uint8_t;
using RegVal_t = uint32_t;
using Stack_t = std::stack<RegVal_t>;

const int REG_FILE_SIZE = 4;
class CPU {
 public:
  RegVal_t REG_FILE[REG_FILE_SIZE] = {};
  RegVal_t PC;
  RegVal_t NEXT_PC;
  Stack_t CALL_STACK;
  Stack_t STACK;
  uint32_t RUN;
  bool stack_ok() {
    if (STACK.empty()) {
      RUN = 0;
      outs() << "[RUNTIME ERROR] STACK ERROR\n";
      return false;
    }
    return true;
  }
  bool call_stack_ok() {
    if (STACK.empty()) {
      RUN = 0;
      outs() << "[RUNTIME ERROR] CALL STACK ERROR\n";
      return false;
    }
    return true;
  }
};

//////////////////////////////
// Universal Instruction
//////////////////////////////

class Instr {
 public:
  InsnId_t m_ID;
  void (*m_INSTR)(CPU *, Instr *);
  RegId_t m_rs1;
  RegId_t m_rs2;
  RegId_t m_rs3;
  RegVal_t m_imm;
  std::string m_name;
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name) {}
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name,
        RegId_t rs1)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name), m_rs1(rs1) {}
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name,
        RegVal_t imm)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name), m_imm(imm) {}
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name,
        RegId_t rs1, RegId_t rs2, RegId_t rs3)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name), m_rs1(rs1), m_rs2(rs2),
        m_rs3(rs3) {}
  Instr(InsnId_t ID, void (*do_INSTR)(CPU *, Instr *), std::string name,
        RegId_t rs1, RegId_t rs2, RegVal_t imm)
      : m_ID(ID), m_INSTR(do_INSTR), m_name(name), m_rs1(rs1), m_rs2(rs2),
        m_imm(imm) {}
  void dump() { outs() << m_name << '\n'; }
  bool isCFI() {
    return m_ID == EXIT || m_ID == B || m_ID == RET || m_ID == BL || m_ID == BEQ || m_ID == BNE || m_ID == BGE || m_ID == BLT;
  }
};

//////////////////////////////
// Interpreter function
//////////////////////////////

void do_exit(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->RUN = 0;
}
void do_push(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->STACK.push(instr->m_imm);
}
void do_pop(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  cpu->REG_FILE[instr->m_rs1] = cpu->STACK.top();
  cpu->STACK.pop();
}
void do_add_s(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val1 = cpu->STACK.top();
  cpu->STACK.pop();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val2 = cpu->STACK.top();
  cpu->STACK.pop();
  cpu->STACK.push(val1 + val2);
}
void do_sub_s(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val1 = cpu->STACK.top();
  cpu->STACK.pop();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val2 = cpu->STACK.top();
  cpu->STACK.pop();
  cpu->STACK.push(val2 - val1);
}
void do_mul_s(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val1 = cpu->STACK.top();
  cpu->STACK.pop();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val2 = cpu->STACK.top();
  cpu->STACK.pop();
  cpu->STACK.push(val1 * val2);
}
void do_div_s(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val1 = cpu->STACK.top();
  cpu->STACK.pop();
  if (!cpu->stack_ok()) {
    return;
  }
  RegVal_t val2 = cpu->STACK.top();
  cpu->STACK.pop();
  cpu->STACK.push(val2 / val1);
}
void do_neg(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = -cpu->REG_FILE[instr->m_rs1];
}
void do_add(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] =
      cpu->REG_FILE[instr->m_rs2] + cpu->REG_FILE[instr->m_rs3];
}
void do_sub(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] =
      cpu->REG_FILE[instr->m_rs2] - cpu->REG_FILE[instr->m_rs3];
}
void do_mul(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] =
      cpu->REG_FILE[instr->m_rs2] * cpu->REG_FILE[instr->m_rs3];
}
void do_div(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] =
      cpu->REG_FILE[instr->m_rs2] / cpu->REG_FILE[instr->m_rs3];
}
void do_addi(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = cpu->REG_FILE[instr->m_rs2] + instr->m_imm;
}
void do_subi(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = cpu->REG_FILE[instr->m_rs2] - instr->m_imm;
}
void do_muli(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = cpu->REG_FILE[instr->m_rs2] * instr->m_imm;
}
void do_divi(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->REG_FILE[instr->m_rs1] = cpu->REG_FILE[instr->m_rs2] / instr->m_imm;
}
void do_b(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->NEXT_PC = instr->m_imm;
}
void do_ret(CPU *cpu, Instr *instr) {
  instr->dump();
  if (!cpu->call_stack_ok()) {
    return;
  }
  cpu->NEXT_PC = cpu->CALL_STACK.top();
  cpu->CALL_STACK.pop();
}
void do_bl(CPU *cpu, Instr *instr) {
  instr->dump();
  cpu->CALL_STACK.push(cpu->PC + 1);
  cpu->NEXT_PC = instr->m_imm;
}
void do_beq(CPU *cpu, Instr *instr) {
  instr->dump();
  if (cpu->REG_FILE[instr->m_rs1] == cpu->REG_FILE[instr->m_rs2])
    cpu->NEXT_PC = instr->m_imm;
}
void do_bne(CPU *cpu, Instr *instr) {
  instr->dump();
  if (cpu->REG_FILE[instr->m_rs1] != cpu->REG_FILE[instr->m_rs2])
    cpu->NEXT_PC = instr->m_imm;
}
void do_bge(CPU *cpu, Instr *instr) {
  instr->dump();
  if (cpu->REG_FILE[instr->m_rs1] >= cpu->REG_FILE[instr->m_rs2])
    cpu->NEXT_PC = instr->m_imm;
}
void do_blt(CPU *cpu, Instr *instr) {
  instr->dump();
  if (cpu->REG_FILE[instr->m_rs1] < cpu->REG_FILE[instr->m_rs2])
    cpu->NEXT_PC = instr->m_imm;
}
void do_read(CPU *cpu, Instr *instr) {
  instr->dump();
  outs() << "[x" << (uint32_t) instr->m_rs1 << "] = ";
  std::cin >> cpu->REG_FILE[instr->m_rs1];
}
void do_write(CPU *cpu, Instr *instr) {
  instr->dump();
  outs() << "[x" << (uint32_t) instr->m_rs1
         << "] = " << cpu->REG_FILE[instr->m_rs1] << '\n';
}

namespace asm_repr {

using RegId_t = uint8_t;
using Bits_t = uint8_t;

struct RegValue {
  RegId_t reg_id;
};

using Value = std::variant<uint8_t, uint16_t, uint32_t, uint64_t, int8_t, int16_t, int32_t, int64_t, RegValue>;

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
  if (bits == 8) {
    return (uint8_t) n;
  } else if (bits == 16) {
    return (uint16_t) n;
  } else if (bits == 32) {
    return (uint32_t) n;
  }
  return n;
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

struct Instruction {
  virtual void translateToIR(llvm::IRBuilder<>&) = 0;
  virtual ~Instruction() = default;
};

struct AddInstruction : Instruction {
  using AddInstructionPtr = std::unique_ptr<AddInstruction>;

  Bits_t bits;
  RegValue res_reg;
  RegValue arg1_reg;
  Value arg2;

  void translateToIR(llvm::IRBuilder<>& builder) override {
    
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
    return std::make_unique<AddInstruction>(AddInstruction{
        .bits = bits,
        .res_reg = RegValue{parseNumber<RegId_t>(res)},
        .arg1_reg = RegValue{parseNumber<RegId_t>(arg1)},
        .arg2 = parseNumberOrRegValue(arg2, bits)});
  }

  ~AddInstruction() = default;
};

struct MovInstruction : Instruction {
  Bits_t bits;
  RegValue res_reg;
  Value arg1;

  static MovInstruction parse(std::string_view &in) {
    in = removeSpaces(in);
    auto bits_sv = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto res = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto arg1 = consumeUntilWhitespace(in);
    auto bits = parseNumber<Bits_t>(bits_sv);
    return {
        .bits = bits,
        .res_reg = RegValue{parseNumber<RegId_t>(res)},
        .arg1 = parseNumberOrRegValue(arg1, bits)};
  }
};

struct RetInstruction : Instruction {
  Bits_t bits;
  Value arg1;

  static RetInstruction parse(std::string_view &in) {
    in = removeSpaces(in);
    auto bits_sv = consumeUntilWhitespace(in);
    in = removeSpaces(in);
    auto arg1 = consumeUntilWhitespace(in);
    auto bits = parseNumber<Bits_t>(bits_sv);
    return {
        .bits = bits,
        .arg1 = parseNumberOrRegValue(arg1, bits)};
  }
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
        bb->instrs.push_back(std::make_unique<AddInstruction>(AddInstruction::parse(in)));
      } else if (label == "mov") {
        bb->instrs.push_back(std::make_unique<MovInstruction>(MovInstruction::parse(in)));
      } else if (label == "ret") {
        bb->instrs.push_back(std::make_unique<RetInstruction>(RetInstruction::parse(in)));
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
