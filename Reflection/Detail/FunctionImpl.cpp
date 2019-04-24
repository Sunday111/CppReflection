#include "FunctionImpl.h"

namespace edt::reflection::detail
{
    const char* FunctionImpl::GetName() const {
        return m_name.c_str();
    }

    void FunctionImpl::SetName(const char* name) {
        m_name = name;
    }

    const Type* FunctionImpl::GetReturnType() const {
        return m_returnType;
    }

    void FunctionImpl::SetReturnType(const Type* type) {
        m_returnType = type;
    }

    const Type* FunctionImpl::GetObjectType() const {
        return m_objectType;
    }

    void FunctionImpl::SetObjectType(const Type* type) {
        m_objectType = type;
    }

    size_t FunctionImpl::GetArgumentsCount() const {
        return m_argumentTypes.size();
    }

    const Type* FunctionImpl::GetArgumentType(size_t index) const {
        if (index < m_argumentTypes.size()) {
            return m_argumentTypes[index];
        }

        return nullptr;
    }

    void FunctionImpl::PushArgumentType(const Type* type) {
        m_argumentTypes.push_back(type);
    }
}
