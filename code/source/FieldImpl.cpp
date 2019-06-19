#include "FieldImpl.h"

namespace cppreflection::detail
{
    const Type* FieldImpl::GetType() const {
        return m_type;
    }

    edt::StringView FieldImpl::GetName() const {
        return edt::StringView(m_name.c_str(), m_name.size());
    }

    void FieldImpl::SetName(const edt::StringView& name) {
        m_name = name.GetData();
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