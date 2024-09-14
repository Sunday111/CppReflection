#pragma once

#include <string>
#include <vector>

#include "CppReflection/Function.hpp"

namespace cppreflection::detail
{
class FunctionImpl : public Function
{
public:
    virtual void SetReturnType(const Type* type) override;
    virtual const Type* GetReturnType() const override;
    virtual void SetObjectType(const Type* type) override;
    virtual const Type* GetObjectType() const override;
    virtual size_t AddArgumentType(const Type* argumentType) override;
    virtual std::span<const Type* const> GetArguments() const override;
    virtual void SetName(const std::string_view& name) override;
    virtual std::string_view GetName() const override;
    virtual void SetCaller(Caller caller) override;
    virtual void Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const override;

private:
    std::string m_name;
    const Type* m_returnType = nullptr;
    const Type* m_objectType = nullptr;
    std::vector<const Type*> m_argumentTypes;
    Caller m_caller = nullptr;
};
}  // namespace cppreflection::detail
