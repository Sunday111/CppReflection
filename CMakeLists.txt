cmake_minimum_required(VERSION 3.5.1)

include(generate_vs_filters)
include(glob_cxx_sources)
include(cxx_version)

set(target_name CppReflection)
set(target_root ${CMAKE_CURRENT_SOURCE_DIR}/code)
set(${target_name} true CACHE BOOL "Reflection for c++ types")
if(NOT ${${target_name}})
    return()
endif()
glob_cxx_sources(${target_root} target_sources)
add_library(${target_name} SHARED ${target_sources})
target_include_directories(${target_name} PUBLIC ${target_root}/include)
target_include_directories(${target_name} PRIVATE ${target_root})
target_link_libraries(${target_name} PUBLIC EverydayTools)
target_compile_definitions(${target_name} PRIVATE -D INSIDE_CPP_REFLECION_LIB)
require_cxx_version(${target_name} 17)
generate_vs_filters(${target_sources})

# tests
set(target_name_tests "${target_name}Tests")
# enable tests by default
set(${target_name_tests} true CACHE BOOL "Tests for ${target_name} target")
# check that user needs tests
if(NOT ${${target_name_tests}})
    return()
endif()

glob_cxx_sources(${CMAKE_CURRENT_SOURCE_DIR}/tests target_sources_tests)
add_executable(${target_name_tests} ${target_sources_tests})
generate_vs_filters(${target_sources_tests})
require_cxx_version(${target_name_tests} 17)
disable_cxx_extensions(${target_name_tests})
add_dependencies(${target_name_tests} gtest)
target_link_libraries(${target_name_tests} gtest gtest_main ${target_name})
target_include_directories(${target_name_tests} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/tests)
target_include_directories(${target_name_tests} PRIVATE ${gtest_SOURCE_DIR}/include)
target_include_directories(${target_name_tests} PRIVATE ${gtest_SOURCE_DIR})
require_cxx_version(${target_name_tests} 17)
enable_testing()
add_test(NAME    ${target_name_tests}
         COMMAND ${target_name_tests})
