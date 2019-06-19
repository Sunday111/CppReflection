#pragma once

#include "CppReflection/Common.h"
#include "EverydayTools/Array/ArrayView.h"
#include "EverydayTools/Array/StringView.h"

namespace cppreflection
{
    class Type;

    class Function
    {
    public:
        using Caller = void(*)(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize);

        /* Function return value type.
         * Null if function doesn't have return type (void)
         */
        [[nodiscard]]
        virtual const Type* GetReturnType() const = 0;

        /* Returns type of object on which instance this function should be called.
         * i.e. function is method.
         * Returns null for pure functions
         */
        [[nodiscard]]
        virtual const Type* GetObjectType() const = 0;

        [[nodiscard]]
        virtual edt::SparseArrayView<const Type* const> GetArguments() const = 0;

        /* Name of function
         */
        [[nodiscard]]
        virtual edt::StringView GetName() const = 0;

        /* Calls method with specified parameters
         * Object - parameter for methods, may be null in case of pure functions.
         * ReturnValue - where to write return value, may be null if return value is void
         */
        virtual void Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const = 0;

        virtual size_t AddArgumentType(const Type* argumentType) = 0;
        virtual void SetObjectType(const Type* objectType) = 0;
        virtual void SetCaller(Caller caller) = 0;
        virtual void SetName(const edt::StringView& name) = 0;
        virtual void SetReturnType(const Type* returnType) = 0;

        //
        virtual ~Function() = default;
    };

    CPP_REFLECTION_API Function* AllocFunction();
}
