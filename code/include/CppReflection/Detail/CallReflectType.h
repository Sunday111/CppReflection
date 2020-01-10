#pragma once

#include <type_traits>
#include "EverydayTools/Template/TypeHasMethod.h"

namespace cppreflection
{
    template<typename T>
    class TypeReflector;

    template<typename T, typename Enable = void>
    struct TypeReflectionProvider
    {
        static constexpr bool Reflected = false;
    };
}

namespace cppreflection::detail
{
    ImplementHasMethod(ReflectType);

    template<typename T>
    inline constexpr bool TypeIsReflectedWithMethod = HasReflectTypeMethod_v<T>;

    template<typename T>
    inline constexpr bool TypeIsReflectedWithProvider = TypeReflectionProvider<T>::Reflected;

    template<typename T>
    void CallReflectType(TypeReflector<T>& typeInfo) {
        constexpr bool provider = TypeIsReflectedWithProvider<T>;
        constexpr bool method = TypeIsReflectedWithMethod<T>;

        static_assert(provider || method, "Type must be reflected");

        if constexpr (provider) {
            TypeReflectionProvider<T>::ReflectType(typeInfo);
        }
        else {
            T::ReflectType(typeInfo);
        }
    }
}

namespace cppreflection
{
    template<typename T>
    inline constexpr bool TypeIsReflected = detail::TypeIsReflectedWithMethod<T> || detail::TypeIsReflectedWithProvider<T>;
}
