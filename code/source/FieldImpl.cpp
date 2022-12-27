#include "FieldImpl.h"

namespace cppreflection::detail
{
    const Type* FieldImpl::GetType() const {
        return m_type;
    }

    std::string_view FieldImpl::GetName() const {
        return std::string_view(m_name.c_str(), m_name.size());
    }

    void FieldImpl::SetName(const std::string_view& name) {
        m_name = name.data();
    }

    void FieldImpl::SetType(const Type* type) {
        m_type = type;
    }

    void FieldImpl::SetValueGetter(ValueGetter getter)
    {
        m_getter = getter;
    }

    void* FieldImpl::GetValue(void* Object) const
    {
        return m_getter(Object);
    }
}


namespace cppreflection
{
    CPP_REFLECTION_API Field* AllocField() {
        return new detail::FieldImpl();
    }
}