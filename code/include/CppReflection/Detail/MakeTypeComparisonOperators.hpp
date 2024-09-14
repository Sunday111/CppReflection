#pragma once

#include <bit>
#include <cstdint>

#include "../TypeComparisonOperators.hpp"
#include "HasOperator.hpp"

#if !defined(_MSC_VER) || defined(__clang__)
#define CPP_REFLECT_IGNORE_FLT_WARNING_PUSH \
    _Pragma("GCC diagnostic push");         \
    _Pragma("GCC diagnostic ignored \"-Wfloat-equal\"")

#define CPP_REFLECT_IGNORE_FLT_WARNING_POP _Pragma("GCC diagnostic pop")
#else
#define CPP_REFLECT_IGNORE_FLT_WARNING_PUSH
#define CPP_REFLECT_IGNORE_FLT_WARNING_POP
#endif

namespace cppreflection::detail
{
template <typename T>
[[nodiscard]] constexpr TypeComparisonOperators MakeTypeComparisonOperators()
{
    CPP_REFLECT_IGNORE_FLT_WARNING_PUSH
    TypeComparisonOperators Result{};

    if constexpr (has_equals_operator_v<T>)
    {
        Result.equals = [](const void* a, const void* b)
        {
            const T* ca = reinterpret_cast<const T*>(a);
            const T* cb = reinterpret_cast<const T*>(b);
            return *ca == *cb;
        };
    }

    if constexpr (has_less_operator_v<T>)
    {
        Result.less = [](const void* a, const void* b)
        {
            const T* ca = reinterpret_cast<const T*>(a);
            const T* cb = reinterpret_cast<const T*>(b);
            return *ca < *cb;
        };
    }

    return Result;
    CPP_REFLECT_IGNORE_FLT_WARNING_POP
}
}  // namespace cppreflection::detail
