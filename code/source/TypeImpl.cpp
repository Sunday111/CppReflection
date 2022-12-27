#include "TypeImpl.hpp"

#include "FunctionImpl.hpp"
#include "FieldImpl.hpp"

#include <cassert>

namespace cppreflection::detail
{
    TypeImpl::TypeImpl() = default;
    TypeImpl::~TypeImpl() = default;

    std::string_view TypeImpl::GetName() const {
        return std::string_view(m_name.c_str(), m_name.size());
    }

    void TypeImpl::SetName(const std::string_view& name) {
        m_name = name.data();
    }

    size_t TypeImpl::AddField(Field* field) {
        m_fields.push_back(field);
        return m_fields.size() - 1;
    }

    size_t TypeImpl::AddMethod(Function* method) {
        m_methods.push_back(method);
        return m_methods.size() - 1;
    }

    size_t TypeImpl::GetInstanceSize() const {
        return m_instanceSize;
    }

    void TypeImpl::SetInstanceSize(size_t instanceSize) {
        assert(m_instanceSize == 0);
        m_instanceSize = instanceSize;
    }

    void TypeImpl::SetFlags(TypeFlag flags) {
        m_flags = flags;
    }

    cppreflection::TypeFlag TypeImpl::GetFlags() const {
        return m_flags;
    }

    void TypeImpl::SetSpecialMembers(const TypeSpecialMembers& specialMembers) {
        m_specialMembers = specialMembers;
    }

    const cppreflection::TypeSpecialMembers& TypeImpl::GetSpecialMembers() const {
        return m_specialMembers;
    }

    void TypeImpl::SetComparisonOperators(const TypeComparisonOperators& comparisonOperators) {
        m_comparisonOperators = comparisonOperators;
    }

    const cppreflection::TypeComparisonOperators& TypeImpl::GetComparisonOperators() const {
        return m_comparisonOperators;
    }

    std::span<const Field* const> TypeImpl::GetFields() const {
        return m_fields;
    }

    std::span<const Function* const> TypeImpl::GetMethods() const {
        return m_methods;
    }

    const edt::GUID& TypeImpl::GetGuid() const {
        return m_guid;
    }

    void TypeImpl::SetGUID(const edt::GUID& guid) {
        m_guid = guid;
    }

}

namespace cppreflection
{
    CPP_REFLECTION_API Type* AllocType() {
        return new detail::TypeImpl();
    }
}
