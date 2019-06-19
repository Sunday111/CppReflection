#pragma once

#include "../Detail/MakeTypeComparisonOperators.h"
#include "../Detail/MakeTypeSpecialMembers.h"
#include "../Type.h"

#include "FieldReflector.h"
#include "FunctionReflector.h"

namespace cppreflection
{
    template<typename T>
    class TypeReflector
    {
    public:
        TypeReflector();

        void SetName(const edt::StringView& name);

        void SetGUID(const edt::GUID& guid);

        template<auto pfn>
        void AddMethod(const edt::StringView& name);

        template<auto pfield>
        void AddField(const edt::StringView& name);

        Type* GetType() const;

    private:
        Type* m_type = nullptr;
    };

    template<typename T>
    void cppreflection::TypeReflector<T>::SetGUID(const edt::GUID& guid) {
        m_type->SetGUID(guid);
    }

    template<typename T>
    Type* TypeReflector<T>::GetType() const {
        return m_type;
    }

    template<typename T>
    void TypeReflector<T>::SetName(const edt::StringView& name) {
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
    void TypeReflector<T>::AddMethod(const edt::StringView& name) {
        detail::FunctionReflector<pfn> functionReflector;
        functionReflector.SetName(name);
        m_type->AddMethod(functionReflector.StealFunction());
    }

    template<typename T>
    template<auto pfield>
    void TypeReflector<T>::AddField(const edt::StringView& name) {
        detail::FieldReflector<pfield> fieldReflector;
        fieldReflector.SetName(name);
        m_type->AddField(fieldReflector.StealField());
    }
}
