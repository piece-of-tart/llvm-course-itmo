add_subdirectory(app)

if(NOT DEFINED PATH_TO_APP_SOURCE)
  message(FATAL_ERROR "app/ must set PATH_TO_APP_SOURCE (use set(... PARENT_SCOPE) in app/CMakeLists.txt)")
endif()


add_subdirectory(pass)
