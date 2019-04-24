#pragma once

#include <string>

#include "../Field.h"

namespace edt::reflection::detail
{
    class FieldImpl : public Field
    {
    public:
        virtual const Type* GetType() const override;
        virtual const char* GetName() const override;

        void SetName(const char* name);
        void SetType(const Type* type);

    private:
        const Type* m_type = nullptr;
        std::string m_name;
    };
}
