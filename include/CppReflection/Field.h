#pragma once

namespace cppreflection
{
    class Type;

    class Field
    {
    public:
        /* Field type
         */
        [[nodiscard]]
        virtual const Type* GetType() const = 0;

        /* Field name
         */
        [[nodiscard]]
        virtual const char* GetName() const = 0;

        /* Get pointer to field value
         */
        [[nodiscard]]
        virtual void* GetValue(void* Object) const = 0;

        // 
        virtual ~Field() = default;
    };
}
