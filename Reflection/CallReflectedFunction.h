#pragma once

#include "GetTypeInfo.h"

namespace edt::reflection
{
    template<typename ReturnType>
    decltype(auto) WrapReflectedFunctionReturnType(const ReflectedFunction* fn, void* instance, void** args, size_t argsCount) {
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
            return static_cast<NoRef>(*pRV);
        }
    }
}
