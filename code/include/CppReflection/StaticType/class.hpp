#pragma once

#include <algorithm>
#include <array>
#include <stdexcept>
#include <string_view>

#include "EverydayTools/Template/StringLiteral.h"

namespace cppreflection {

template <edt::StringLiteral name, auto object>
struct NamedObject {
  [[nodiscard]] inline constexpr std::string_view GetName() const {
    return name.GetView();
  }
  [[nodiscard]] inline constexpr auto GetObject() const { return object; }
};

template <NamedObject... objects>
struct NamedObjectsCollection {
  template <NamedObject new_element>
  using Add = NamedObjectsCollection<objects..., new_element>;

  template <size_t index>
  using AtIndex = std::tuple_element_t<index, std::tuple<decltype(objects)...>>;

  [[nodiscard]] inline static constexpr bool Contains(std::string_view name) {
    return [&]<size_t... indices>(std::index_sequence<indices...>) {
      return (false || ... || (AtIndex<indices>{}.GetName() == name));
    }
    (std::make_index_sequence<sizeof...(objects)>());
  }

  template <edt::StringLiteral name>
  [[nodiscard]] inline static constexpr auto GetByName() {
    return GetByNameImpl<name, 0>();
  }

  template <edt::StringLiteral name, size_t index>
  [[nodiscard]] inline static constexpr auto GetByNameImpl() {
    if constexpr (index == sizeof...(objects)) {
      throw std::runtime_error("Cannot find object by name");
    } else {
      constexpr auto current_named_object = AtIndex<index>{};
      if constexpr (AtIndex<index>{}.GetName() == name.GetView()) {
        return current_named_object.GetObject();
      } else {
        return GetByNameImpl<name, index + 1>();
      }
    }
  }
};

template <typename T,
          NamedObjectsCollection methods = NamedObjectsCollection<>{},
          NamedObjectsCollection fields = NamedObjectsCollection<>{}>
struct StaticClassTypeInfo {
  constexpr StaticClassTypeInfo(std::string_view in_type_name,
                                edt::GUID in_guid)
      : type_name(in_type_name), guid(in_guid) {}

  template <edt::StringLiteral name, auto method>
  [[nodiscard]] inline constexpr auto Method() const {
    using CurrentMethods = decltype(methods);
    using NewMethods =
        CurrentMethods::template Add<NamedObject<name, method>{}>;
    using CurrentFields = decltype(fields);
    return StaticClassTypeInfo<T, NewMethods{}, CurrentFields{}>(type_name,
                                                                 guid);
  }

  template <edt::StringLiteral name, auto field>
  [[nodiscard]] inline constexpr auto Field() const {
    using CurrentMethods = decltype(methods);
    using CurrentFields = decltype(fields);
    using NewFields = CurrentFields::template Add<NamedObject<name, field>{}>;
    return StaticClassTypeInfo<T, CurrentMethods{}, NewFields{}>(type_name,
                                                                 guid);
  }

  template <edt::StringLiteral name>
  [[nodiscard]] inline constexpr auto GetField() const {
    return fields.template GetByName<name>();
  }

  template <edt::StringLiteral name>
  [[nodiscard]] inline constexpr auto GetMethod() const {
    return methods.template GetByName<name>();
  }

  [[nodiscard]] inline constexpr bool HasField(std::string_view name) const {
    return fields.Contains(name);
  }

  [[nodiscard]] inline constexpr bool HasMethod(std::string_view name) const {
    return methods.Contains(name);
  }

  std::string_view type_name;
  edt::GUID guid;
};

template <typename Test>
struct IsStaticClassTypeInfoTrait : std::false_type {};

template <typename T, NamedObjectsCollection methods,
          NamedObjectsCollection fields>
struct IsStaticClassTypeInfoTrait<StaticClassTypeInfo<T, methods, fields>>
    : std::true_type {};

template <typename Test>
inline constexpr bool is_static_class_type_info_v =
    IsStaticClassTypeInfoTrait<Test>::value;

template <typename Test>
concept IsStaticClassTypeInfo = is_static_class_type_info_v<Test>;

}  // namespace cppreflection