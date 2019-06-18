#pragma once

#ifdef INSIDE_CPP_REFLECION_LIB
    #define CPP_REFLECTION_API __declspec(dllexport)
#else
    #define CPP_REFLECTION_API __declspec(dllimport)
#endif
