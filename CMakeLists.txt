cmake_minimum_required(VERSION 3.31.0)
project(LLVM_COURSE_2025)

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Clang/LLVM compiler is required")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(sfml)
find_package(LLVM 21.1 REQUIRED)

add_subdirectory(src)
