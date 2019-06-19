#pragma once

#include <cassert>
#include "../Detail/FieldTraits.h"
#include "../Field.h"
#include "EverydayTools/UnusedVar.h"

namespace cppreflection
{
    template<typename T>
    const Type* GetTypeInfo();
}

namespace cppreflection::detail
{
    template<auto pField>
    class FieldReflector
    {
    public:
        using FieldTraits = FieldPointerTraits<pField>;

        FieldReflector() {
            m_field = AllocField();
            using Traits = FieldPointerTraits<pField>;
            using Field = typename Traits::Field;
            m_field->SetType(GetTypeInfo<Field>());

            using Traits = FieldPointerTraits<pField>;
            if constexpr (Traits::IsStatic()) {
                m_field->SetValueGetter([](void* instance) -> void* {
                    UnusedVar(instance);
                    return pField;
                });
            }
            else {
                m_field->SetValueGetter([](void* instance) -> void* {
                    assert(instance != nullptr);
                    using Class = typename Traits::Class;
                    auto casted = reinterpret_cast<Class*>(instance);
                    return &(casted->*pField);
                });
            }
        }

        void SetName(const edt::StringView& name) {
            m_field->SetName(name);
        }

        Field* StealField() {
            Field* temp = m_field;
            m_field = nullptr;
            return temp;
        }

    private:
        Field* m_field = nullptr;
    };
}

