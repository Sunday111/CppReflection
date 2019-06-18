#pragma once

#include "CppReflection/TypeRegistry.h"
#include "CppReflection/TypeReflector.h"

namespace cppreflection::detail
{
    class TypeRegistryImpl : public TypeRegistry
    {
    public:
        template<typename T>
        TypeReflector<T>& Register();
        static TypeRegistryImpl& Instance();
        virtual const Type* GetTypeInfo(size_t index) const override;
        virtual size_t GetTypesCount() const override;
        virtual bool RegisterType(Type* type) override;
        virtual void ClearRegistry() override;
        virtual ~TypeRegistryImpl() override;

    private:
        std::vector<Type*> m_types;
    };

    template<typename T>
    TypeReflector<T>& TypeRegistryImpl::Register() {
        auto newType = new TypeReflector<T>();
        RegisterType(newType);
        return static_cast<TypeReflector<T>&>(*newType);
    }
}
