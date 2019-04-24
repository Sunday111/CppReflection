#include "TypeImpl.h"
#include "FunctionImpl.h"
#include "FieldImpl.h"

namespace edt::reflection::detail
{
    size_t TypeImpl::GetMethodsCount() const {
        return m_methods.size();
    }

    const Function* TypeImpl::GetMethod(size_t index) const {
        if (m_methods.size() > index) {
            return m_methods[index].get();
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
        return m_fields[index].get();
    }

    TypeImpl::TypeImpl(TypeImpl&&) = default;
    TypeImpl::TypeImpl() = default;
    TypeImpl::~TypeImpl() = default;
}
