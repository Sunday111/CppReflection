#pragma once

#include <string>
#include <vector>
#include <memory>

#include "CppReflection/Common.h"
#include "CppReflection/Type.h"

namespace cppreflection::detail
{
    class  TypeImpl : public Type
    {
    public:
        TypeImpl();
        TypeImpl(const TypeImpl&) = delete;
        TypeImpl(TypeImpl&&) = delete;
        ~TypeImpl();

        virtual size_t GetInstanceSize() const override;
        virtual void SetInstanceSize(size_t instanceSize) override;
        virtual const char* GetName() const override;
        virtual void SetName(const char* name) override;
        virtual size_t GetMethodsCount() const override;
        virtual size_t AddMethod(Function* function) override;
        virtual const Function* GetMethod(size_t index) const override;
        virtual size_t GetFieldsCount() const override;
        virtual size_t AddField(Field* field) override;
        virtual const Field* GetField(size_t index) const override;
        virtual void SetFlags(TypeFlag flags) override;
        virtual TypeFlag GetFlags() const override;
        virtual void SetSpecialMembers(const TypeSpecialMembers& specialMembers) override;
        virtual const TypeSpecialMembers& GetSpecialMembers() const override;
        virtual void SetComparisonOperators(const TypeComparisonOperators& comparisonOperators) override;
        virtual const TypeComparisonOperators& GetComparisonOperators() const override;

    private:
        TypeFlag m_flags = TypeFlag::None;
        size_t m_instanceSize = 0;
        std::string m_name;
        std::vector<Field*> m_fields;
        std::vector<Function*> m_methods;
        TypeSpecialMembers m_specialMembers;
        TypeComparisonOperators m_comparisonOperators;
    };
}
