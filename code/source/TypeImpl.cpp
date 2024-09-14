#include "TypeImpl.hpp"

#include <cassert>
#include <stdexcept>

#include "CppReflection/TypeRegistry.hpp"
#include "FieldImpl.hpp"
#include "FunctionImpl.hpp"

namespace cppreflection::detail
{
TypeImpl::TypeImpl() = default;
TypeImpl::~TypeImpl() = default;

std::string_view TypeImpl::GetName() const
{
    return std::string_view(m_name.c_str(), m_name.size());
}

void TypeImpl::SetName(const std::string_view& name)
{
    m_name = name.data();
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

std::span<const Field* const> TypeImpl::GetFields() const
{
    return m_fields;
}

std::span<const Function* const> TypeImpl::GetMethods() const
{
    return m_methods;
}

const edt::GUID& TypeImpl::GetGuid() const
{
    return m_guid;
}

void TypeImpl::SetGUID(const edt::GUID& guid)
{
    m_guid = guid;
}

bool TypeImpl::IsA(edt::GUID type_guid) const
{
    if (m_guid == type_guid)
    {
        return true;
    }

    auto type_registry = GetTypeRegistry();
    if ((m_flags & TypeFlag::Class) == TypeFlag::None)
    {
        std::optional<edt::GUID> parent = m_base_class_guid;
        while (parent.has_value())
        {
            if (*parent == type_guid)
            {
                return true;
            }

            const Type* parent_info = type_registry->GetType(*parent);
            parent = parent_info->GetBaseClass();
        }
    }

    return false;
}

std::optional<edt::GUID> TypeImpl::GetBaseClass() const
{
    return m_base_class_guid;
}

void TypeImpl::SetBaseClass(edt::GUID base_class_guid)
{
    assert(!m_base_class_guid.has_value());
    m_base_class_guid = base_class_guid;
}

}  // namespace cppreflection::detail

namespace cppreflection
{
CPP_REFLECTION_API Type* AllocType()
{
    return new detail::TypeImpl();
}
}  // namespace cppreflection
