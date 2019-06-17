#pragma once

#include "../TypeRegistry.h"
#include "../TypeReflector.h"

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

    private:
        std::vector<std::unique_ptr<TypeImpl>> m_types;
    };

    template<typename T>
    TypeReflector<T>& TypeRegistryImpl::Register() {
        m_types.push_back(std::make_unique<TypeReflector<T>>());
        return static_cast<TypeReflector<T>&>(*m_types.back().get());
    }
}
