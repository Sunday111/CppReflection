#pragma once

#include <string>

#include "../Field.h"

namespace cppreflection::detail
{
    class FieldImpl : public Field
    {
    public:
        [[nodiscard]]
        virtual const Type* GetType() const override;

        [[nodiscard]]
        virtual const char* GetName() const override;

        void SetName(const char* name);
        void SetType(const Type* type);

    private:
        const Type* m_type = nullptr;
        std::string m_name;
    };
}
