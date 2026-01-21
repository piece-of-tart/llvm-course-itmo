add_library(sim STATIC sim.cpp)
target_link_libraries(sim PUBLIC SFML::System SFML::Window SFML::Graphics)
target_include_directories(sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


add_library(game_of_life_app STATIC  app.cpp)
target_link_libraries(game_of_life_app PUBLIC sim)
target_compile_options(game_of_life_app PRIVATE -Wall -Wextra)

set(PATH_TO_APP_SOURCE ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

add_executable(game_of_live_main
  main.cpp
)
target_link_libraries(game_of_live_main PRIVATE game_of_life_app)


add_custom_target(app_llvm_ir
  COMMAND ${CMAKE_CXX_COMPILER} -O3 -S -emit-llvm -o ${CMAKE_BINARY_DIR}/app_ir.ll ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/app.cpp
  COMMENT "Generating LLVM IR for app.cpp"
)
