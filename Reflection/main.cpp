#include <iostream>
#include <string>
#include <string_view>

#include "TypeReflector.h"
#include "GetTypeInfo.h"

#include "CallReflectedFunction.h"

#include "Detail/TypeRegistryImpl.h"

namespace edt::reflection
{
    void ReflectType(TypeReflector<int>& rt) {
        rt.SetName("int");
    }
}

namespace test_method_ret_void_arg_void
{
    class ReflectedType
    {
    public:
        void f1() {
            ++member;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_void_arg_void::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        int member = 0;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_void::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        edt::reflection::WrapReflectedMethodCall<void>(functionInfo, object);
        assert(object.member == 1);
    }
}

namespace test_method_ret_void_arg_int
{
    class ReflectedType
    {
    public:
        void f1(int) {

        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_void_arg_int::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_int::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<int>());

        ReflectedType object;
        int arg;
        edt::reflection::WrapReflectedMethodCall<void>(functionInfo, object, arg);
    }
}

namespace test_method_ret_void_arg_int_ptr
{
    class ReflectedType
    {
    public:
        void f1(int* arg) {
            *arg = member;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_void_arg_int_ptr::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        int member = 123;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_int_ptr::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<int*>());

        ReflectedType object;
        int arg;
        int* pArg = &arg;
        edt::reflection::WrapReflectedMethodCall<void>(functionInfo, object, pArg);
        assert(arg == object.member);
    }
}

namespace test_method_ret_void_arg_int_ref
{
    class ReflectedType
    {
    public:
        void f1(int& arg) {
            arg = 110;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_void_arg_int_ref::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_int_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<int&>());

        ReflectedType object;
        int arg;
        edt::reflection::WrapReflectedMethodCall<void>(functionInfo, object, arg);
        assert(arg == 110);
    }
}

namespace test_method_ret_void_arg_int_ptr_ref
{
    class ReflectedType
    {
    public:
        void f1(int*& arg) {
            arg = &member;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_void_arg_int_ptr_ref::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        int member = 111;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_int_ptr_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<int*&>());

        ReflectedType object;
        int* arg = nullptr;
        edt::reflection::WrapReflectedMethodCall<void>(functionInfo, object, arg);
        assert(arg == &object.member);
    }
}

namespace test_method_ret_void_arg_rvalue
{
    struct MovableType
    {
        static void ReflectType(edt::reflection::TypeReflector<MovableType>& rt) {
            rt.SetName("test_method_ret_void_arg_rvalue::MovableType");
        }

        std::vector<int> values;
    };

    class ReflectedType
    {
    public:
        void f1(MovableType&& object) {
            value = std::move(object);
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_void_arg_void::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        MovableType value;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_void::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<MovableType&&>());

        MovableType arg;
        arg.values.resize(10);

        ReflectedType object;
        edt::reflection::WrapReflectedMethodCall<void>(functionInfo, object, arg);
        assert(arg.values.empty());
        assert(object.value.values.size() == 10);
    }
}

namespace test_method_ret_int
{
    class ReflectedType
    {
    public:
        int f1() {
            return member;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_int::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        int member = 112;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_int::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        int returnValue = edt::reflection::WrapReflectedMethodCall<int>(functionInfo, object);
        assert(returnValue == object.member);
    }
}

namespace test_method_ret_int_ptr
{
    class ReflectedType
    {
    public:
        int* f1() {
            return &member;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_int_ptr::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        int member = 112;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_int_ptr::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int*>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        int* returnValue = edt::reflection::WrapReflectedMethodCall<int*>(functionInfo, object);
        assert(returnValue == &object.member);
    }
}

namespace test_method_ret_int_ref
{
    class ReflectedType
    {
    public:
        int& f1() {
            return member;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_int_ref::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        int member = 112;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_int_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int&>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        int& returnValue = edt::reflection::WrapReflectedMethodCall<int&>(functionInfo, object);
        assert(&returnValue == &object.member);
    }
}

namespace test_method_ret_int_ptr_ref
{
    class ReflectedType
    {
    public:
        ReflectedType() {
            pMember = &member;
        }

        int*& f1() {
            return pMember;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_int_ptr_ref::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        int* pMember = nullptr;
        int member = 112;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_int_ptr_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int*&>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        int*& returnValue = edt::reflection::WrapReflectedMethodCall<int*&>(functionInfo, object);
        assert(&returnValue == &object.pMember);
    }
}

namespace test_method_ret_rvalue
{
    struct MovableType
    {
        static void ReflectType(edt::reflection::TypeReflector<MovableType>& rt) {
            rt.SetName("test_method_ret_rvalue::MovableType");
        }

        MovableType() = default;
        MovableType(MovableType&& another) = default;
        MovableType(const MovableType&) = delete;

        ~MovableType() {
            assert(value.empty());
        }

        MovableType& operator=(MovableType&& another) = default;
        MovableType& operator=(const MovableType&) = delete;

        std::vector<int> value;
    };

    class ReflectedType
    {
    public:
        ReflectedType() {
            member.value.resize(10);
            std::cout << "ReflectedType() " << '\n';
        }

        MovableType&& f1() {
            return std::move(member);
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_rvalue::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        MovableType member;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_rvalue::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<MovableType&&>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        MovableType moved = edt::reflection::WrapReflectedFunctionReturnType<MovableType&&>(functionInfo, &object, nullptr, 0);
        assert(moved.value.size() == 10);
        moved.value.clear();
    }
}

namespace test_method_ret_void_arg_same_type_ref
{
    class ReflectedType
    {
    public:
        void f1(ReflectedType& arg) {
            arg.member *= member;
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_method_ret_void_arg_same_type_ref::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }

        int member = 12;
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_same_type_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<ReflectedType&>());

        ReflectedType object;
        ReflectedType arg{ 11 };
        edt::reflection::WrapReflectedMethodCall<void>(functionInfo, object, arg);
        assert(arg.member == 11 * 12);
    }
}

namespace test_function_ret_void_arg_void
{
    class ReflectedType
    {
    public:
        static void f1() {
        }

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_function_ret_void_arg_void::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
        }
    };

    void test() {
        using namespace std::literals;
        const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_function_ret_void_arg_void::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == nullptr);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 0);
    }
}

void PrintType(const edt::reflection::TypeInfo* typeInfo, std::ostream& output) {
    assert(typeInfo->GetName() != nullptr);
    output << typeInfo->GetName() << '\n';
    bool needNewLine = false;
    if (typeInfo->GetMethodsCount() > 0) {
        output << "   Methods:\n";
        const size_t methodsCount = typeInfo->GetMethodsCount();
        for (size_t methodIndex = 0; methodIndex < methodsCount; ++methodIndex) {
            auto methodInfo = typeInfo->GetMethod(methodIndex);
            output << "      ";

            if (auto objectType = methodInfo->GetObjectType(); objectType == nullptr) {
                output << "static ";
            }

            if (auto rv = methodInfo->GetReturnType()) {
                output << rv->GetName();
            }
            else {
                output << "void";
            }

            output << ' ' << methodInfo->GetName() << '(';
            const size_t methodArgsCount = methodInfo->GetArgumentsCount();
            for (size_t methodArgIndex = 0; methodArgIndex < methodArgsCount; ++methodArgIndex) {
                auto methodArgTypeInfo = methodInfo->GetArgumentType(methodArgIndex);
                output << methodArgTypeInfo->GetName();
                if (methodArgIndex < methodArgsCount - 1) {
                    output << ", ";
                }
            }
            output << ");\n";
        }
        needNewLine = true;
    }
    if (needNewLine) {
        output << '\n';
    }
}

void PrintReflectedTypes(const edt::reflection::TypeRegistry& registry, std::ostream& output) {
    for (size_t i = 0; i < registry.GetTypesCount(); ++i) {
        PrintType(registry.GetTypeInfo(i), output);
    }
}

int main() {
    test_method_ret_void_arg_void::test();
    test_method_ret_void_arg_int::test();
    test_method_ret_void_arg_int_ptr::test();
    test_method_ret_void_arg_int_ref::test();
    test_method_ret_void_arg_int_ptr_ref::test();
    test_method_ret_void_arg_rvalue::test();
    test_method_ret_int::test();
    test_method_ret_int_ptr::test();
    test_method_ret_int_ref::test();
    test_method_ret_int_ptr_ref::test();
    test_method_ret_rvalue::test();
    test_method_ret_void_arg_same_type_ref::test();
    test_function_ret_void_arg_void::test();

    PrintReflectedTypes(edt::reflection::detail::TypeRegistryImpl::Instance(), std::cout);

    return 0;
}
