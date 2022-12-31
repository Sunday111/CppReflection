#pragma once

#include "EverydayTools/Template/IsSpecialization.hpp"
#include "ReflectionProvider.hpp"
#include "Reflector/TypeReflector.hpp"
#include "StaticType/class.hpp"
#include "StaticType/enum.hpp"
#include "StaticType/fundamental.hpp"
#include "TypeRegistry.hpp"

namespace cppreflection {

template <typename Test>
concept IsStaticTypeInfoTrait =
    detail::IsStaticClassTypeInfo<Test> || detail::IsStaticEnumTypeInfo<Test> ||
    detail::IsStaticFundamentalTypeInfo<Test>;

template <typename T, typename Enable>
struct TypeReflectionProvider;

template <typename T>
concept HasConstexprReflectTypeMethod = requires() {
  { T::ReflectType() } -> IsStaticTypeInfoTrait;
};

template <typename T>
concept HasConstexprRelectionProvider = requires() {
  { TypeReflectionProvider<T>::ReflectType() } -> IsStaticTypeInfoTrait;
};

template <typename T>
concept IsTypeStaticallyReflected =
    HasConstexprReflectTypeMethod<T> || HasConstexprRelectionProvider<T>;

template <typename T>
[[nodiscard]] inline constexpr auto GetStaticTypeInfo() {
  static_assert(IsTypeStaticallyReflected<T>);
  if constexpr (HasConstexprReflectTypeMethod<T>) {
    return T::ReflectType();
  } else {
    return TypeReflectionProvider<T>::ReflectType();
  }
}

template <typename T>
[[nodiscard]] inline constexpr edt::GUID GetStaticTypeGUID() {
  return GetStaticTypeInfo<T>().guid;
}
}  // namespace cppreflection

#include "StaticType/class_to_dynamic.hpp"

namespace cppreflection {

// Some utilities

template <typename Test>
concept IsStaticallyReflectedEnum = requires() {
  { GetStaticTypeInfo<Test>() } -> detail::IsStaticEnumTypeInfo;
};

template <IsStaticallyReflectedEnum T>
[[nodiscard]] inline constexpr std::string_view EnumToString(T value) {
  return GetStaticTypeInfo<T>().ToString(value);
}

template <IsStaticallyReflectedEnum T>
[[nodiscard]] inline constexpr bool TryParseEnum(std::string_view str,
                                                 T& out_value) {
  return GetStaticTypeInfo<T>().TryParse(str, out_value);
}

template <IsStaticallyReflectedEnum T>
[[nodiscard]] inline constexpr T ParseEnum(std::string_view str) {
  return GetStaticTypeInfo<T>().Parse(str);
}

}  // namespace cppreflection