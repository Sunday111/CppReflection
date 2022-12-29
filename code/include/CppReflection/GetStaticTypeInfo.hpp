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
concept HasConstexprReflectTypeMethod = requires(T) {
  { T::ReflectType() } -> IsStaticTypeInfoTrait;
};

template <typename T>
concept HasConstexprRelectionProvider = requires(T) {
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
}  // namespace cppreflection