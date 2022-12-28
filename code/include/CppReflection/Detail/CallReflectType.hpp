#pragma once

#include <type_traits>

#include "../ReflectionProvider.hpp"

namespace cppreflection::detail {

template <typename T>
void CallReflectType(TypeReflector<T>& typeInfo) {
  constexpr bool provider = TypeIsReflectedWithProvider<T>;
  constexpr bool method = HasReflectTypeMethod<T>;

  static_assert(provider || method, "Type must be reflected");

  if constexpr (provider) {
    TypeReflectionProvider<T>::ReflectType(typeInfo);
  } else {
    T::ReflectType(typeInfo);
  }
}

}  // namespace cppreflection::detail
