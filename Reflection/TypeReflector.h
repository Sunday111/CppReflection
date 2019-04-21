#pragma once

#include <string>
#include <vector>
#include <memory>

#include "TypeInfo.h"
#include "TypeInfoImpl.h"

#include "FunctionReflector.h"

namespace edt::reflection
{
    template<typename T>
    class TypeReflector : public TypeInfoImpl
    {
    public:
        virtual size_t GetInstanceSize() const override {
            return sizeof(T);
        }

        template<auto pfn>
        void AddMethod(const char* name) {
            auto ptr = std::make_unique<FunctionReflector<pfn>>();
            ptr->SetName(name);
            m_methods.push_back(std::move(ptr));
        }
    };
}
