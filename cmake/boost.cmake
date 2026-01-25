

if (LLVM_COURSE_ITMO_USE_CONAN)
    find_package(Boost 1.89.0 REQUIRED)
else ()
    set(BOOST_ENABLE_CMAKE ON)
    include(FetchContent)
    FetchContent_Declare(
      Boost
      GIT_REPOSITORY https://github.com/boostorg/boost.git
      GIT_TAG boost-1.89.0
    )
    FetchContent_MakeAvailable(Boost)
endif ()
