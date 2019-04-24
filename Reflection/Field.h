#pragma once

namespace edt::reflection
{
    class Type;

    class Field
    {
    public:
        /* Field type
         */
        virtual const Type* GetType() const = 0;

        /* Field name
         */
        virtual const char* GetName() const = 0;

        /* Get pointer to field value
         */
        virtual void* GetValue(void* Object) const = 0;

        // 
        virtual ~Field() = default;
    };
}
