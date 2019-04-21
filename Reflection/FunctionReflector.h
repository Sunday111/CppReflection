#pragma once

#include "ReflectedFunctionImpl.h"
#include "FunctionPoinerReflector.h"

namespace edt::reflection
{
    template<typename T>
    const TypeInfo* GetTypeInfo();

    template<auto pfn>
    class FunctionReflector : public ReflectedFunctionImpl
    {
        using FnReflector = FunctionPointerReflector<pfn>;

    public:
        FunctionReflector();
        virtual void Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const override;

    private:
        template<size_t Index>
        static constexpr decltype(auto) Cast_i(void** ArgsArray);

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

namespace edt::reflection::function_reflection_details
{
    template<typename T>
    constexpr decltype(auto) Cast_t(void* rawArg) {
        if constexpr (std::is_reference_v<T>) {
            using NoRef = std::remove_reference_t<T>;
            return *reinterpret_cast<NoRef*>(rawArg);
        }
        else {
            return *reinterpret_cast<T*>(rawArg);
        }
    }
}

namespace edt::reflection
{
    template<auto pfn>
    void FunctionReflector<pfn>::Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const {
        Call_i(Object, ReturnValue, ArgsArray, ArgsArraySize, std::make_index_sequence<FnReflector::GetArgsCount()>());
    }

    template<auto pfn>
    template<size_t Index>
    constexpr decltype(auto) FunctionReflector<pfn>::Cast_i(void** ArgsArray) {
        using Arguments = typename FnReflector::Arguments;
        using T = std::tuple_element_t<Index, Arguments>;
        return function_reflection_details::Cast_t<T>(ArgsArray[Index]);
    }

    template<auto pfn>
    template<size_t... Index>
    void FunctionReflector<pfn>::Call_i(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize, std::index_sequence<Index...>) const {
        using namespace function_reflection_details;
        using ReturnType = typename FnReflector::ReturnType;
        if constexpr (FnReflector::IsMethod()) {
            using Class = typename FnReflector::Class;
            auto pObject = reinterpret_cast<Class*>(Object);
            if constexpr (std::is_same_v<void, ReturnType>) {
                // Method without return type
                (pObject->*pfn)(Cast_i<Index>(ArgsArray)...);
            }
            else {
                // Method with return type
                auto& pRV = Cast_t<ReturnType>(ReturnValue);
                pRV = (pObject->*pfn)(Cast_i<Index>(ArgsArray)...);
            }
        }
        else {
            if constexpr (std::is_same_v<void, ReturnType>) {
                // free function without return type
                pfn(Cast_i<Index>(ArgsArray)...);
            }
            else {
                // free function with some return type
                auto& pRV = Cast_t<ReturnType>(ReturnValue);
                pRV = pfn(Cast_i<Index>(ArgsArray)...);
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
