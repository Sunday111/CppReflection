#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Type.h"

#include "Detail/TypeImpl.h"
#include "Detail/FieldReflector.h"
#include "Detail/FunctionReflector.h"
#include "Detail/MakeTypeComparisonOperators.h"
#include "Detail/MakeTypeSpecialMembers.h"

namespace cppreflection
{
    template<typename T>
    class TypeReflector : public detail::TypeImpl
    {
    public:
        TypeReflector();

        virtual size_t GetInstanceSize() const override;

        virtual TypeFlag GetFlags() const;

        template<auto pfn>
        void AddMethod(const char* name);

        template<auto pfield>
        void AddField(const char* name);
    };

    template<typename T>
    TypeReflector<T>::TypeReflector()
    {
        specialMembers = detail::MakeTypeSpecialMembers<std::decay_t<T>>();
        comparisonOperators = detail::MakeTypeComparisonOperators<std::decay_t<T>>();
    }

    template<typename T>
    size_t TypeReflector<T>::GetInstanceSize() const
    {
        return sizeof(T);
    }

    template<typename T>
    TypeFlag TypeReflector<T>::GetFlags() const
    {
        return TypeFlag::None;
    }

    template<typename T>
    template<auto pfn>
    void TypeReflector<T>::AddMethod(const char* name)
    {
        auto ptr = std::make_unique<detail::FunctionReflector<pfn>>();
        ptr->SetName(name);
        m_methods.push_back(std::move(ptr));
    }

    template<typename T>
    template<auto pfield>
    void TypeReflector<T>::AddField(const char* name)
    {
        auto ptr = std::make_unique<detail::FieldReflector<pfield>>();
        ptr->SetName(name);
        m_fields.push_back(std::move(ptr));
    }


}
