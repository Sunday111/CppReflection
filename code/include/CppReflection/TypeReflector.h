#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Type.h"

#include "Detail/FieldReflector.h"
#include "Detail/FunctionReflector.h"
#include "Detail/MakeTypeComparisonOperators.h"
#include "Detail/MakeTypeSpecialMembers.h"

namespace cppreflection
{
    template<typename T>
    class TypeReflector
    {
    public:
        TypeReflector();

        void SetName(const char* name);

        template<auto pfn>
        void AddMethod(const char* name);

        template<auto pfield>
        void AddField(const char* name);

        Type* GetType() const;

    private:
        Type* m_type = nullptr;
    };

    template<typename T>
    Type* TypeReflector<T>::GetType() const {
        return m_type;
    }

    template<typename T>
    void TypeReflector<T>::SetName(const char* name) {
        m_type->SetName(name);
    }

    template<typename T>
    TypeReflector<T>::TypeReflector() {
        m_type = AllocType();
        m_type->SetSpecialMembers(detail::MakeTypeSpecialMembers<std::decay_t<T>>());
        m_type->SetComparisonOperators(detail::MakeTypeComparisonOperators<std::decay_t<T>>());
        m_type->SetInstanceSize(sizeof(T));
    }

    template<typename T>
    template<auto pfn>
    void TypeReflector<T>::AddMethod(const char* name) {
        detail::FunctionReflector<pfn> functionReflector;
        functionReflector.SetName(name);
        m_type->AddMethod(functionReflector.StealFunction());
    }

    template<typename T>
    template<auto pfield>
    void TypeReflector<T>::AddField(const char* name) {
        detail::FieldReflector<pfield> fieldReflector;
        fieldReflector.SetName(name);
        m_type->AddField(fieldReflector.StealField());
    }
}
