#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../TypeInfo.h"

namespace edt::reflection::detail
{
    class ReflectedFunctionImpl;

    class TypeInfoImpl : public TypeInfo
    {
    public:
        TypeInfoImpl();
        TypeInfoImpl(const TypeInfoImpl&) = delete;
        TypeInfoImpl(TypeInfoImpl&&);
        ~TypeInfoImpl();

        virtual size_t GetMethodsCount() const override;
        virtual const ReflectedFunction* GetMethod(size_t index) const override;
        virtual const char* GetName() const override;

        void SetName(const char* name);

    protected:
        std::string m_name;
        std::vector<std::unique_ptr<ReflectedFunctionImpl>> m_methods;
    };
}
