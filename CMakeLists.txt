cmake_minimum_required(VERSION 3.31.0)
project(game_of_life_llvm)

if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(FATAL_ERROR "Clang/LLVM compiler is required")
endif()

set(CMAKE_CXX_STANDARD 23)

set(MAIN_TARGET ${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_library(game_of_life_app STATIC src/app/sim.cpp src/app/app.cpp)
target_link_libraries(game_of_life_app PUBLIC SFML::System SFML::Window SFML::Graphics)
target_compile_options(game_of_life_app PRIVATE -Wall -Wextra)

add_executable(game_of_live_main
  src/app/main.cpp
)
target_link_libraries(game_of_live_main PRIVATE game_of_life_app)


add_custom_target(app_llvm_ir
  COMMAND ${CMAKE_CXX_COMPILER} -O3 -S -emit-llvm -o ${CMAKE_BINARY_DIR}/app_ir.ll ${CMAKE_SOURCE_DIR}/src/app/app.cpp
  DEPENDS ${CMAKE_SOURCE_DIR}/src/app/app.cpp
  COMMENT "Generating LLVM IR for app.cpp"
)
