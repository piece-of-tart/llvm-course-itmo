
if (LLVM_COURSE_ITMO_USE_CONAN)
    find_package(SFML 3.0 COMPONENTS system window graphics REQUIRED)
else ()
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif ()
