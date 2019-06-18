#include "TypeImpl.h"
#include "FunctionImpl.h"
#include "FieldImpl.h"

#include <cassert>

namespace cppreflection::detail
{
    TypeImpl::TypeImpl() = default;
    TypeImpl::~TypeImpl() = default;

    size_t TypeImpl::GetMethodsCount() const {
        return m_methods.size();
    }

    const Function* TypeImpl::GetMethod(size_t index) const {
        if (m_methods.size() > index) {
            return m_methods[index];
        }
        return nullptr;
    }

    const char* TypeImpl::GetName() const {
        return m_name.c_str();
    }

    void TypeImpl::SetName(const char* name) {
        m_name = name;
    }

    size_t TypeImpl::GetFieldsCount() const {
        return m_fields.size();
    }

    const Field* TypeImpl::GetField(size_t index) const {
        return m_fields[index];
    }

    size_t TypeImpl::AddField(Field* field)
    {
        m_fields.push_back(field);
        return m_fields.size() - 1;
    }

    size_t TypeImpl::AddMethod(Function* method)
    {
        m_methods.push_back(method);
        return m_methods.size() - 1;
    }

    size_t TypeImpl::GetInstanceSize() const
    {
        return m_instanceSize;
    }

    void TypeImpl::SetInstanceSize(size_t instanceSize)
    {
        assert(m_instanceSize == 0);
        m_instanceSize = instanceSize;
    }

    void TypeImpl::SetFlags(TypeFlag flags)
    {
        m_flags = flags;
    }

    cppreflection::TypeFlag TypeImpl::GetFlags() const
    {
        return m_flags;
    }

    void TypeImpl::SetSpecialMembers(const TypeSpecialMembers& specialMembers)
    {
        m_specialMembers = specialMembers;
    }

    const cppreflection::TypeSpecialMembers& TypeImpl::GetSpecialMembers() const
    {
        return m_specialMembers;
    }

    void TypeImpl::SetComparisonOperators(const TypeComparisonOperators& comparisonOperators)
    {
        m_comparisonOperators = comparisonOperators;
    }

    const cppreflection::TypeComparisonOperators& TypeImpl::GetComparisonOperators() const
    {
        return m_comparisonOperators;
    }
}

namespace cppreflection
{
    CPP_REFLECTION_API Type* AllocType() {
        return new detail::TypeImpl();
    }
}
