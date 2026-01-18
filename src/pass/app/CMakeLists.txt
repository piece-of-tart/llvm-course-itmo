set(APP_SRCS
  ${PATH_TO_APP_SOURCE}/app.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/log.c
)

add_library(sim STATIC ${PATH_TO_APP_SOURCE}/sim.cpp )
target_link_libraries(sim PUBLIC SFML::System SFML::Window SFML::Graphics)

set(PASS_STAMP "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/instruction_pass.stamp")

add_custom_command(
  OUTPUT  "${PASS_STAMP}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}"
  COMMAND ${CMAKE_COMMAND} -E touch "${PASS_STAMP}"
  DEPENDS instruction_pass
  VERBATIM
)
add_custom_target(instruction_pass_ready DEPENDS "${PASS_STAMP}")

foreach(src IN LISTS APP_SRCS)
  set_source_files_properties(${src} PROPERTIES OBJECT_DEPENDS "${PASS_STAMP}")
endforeach()

foreach(OL IN ITEMS 0 1 2 3)
  set(TGT app_O${OL})
  add_library(${TGT} STATIC ${APP_SRCS} )
  target_link_libraries(${TGT} PUBLIC sim)  

  add_dependencies(${TGT} instruction_pass_ready)

  target_compile_options(${TGT} PRIVATE
    -O${OL}
    "-fpass-plugin=$<TARGET_FILE:instruction_pass>"
  )
  set(MAIN_TGT main_O${OL})
  add_executable(${MAIN_TGT} ${PATH_TO_APP_SOURCE}/main.cpp)
  target_link_libraries(${MAIN_TGT} PRIVATE ${TGT})
endforeach()

add_custom_target(app_all DEPENDS app_O0 app_O1 app_O2 app_O3)

