cmake_minimum_required(VERSION 3.20)

project(CppReflection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(code)

option(CPP_REFLECTION_WITH_TESTS "Enable if you want to build tests" OFF)

if (CPP_REFLECTION_WITH_TESTS)
    add_subdirectory(tests)
endif()
