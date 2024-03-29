#pragma once

#include <string>

#include "CppReflection/Field.hpp"

namespace cppreflection::detail
{
    class FieldImpl : public Field
    {
    public:
        virtual void SetType(const Type* type) override;

        [[nodiscard]]
        virtual const Type* GetType() const override;

        virtual void SetName(const std::string_view& name) override;

        [[nodiscard]]
        virtual std::string_view GetName() const override;

        virtual void SetValueGetter(ValueGetter getter) override;

        [[nodiscard]]
        virtual void* GetValue(void* Object) const override;

    private:
        const Type* m_type = nullptr;
        std::string m_name;
        ValueGetter m_getter = nullptr;
    };
}
