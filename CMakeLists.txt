cmake_minimum_required(VERSION 3.20)

project(CppReflection)
add_subdirectory(code)

option(CPP_REFLECTION_WITH_TESTS "Enable if you want to build tests" OFF)

if (CPP_REFLECTION_WITH_TESTS)
    add_subdirectory(tests)
endif()
