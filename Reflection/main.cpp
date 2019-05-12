#include <iostream>
#include <string>
#include <string_view>

#include "TypeReflector.h"
#include "PrimitiveTypeReflection.h"
#include "CallReflectedFunction.h"
#include "Detail/TypeRegistryImpl.h"

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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_void::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        edt::reflection::CallMethod<void>(functionInfo, object);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_int::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<int>());

        ReflectedType object;
        int arg;
        edt::reflection::CallMethod<void>(functionInfo, object, arg);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_int_ptr::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<int*>());

        ReflectedType object;
        int arg;
        int* pArg = &arg;
        edt::reflection::CallMethod<void>(functionInfo, object, pArg);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_int_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<int&>());

        ReflectedType object;
        int arg;
        edt::reflection::CallMethod<void>(functionInfo, object, arg);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_int_ptr_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<int*&>());

        ReflectedType object;
        int* arg = nullptr;
        edt::reflection::CallMethod<void>(functionInfo, object, arg);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_void::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<MovableType&&>());

        MovableType arg;
        arg.values.resize(10);

        ReflectedType object;
        edt::reflection::CallMethod<void>(functionInfo, object, arg);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_int::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        int returnValue = edt::reflection::CallMethod<int>(functionInfo, object);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_int_ptr::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int*>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        int* returnValue = edt::reflection::CallMethod<int*>(functionInfo, object);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_int_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int&>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        int& returnValue = edt::reflection::CallMethod<int&>(functionInfo, object);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_int_ptr_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int*&>());
        assert(functionInfo->GetArgumentsCount() == 0);

        ReflectedType object;
        int*& returnValue = edt::reflection::CallMethod<int*&>(functionInfo, object);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_rvalue::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
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
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_method_ret_void_arg_same_type_ref::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 1);
        const edt::reflection::Function* functionInfo = typeInfo->GetMethod(0);
        assert(functionInfo != nullptr);
        assert(functionInfo->GetName() == "f1"sv);
        assert(functionInfo->GetObjectType() == typeInfo);
        assert(functionInfo->GetReturnType() == nullptr);
        assert(functionInfo->GetArgumentsCount() == 1);
        assert(functionInfo->GetArgumentType(0) == edt::reflection::GetTypeInfo<ReflectedType&>());

        ReflectedType object;
        ReflectedType arg{ 11 };
        edt::reflection::CallMethod<void>(functionInfo, object, arg);
        assert(arg.member == 11 * 12);
    }
}

namespace test_function_ret_void_arg_void
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

        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
            rt.SetName("test_function_ret_void_arg_void::ReflectedType");
            rt.AddMethod<&ReflectedType::f1>("f1");
            rt.AddMethod<&ReflectedType::f2>("f2");
            rt.AddMethod<&ReflectedType::f3>("f3");
            rt.AddMethod<&ReflectedType::f4>("f4");
        }

        static int k;
    };

    int ReflectedType::k = 10;

    void test() {
        using namespace std::literals;
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_function_ret_void_arg_void::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetMethodsCount() == 4);

        {
            const edt::reflection::Function* f = typeInfo->GetMethod(0);
            assert(f != nullptr);
            assert(f->GetName() == "f1"sv);
            assert(f->GetObjectType() == nullptr);
            assert(f->GetReturnType() == nullptr);
            assert(f->GetArgumentsCount() == 0);
            edt::reflection::CallFunction<void>(f);
            assert(ReflectedType::k == 11);
        }

        {
            const edt::reflection::Function* f = typeInfo->GetMethod(1);
            assert(f != nullptr);
            assert(f->GetName() == "f2"sv);
            assert(f->GetObjectType() == nullptr);
            assert(f->GetReturnType() == nullptr);
            assert(f->GetArgumentsCount() == 1);
            assert(f->GetArgumentType(0) == edt::reflection::GetTypeInfo<int>());
            edt::reflection::CallFunction<void>(f, 2);
            assert(ReflectedType::k == 13);
        }

        {
            const edt::reflection::Function* f = typeInfo->GetMethod(2);
            assert(f != nullptr);
            assert(f->GetName() == "f3"sv);
            assert(f->GetObjectType() == nullptr);
            assert(f->GetReturnType() == nullptr);
            assert(f->GetArgumentsCount() == 1);
            assert(f->GetArgumentType(0) == edt::reflection::GetTypeInfo<int*>());
            int arg = 3;
            edt::reflection::CallFunction<void>(f, &arg);
            assert(arg == 114);
        }

        {
            const edt::reflection::Function* f = typeInfo->GetMethod(3);
            assert(f != nullptr);
            assert(f->GetName() == "f4"sv);
            assert(f->GetObjectType() == nullptr);
            assert(f->GetReturnType() == nullptr);
            assert(f->GetArgumentsCount() == 1);
            assert(f->GetArgumentType(0) == edt::reflection::GetTypeInfo<int&>());
            int arg = 3;
            edt::reflection::CallFunction<void>(f, arg);
            assert(arg == 115);
        }
    }
}

namespace test_fields
{
    class ReflectedType
    {
    public:
        static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
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

    void test() {
        using namespace std::literals;
        const edt::reflection::Type* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
        assert(typeInfo != nullptr);
        assert(typeInfo->GetName() == "test_field_value::ReflectedType"sv);
        assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
        assert(typeInfo->GetFieldsCount() == 4);

        ReflectedType instance(100);
        // Reflected int
        {
            auto f = typeInfo->GetField(0);
            assert(f != nullptr);
            assert(f->GetName() == "m_int"sv);
            assert(f->GetType() == edt::reflection::GetTypeInfo<int>());
            assert(f->GetValue(&instance) == &instance.m_int);
        }

        // Reflected int*
        {
            auto f = typeInfo->GetField(1);
            assert(f != nullptr);
            assert(f->GetName() == "m_int_ptr"sv);
            assert(f->GetType() == edt::reflection::GetTypeInfo<int*>());
            assert(f->GetValue(&instance) == &instance.m_int_ptr);
        }

        // Reflected static int
        {
            auto f = typeInfo->GetField(2);
            assert(f != nullptr);
            assert(f->GetName() == "ms_int"sv);
            assert(f->GetType() == edt::reflection::GetTypeInfo<int>());
            assert(f->GetValue(nullptr) == &instance.ms_int);
        }

        // Reflected static int*
        {
            auto f = typeInfo->GetField(3);
            assert(f != nullptr);
            assert(f->GetName() == "ms_int_ptr"sv);
            assert(f->GetType() == edt::reflection::GetTypeInfo<int*>());
            assert(f->GetValue(nullptr) == &instance.ms_int_ptr);
        }
    }
}

namespace test_special_members
{
    namespace default_constructor
    {
        class ReflectedType
        {
        public:
            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_special_members::default_constructor::ReflectedType");
            }

            ReflectedType()
                : member(124)
            {}

            int member = 112;
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->specialMembers.defaultConstructor != nullptr);

            std::aligned_storage_t<sizeof(ReflectedType), alignof(ReflectedType)> data;
            ReflectedType* pointer = reinterpret_cast<ReflectedType*>(&data);
            type->specialMembers.defaultConstructor(pointer);
            assert(pointer->member == 124);
        }
    }

    namespace no_default_constructor
    {
        class ReflectedType
        {
        public:
            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_special_members::no_default_constructor::ReflectedType");
            }

            ReflectedType(int) {}
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->specialMembers.defaultConstructor == nullptr);
        }
    }

    namespace copy_assign
    {
        class ReflectedType
        {
        public:
            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_special_members::copy_assign::ReflectedType");
            }

            ReflectedType& operator=(const ReflectedType& another) {
                member = another.member;
                return *this;
            }

            std::vector<int> member;
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->specialMembers.copyAssign != nullptr);

            ReflectedType a, b;
            std::vector<int> member{ 1, 2, 3 };
            b.member = member;
            type->specialMembers.copyAssign(&a, &b);
            assert(b.member == member);
            assert(a.member == member);
        }
    }

    namespace no_copy_assign
    {
        class ReflectedType
        {
        public:
            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_special_members::no_copy_assign::ReflectedType");
            }

            ReflectedType& operator=(const ReflectedType& another) = delete;
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->specialMembers.copyAssign == nullptr);
        }
    }

    namespace move_assign
    {
        class ReflectedType
        {
        public:
            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_special_members::move_assign::ReflectedType");
            }

            ReflectedType& operator=(ReflectedType&& another) {
                member = std::move(another.member);
                return *this;
            }

            std::vector<int> member;
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->specialMembers.moveAssign != nullptr);

            ReflectedType a, b;
            std::vector<int> member{ 1, 2, 3 };
            b.member = member;
            type->specialMembers.moveAssign(&a, &b);
            assert(b.member.empty());
            assert(a.member == member);
        }
    }

    namespace no_move_assign
    {
        class ReflectedType
        {
        public:
            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_special_members::no_move_assign::ReflectedType");
            }

            ReflectedType& operator=(ReflectedType&& another) = delete;
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->specialMembers.moveAssign == nullptr);
        }
    }

    namespace destructor
    {
        class ReflectedType
        {
        public:
            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_special_members::destructor::ReflectedType");
            }

            ~ReflectedType() {
                member = 2048;
            }

            int member = 1024;
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->specialMembers.defaultConstructor != nullptr);
            assert(type->specialMembers.destructor != nullptr);

            std::aligned_storage_t<sizeof(ReflectedType), alignof(ReflectedType)> data;
            ReflectedType* pointer = reinterpret_cast<ReflectedType*>(&data);
            type->specialMembers.defaultConstructor(pointer);
            assert(pointer->member == 1024);
            type->specialMembers.destructor(pointer);
            assert(pointer->member == 2048);
        }
    }
}

namespace test_comparison_operators {
    namespace less_operator {
        class ReflectedType
        {
        public:
            friend bool operator<(const ReflectedType& a, const ReflectedType& b) {
                return a.member < b.member;
            }

            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_comparison_operators::less_operator::ReflectedType");
            }

            int member = 1024;
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->comparisonOperators.less != nullptr);

            ReflectedType a;
            a.member = 10;

            ReflectedType b;
            a.member = 20;

            assert(type->comparisonOperators.less(&a, &b));
            assert(!type->comparisonOperators.less(&a, &a));
            assert(!type->comparisonOperators.less(&b, &a));
        }
    }

    namespace equals_operator {
        class ReflectedType
        {
        public:
            friend bool operator==(const ReflectedType& a, const ReflectedType& b) {
                return a.member == b.member;
            }

            static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
                rt.SetName("test_comparison_operators::equals_operator::ReflectedType");
            }

            int member = 1024;
        };

        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType>();
            assert(type != nullptr);
            assert(type->comparisonOperators.equals != nullptr);

            ReflectedType a;
            a.member = 10;

            ReflectedType b;
            a.member = 20;

            assert(!type->comparisonOperators.equals(&a, &b));
            assert(!type->comparisonOperators.equals(&b, &a));
            assert(type->comparisonOperators.equals(&a, &a));
            assert(type->comparisonOperators.equals(&b, &b));
        }
    }

    class ReflectedType_NoCompare
    {
    public:
        static void ReflectType(edt::reflection::TypeReflector<ReflectedType_NoCompare>& rt) {
            rt.SetName("test_comparison_operators::ReflectedType_NoCompare");
        }
    };

    namespace no_less_operator {
        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType_NoCompare>();
            assert(type != nullptr);
            assert(type->comparisonOperators.less == nullptr);
        }
    }

    namespace no_equals_operator {
        void test() {
            const edt::reflection::Type* type = edt::reflection::GetTypeInfo<ReflectedType_NoCompare>();
            assert(type != nullptr);
            assert(type->comparisonOperators.equals == nullptr);
        }
    }
}

void PrintType(const edt::reflection::Type* typeInfo, std::ostream& output) {
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

class Foo
{
public:
    bool operator==(const Foo& b) const {
        return ll == b.ll;
    }

    int ll;
};

constexpr bool TypeHasEqOp(...) {
    return false;
}

template<typename T>
constexpr auto TypeHasEqOp(const T* ptr) ->
    decltype((
        *ptr == *ptr
        , true))
{
    return true;
}

template<typename T>
using CompareOp = bool(*)(const T& a, const T& b);

template<typename T>
constexpr CompareOp<T> GetCompareOperator() {
    constexpr const T* const pppp = nullptr;
    if constexpr (TypeHasEqOp(pppp)) {
        return [](const T& a, const T& b) {
            return a == b;
        };
    }
    else {
        return nullptr;
    }
}

int main() {
    Foo f1{ 1 }, f2{ 2 };
    constexpr auto op = GetCompareOperator<Foo>();
    if constexpr (op) {
        op(f1, f2);
    }

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
    test_fields::test();
    test_special_members::default_constructor::test();
    test_special_members::no_default_constructor::test();
    test_special_members::copy_assign::test();
    test_special_members::no_copy_assign::test();
    test_special_members::move_assign::test();
    test_special_members::no_move_assign::test();
    test_special_members::destructor::test();
    test_comparison_operators::less_operator::test();
    test_comparison_operators::no_less_operator::test();
    test_comparison_operators::equals_operator::test();
    test_comparison_operators::no_equals_operator::test();

    PrintReflectedTypes(edt::reflection::detail::TypeRegistryImpl::Instance(), std::cout);

    return 0;
}
