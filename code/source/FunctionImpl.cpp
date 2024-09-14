#include "FunctionImpl.hpp"

namespace cppreflection::detail
{
std::string_view FunctionImpl::GetName() const
{
    return std::string_view(m_name.c_str(), m_name.size());
}

void FunctionImpl::SetName(const std::string_view& name)
{
    m_name = name.data();
}

const Type* FunctionImpl::GetReturnType() const
{
    return m_returnType;
}

void FunctionImpl::SetReturnType(const Type* type)
{
    m_returnType = type;
}

const Type* FunctionImpl::GetObjectType() const
{
    return m_objectType;
}

void FunctionImpl::SetObjectType(const Type* type)
{
    m_objectType = type;
}

size_t FunctionImpl::AddArgumentType(const Type* argumentType)
{
    m_argumentTypes.push_back(argumentType);
    return m_argumentTypes.size() - 1;
}

void FunctionImpl::SetCaller(Caller caller)
{
    m_caller = caller;
}

void FunctionImpl::Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const
{
    m_caller(Object, ReturnValue, ArgsArray, ArgsArraySize);
}

std::span<const Type* const> FunctionImpl::GetArguments() const
{
    return m_argumentTypes;
}
}  // namespace cppreflection::detail

namespace cppreflection
{
CPP_REFLECTION_API Function* AllocFunction()
{
    return new detail::FunctionImpl();
}
}  // namespace cppreflection