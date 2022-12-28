#pragma once

#include "EverydayTools/Template/IsSpecialization.h"
#include "ReflectionProvider.hpp"
#include "Reflector/TypeReflector.hpp"
#include "StaticType/class.hpp"
#include "StaticType/enum.hpp"
#include "TypeRegistry.hpp"

namespace cppreflection {

template <typename Test>
concept IsStaticTypeInfoTrait =
    IsStaticClassTypeInfo<Test> || IsStaticEnumTypeInfo<Test>;

template <typename T, typename Enable>
struct TypeReflectionProvider;

template <typename T>
concept HasConstexprReflectTypeMethod = requires(T) {
  { T::ReflectType() } -> IsStaticTypeInfoTrait;
};

template <typename T>
[[nodiscard]] inline constexpr auto GetStaticTypeInfo() {
  if constexpr (HasConstexprReflectTypeMethod<T>) {
    return T::ReflectType();
  } else {
    return TypeReflectionProvider<T>::ReflectType();
  }
}
}  // namespace cppreflection