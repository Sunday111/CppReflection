#pragma once

#include <vector>

#include "CppReflection/TypeRegistry.hpp"
#include "CppReflection/Reflector/TypeReflector.hpp"

namespace cppreflection::detail
{
    class TypeRegistryImpl : public TypeRegistry
    {
    public:
        static TypeRegistryImpl& Instance();
        virtual const Type* GetTypeInfo(size_t index) const override;
        virtual size_t GetTypesCount() const override;
        virtual bool RegisterType(Type* type) override;
        virtual void ClearRegistry() override;
        virtual ~TypeRegistryImpl() override;

    private:
        std::vector<Type*> m_types;
    };
}
