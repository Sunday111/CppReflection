#pragma once

#include <memory>
#include <vector>

namespace edt::reflection
{
    class Field;
    class Function;

    class Type
    {
    public:
        virtual size_t GetInstanceSize() const = 0;
        virtual const char* GetName() const = 0;
        virtual size_t GetMethodsCount() const = 0;
        virtual const Function* GetMethod(size_t index) const = 0;
        virtual size_t GetFieldsCount() const = 0;
        virtual const Field* GetField(size_t index) const = 0;

        //
        virtual ~Type() = default;
    };
}
