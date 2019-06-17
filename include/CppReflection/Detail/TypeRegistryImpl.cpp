#include "TypeRegistryImpl.h"

namespace cppreflection::detail
{
    TypeRegistryImpl& TypeRegistryImpl::Instance() {
        static TypeRegistryImpl instance;
        return instance;
    }

    const cppreflection::Type* TypeRegistryImpl::GetTypeInfo(size_t index) const {
        return m_types[index].get();
    }

    size_t TypeRegistryImpl::GetTypesCount() const {
        return m_types.size();
    }

}
