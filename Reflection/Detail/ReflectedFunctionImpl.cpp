#include "ReflectedFunctionImpl.h"

namespace edt::reflection::detail
{
    const char* ReflectedFunctionImpl::GetName() const {
        return m_name.c_str();
    }

    void ReflectedFunctionImpl::SetName(const char* name) {
        m_name = name;
    }

    const TypeInfo* ReflectedFunctionImpl::GetReturnType() const {
        return m_returnType;
    }

    void ReflectedFunctionImpl::SetReturnType(const TypeInfo* type) {
        m_returnType = type;
    }

    const TypeInfo* ReflectedFunctionImpl::GetObjectType() const {
        return m_objectType;
    }

    void ReflectedFunctionImpl::SetObjectType(const TypeInfo* type) {
        m_objectType = type;
    }

    size_t ReflectedFunctionImpl::GetArgumentsCount() const {
        return m_argumentTypes.size();
    }

    const TypeInfo* ReflectedFunctionImpl::GetArgumentType(size_t index) const {
        if (index < m_argumentTypes.size()) {
            return m_argumentTypes[index];
        }

        return nullptr;
    }

    void ReflectedFunctionImpl::PushArgumentType(const TypeInfo* type) {
        m_argumentTypes.push_back(type);
    }
}
