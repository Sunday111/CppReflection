#include <iostream>
#include <string>
#include <string_view>

#include "gtest/gtest.h"

#include "CppReflection/TypeReflector.h"
#include "CppReflection/PrimitiveTypeReflection.h"
#include "CppReflection/CallReflectedFunction.h"
#include "CppReflection/Detail/TypeRegistryImpl.h"

TEST(CppReflectionTest, ComparisonOperators_LessOperator) {
    class ReflectedType
    {
    public:
        bool operator<(const ReflectedType& b) const {
            return member < b.member;
        }

        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_comparison_operators::less_operator::ReflectedType");
        }

        int member = 1024;
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->comparisonOperators.less != nullptr);

    ReflectedType a;
    a.member = 10;

    ReflectedType b;
    a.member = 20;

    EXPECT_TRUE(type->comparisonOperators.less(&a, &b));
    EXPECT_TRUE(!type->comparisonOperators.less(&a, &a));
    EXPECT_TRUE(!type->comparisonOperators.less(&b, &a));
}

TEST(CppReflectionTest, ComparisonOperators_EqualsOperator) {
    class ReflectedType
    {
    public:
        bool operator==(const ReflectedType& b) const {
            return member == b.member;
        }

        static void ReflectType(cppreflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_comparison_operators::equals_operator::ReflectedType");
        }

        int member = 1024;
    };

    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->comparisonOperators.equals != nullptr);

    ReflectedType a;
    a.member = 10;

    ReflectedType b;
    a.member = 20;

    EXPECT_TRUE(!type->comparisonOperators.equals(&a, &b));
    EXPECT_TRUE(!type->comparisonOperators.equals(&b, &a));
    EXPECT_TRUE(type->comparisonOperators.equals(&a, &a));
    EXPECT_TRUE(type->comparisonOperators.equals(&b, &b));
}

class ReflectedType_NoCompare
{
public:
    static void ReflectType(cppreflection::TypeReflector<ReflectedType_NoCompare>& rt) {
        rt.SetName("test_comparison_operators::ReflectedType_NoCompare");
    }
};

TEST(CppReflectionTest, ComparisonOperators_NoLessOperator) {
    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType_NoCompare>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->comparisonOperators.less == nullptr);
}

TEST(CppReflectionTest, ComparisonOperators_NoEqualsOperator) {
    const cppreflection::Type* type = cppreflection::GetTypeInfo<ReflectedType_NoCompare>();
    EXPECT_TRUE(type != nullptr);
    EXPECT_TRUE(type->comparisonOperators.equals == nullptr);
}