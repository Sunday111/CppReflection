cmake_minimum_required(VERSION 3.16)

find_package(GTest REQUIRED)

set(target_name "CppReflectionTests")
set(target)

set(target_sources
    "ComparisonOperators.cpp"
    "Fields.cpp"
    "Methods.cpp"
    "SpecialMembers.cpp"
    "StaticMethods.cpp"
    "TypeGUID.cpp"
    "util.cpp"
)

add_executable(${target_name} ${target_sources})
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_include_directories(${target_name} PRIVATE ${gtest_SOURCE_DIR}/include)
target_include_directories(${target_name} PRIVATE ${gtest_SOURCE_DIR})
target_link_libraries(${target_name} gtest gtest_main ${target_name})

enable_testing()
add_test(NAME    ${target_name_tests}
         COMMAND ${target_name_tests})