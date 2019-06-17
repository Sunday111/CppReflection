#pragma once

#include "EverydayTools/Bitset/EnumBitset.h"

namespace edt::reflection
{
    enum class TypeFlag
    {
        None = 0,
        Common = (1 << 0),
        Number = (1 << 1),
        Enumeration = (1 << 3),
        Class = (1 << 4),
    };
}

namespace edt
{
    template<>
    struct enable_enum_bitset<edt::reflection::TypeFlag>
    {
        static constexpr bool value = true;
    };
}
