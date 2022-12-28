#include <array>
#include <iostream>
#include <string>
#include <string_view>

#include "CppReflection/CallReflectedFunction.hpp"
#include "CppReflection/GetStaticTypeInfo.hpp"
#include "CppReflection/GetTypeInfo.hpp"
#include "CppReflection/PrimitiveTypeReflection.hpp"
#include "CppReflection/Reflector/TypeReflector.hpp"
#include "CppReflection/StaticType/class.hpp"
#include "CppReflection/StaticType/enum.hpp"
#include "gtest/gtest.h"

enum class ExampleEnum {
  EntryA,
  EntryB,
  EntryC,
  EntryD,
  EntryE,
  EntryF,
  EntryG
};

namespace cppreflection {
template <>
struct TypeReflectionProvider<ExampleEnum> {
  [[nodiscard]] inline constexpr static auto ReflectType() {
    return StaticEnumTypeInfo<ExampleEnum>(
               "ExampleEnum",
               edt::GUID::Create("0706BBE6-79CC-425C-812E-5ABDDC52DCAD"))
        .Value(ExampleEnum::EntryA, "EntryA")
        .Value(ExampleEnum::EntryB, "EntryB")
        .Value(ExampleEnum::EntryC, "EntryC")
        .Value(ExampleEnum::EntryD, "EntryD")
        .Value(ExampleEnum::EntryE, "EntryE")
        .Value(ExampleEnum::EntryF, "EntryF")
        .Value(ExampleEnum::EntryG, "EntryG");
  }
};

}  // namespace cppreflection

struct ExampleStruct {
  int field_int;
  float field_float;

  constexpr int Foo(int arg) const { return field_int * arg; }
  int Bar() {}

  [[nodiscard]] inline constexpr static auto ReflectType() {
    return cppreflection::StaticClassTypeInfo<ExampleStruct>(
               "ExampleStruct",
               edt::GUID::Create("3F1144D7-97A8-40E8-AD83-58CDC61B4815"))
        .Field<"field_int", &ExampleStruct::field_int>()
        .Field<"field_float", &ExampleStruct::field_float>()
        .Method<"Foo", &ExampleStruct::Foo>()
        .Method<"Bar", &ExampleStruct::Bar>();
  }
};

TEST(CppReflectionTest, StaticEnumerationInfo) {
  constexpr const auto example_ti =
      cppreflection::GetStaticTypeInfo<ExampleEnum>();
  static_assert(example_ti.ToString(ExampleEnum::EntryA) == "EntryA");
  static_assert(example_ti.FromString("EntryA") == ExampleEnum::EntryA);

  static_assert(example_ti.ToString(ExampleEnum::EntryB) == "EntryB");
  static_assert(example_ti.FromString("EntryB") == ExampleEnum::EntryB);

  static_assert(example_ti.ToString(ExampleEnum::EntryC) == "EntryC");
  static_assert(example_ti.FromString("EntryC") == ExampleEnum::EntryC);

  static_assert(example_ti.ToString(ExampleEnum::EntryD) == "EntryD");
  static_assert(example_ti.FromString("EntryD") == ExampleEnum::EntryD);

  static_assert(example_ti.ToString(ExampleEnum::EntryE) == "EntryE");
  static_assert(example_ti.FromString("EntryE") == ExampleEnum::EntryE);

  static_assert(example_ti.ToString(ExampleEnum::EntryF) == "EntryF");
  static_assert(example_ti.FromString("EntryF") == ExampleEnum::EntryF);

  static_assert(example_ti.ToString(ExampleEnum::EntryG) == "EntryG");
  static_assert(example_ti.FromString("EntryG") == ExampleEnum::EntryG);
}

TEST(CppReflectionTest, StaticStructureInfo) {
  constexpr const auto example_ti =
      cppreflection::GetStaticTypeInfo<ExampleStruct>();
  static_assert(example_ti.HasField("field_int"));
  static_assert(!example_ti.HasField("field_hint"));

  static_assert(example_ti.HasMethod("Foo"));
  static_assert(!example_ti.HasMethod("Fooo"));

  constexpr ExampleStruct obj{.field_int = 11, .field_float = 1.0f};

  // Find and call method
  constexpr auto method_ptr = example_ti.template GetMethod<"Foo">();
  static_assert(((obj.*method_ptr)(10)) == 110);

  // Find field and get value
  constexpr auto field_ptr = example_ti.template GetField<"field_int">();
  static_assert((obj.*field_ptr) == 11);
}