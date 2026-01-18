include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

include(AddLLVM)

add_llvm_pass_plugin(instruction_pass instruction_pass.cpp)
