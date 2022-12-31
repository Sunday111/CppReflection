#pragma once

#include <cassert>

#include "../Function.hpp"
#include "EverydayTools/Template/Signature.hpp"

namespace cppreflection {
template <typename T>
const Type* GetTypeInfo();
}

namespace cppreflection::detail {
template <auto pfn>
class FunctionReflector {
  using Signature = edt::SignatureFromPtr<pfn>;

 public:
  FunctionReflector();

  Function* StealFunction();

  void SetName(const std::string_view& name);

 private:
  template <size_t Index>
  static constexpr decltype(auto) CastArg_i(void** ArgsArray);

  static void Call(void* Object, void* ReturnValue, void** ArgsArray,
                   size_t ArgsArraySize);

  template <size_t... Index>
  static void Call_i(void* Object, void* ReturnValue, void** ArgsArray,
                     size_t ArgsArraySize, std::index_sequence<Index...>);

  template <size_t... Index>
  void InitializeArgs(std::index_sequence<Index...>);

  template <size_t Index>
  void InitializeArg();

  void InitializeCaller() { m_function->SetCaller(Call); }

 private:
  Function* m_function = nullptr;
};

template <auto pfn>
FunctionReflector<pfn>::FunctionReflector() {
  m_function = AllocFunction();

  using ReturnType = typename Signature::Ret;
  if constexpr (!std::is_same_v<ReturnType, void>) {
    m_function->SetReturnType(GetTypeInfo<ReturnType>());
  }

  if constexpr (!Signature::Pure) {
    using Class = typename Signature::Class;
    m_function->SetObjectType(GetTypeInfo<Class>());
  }

  InitializeArgs(std::make_index_sequence<Signature::GetArgsCount()>());
  InitializeCaller();
}
}  // namespace cppreflection::detail

namespace cppreflection::detail {
template <typename T>
inline constexpr decltype(auto) CastArg_t(void* rawArg) {
  if constexpr (std::is_reference_v<T>) {
    using NoRef = std::remove_reference_t<T>;
    if constexpr (std::is_rvalue_reference_v<T>) {
      return std::move(*reinterpret_cast<NoRef*>(rawArg));
    } else {
      return *reinterpret_cast<NoRef*>(rawArg);
    }
  } else {
    return *reinterpret_cast<T*>(rawArg);
  }
}

template <>
inline decltype(auto) CastArg_t<void>(void* rawArg) {
  // assert(!"This hack exist to simplify code but shouldn't be ever called");
  return *reinterpret_cast<int*>(rawArg);
}
}  // namespace cppreflection::detail

namespace cppreflection::detail {
template <auto pfn>
void FunctionReflector<pfn>::SetName(const std::string_view& name) {
  m_function->SetName(name);
}

template <auto pfn>
void FunctionReflector<pfn>::Call(void* Object, void* ReturnValue,
                                  void** ArgsArray, size_t ArgsArraySize) {
  Call_i(Object, ReturnValue, ArgsArray, ArgsArraySize,
         std::make_index_sequence<Signature::GetArgsCount()>());
}

template <auto pfn>
template <size_t Index>
constexpr decltype(auto) FunctionReflector<pfn>::CastArg_i(void** ArgsArray) {
  using Arguments = typename Signature::Args;
  using T = std::tuple_element_t<Index, Arguments>;
  return CastArg_t<T>(ArgsArray[Index]);
}

// Make object that will call function or method in the same way
template <auto pfn>
decltype(auto) WrapMethodCalls([[maybe_unused]] void* Object) {
  using Signature = edt::SignatureFromPtr<pfn>;
  using ReturnType = typename Signature::Ret;
  if constexpr (!Signature::Pure) {
    return [Object](auto&&... args) -> decltype(auto) {
      using Class = typename Signature::Class;
      auto pObject = reinterpret_cast<Class*>(Object);
      return static_cast<ReturnType>(
          (pObject->*pfn)(std::forward<decltype(args)>(args)...));
    };
  } else {
    return [](auto&&... args) -> decltype(auto) {
      return static_cast<ReturnType>(
          pfn(std::forward<decltype(args)>(args)...));
    };
  }
}

template <auto pfn>
template <size_t... Index>
void FunctionReflector<pfn>::Call_i(void* Object,
                                    [[maybe_unused]] void* ReturnValue,
                                    void** ArgsArray,
                                    [[maybe_unused]] size_t ArgsArraySize,
                                    std::index_sequence<Index...>) {
  assert(ArgsArraySize >= Signature::GetArgsCount());

  using ReturnType = typename Signature::Ret;
  auto call = [&]() -> decltype(auto) {
    auto f = WrapMethodCalls<pfn>(Object);
    return static_cast<ReturnType>(f(CastArg_i<Index>(ArgsArray)...));
  };

  if constexpr (std::is_same_v<void, ReturnType>) {
    // free function without return type
    call();
  } else {
    // free function with some return type
    assert(ReturnValue != nullptr);
    if constexpr (std::is_reference_v<ReturnType>) {
      using NoRef = std::remove_reference_t<ReturnType>;
      if constexpr (std::is_rvalue_reference_v<ReturnType>) {
        // Return type is rvalue reference
        auto pRV = reinterpret_cast<NoRef*>(ReturnValue);
        // Construct instance in given memory
        new (pRV) NoRef(call());
      } else {
        // Return type is lvalue reference
        auto ppRV = reinterpret_cast<NoRef**>(ReturnValue);
        *ppRV = &call();
      }
    } else {
      // Return type is not reference
      auto& pRV = CastArg_t<ReturnType>(ReturnValue);
      pRV = call();
    }
  }
}

template <auto pfn>
template <size_t... Index>
void FunctionReflector<pfn>::InitializeArgs(std::index_sequence<Index...>) {
  (InitializeArg<Index>(), ...);
}

template <auto pfn>
template <size_t Index>
void FunctionReflector<pfn>::InitializeArg() {
  using Arguments = typename Signature::Args;
  using Argument = std::tuple_element_t<Index, Arguments>;
  auto typeInfo = GetTypeInfo<Argument>();
  m_function->AddArgumentType(typeInfo);
}

template <auto pfn>
Function* FunctionReflector<pfn>::StealFunction() {
  auto temp = m_function;
  m_function = nullptr;
  return temp;
}
}  // namespace cppreflection::detail
