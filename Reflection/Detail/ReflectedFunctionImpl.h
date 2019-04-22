#pragma once

#include <vector>

#include "../ReflectedFunction.h"

namespace edt::reflection::detail
{
    class ReflectedFunctionImpl : public ReflectedFunction
    {
    public:
        virtual const char* GetName() const override;
        virtual const TypeInfo* GetReturnType() const override;
        virtual const TypeInfo* GetObjectType() const override;
        virtual size_t GetArgumentsCount() const override;
        virtual const TypeInfo* GetArgumentType(size_t index) const override;

        void SetName(const char* name);
        void SetReturnType(const TypeInfo* type);
        void SetObjectType(const TypeInfo* type);
        void PushArgumentType(const TypeInfo* type);

    private:
        std::string m_name;
        const TypeInfo* m_returnType;
        const TypeInfo* m_objectType;
        std::vector<const TypeInfo*> m_argumentTypes;
    };
}
