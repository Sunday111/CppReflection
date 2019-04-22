#pragma once

#include <memory>
#include <vector>

namespace edt::reflection
{
    class ReflectedFunction;

    class TypeInfo
    {
    public:
        virtual size_t GetInstanceSize() const = 0;
        virtual const char* GetName() const = 0;
        virtual size_t GetMethodsCount() const = 0;
        virtual const ReflectedFunction* GetMethod(size_t index) const = 0;

		//
		virtual ~TypeInfo() = default;
    };
}
