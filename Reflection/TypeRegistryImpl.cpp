#include "TypeRegistryImpl.h"

namespace edt::reflection
{
    TypeRegistryImpl& TypeRegistryImpl::Instance()
    {
        static TypeRegistryImpl instance;
        return instance;
    }

    const edt::reflection::TypeInfo* TypeRegistryImpl::GetTypeInfo(size_t index) const
    {
        return m_types[index].get();
    }

    size_t TypeRegistryImpl::GetTypesCount() const
    {
        return m_types.size();
    }

}
