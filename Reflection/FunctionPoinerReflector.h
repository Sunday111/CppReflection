#pragma once

#include "FunctionTypeReflector.h"

namespace edt::reflection
{
    template<auto pfn>
    struct FunctionPointerReflector
        : public FunctionTypeReflector<decltype(pfn)>
    {
    };
}
