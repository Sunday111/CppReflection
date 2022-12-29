#pragma once

#include <algorithm>
#include <array>
#include <stdexcept>
#include <string_view>

#include "EverydayTools/GUID.hpp"

namespace cppreflection {

template <typename T>
class TypeReflector;

template <typename T>
struct StaticFundamentalTypeInfo {
  constexpr StaticFundamentalTypeInfo(std::string_view in_type_name,
                                      edt::GUID in_guid)
      : type_name(in_type_name), guid(in_guid) {}

  edt::GUID guid;
  std::string_view type_name;
};

template <typename Test>
struct IsStaticFundamentalTypeInfoTrait : std::false_type {};

template <typename T>
struct IsStaticFundamentalTypeInfoTrait<StaticFundamentalTypeInfo<T>>
    : std::true_type {};

template <typename Test>
inline constexpr bool is_static_fundamental_type_info_v =
    IsStaticFundamentalTypeInfoTrait<Test>::value;

template <typename Test>
concept IsStaticFundamentalTypeInfo = is_static_fundamental_type_info_v<Test>;

}  // namespace cppreflection

namespace cppreflection::detail {
template <IsStaticFundamentalTypeInfo StaticEnumInfoT, typename T>
void StaticToDynamic(StaticEnumInfoT static_type_info,
                     TypeReflector<T>& dynamic_type_info) {
  dynamic_type_info.SetName(static_type_info.type_name);
  dynamic_type_info.SetGUID(static_type_info.guid);
}
}  // namespace cppreflection::detail