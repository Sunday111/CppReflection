#pragma once

#include <memory>
#include <vector>

#include "CppReflection/Common.h"
#include "TypeComparisonOperators.h"
#include "TypeFlag.h"
#include "TypeSpecialMembers.h"

namespace cppreflection
{
    class Field;
    class Function;

    class Type
    {
    public:
        [[nodiscard]]
        virtual size_t GetInstanceSize() const = 0;

        virtual void SetInstanceSize(size_t instanceSize) = 0;

        [[nodiscard]]
        virtual const char* GetName() const = 0;

        virtual void SetName(const char* name) = 0;

        [[nodiscard]]
        virtual size_t GetMethodsCount() const = 0;

        virtual size_t AddMethod(Function* function) = 0;

        [[nodiscard]]
        virtual const Function* GetMethod(size_t index) const = 0;

        [[nodiscard]]
        virtual size_t GetFieldsCount() const = 0;

        virtual size_t AddField(Field* field) = 0;

        [[nodiscard]]
        virtual const Field* GetField(size_t index) const = 0;

        virtual void SetFlags(TypeFlag flags) = 0;

        [[nodiscard]]
        virtual TypeFlag GetFlags() const = 0;

        virtual void SetSpecialMembers(const TypeSpecialMembers& specialMembers) = 0;

        [[nodiscard]]
        virtual const TypeSpecialMembers& GetSpecialMembers() const = 0;

        virtual void SetComparisonOperators(const TypeComparisonOperators& comparisonOperators) = 0;

        [[nodiscard]]
        virtual const TypeComparisonOperators& GetComparisonOperators() const = 0;

        //
        virtual ~Type() = default;

    public:
    };

    CPP_REFLECTION_API Type* AllocType();
}
