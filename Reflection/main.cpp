#include <iostream>
#include <string>
#include <string_view>

#include "TypeReflector.h"
#include "GetTypeInfo.h"

#include "Detail/TypeRegistryImpl.h"

namespace edt::reflection
{
	void ReflectType(TypeReflector<int>& rt) {
		rt.SetName("int");
	}
}

namespace test_function_return_void_argument_int
{
	class ReflectedType
	{
	public:
		void f1(int) {

		}

		static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
			rt.SetName("test_function_return_void_argument_int::ReflectedType");
			rt.AddMethod<&ReflectedType::f1>("f1");
		}
	};

	void test() {
		using namespace std::literals;
		const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
		assert(typeInfo != nullptr);
		assert(typeInfo->GetName() == "test_function_return_void_argument_int::ReflectedType"sv);
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
		void* argsArray[] = {&arg};
		functionInfo->Call(&object, nullptr, argsArray, 1);
	}
}

namespace test_function_return_void_argument_int_ref
{
	class ReflectedType
	{
	public:
		void f1(int& arg) {
			arg = 110;
		}

		static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
			rt.SetName("test_function_return_void_argument_int_ref::ReflectedType");
			rt.AddMethod<&ReflectedType::f1>("f1");
		}
	};

	void test() {
		using namespace std::literals;
		const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
		assert(typeInfo != nullptr);
		assert(typeInfo->GetName() == "test_function_return_void_argument_int_ref::ReflectedType"sv);
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
		void* argsArray[] = { &arg };
		functionInfo->Call(&object, nullptr, argsArray, 1);
		assert(arg == 110);
	}
}

namespace test_function_return_void_argument_int_pointer_ref
{
	class ReflectedType
	{
	public:
		void f1(int*& arg) {
			arg = &member;
		}

		static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
			rt.SetName("test_function_return_void_argument_int_pointer_ref::ReflectedType");
			rt.AddMethod<&ReflectedType::f1>("f1");
		}

		int member = 111;
	};

	void test() {
		using namespace std::literals;
		const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
		assert(typeInfo != nullptr);
		assert(typeInfo->GetName() == "test_function_return_void_argument_int_pointer_ref::ReflectedType"sv);
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
		void* argsArray[] = { &arg };
		functionInfo->Call(&object, nullptr, argsArray, 1);
		assert(arg == &object.member);
	}
}

namespace test_function_return_int
{
	class ReflectedType
	{
	public:
		int f1() {
			return member;
		}

		static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
			rt.SetName("test_function_return_int::ReflectedType");
			rt.AddMethod<&ReflectedType::f1>("f1");
		}

		int member = 112;
	};

	void test() {
		using namespace std::literals;
		const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
		assert(typeInfo != nullptr);
		assert(typeInfo->GetName() == "test_function_return_int::ReflectedType"sv);
		assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
		assert(typeInfo->GetMethodsCount() == 1);
		const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
		assert(functionInfo != nullptr);
		assert(functionInfo->GetName() == "f1"sv);
		assert(functionInfo->GetObjectType() == typeInfo);
		assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int>());
		assert(functionInfo->GetArgumentsCount() == 0);

		ReflectedType object;
		int returnValue = 111;
		functionInfo->Call(&object, &returnValue, nullptr, 0);
		assert(returnValue == object.member);
	}
}

namespace test_function_return_int_ptr
{
	class ReflectedType
	{
	public:
		int* f1() {
			return &member;
		}

		static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
			rt.SetName("test_function_return_int_ptr::ReflectedType");
			rt.AddMethod<&ReflectedType::f1>("f1");
		}

		int member = 112;
	};

	void test() {
		using namespace std::literals;
		const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
		assert(typeInfo != nullptr);
		assert(typeInfo->GetName() == "test_function_return_int_ptr::ReflectedType"sv);
		assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
		assert(typeInfo->GetMethodsCount() == 1);
		const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
		assert(functionInfo != nullptr);
		assert(functionInfo->GetName() == "f1"sv);
		assert(functionInfo->GetObjectType() == typeInfo);
		assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int*>());
		assert(functionInfo->GetArgumentsCount() == 0);

		ReflectedType object;
		int* returnValue = nullptr;
		functionInfo->Call(&object, &returnValue, nullptr, 0);
		assert(returnValue == &object.member);
	}
}

namespace test_function_return_int_ref
{
	class ReflectedType
	{
	public:
		int& f1() {
			return member;
		}

		static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
			rt.SetName("test_function_return_int_ref::ReflectedType");
			rt.AddMethod<&ReflectedType::f1>("f1");
		}

		int member = 112;
	};

	void test() {
		using namespace std::literals;
		const edt::reflection::TypeInfo* typeInfo = edt::reflection::GetTypeInfo<ReflectedType>();
		assert(typeInfo != nullptr);
		assert(typeInfo->GetName() == "test_function_return_int_ref::ReflectedType"sv);
		assert(typeInfo->GetInstanceSize() == sizeof(ReflectedType));
		assert(typeInfo->GetMethodsCount() == 1);
		const edt::reflection::ReflectedFunction* functionInfo = typeInfo->GetMethod(0);
		assert(functionInfo != nullptr);
		assert(functionInfo->GetName() == "f1"sv);
		assert(functionInfo->GetObjectType() == typeInfo);
		assert(functionInfo->GetReturnType() == edt::reflection::GetTypeInfo<int&>());
		assert(functionInfo->GetArgumentsCount() == 0);

		ReflectedType object;
		int* returnValue = nullptr;
		functionInfo->Call(&object, &returnValue, nullptr, 0);
		assert(returnValue == &object.member);
	}
}

namespace test_2
{
	class ReflectedType
	{
	public:
		void f1(ReflectedType&) {

		}

		void f2(ReflectedType*********) {

		}

		ReflectedType& f3(ReflectedType*) {
			return *this;
		}

		void f4(int, int) {

		}

		int f5(int a, int b) {
			return a + b;
		}

		static void ReflectType(edt::reflection::TypeReflector<ReflectedType>& rt) {
			rt.SetName("ReflectedType");
			rt.AddMethod<&ReflectedType::f1>("f1");
			rt.AddMethod<&ReflectedType::f2>("f2");
			rt.AddMethod<&ReflectedType::f3>("f3");
			rt.AddMethod<&ReflectedType::f4>("f4");
			rt.AddMethod<&ReflectedType::f5>("f5");
		}
	};

	void test_1() {

	}
}

void PrintType(const edt::reflection::TypeInfo* typeInfo, std::ostream& output) {
	output << typeInfo->GetName() << '\n';
	bool needNewLine = false;
	if (typeInfo->GetMethodsCount() > 0) {
		output << "   Methods:\n";
		const size_t methodsCount = typeInfo->GetMethodsCount();
		for (size_t methodIndex = 0; methodIndex < methodsCount; ++methodIndex) {
			auto methodInfo = typeInfo->GetMethod(methodIndex);
			output << "      ";

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
	test_function_return_void_argument_int::test();
	test_function_return_void_argument_int_ref::test();
	test_function_return_void_argument_int_pointer_ref::test();
	test_function_return_int::test();
	test_function_return_int_ptr::test();
	test_function_return_int_ref::test();
    auto& registry = edt::reflection::detail::TypeRegistryImpl::Instance();
	PrintReflectedTypes(registry, std::cout);
    return 0;
}
