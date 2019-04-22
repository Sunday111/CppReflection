#pragma once

#include "FunctionTypeTraits.h"

namespace edt::reflection::detail
{
    template<auto pfn>
    struct FunctionPointerTraits
        : public FunctionTypeTraits<decltype(pfn)>
    {
    };
}
