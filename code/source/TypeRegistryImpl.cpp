#include "TypeRegistryImpl.hpp"

namespace cppreflection::detail
{
    TypeRegistryImpl& TypeRegistryImpl::Instance() {
        static TypeRegistryImpl instance;
        return instance;
    }

    const Type* TypeRegistryImpl::GetTypeInfo(size_t index) const {
        return m_types[index];
    }

    size_t TypeRegistryImpl::GetTypesCount() const {
        return m_types.size();
    }

    bool TypeRegistryImpl::RegisterType(Type* type)
    {
        m_types.push_back(type);
        return true;
    }

    void TypeRegistryImpl::ClearRegistry()
    {
        for (auto type : m_types) {
            delete type;
        }

        m_types.clear();
    }

    TypeRegistryImpl::~TypeRegistryImpl()
    {
        ClearRegistry();
    }

}

namespace cppreflection
{
    CPP_REFLECTION_API TypeRegistry* GetTypeRegistry()
    {
        return &detail::TypeRegistryImpl::Instance();
    }
}
