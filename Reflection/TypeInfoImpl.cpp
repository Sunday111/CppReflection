#include "TypeInfoImpl.h"
#include "ReflectedFunctionImpl.h"

namespace edt::reflection
{
    size_t TypeInfoImpl::GetMethodsCount() const {
        return m_methods.size();
    }

    const ReflectedFunction* TypeInfoImpl::GetMethod(size_t index) const {
        if (m_methods.size() > index) {
            return m_methods[index].get();
        }
        return nullptr;
    }

    const char* TypeInfoImpl::GetTypeName() const {
        return m_name.c_str();
    }

    void TypeInfoImpl::SetName(const char* name) {
        m_name = name;
    }

    TypeInfoImpl::TypeInfoImpl(TypeInfoImpl&&) = default;
    TypeInfoImpl::TypeInfoImpl() = default;
    TypeInfoImpl::~TypeInfoImpl() = default;
}
