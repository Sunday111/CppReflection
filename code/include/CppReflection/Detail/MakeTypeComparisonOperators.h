#pragma once

#include "HasOperator.h"
#include "../TypeComparisonOperators.h"

namespace cppreflection::detail
{
    template<typename T>
    [[nodiscard]]
    constexpr TypeComparisonOperators MakeTypeComparisonOperators() {
        TypeComparisonOperators Result{};

        if constexpr (has_equals_operator_v<T>) {
            Result.equals = [](const void* a, const void* b) {
                const T* ca = reinterpret_cast<const T*>(a);
                const T* cb = reinterpret_cast<const T*>(b);
                return *ca == *cb;
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
}
