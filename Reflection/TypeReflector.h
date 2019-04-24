#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Type.h"

#include "Detail/TypeImpl.h"
#include "Detail/FieldReflector.h"
#include "Detail/FunctionReflector.h"

namespace edt::reflection
{
    template<typename T>
    class TypeReflector : public detail::TypeImpl
    {
    public:
        virtual size_t GetInstanceSize() const override {
            return sizeof(T);
        }

        template<auto pfn>
        void AddMethod(const char* name) {
            auto ptr = std::make_unique<detail::FunctionReflector<pfn>>();
            ptr->SetName(name);
            m_methods.push_back(std::move(ptr));
        }

        template<auto pfield>
        void AddField(const char* name) {
            auto ptr = std::make_unique<detail::FieldReflector<pfield>>();
            ptr->SetName(name);
            m_fields.push_back(std::move(ptr));
        }
    };
}
