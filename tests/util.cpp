#include <iostream>
#include <string>
#include <string_view>

#include "gtest/gtest.h"

#include "CppReflection/TypeReflector.h"
#include "CppReflection/PrimitiveTypeReflection.h"
#include "CppReflection/CallReflectedFunction.h"
#include "CppReflection/Detail/TypeRegistryImpl.h"

void PrintType(const cppreflection::Type* typeInfo, std::ostream& output) {
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

void PrintReflectedTypes(const cppreflection::TypeRegistry& registry, std::ostream& output) {
    for (size_t i = 0; i < registry.GetTypesCount(); ++i) {
        PrintType(registry.GetTypeInfo(i), output);
    }
}
