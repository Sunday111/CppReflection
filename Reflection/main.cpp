#include <iostream>
#include <string>

#include "FunctionReflector.h"
#include "TypeReflector.h"
#include "GetTypeInfo.h"

#include "TypeRegistryImpl.h"

class ReflectedType
{
public:
    void f1(ReflectedType&) {

    }

    void f2(ReflectedType*) {

    }

    ReflectedType& f3(ReflectedType*) {
        return *this;
    }

    void f4(int a, int b) {

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

namespace edt::reflection
{
    void ReflectType(TypeReflector<int>& rt) {
        rt.SetName("int");
    }
}

void PrintType(const edt::reflection::TypeInfo* ti) {
    std::cout << ti->GetTypeName() << '\n';
    bool needNewLine = false;
    if (ti->GetMethodsCount() > 0) {
        std::cout << "   Methods:\n";
        for (size_t i = 0; i < ti->GetMethodsCount(); ++i) {
            auto mi = ti->GetMethod(i);
            std::cout << "      ";

            if (auto rv = mi->GetReturnType()) {
                std::cout << rv->GetTypeName();
            }
            else {
                std::cout << "void";
            }

            std::cout << ' ' << mi->GetName() << '(';
            for (size_t j = 0; j < mi->GetArgumentsCount(); ++j) {
                auto ai = mi->GetArgumentType(j);
                std::cout << ai->GetTypeName();
                if (j < mi->GetArgumentsCount() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << ");\n";
        }
        bool needNewLine = true;
    }
    if (needNewLine) {
        std::cout << '\n';
    }
}


int main() {
    edt::reflection::GetTypeInfo<ReflectedType>();

    auto& registry = edt::reflection::TypeRegistryImpl::Instance();
    for (size_t i = 0; i < registry.GetTypesCount(); ++i) {
        PrintType(registry.GetTypeInfo(i));
    }

    return 0;
}
