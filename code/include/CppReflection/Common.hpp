#pragma once

#ifdef CPP_REFLECTION_SHARED
#if defined(_MSC_VER) && !defined(__clang__)
#define CPP_REFLECTION_EXPORT __declspec(dllexport)
#define CPP_REFLECTION_IMPORT __declspec(dllimport)
#endif

#ifdef __GNUC__
#define CPP_REFLECTION_EXPORT __attribute__((visibility("default")))
#define CPP_REFLECTION_IMPORT __attribute__((visibility("default")))
#endif

#ifdef __clang__
#define CPP_REFLECTION_EXPORT __attribute__((visibility("default")))
#define CPP_REFLECTION_IMPORT __attribute__((visibility("default")))
#endif
#else
#define CPP_REFLECTION_EXPORT
#define CPP_REFLECTION_IMPORT
#endif

#ifdef INSIDE_CPP_REFLECION_LIB
#define CPP_REFLECTION_API CPP_REFLECTION_EXPORT
#else
#define CPP_REFLECTION_API CPP_REFLECTION_IMPORT
#endif
