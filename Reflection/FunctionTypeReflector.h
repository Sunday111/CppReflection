#pragma once

#include <tuple>

namespace edt::reflection
{
    template<typename T>
    struct FunctionTypeReflector;

    template<typename ReturnType_, typename... Args>
    struct FunctionTypeReflector<ReturnType_(*)(Args...)> {
        using ReturnType = ReturnType_;
        using Arguments = std::tuple<Args...>;
        static constexpr size_t GetArgsCount() { return sizeof...(Args); }
        static constexpr bool IsMethod() { return false; };
    };

    template<typename ReturnType_, typename Class_, typename... Args>
    struct FunctionTypeReflector<ReturnType_(Class_::*)(Args...)> {
        using ReturnType = ReturnType_;
        using Arguments = std::tuple<Args...>;
        using Class = Class_;
        static constexpr size_t GetArgsCount() { return sizeof...(Args); }
        static constexpr bool IsMethod() { return true; };
    };
}
