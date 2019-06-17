#pragma once

#include <memory>
#include <vector>

#include "TypeFlag.h"
#include "TypeSpecialMembers.h"
#include "TypeComparisonOperators.h"

namespace cppreflection
{
    class Field;
    class Function;

    class Type
    {
    public:
        [[nodiscard]]
        virtual size_t GetInstanceSize() const = 0;

        [[nodiscard]]
        virtual const char* GetName() const = 0;

        [[nodiscard]]
        virtual size_t GetMethodsCount() const = 0;

        [[nodiscard]]
        virtual const Function* GetMethod(size_t index) const = 0;

        [[nodiscard]]
        virtual size_t GetFieldsCount() const = 0;

        [[nodiscard]]
        virtual const Field* GetField(size_t index) const = 0;

        [[nodiscard]]
        /*constexpr*/ virtual TypeFlag GetFlags() const = 0;

        //
        virtual ~Type() = default;

    public:
        TypeSpecialMembers specialMembers;
        TypeComparisonOperators comparisonOperators;
    };
}
