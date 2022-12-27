cmake_minimum_required(VERSION 3.16)

set(target_name CppReflection)

option(CPP_REFLECTION_SHARED "Enable if you want to use it as shared library" OFF)

set(target_sources
    include/CppReflection/Detail/CallReflectType.h
    include/CppReflection/Detail/FieldTraits.h
    include/CppReflection/Detail/FunctionTraits.h
    include/CppReflection/Detail/HasOperator.h
    include/CppReflection/Detail/MakeTypeComparisonOperators.h
    include/CppReflection/Detail/MakeTypeSpecialMembers.h
    include/CppReflection/Reflector/FieldReflector.h
    include/CppReflection/Reflector/FunctionReflector.h
    include/CppReflection/Reflector/TypeReflector.h
    include/CppReflection/CallReflectedFunction.h
    include/CppReflection/Common.h
    include/CppReflection/Field.h
    include/CppReflection/Function.h
    include/CppReflection/GetTypeInfo.h
    include/CppReflection/PrimitiveTypeReflection.h
    include/CppReflection/Type.h
    include/CppReflection/TypeComparisonOperators.h
    include/CppReflection/TypeFlag.h
    include/CppReflection/TypeRegistry.h
    include/CppReflection/TypeSpecialMembers.h
    source/FieldImpl.h
    source/FieldImpl.cpp
    source/FunctionImpl.h
    source/FunctionImpl.cpp
    source/TypeImpl.h
    source/TypeImpl.cpp
    source/TypeRegistryImpl.h
    source/TypeRegistryImpl.cpp
)

if (CPP_REFLECTION_SHARED)
    add_library(${target_name} SHARED ${target_sources})
else()
    add_library(${target_name} STATIC ${target_sources})
    target_compile_definitions(${target_name} PRIVATE -DCPP_REFLECTION_SHARED -DINSIDE_CPP_REFLECION_LIB)
endif()

target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${target_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${target_name} PUBLIC EverydayTools)