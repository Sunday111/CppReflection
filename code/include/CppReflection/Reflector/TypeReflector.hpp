#pragma once

#include "../Detail/MakeTypeComparisonOperators.hpp"
#include "../Detail/MakeTypeSpecialMembers.hpp"
#include "../Type.hpp"

#include "FieldReflector.hpp"
#include "FunctionReflector.hpp"

namespace cppreflection
{
    template<typename T>
    class TypeReflector
    {
    public:
        TypeReflector();

        void SetName(const std::string_view& name);

        void SetGUID(const edt::GUID& guid);

        template<auto pfn>
        void AddMethod(const std::string_view& name);

        template<auto pfield>
        void AddField(const std::string_view& name);

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
    void TypeReflector<T>::SetName(const std::string_view& name) {
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
    void TypeReflector<T>::AddMethod(const std::string_view& name) {
        detail::FunctionReflector<pfn> functionReflector;
        functionReflector.SetName(name);
        m_type->AddMethod(functionReflector.StealFunction());
    }

    template<typename T>
    template<auto pfield>
    void TypeReflector<T>::AddField(const std::string_view& name) {
        detail::FieldReflector<pfield> fieldReflector;
        fieldReflector.SetName(name);
        m_type->AddField(fieldReflector.StealField());
    }
}
