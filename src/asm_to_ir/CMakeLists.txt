separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND "${LLVM_DEFINITIONS}")
add_executable(asm_to_ir asm_to_ir.cpp)
target_include_directories(asm_to_ir PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_options(asm_to_ir PRIVATE ${LLVM_DEFINITIONS_LIST})
include(AddLLVM)
llvm_map_components_to_libnames(LLVM_LIBS
  Core
  Support
  IRReader
  Passes
  ExecutionEngine
  native
  X86
  Interpreter
)
target_link_libraries(asm_to_ir PRIVATE sim ${LLVM_LIBS} Boost::headers)