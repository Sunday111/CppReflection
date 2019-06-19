#include "FunctionImpl.h"
#include "EverydayTools/Array/ArrayViewVector.h"

namespace cppreflection::detail
{
    edt::StringView FunctionImpl::GetName() const {
        return edt::StringView(m_name.c_str(), m_name.size());
    }

    void FunctionImpl::SetName(const edt::StringView& name) {
        m_name = name.GetData();
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

    edt::SparseArrayView<const Type* const> FunctionImpl::GetArguments() const {
        return edt::MakeArrayView(m_argumentTypes);
    }
}


namespace cppreflection
{
    CPP_REFLECTION_API Function* AllocFunction() {
        return new detail::FunctionImpl();
    }
}