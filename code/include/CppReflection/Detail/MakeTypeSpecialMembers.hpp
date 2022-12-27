#pragma once

#include <type_traits>
#include "../TypeSpecialMembers.hpp"

namespace cppreflection::detail
{
    template<typename T>
    [[nodiscard]]
    constexpr TypeSpecialMembers::DefaultConstructor MakeDefaultConstructor() noexcept {
        if constexpr (!std::is_default_constructible_v<T>) {
            return nullptr;
        }
        else {
            return [](void* object) {
                new (object) T();
            };
        }
    }

    template<typename T>
    [[nodiscard]]
    constexpr TypeSpecialMembers::CopyConstructor MakeCopyConstructor() noexcept {
        if constexpr (!std::is_copy_constructible_v<T>) {
            return nullptr;
        }
        else {
            return [](void* objectToConstruct, const void* referenceObject) {
                new (objectToConstruct) T(*reinterpret_cast<const T*>(referenceObject));
            };
        }
    }

    template<typename T>
    [[nodiscard]]
    constexpr TypeSpecialMembers::MoveConstructor MakeMoveConstructor() noexcept {
        if constexpr (!std::is_move_constructible_v<T>) {
            return nullptr;
        }
        else {
            return [](void* destinationObject, void* sourceObject) {
                new (destinationObject) T(std::move(*reinterpret_cast<T*>(sourceObject)));
            };
        }
    }

    template<typename T>
    [[nodiscard]]
    constexpr TypeSpecialMembers::CopyAssign MakeCopyAssignOperator() noexcept {
        if constexpr (!std::is_copy_assignable_v<T>) {
            return nullptr;
        }
        else {
            return [](void* destination, const void* source) {
                const T& src = *reinterpret_cast<const T*>(source);
                T& dst = *reinterpret_cast<T*>(destination);
                dst = src;
            };
        }
    }

    template<typename T>
    [[nodiscard]]
    constexpr TypeSpecialMembers::MoveAssign MakeMoveAssignOperator() noexcept {
        if constexpr (!std::is_move_assignable_v<T>) {
            return nullptr;
        }
        else {
            return [](void* destination, void* source) {
                T& src = *reinterpret_cast<T*>(source);
                T& dst = *reinterpret_cast<T*>(destination);
                dst = std::move(src);
            };
        }
    }

    template<typename T>
    [[nodiscard]]
    constexpr TypeSpecialMembers::Destructor MakeDestructor() noexcept {
        if constexpr (!std::is_destructible_v<T>) {
            return nullptr;
        }
        else {
            return [](void* object) {
                T& obj = *reinterpret_cast<T*>(object);
                obj.~T();
            };
        }
    }

    template<typename T>
    [[nodiscard]]
    constexpr TypeSpecialMembers MakeTypeSpecialMembers() {
        TypeSpecialMembers Result{};

        Result.defaultConstructor = MakeDefaultConstructor<T>();
        Result.copyConstructor = MakeCopyConstructor<T>();
        Result.moveConstructor = MakeMoveConstructor<T>();
        Result.copyAssign = MakeCopyAssignOperator<T>();
        Result.moveAssign = MakeMoveAssignOperator<T>();
        Result.destructor = MakeDestructor<T>();

        return Result;
    }
}
