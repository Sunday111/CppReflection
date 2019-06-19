#pragma once

#include <vector>

#include "CppReflection/Function.h"

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
        virtual edt::SparseArrayView<const Type* const> GetArguments() const override;
        virtual void SetName(const edt::StringView& name) override;
        virtual edt::StringView GetName() const override;
        virtual void SetCaller(Caller caller) override;
        virtual void Call(void* Object, void* ReturnValue, void** ArgsArray, size_t ArgsArraySize) const override;

    private:
        std::string m_name;
        const Type* m_returnType = nullptr;
        const Type* m_objectType = nullptr;
        std::vector<const Type*> m_argumentTypes;
        Caller m_caller = nullptr;
    };
}
