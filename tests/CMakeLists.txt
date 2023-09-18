cmake_minimum_required(VERSION 3.16)

set(target_name "CppReflectionTests")

file(GLOB_RECURSE target_headers "*.hpp")
file(GLOB_RECURSE target_sources "*.cpp")

add_executable(${target_name} ${target_headers} ${target_sources})
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_link_libraries(${target_name} gtest gtest_main CppReflection)

enable_testing()
add_test(NAME ${target_name}
    COMMAND ${target_name})
