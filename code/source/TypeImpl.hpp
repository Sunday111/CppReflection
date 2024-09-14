#pragma once

#include <memory>
#include <string>
#include <vector>

#include "CppReflection/Common.hpp"
#include "CppReflection/Type.hpp"

namespace cppreflection::detail
{
class TypeImpl : public Type
{
public:
    TypeImpl();
    TypeImpl(const TypeImpl&) = delete;
    TypeImpl(TypeImpl&&) = delete;
    ~TypeImpl();

    virtual bool IsA(edt::GUID type_guid) const override;
    virtual size_t GetInstanceSize() const override;
    virtual void SetInstanceSize(size_t instanceSize) override;
    virtual size_t GetAlignment() const override { return m_alignment; }
    virtual void SetAlignment(size_t alignment) override { m_alignment = alignment; }
    virtual std::string_view GetName() const override;
    virtual void SetName(const std::string_view& name) override;
    virtual std::span<const Function* const> GetMethods() const override;
    virtual size_t AddMethod(Function* function) override;
    virtual size_t AddField(Field* field) override;
    virtual std::span<const Field* const> GetFields() const override;
    virtual void SetFlags(TypeFlag flags) override;
    virtual TypeFlag GetFlags() const override;
    virtual void SetSpecialMembers(const TypeSpecialMembers& specialMembers) override;
    virtual const TypeSpecialMembers& GetSpecialMembers() const override;
    virtual void SetComparisonOperators(const TypeComparisonOperators& comparisonOperators) override;
    virtual const TypeComparisonOperators& GetComparisonOperators() const override;
    virtual const edt::GUID& GetGuid() const override;
    virtual void SetGUID(const edt::GUID& guid) override;
    virtual std::optional<edt::GUID> GetBaseClass() const override;
    virtual void SetBaseClass(edt::GUID base_class_guid) override;

private:
    edt::GUID m_guid;
    std::optional<edt::GUID> m_base_class_guid;
    TypeFlag m_flags = TypeFlag::None;
    size_t m_instanceSize = 0;
    size_t m_alignment = 0;
    std::string m_name;
    std::vector<Field*> m_fields;
    std::vector<Function*> m_methods;
    TypeSpecialMembers m_specialMembers;
    TypeComparisonOperators m_comparisonOperators;
};
}  // namespace cppreflection::detail
