#pragma once

#include "CppReflection/Common.h"

namespace cppreflection
{
    class Type;

    class TypeRegistry
    {
    public:
        [[nodiscard]]
        virtual const Type* GetTypeInfo(size_t index) const = 0;

        [[nodiscard]]
        virtual size_t GetTypesCount() const = 0;

        virtual bool RegisterType(Type* type) = 0;

        virtual void ClearRegistry() = 0;

        //
        virtual ~TypeRegistry() = default;
    };

    CPP_REFLECTION_API TypeRegistry* GetTypeRegistry();
}
