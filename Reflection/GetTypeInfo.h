#pragma once

#include "TypeRegistryImpl.h"
#include "TypeReflector.h"

namespace edt::reflection
{
    class TypeInfo;

    // Recursive reflection for pointer and reference types
    template<typename T, typename = std::enable_if_t<std::is_pointer_v<T> || std::is_reference_v<T>>>
    void ReflectType(TypeReflector<T>& rt) {
        if constexpr (std::is_pointer_v<T>) {
            using Naked = std::remove_pointer_t<T>;
            auto ti = GetTypeInfo<Naked>();
            auto name = std::string(ti->GetTypeName()) + '*';
            rt.SetName(name.c_str());
        }
        else {
            using Naked = std::remove_reference_t<T>;
            auto ti = GetTypeInfo<Naked>();
            auto name = std::string(ti->GetTypeName()) + '&';
            rt.SetName(name.c_str());
        }
    }

    template<typename T>
    inline const TypeInfo* GetTypeInfo() {
        static const TypeInfo* ptr = nullptr;
        if (ptr != nullptr) {
            return ptr;
        }
        TypeReflector<T>& ref = TypeRegistryImpl::Instance().Register<T>();
        ptr = &ref;
        detail::CallReflectType(ref);
        return ptr;
    }
}
