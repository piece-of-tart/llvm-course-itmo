#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <stack>

using RegId_t = uint8_t;
using RegVal_t = uint32_t;
using Stack_t = std::stack<RegVal_t>;

template<size_t REG_FILE_SIZE>
class CPU {
 public:
  std::array<RegVal_t, REG_FILE_SIZE> REG_FILE = {};
  RegVal_t pc{0};
  RegVal_t next_pc{0};
  Stack_t call_stack;
  Stack_t stack;
  uint32_t run{0};
  std::ostream &out; // NOLINT

public:
  bool isStackOk() {
    if (stack.empty()) {
      run = 0;
      out << "[RUNTIME ERROR] STACK ERROR\n";
      return false;
    }
    return true;
  }

  bool call_stack_ok() {
    if (stack.empty()) {
      run = 0;
      out << "[RUNTIME ERROR] CALL STACK ERROR\n";
      return false;
    }
    return true;
  }
};