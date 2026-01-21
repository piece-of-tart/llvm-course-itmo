
message(STATUS "LLVM_DIR = ${LLVM_DIR}")
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND "${LLVM_DEFINITIONS}")

add_executable(ir_generator ir_generator.cpp)
target_include_directories(ir_generator PRIVATE ${LLVM_INCLUDE_DIRS})
target_compile_options(ir_generator PRIVATE ${LLVM_DEFINITIONS_LIST})
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
target_link_libraries(ir_generator PRIVATE sim ${LLVM_LIBS})