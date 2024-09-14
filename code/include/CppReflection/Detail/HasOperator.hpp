#pragma once

#include <functional>
#include <type_traits>

namespace cppreflection::detail
{
template <class F, class... T, typename = decltype(std::declval<F>()(std::declval<T>()...))>
std::true_type supports_test(const F&, const T&...);
std::false_type supports_test(...);

template <class>
struct supports;
template <class F, class... T>
struct supports<F(T...)> : decltype(supports_test(std::declval<F>(), std::declval<T>()...)){};

template <typename T>
inline constexpr bool supports_v = supports<T>::value;

template <typename T>
inline constexpr bool has_equals_operator_v = supports_v<std::equal_to<>(T&, T&)>;

template <typename T>
inline constexpr bool has_less_operator_v = supports_v<std::less<>(T&, T&)>;
}  // namespace cppreflection::detail
