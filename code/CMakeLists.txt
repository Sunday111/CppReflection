cmake_minimum_required(VERSION 3.16)

include(generic_compile_options)
set(target_name CppReflection)

option(CPP_REFLECTION_SHARED "Enable if you want to use it as shared library" OFF)

file(GLOB_RECURSE target_headers "*.hpp")
file(GLOB_RECURSE target_sources "*.cpp")

if (CPP_REFLECTION_SHARED)
    add_library(${target_name} SHARED ${target_headers} ${target_sources})
else()
    add_library(${target_name} STATIC ${target_headers} ${target_sources})
    target_compile_definitions(${target_name} PRIVATE -DCPP_REFLECTION_SHARED -DINSIDE_CPP_REFLECION_LIB)
endif()

target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target_name} PUBLIC EverydayTools)
