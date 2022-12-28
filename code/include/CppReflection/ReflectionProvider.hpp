#pragma once

#include <concepts>
#include <type_traits>

namespace cppreflection {
template <typename T>
class TypeReflector;

template <typename T, typename Enable = void>
struct TypeReflectionProvider {
  static constexpr bool Reflected = false;
};
}  // namespace cppreflection

namespace cppreflection::detail {
template <typename T>
inline constexpr bool TypeIsReflectedWithProvider =
    TypeReflectionProvider<T>::Reflected;

template <typename T>
concept HasReflectTypeMethod = requires(T, TypeReflector<T>& rt) {
  { T::ReflectType(rt) } -> std::same_as<void>;
};

}  // namespace cppreflection::detail

namespace cppreflection {
template <typename T>
inline constexpr bool TypeIsReflected = detail::TypeIsReflectedWithMethod<T> ||
                                        detail::TypeIsReflectedWithProvider<T>;
}