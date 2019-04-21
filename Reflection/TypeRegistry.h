#pragma once

namespace edt::reflection
{
    class TypeInfo;

    class TypeRegistry
    {
    public:
        virtual const TypeInfo* GetTypeInfo(size_t index) const = 0;
        virtual size_t GetTypesCount() const = 0;
        virtual ~TypeRegistry() = default;
    };
}
