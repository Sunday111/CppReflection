#pragma once

namespace edt::reflection
{
    class Type;

    class TypeRegistry
    {
    public:
        [[nodiscard]] virtual const Type* GetTypeInfo(size_t index) const = 0;
        [[nodiscard]] virtual size_t GetTypesCount() const = 0;

        //
        virtual ~TypeRegistry() = default;
    };
}
