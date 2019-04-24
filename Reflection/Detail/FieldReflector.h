#pragma once

#include <cassert>
#include "FieldImpl.h"
#include "FieldTraits.h"
#include "UnusedVar.h"

namespace edt::reflection
{
    template<typename T>
    const Type* GetTypeInfo();
}

namespace edt::reflection::detail
{
    template<auto pField>
    class FieldReflector : public FieldImpl
    {
    public:
        using FieldTraits = FieldPointerTraits<pField>;

        FieldReflector() {
            using Traits = FieldPointerTraits<pField>;
            using Field = typename Traits::Field;
            SetType(GetTypeInfo<Field>());
        }

        virtual void* GetValue(void* instance) const override {
            using Traits = FieldPointerTraits<pField>;
            if constexpr (Traits::IsStatic()) {
                UnusedVar(instance);
                return pField;
            }
            else {
                assert(instance != nullptr);
                using Class = typename Traits::Class;
                auto casted = reinterpret_cast<Class*>(instance);
                return &(casted->*pField);
            }
        }
    };
}

