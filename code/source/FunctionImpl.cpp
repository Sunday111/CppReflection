#include "FunctionImpl.h"

namespace cppreflection::detail
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

    size_t FunctionImpl::AddArgumentType(const Type* argumentType) {
        m_argumentTypes.push_back(argumentType);
        return m_argumentTypes.size() - 1;
    }

    void FunctionImpl::SetCaller(Caller caller) {
        m_caller = caller;
    }

    void FunctionImpl::Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const {
        m_caller(Object, ReturnValue, ArgsArray, ArgsArraySize);
    }
}


namespace cppreflection
{
    CPP_REFLECTION_API Function* AllocFunction() {
        return new detail::FunctionImpl();
    }
}