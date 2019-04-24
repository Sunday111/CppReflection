#pragma once

#include <cassert>
#include "FunctionImpl.h"
#include "Detail/FunctionTraits.h"
#include "UnusedVar.h"

namespace edt::reflection
{
    template<typename T>
    const Type* GetTypeInfo();
}

namespace edt::reflection::detail
{
    template<auto pfn>
    class FunctionReflector : public FunctionImpl
    {
        using FnReflector = detail::FunctionPointerTraits<pfn>;

    public:
        FunctionReflector();
        virtual void Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const override;

    private:
        template<size_t Index>
        static constexpr decltype(auto) CastArg_i(void** ArgsArray);

        template<size_t... Index>
        void Call_i(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize, std::index_sequence<Index...>) const;

        template<size_t... Index>
        void InitializeArgs(std::index_sequence<Index...>);

        template<size_t Index>
        void InitializeArg();
    };

    template<auto pfn>
    FunctionReflector<pfn>::FunctionReflector() {
        using ReturnType = typename FnReflector::ReturnType;
        if constexpr (!std::is_same_v<ReturnType, void>) {
            SetReturnType(GetTypeInfo<ReturnType>());
        }

        if constexpr (FnReflector::IsMethod()) {
            using Class = typename FnReflector::Class;
            SetObjectType(GetTypeInfo<Class>());
        }

        InitializeArgs(std::make_index_sequence<FnReflector::GetArgsCount()>());
    }

}

namespace edt::reflection::detail
{
    template<typename T>
    constexpr decltype(auto) CastArg_t(void* rawArg) {
        if constexpr (std::is_reference_v<T>) {
            using NoRef = std::remove_reference_t<T>;
            if constexpr (std::is_rvalue_reference_v<T>) {
                return std::move(*reinterpret_cast<NoRef*>(rawArg));
            }
            else {
                return *reinterpret_cast<NoRef*>(rawArg);
            }
        }
        else {
            return *reinterpret_cast<T*>(rawArg);
        }
    }
}

namespace edt::reflection::detail
{
    template<auto pfn>
    void FunctionReflector<pfn>::Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const {
        Call_i(Object, ReturnValue, ArgsArray, ArgsArraySize, std::make_index_sequence<FnReflector::GetArgsCount()>());
    }

    template<auto pfn>
    template<size_t Index>
    constexpr decltype(auto) FunctionReflector<pfn>::CastArg_i(void** ArgsArray) {
        using Arguments = typename FnReflector::Arguments;
        using T = std::tuple_element_t<Index, Arguments>;
        return CastArg_t<T>(ArgsArray[Index]);
    }

    // Make object that will call function or method in the same way
    template<auto pfn>
    decltype(auto) WrapMethodCalls(void* Object) {
        using FnReflector = detail::FunctionPointerTraits<pfn>;
        using ReturnType = typename FnReflector::ReturnType;
        if constexpr (FnReflector::IsMethod()) {
            return [Object](auto&&... args) -> decltype(auto) {
                using Class = typename FnReflector::Class;
                auto pObject = reinterpret_cast<Class*>(Object);
                return static_cast<ReturnType>((pObject->*pfn)(std::forward<decltype(args)>(args)...));
            };
        }
        else {
            UnusedVar(Object);
            return [](auto&&... args) -> decltype(auto) {
                return static_cast<ReturnType>(pfn(std::forward<decltype(args)>(args)...));
            };
        }
    }

    template<auto pfn>
    template<size_t... Index>
    void FunctionReflector<pfn>::Call_i(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize, std::index_sequence<Index...>) const {
        assert(ArgsArraySize >= FnReflector::GetArgsCount());
        using ReturnType = typename FnReflector::ReturnType;
        auto call = [&]() -> decltype(auto) {
            auto f = WrapMethodCalls<pfn>(Object);
            return static_cast<ReturnType>(f(CastArg_i<Index>(ArgsArray)...));
        };

        if constexpr (std::is_same_v<void, ReturnType>) {
            // free function without return type
            call();
        }
        else {
            // free function with some return type
            assert(ReturnValue != nullptr);
            if constexpr (std::is_reference_v<ReturnType>) {
                using NoRef = std::remove_reference_t<ReturnType>;
                if constexpr (std::is_rvalue_reference_v<ReturnType>) {
                    // Return type is rvalue reference
                    auto pRV = reinterpret_cast<NoRef*>(ReturnValue);
                    // Construct instance in given memory
                    new (pRV)NoRef(call());
                }
                else {
                    // Return type is lvalue reference
                    auto ppRV = reinterpret_cast<NoRef**>(ReturnValue);
                    *ppRV = &call();
                }
            }
            else {
                // Return type is not reference
                auto& pRV = CastArg_t<ReturnType>(ReturnValue);
                pRV = call();
            }
        }
    }

    template<auto pfn>
    template<size_t... Index>
    void FunctionReflector<pfn>::InitializeArgs(std::index_sequence<Index...>) {
        (InitializeArg<Index>(), ...);
    }

    template<auto pfn>
    template<size_t Index>
    void FunctionReflector<pfn>::InitializeArg() {
        using Arguments = typename FnReflector::Arguments;
        using Argument = std::tuple_element_t<Index, Arguments>;
        auto typeInfo = GetTypeInfo<Argument>();
        PushArgumentType(typeInfo);
    }
}
