#pragma once

#include <string_view>

#include "CppReflection/Common.hpp"

namespace cppreflection
{
class Type;

class Field
{
public:
    using ValueGetter = void* (*)(void* instance);

    virtual void SetType(const Type* type) = 0;
    virtual void SetName(const std::string_view& name) = 0;
    virtual void SetValueGetter(ValueGetter getter) = 0;

    /* Field type
     */
    [[nodiscard]]
    virtual const Type* GetType() const = 0;

    /* Field name
     */
    [[nodiscard]]
    virtual std::string_view GetName() const = 0;

    /* Get pointer to field value
     */
    [[nodiscard]]
    virtual void* GetValue(void* Object) const = 0;

    //
    virtual ~Field() = default;
};

CPP_REFLECTION_API Field* AllocField();
}  // namespace cppreflection
