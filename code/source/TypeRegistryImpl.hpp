#pragma once

#include <unordered_map>
#include <vector>

#include "CppReflection/Reflector/TypeReflector.hpp"
#include "CppReflection/TypeRegistry.hpp"

namespace cppreflection::detail {
class TypeRegistryImpl : public TypeRegistry {
 public:
  static TypeRegistryImpl& Instance();
  virtual const Type* GetTypeInfo(size_t index) const override;
  virtual size_t GetTypesCount() const override;
  virtual const Type* FindType(const edt::GUID& guid) const override;
  virtual const Type* GetType(const edt::GUID& guid) const override;
  virtual bool RegisterType(Type* type) override;
  virtual bool RefreshType(Type* type) override;
  virtual void ClearRegistry() override;
  virtual ~TypeRegistryImpl() override;

 private:
  std::vector<Type*> m_types;
  std::unordered_map<edt::GUID, Type*> m_map;
};
}  // namespace cppreflection::detail
