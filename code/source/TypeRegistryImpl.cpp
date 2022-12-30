#include "TypeRegistryImpl.hpp"

#include <sstream>

namespace cppreflection::detail {
TypeRegistryImpl& TypeRegistryImpl::Instance() {
  static TypeRegistryImpl instance;
  return instance;
}

const Type* TypeRegistryImpl::GetTypeInfo(size_t index) const {
  return m_types[index];
}

size_t TypeRegistryImpl::GetTypesCount() const { return m_types.size(); }

const Type* TypeRegistryImpl::FindType(const edt::GUID& guid) const {
  if (const auto it = m_map.find(guid); m_map.end() != it) {
    return it->second;
  }

  return nullptr;
}

const Type* TypeRegistryImpl::GetType(const edt::GUID& guid) const {
  [[likely]] if (const Type* type = FindType(guid); type != nullptr) {
    return type;
  }

  std::stringstream msg;
  msg << "Type with guid " << guid << " is not registered.";

  throw std::runtime_error(msg.str());
}

bool TypeRegistryImpl::RegisterType(Type* type) {
  m_types.push_back(type);

  return true;
}

bool TypeRegistryImpl::RefreshType(Type* type) {
  const auto guid = type->GetGuid();

  if (m_map.contains(guid)) {
    return false;
  }

  m_map[guid] = type;

  return true;
}

void TypeRegistryImpl::ClearRegistry() {
  for (auto type : m_types) {
    delete type;
  }

  m_types.clear();
  m_map.clear();
}

TypeRegistryImpl::~TypeRegistryImpl() { ClearRegistry(); }

}  // namespace cppreflection::detail

namespace cppreflection {
CPP_REFLECTION_API TypeRegistry* GetTypeRegistry() {
  return &detail::TypeRegistryImpl::Instance();
}
}  // namespace cppreflection
