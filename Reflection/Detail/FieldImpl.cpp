#include "FieldImpl.h"

namespace edt::reflection::detail
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

}
