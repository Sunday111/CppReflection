#pragma once

#include "Detail/CallReflectType.h"
#include "Reflector/TypeReflector.h"
#include "TypeRegistry.h"

namespace cppreflection
{
    class Type;

    // Recursive reflection for pointer and reference types
    template<typename T, typename = std::enable_if_t<std::is_pointer_v<T> || std::is_reference_v<T>>>
    inline void ReflectType(TypeReflector<T>& rt) {
        if constexpr (std::is_pointer_v<T>) {
            using Naked = std::remove_pointer_t<T>;
            auto ti = GetTypeInfo<Naked>();
            auto name = std::string(ti->GetName()) + "*";
            rt.SetName(name.c_str());
        }
        else if constexpr (std::is_rvalue_reference_v<T>) {
            using Naked = std::remove_reference_t<T>;
            auto ti = GetTypeInfo<Naked>();
            auto name = std::string(ti->GetName()) + "&&";
            rt.SetName(name.c_str());
        }
        else {
            using Naked = std::remove_reference_t<T>;
            auto ti = GetTypeInfo<Naked>();
            auto name = std::string(ti->GetName()) + '&';
            rt.SetName(name.c_str());
        }
    }

    template<typename T>
    [[nodiscard]]
    inline const Type* GetTypeInfo() {
        static const Type* ptr = nullptr;
        if (ptr != nullptr) {
            return ptr;
        }

        TypeReflector<T> typeReflector;
        Type* type = typeReflector.GetType();
        GetTypeRegistry()->RegisterType(type);
        ptr = type;

        detail::CallReflectType(typeReflector);
        return ptr;
    }
}
