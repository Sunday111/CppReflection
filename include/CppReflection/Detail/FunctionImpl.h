#pragma once

#include <vector>

#include "../Function.h"

namespace cppreflection::detail
{
    class FunctionImpl : public Function
    {
    public:
        virtual const char* GetName() const override;
        virtual const Type* GetReturnType() const override;
        virtual const Type* GetObjectType() const override;
        virtual size_t GetArgumentsCount() const override;
        virtual const Type* GetArgumentType(size_t index) const override;

        void SetName(const char* name);
        void SetReturnType(const Type* type);
        void SetObjectType(const Type* type);
        void PushArgumentType(const Type* type);

    private:
        std::string m_name;
        const Type* m_returnType = nullptr;
        const Type* m_objectType = nullptr;
        std::vector<const Type*> m_argumentTypes;
    };
}
