#include <iostream>
#include <string>
#include <string_view>

#include "gtest/gtest.h"

#include "CppReflection/CallReflectedFunction.h"
#include "CppReflection/PrimitiveTypeReflection.h"
#include "CppReflection/Reflector/TypeReflector.h"

namespace FunctionReturnsVoidArgumentVoid_nm
{
    class ReflectedType
    {
    public:
        static void f1() {
            ++k;
        }

        static void f2(int arg) {
            k += arg;
        }

        static void f3(int* arg) {
            *arg = 114;
        }

        static void f4(int& arg) {
            arg = 115;
        }

        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_function_ret_void_arg_void::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
            rt.AddMethod<&ReflectedType::f2>("f2");
            rt.AddMethod<&ReflectedType::f3>("f3");
            rt.AddMethod<&ReflectedType::f4>("f4");
        }

        static int k;
    };

    int ReflectedType::k = 10;
}

TEST(CppReflectionTest, StaticMethod) {
    using namespace std::literals;
    using namespace FunctionReturnsVoidArgumentVoid_nm;
    const cppreflection::Type* typeInfo = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(typeInfo != nullptr);
    EXPECT_TRUE(typeInfo->GetName() == "test_function_ret_void_arg_void::ReflectedType"sv);
    EXPECT_TRUE(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
    EXPECT_TRUE(typeInfo->GetMethodsCount() == 4);

    {
        const cppreflection::Function* f = typeInfo->GetMethod(0);
        EXPECT_TRUE(f != nullptr);
        EXPECT_TRUE(f->GetName() == "f1"sv);
        EXPECT_TRUE(f->GetObjectType() == nullptr);
        EXPECT_TRUE(f->GetReturnType() == nullptr);
        EXPECT_TRUE(f->GetArgumentsCount() == 0);
        cppreflection::CallFunction<void>(f);
        EXPECT_TRUE(ReflectedType::k == 11);
    }

    {
        const cppreflection::Function* f = typeInfo->GetMethod(1);
        EXPECT_TRUE(f != nullptr);
        EXPECT_TRUE(f->GetName() == "f2"sv);
        EXPECT_TRUE(f->GetObjectType() == nullptr);
        EXPECT_TRUE(f->GetReturnType() == nullptr);
        EXPECT_TRUE(f->GetArgumentsCount() == 1);
        EXPECT_TRUE(f->GetArgumentType(0) == cppreflection::GetTypeInfo<int>());
        cppreflection::CallFunction<void>(f, 2);
        EXPECT_TRUE(ReflectedType::k == 13);
    }

    {
        const cppreflection::Function* f = typeInfo->GetMethod(2);
        EXPECT_TRUE(f != nullptr);
        EXPECT_TRUE(f->GetName() == "f3"sv);
        EXPECT_TRUE(f->GetObjectType() == nullptr);
        EXPECT_TRUE(f->GetReturnType() == nullptr);
        EXPECT_TRUE(f->GetArgumentsCount() == 1);
        EXPECT_TRUE(f->GetArgumentType(0) == cppreflection::GetTypeInfo<int*>());
        int arg = 3;
        cppreflection::CallFunction<void>(f, &arg);
        EXPECT_TRUE(arg == 114);
    }

    {
        const cppreflection::Function* f = typeInfo->GetMethod(3);
        EXPECT_TRUE(f != nullptr);
        EXPECT_TRUE(f->GetName() == "f4"sv);
        EXPECT_TRUE(f->GetObjectType() == nullptr);
        EXPECT_TRUE(f->GetReturnType() == nullptr);
        EXPECT_TRUE(f->GetArgumentsCount() == 1);
        EXPECT_TRUE(f->GetArgumentType(0) == cppreflection::GetTypeInfo<int&>());
        int arg = 3;
        cppreflection::CallFunction<void>(f, arg);
        EXPECT_TRUE(arg == 115);
    }
}