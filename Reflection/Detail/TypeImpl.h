#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../Type.h"

namespace edt::reflection::detail
{
    class FieldImpl;
    class FunctionImpl;

    class TypeImpl : public Type
    {
    public:
        TypeImpl();
        TypeImpl(const TypeImpl&) = delete;
        TypeImpl(TypeImpl&&);
        ~TypeImpl();

        virtual size_t GetMethodsCount() const override;
        virtual const Function* GetMethod(size_t index) const override;
        virtual const char* GetName() const override;
        virtual size_t GetFieldsCount() const override;
        virtual const Field* GetField(size_t index) const override;

        void SetName(const char* name);

    protected:
        std::string m_name;
        std::vector<std::unique_ptr<FieldImpl>> m_fields;
        std::vector<std::unique_ptr<FunctionImpl>> m_methods;
    };
}
