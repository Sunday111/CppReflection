#pragma once

#include <algorithm>
#include <array>
#include <sstream>
#include <stdexcept>
#include <string_view>

namespace cppreflection {

template <typename T>
class TypeReflector;

template <typename T>
struct EnumValue {
  T value;
  std::string_view name;
};

template <typename T, size_t num_values = 0>
struct StaticEnumTypeInfo {
  constexpr StaticEnumTypeInfo(std::string_view in_type_name, edt::GUID in_guid)
      : guid(in_guid), type_name(in_type_name) {}

  [[nodiscard]] constexpr auto Value(T value, std::string_view name) const {
    StaticEnumTypeInfo<T, num_values + 1> r(type_name, guid);
    std::copy(values.begin(), values.end(), r.values.begin());
    r.values[num_values].value = value;
    r.values[num_values].name = name;
    return r;
  }

  [[nodiscard]] constexpr std::string_view ToString(T value) const {
    for (const auto& ev : values) {
      if (ev.value == value) {
        return ev.name;
      }
    }

    throw std::runtime_error("Cannot convert value to string");
  }

  [[nodiscard]] constexpr bool TryParse(std::string_view str,
                                        T& out_value) const {
    for (const auto& ev : values) {
      if (ev.name == str) {
        out_value = ev.value;
        return true;
      }
    }

    return false;
  }

  [[nodiscard]] constexpr T Parse(std::string_view str) const {
    T result;
    [[likely]] if (TryParse(str, result)) { return result; }

#if defined(_MSC_VER) && !defined(__clang__)
    std::stringstream msg;
    msg << "Failed to parse " << type_name << " from string \"" << str << "\"";
    throw std::runtime_error(msg.str());
#else
    throw std::runtime_error("Failed to parse enum value");
#endif
  }

  edt::GUID guid;
  std::string_view type_name;
  std::array<EnumValue<T>, num_values> values{};
};

}  // namespace cppreflection

namespace cppreflection::detail {

template <typename Test>
struct IsStaticEnumTypeInfoTrait : std::false_type {};

template <typename T, size_t N>
struct IsStaticEnumTypeInfoTrait<StaticEnumTypeInfo<T, N>> : std::true_type {};

template <typename Test>
inline constexpr bool is_static_enum_type_info_v =
    IsStaticEnumTypeInfoTrait<Test>::value;

template <typename Test>
concept IsStaticEnumTypeInfo = is_static_enum_type_info_v<std::decay_t<Test>>;

template <IsStaticEnumTypeInfo StaticEnumInfoT, typename T>
void StaticToDynamic(StaticEnumInfoT static_type_info,
                     TypeReflector<T>& dynamic_type_info) {
  dynamic_type_info.SetName(static_type_info.type_name);
  dynamic_type_info.SetGUID(static_type_info.guid);
}
}  // namespace cppreflection::detail
