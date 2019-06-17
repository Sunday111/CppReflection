#pragma once

#pragma once

namespace edt::reflection
{
    class TypeComparisonOperators
    {
    public:
        using Less = bool(*)(const void* lhs, const void* rhs);
        using Equals = bool(*)(const void* a, const void* b);

        Less less = nullptr;
        Equals equals = nullptr;
    };
}
