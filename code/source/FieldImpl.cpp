#include "FieldImpl.h"

namespace cppreflection::detail
{
    const Type* FieldImpl::GetType() const {
        return m_type;
    }

    const char* FieldImpl::GetName() const {
        return m_name.c_str();
    }

    void FieldImpl::SetName(const char* name) {
        m_name = name;
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