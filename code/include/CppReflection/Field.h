#pragma once

#include "CppReflection/Common.h"

namespace cppreflection
{
    class Type;

    class Field
    {
    public:
        using ValueGetter = void* (*) (void* instance);

        virtual void SetType(const Type* type) = 0;

        /* Field type
         */
        [[nodiscard]]
        virtual const Type* GetType() const = 0;

        virtual void SetName(const char* name) = 0;

        /* Field name
         */
        [[nodiscard]]
        virtual const char* GetName() const = 0;

        /* Get pointer to field value
         */
        [[nodiscard]]
        virtual void* GetValue(void* Object) const = 0;

        virtual void SetValueGetter(ValueGetter getter) = 0;

        // 
        virtual ~Field() = default;
    };

    CPP_REFLECTION_API Field* AllocField();
}
