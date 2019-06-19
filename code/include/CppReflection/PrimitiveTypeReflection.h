#pragma once

#include <cstdint>
#include "GetTypeInfo.h"

namespace cppreflection
{
    inline void ReflectType(TypeReflector<int8_t>& rt) {
        rt.SetName("int8");
        rt.SetGUID(edt::GUID::Create("0706BBE6-79CC-425C-812E-5ABDDC52DCAD"));
    }

    inline void ReflectType(TypeReflector<int16_t>& rt) {
        rt.SetName("int16");
        rt.SetGUID(edt::GUID::Create("B88D207C-4BBD-4D81-A70F-F3E9162F044C"));
    }

    inline void ReflectType(TypeReflector<int32_t>& rt) {
        rt.SetName("int32");
        rt.SetGUID(edt::GUID::Create("F8F358DF-D954-4CED-B7EB-0B76F90459AF"));
    }

    inline void ReflectType(TypeReflector<int64_t>& rt) {
        rt.SetName("int64");
        rt.SetGUID(edt::GUID::Create("D143D95D-EEF8-4A32-8DB1-FB326B593F76"));
    }

    inline void ReflectType(TypeReflector<uint8_t>& rt) {
        rt.SetName("uint8");
        rt.SetGUID(edt::GUID::Create("86D0C889-7FEA-45CE-BA4E-020895E750E4"));
    }

    inline void ReflectType(TypeReflector<uint16_t>& rt) {
        rt.SetName("uint16");
        rt.SetGUID(edt::GUID::Create("5AB951D5-91A8-4E2B-B5A8-DE67AA6414F4"));
    }

    inline void ReflectType(TypeReflector<uint32_t>& rt) {
        rt.SetName("uint32");
        rt.SetGUID(edt::GUID::Create("3B9AD7E1-C6AF-4091-AA3A-D6B040A4F261"));
    }

    inline void ReflectType(TypeReflector<uint64_t>& rt) {
        rt.SetName("uint64");
        rt.SetGUID(edt::GUID::Create("F51D1445-C233-4750-86D2-203BBBACB6F1"));
    }
}
