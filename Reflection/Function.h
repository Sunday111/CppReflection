#pragma once

namespace edt::reflection
{
    class Type;

    class Function
    {
    public:
        /* Function return value type.
         * Null if function doesn't have return type (void)
         */
        virtual const Type* GetReturnType() const = 0;

        /* Returns type of object on which instance this function should be called.
         * i.e. function is method.
         * Returns null for pure functions
         */
        virtual const Type* GetObjectType() const = 0;

        /* Function parameters count
         */
        virtual size_t GetArgumentsCount() const = 0;

        /* Function parameter type by index
         * index should be in range [0; GetArgumentsCount())
         */
        virtual const Type* GetArgumentType(size_t index) const = 0;

        /* Name of function
         */
        virtual const char* GetName() const = 0;

        /* Calls method with specified parameters
         * Object - parameter for methods, may be null in case of pure functions.
         * ReturnValue - where to write return value, may be null if return value is void
         */
        virtual void Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const = 0;

		//
		virtual ~Function() = default;
    };
}
