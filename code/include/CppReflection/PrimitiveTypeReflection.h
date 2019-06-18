#pragma once

#include <cstdint>
#include "GetTypeInfo.h"

namespace cppreflection
{
    inline void ReflectType(TypeReflector<int8_t>& rt) {
        rt.SetName("int8");
    }

    inline void ReflectType(TypeReflector<int16_t>& rt) {
        rt.SetName("int16");
    }

    inline void ReflectType(TypeReflector<int32_t>& rt) {
        rt.SetName("int32");
    }

    inline void ReflectType(TypeReflector<int64_t>& rt) {
        rt.SetName("int64");
    }

    inline void ReflectType(TypeReflector<uint8_t>& rt) {
        rt.SetName("uint8");
    }

    inline void ReflectType(TypeReflector<uint16_t>& rt) {
        rt.SetName("uint16");
    }

    inline void ReflectType(TypeReflector<uint32_t>& rt) {
        rt.SetName("uint32");
    }

    inline void ReflectType(TypeReflector<uint64_t>& rt) {
        rt.SetName("uint64");
    }
}
