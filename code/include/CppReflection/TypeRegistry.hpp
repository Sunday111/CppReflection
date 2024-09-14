#pragma once

#include "CppReflection/Common.hpp"
#include "EverydayTools/GUID.hpp"

namespace cppreflection
{
class Type;

class TypeRegistry
{
public:
    [[nodiscard]] virtual const Type* GetTypeInfo(size_t index) const = 0;
    [[nodiscard]] virtual size_t GetTypesCount() const = 0;
    [[nodiscard]] virtual const Type* FindType(const edt::GUID& guid) const = 0;

    /* Same as FindType but throws an exception if type was not found */
    [[nodiscard]] virtual const Type* GetType(const edt::GUID& guid) const = 0;

    virtual bool RegisterType(Type* type) = 0;
    virtual bool RefreshType(Type* type) = 0;

    virtual void ClearRegistry() = 0;

    //
    virtual ~TypeRegistry() = default;
};

CPP_REFLECTION_API TypeRegistry* GetTypeRegistry();
}  // namespace cppreflection
