#pragma once

#include "EverydayTools/Array/ArrayView.h"
#include "EverydayTools/Array/StringView.h"
#include "EverydayTools/GUID.h"

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
        /* Returns size (in bytes) of type instance
         */
        [[nodiscard]]
        virtual size_t GetInstanceSize() const = 0;

        /* Name of type
         */
        [[nodiscard]]
        virtual edt::StringView GetName() const = 0;

        /* Type methods (including static methods)
         */
        [[nodiscard]]
        virtual edt::SparseArrayView<const Function* const> GetMethods() const = 0;

        /* Type fields (including static fields)
         */
        [[nodiscard]]
        virtual edt::SparseArrayView<const Field* const> GetFields() const = 0;

        /* Type flags
         */
        [[nodiscard]]
        virtual TypeFlag GetFlags() const = 0;

        /* Type special members
         */
        [[nodiscard]]
        virtual const TypeSpecialMembers& GetSpecialMembers() const = 0;

        /* Comparison operators for type
         */
        [[nodiscard]]
        virtual const TypeComparisonOperators& GetComparisonOperators() const = 0;

        /* Type Guid
         */
        [[nodiscard]]
        virtual const edt::GUID& GetGuid() const = 0;

        /* Adds method to type/ Should not be null.
         * Returns method index in internal methods array.
         */
        virtual size_t AddMethod(Function* function) = 0;

        /* Adds type field. Should not be null.
         * Returns fields index in internal fields array.
         */
        virtual size_t AddField(Field* field) = 0;

        /* Sets type flags
         */
        virtual void SetFlags(TypeFlag flags) = 0;

        /* Sets size (in bytes) of type instance
         */
        virtual void SetInstanceSize(size_t instanceSize) = 0;

        /* Sets type name
         */
        virtual void SetName(const edt::StringView& name) = 0;

        /* Sets type special members
         */
        virtual void SetSpecialMembers(const TypeSpecialMembers& specialMembers) = 0;

        /* Sets type comparison operators
         */
        virtual void SetComparisonOperators(const TypeComparisonOperators& comparisonOperators) = 0;

        /* Sets type GUID
         */
        virtual void SetGUID(const edt::GUID& guid) = 0;

        //
        virtual ~Type() = default;
    };

    CPP_REFLECTION_API Type* AllocType();
}
