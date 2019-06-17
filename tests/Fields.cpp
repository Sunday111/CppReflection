#include <iostream>
#include <string>
#include <string_view>

#include "gtest/gtest.h"

#include "CppReflection/TypeReflector.h"
#include "CppReflection/PrimitiveTypeReflection.h"
#include "CppReflection/CallReflectedFunction.h"
#include "CppReflection/Detail/TypeRegistryImpl.h"

namespace CppReflectionTest_Fields
{
    class ReflectedType
    {
    public:
        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_field_value::ReflectedType");
            rt.AddField<&ReflectedType::m_int>("m_int");
            rt.AddField<&ReflectedType::m_int_ptr>("m_int_ptr");
            rt.AddField<&ReflectedType::ms_int>("ms_int");
            rt.AddField<&ReflectedType::ms_int_ptr>("ms_int_ptr");
        }

        ReflectedType(int value)
            : m_int(value)
            , m_int_ptr(&m_int)
        {
        }

        int m_int;
        int* m_int_ptr;

        static int ms_int;
        static int* ms_int_ptr;
        static int& ms_int_ref;
    };

    int ReflectedType::ms_int = 12;
    int* ReflectedType::ms_int_ptr = &ReflectedType::ms_int;
}

TEST(CppReflectionTest, Fields) {
    using namespace std::literals;
    using namespace CppReflectionTest_Fields;
    const cppreflection::Type* typeInfo = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(typeInfo != nullptr);
    EXPECT_TRUE(typeInfo->GetName() == "test_field_value::ReflectedType"sv);
    EXPECT_TRUE(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
    EXPECT_TRUE(typeInfo->GetFieldsCount() == 4);

    ReflectedType instance(100);
    // Reflected int
    {
        auto f = typeInfo->GetField(0);
        EXPECT_TRUE(f != nullptr);
        EXPECT_TRUE(f->GetName() == "m_int"sv);
        EXPECT_TRUE(f->GetType() == cppreflection::GetTypeInfo<int>());
        EXPECT_TRUE(f->GetValue(&instance) == &instance.m_int);
    }

    // Reflected int*
    {
        auto f = typeInfo->GetField(1);
        EXPECT_TRUE(f != nullptr);
        EXPECT_TRUE(f->GetName() == "m_int_ptr"sv);
        EXPECT_TRUE(f->GetType() == cppreflection::GetTypeInfo<int*>());
        EXPECT_TRUE(f->GetValue(&instance) == &instance.m_int_ptr);
    }

    // Reflected static int
    {
        auto f = typeInfo->GetField(2);
        EXPECT_TRUE(f != nullptr);
        EXPECT_TRUE(f->GetName() == "ms_int"sv);
        EXPECT_TRUE(f->GetType() == cppreflection::GetTypeInfo<int>());
        EXPECT_TRUE(f->GetValue(nullptr) == &instance.ms_int);
    }

    // Reflected static int*
    {
        auto f = typeInfo->GetField(3);
        EXPECT_TRUE(f != nullptr);
        EXPECT_TRUE(f->GetName() == "ms_int_ptr"sv);
        EXPECT_TRUE(f->GetType() == cppreflection::GetTypeInfo<int*>());
        EXPECT_TRUE(f->GetValue(nullptr) == &instance.ms_int_ptr);
    }
}