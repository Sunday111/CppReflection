#pragma once

#include <cassert>
#include "ReflectedFunctionImpl.h"
#include "Detail/FunctionPoinerTraits.h"

namespace edt::reflection
{
	template<typename T>
	const TypeInfo* GetTypeInfo();
}

namespace edt::reflection::detail
{
    template<auto pfn>
    class FunctionReflector : public ReflectedFunctionImpl
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
            return *reinterpret_cast<NoRef*>(rawArg);
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

    template<auto pfn>
    template<size_t... Index>
	void FunctionReflector<pfn>::Call_i(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize, std::index_sequence<Index...>) const {
		assert(ArgsArraySize >= std::tuple_size_v<typename FnReflector::Arguments>);
        using ReturnType = typename FnReflector::ReturnType;
        if constexpr (FnReflector::IsMethod()) {
            using Class = typename FnReflector::Class;
			assert(Object != nullptr);
            auto pObject = reinterpret_cast<Class*>(Object);
            if constexpr (std::is_same_v<void, ReturnType>) {
                // Method without return type
                (pObject->*pfn)(CastArg_i<Index>(ArgsArray)...);
            }
            else {
                // Method with with some return type
				assert(ReturnValue != nullptr);
				if constexpr (std::is_reference_v<ReturnType>) {
					// Return type is reference (expect pointer to pointer here)
					using NoRef = std::remove_reference_t<ReturnType>;
					auto ppRV = reinterpret_cast<NoRef**>(ReturnValue);
					*ppRV = &(pObject->*pfn)(CastArg_i<Index>(ArgsArray)...);
				}
				else {
					auto& RV = CastArg_t<ReturnType>(ReturnValue);
					RV = (pObject->*pfn)(CastArg_i<Index>(ArgsArray)...);
				}
            }
        }
        else {
            if constexpr (std::is_same_v<void, ReturnType>) {
                // free function without return type
                pfn(CastArg_i<Index>(ArgsArray)...);
            }
            else {
				// free function with some return type
				assert(ReturnValue != nullptr);
				if constexpr (std::is_reference_v<ReturnType>) {
					// Return type is reference (expect pointer to pointer here)
					using NoRef = std::remove_reference_t<ReturnType>;
					auto ppRV = reinterpret_cast<NoRef**>(ReturnValue);
					*ppRV = pfn(CastArg_i<Index>(ArgsArray)...);
				}
				else {
					auto& pRV = CastArg_t<ReturnType>(ReturnValue);
					pRV = pfn(CastArg_i<Index>(ArgsArray)...);
				}
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
