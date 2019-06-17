#pragma once

#include <tuple>

namespace cppreflection::detail
{
    template<typename T>
    struct FunctionTypeTraits;

    template<typename ReturnType_, typename... Args>
    struct FunctionTypeTraits<ReturnType_(*)(Args...)> {
        using ReturnType = ReturnType_;
        using Arguments = std::tuple<Args...>;
        static constexpr size_t GetArgsCount() { return sizeof...(Args); }
        static constexpr bool IsMethod() { return false; };
    };

    template<typename ReturnType_, typename Class_, typename... Args>
    struct FunctionTypeTraits<ReturnType_(Class_::*)(Args...)> {
        using ReturnType = ReturnType_;
        using Arguments = std::tuple<Args...>;
        using Class = Class_;
        static constexpr size_t GetArgsCount() { return sizeof...(Args); }
        static constexpr bool IsMethod() { return true; };
    };

    template<auto pfn>
    struct FunctionPointerTraits
        : public FunctionTypeTraits<decltype(pfn)>
    {
    };
}
