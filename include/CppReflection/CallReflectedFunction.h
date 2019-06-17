#pragma once

#include "GetTypeInfo.h"
#include "EverydayTools/UnusedVar.h"

namespace cppreflection
{
    template<typename ReturnType>
    decltype(auto) WrapReflectedFunctionReturnType(const Function* fn, void* instance, void** args, size_t argsCount) {
        if constexpr (!std::is_same_v<void, ReturnType>) {
            assert(GetTypeInfo<ReturnType>() == fn->GetReturnType());
            if constexpr (std::is_pointer_v<ReturnType>) {
                ReturnType result;
                fn->Call(instance, &result, args, argsCount);
                return result;
            }
            else if constexpr (std::is_rvalue_reference_v<ReturnType>) {
                using NoRef = std::remove_reference_t<ReturnType>;
                uint8_t rvMemory[sizeof(NoRef)];
                fn->Call(instance, rvMemory, args, argsCount);
                NoRef* pRV = reinterpret_cast<NoRef*>(rvMemory);
                NoRef rv(std::move(*pRV));
                pRV->~NoRef();
                return rv;
            }
            else if constexpr (std::is_reference_v<ReturnType>) {
                using NoRef = std::remove_reference_t<ReturnType>;
                NoRef* pRV;
                fn->Call(instance, &pRV, args, argsCount);
                return static_cast<NoRef&>(*pRV);
            }
            else {
                // TODO: utilize with rvalue reference branch
                using NoRef = std::remove_reference_t<ReturnType>;
                uint8_t rvMemory[sizeof(NoRef)];
                fn->Call(instance, rvMemory, args, argsCount);
                NoRef* pRV = reinterpret_cast<NoRef*>(rvMemory);
                NoRef rv(std::move(*pRV));
                pRV->~NoRef();
                return rv;
            }
        }
        else {
            fn->Call(instance, nullptr, args, argsCount);
        }
    }

    template<typename ReturnType, typename Class, typename... Args>
    decltype(auto) CallMethod(const Function* fn, Class& instance, Args&&... args) {
        constexpr const size_t argsCount = sizeof...(Args);
        if constexpr (argsCount > 0) {
            void* arr[argsCount]{ &args... };
            return WrapReflectedFunctionReturnType<ReturnType>(fn, &instance, arr, argsCount);
        }
        else {
            return WrapReflectedFunctionReturnType<ReturnType>(fn, &instance, nullptr, 0);
        }
    }

    template<typename ReturnType, typename... Args>
    decltype(auto) CallFunction(const Function* fn, Args&&... args) {
        constexpr const size_t argsCount = sizeof...(Args);
        if constexpr (argsCount > 0) {
            void* arr[argsCount]{ &args... };
            return WrapReflectedFunctionReturnType<ReturnType>(fn, nullptr, arr, argsCount);
        }
        else {
            return WrapReflectedFunctionReturnType<ReturnType>(fn, nullptr, nullptr, 0);
        }
    }

}
