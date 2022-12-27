#include <iostream>
#include <string>
#include <string_view>

#include "gtest/gtest.h"

#include "CppReflection/CallReflectedFunction.hpp"
#include "CppReflection/PrimitiveTypeReflection.hpp"
#include "CppReflection/Reflector/TypeReflector.hpp"

TEST(CppReflectionTest, SpecialMembers_DefaultConstructor) {
    class ReflectedType
    {
    public:
        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_special_members::default_constructor::ReflectedType");
        }

        ReflectedType()
            : member(124)
        {}

        int member = 112;
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->GetSpecialMembers().defaultConstructor != nullptr);

    std::aligned_storage_t<sizeof(ReflectedType), alignof(ReflectedType)> data;
    ReflectedType* pointer = reinterpret_cast<ReflectedType*>(&data);
    type->GetSpecialMembers().defaultConstructor(pointer);
    EXPECT_TRUE(pointer->member == 124);
}

TEST(CppReflectionTest, SpecialMembers_NoDefaultConstructor) {
    class ReflectedType
    {
    public:
        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_special_members::no_default_constructor::ReflectedType");
        }

        ReflectedType(int) {}
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->GetSpecialMembers().defaultConstructor == nullptr);
}

TEST(CppReflectionTest, SpecialMembers_CopyAssign) {
    class ReflectedType
    {
    public:
        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_special_members::copy_assign::ReflectedType");
        }

        ReflectedType& operator=(const ReflectedType& another) {
            member = another.member;
            return *this;
        }

        std::vector<int> member;
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->GetSpecialMembers().copyAssign != nullptr);

    ReflectedType a, b;
    std::vector<int> member{ 1, 2, 3 };
    b.member = member;
    type->GetSpecialMembers().copyAssign(&a, &b);
    EXPECT_TRUE(b.member == member);
    EXPECT_TRUE(a.member == member);
}

TEST(CppReflectionTest, SpecialMembers_NoCopyAssign) {
    class ReflectedType
    {
    public:
        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_special_members::no_copy_assign::ReflectedType");
        }

        ReflectedType& operator=(const ReflectedType& another) = delete;
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->GetSpecialMembers().copyAssign == nullptr);
}

TEST(CppReflectionTest, SpecialMembers_MoveAssign) {
    class ReflectedType
    {
    public:
        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_special_members::move_assign::ReflectedType");
        }

        ReflectedType& operator=(ReflectedType&& another) {
            member = std::move(another.member);
            return *this;
        }

        std::vector<int> member;
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->GetSpecialMembers().moveAssign != nullptr);

    ReflectedType a, b;
    std::vector<int> member{ 1, 2, 3 };
    b.member = member;
    type->GetSpecialMembers().moveAssign(&a, &b);
    EXPECT_TRUE(b.member.empty());
    EXPECT_TRUE(a.member == member);
}

TEST(CppReflectionTest, SpecialMembers_NoMoveAssign) {
    class ReflectedType
    {
    public:
        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_special_members::no_move_assign::ReflectedType");
        }

        ReflectedType& operator=(ReflectedType&& another) = delete;
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->GetSpecialMembers().moveAssign == nullptr);
}

TEST(CppReflectionTest, SpecialMembers_Destructor) {
    class ReflectedType
    {
    public:
        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_special_members::destructor::ReflectedType");
        }

        ~ReflectedType() {
            member = 2048;
        }

        int member = 1024;
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->GetSpecialMembers().defaultConstructor != nullptr);
    EXPECT_TRUE(type->GetSpecialMembers().destructor != nullptr);

    std::aligned_storage_t<sizeof(ReflectedType), alignof(ReflectedType)> data;
    ReflectedType* pointer = reinterpret_cast<ReflectedType*>(&data);
    type->GetSpecialMembers().defaultConstructor(pointer);
    EXPECT_TRUE(pointer->member == 1024);
    type->GetSpecialMembers().destructor(pointer);
    EXPECT_TRUE(pointer->member == 2048);
}