#pragma once

#include "../TypeComparisonOperators.hpp"
#include "HasOperator.hpp"

namespace cppreflection::detail {
template <typename T>
[[nodiscard]] constexpr TypeComparisonOperators MakeTypeComparisonOperators() {
  TypeComparisonOperators Result{};

  if constexpr (has_equals_operator_v<T>) {
    Result.equals = [](const void* a, const void* b) {
      const T* ca = reinterpret_cast<const T*>(a);
      const T* cb = reinterpret_cast<const T*>(b);
      #ifndef _MSC_VER
      _Pragma("GCC diagnostic push");
      _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"");
      #endif
      return *ca == *cb;
      #ifndef _MSC_VER
      _Pragma("GCC diagnostic pop");
      #endif
    };
  }

  if constexpr (has_less_operator_v<T>) {
    Result.less = [](const void* a, const void* b) {
      const T* ca = reinterpret_cast<const T*>(a);
      const T* cb = reinterpret_cast<const T*>(b);
      return *ca < *cb;
    };
  }

  return Result;
}
}  // namespace cppreflection::detail
