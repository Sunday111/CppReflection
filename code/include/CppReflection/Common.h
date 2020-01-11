#pragma once

#include "EverydayTools/Preprocessor/ExpotImport.h"

#ifdef INSIDE_CPP_REFLECION_LIB
    #define CPP_REFLECTION_API EXPORT
#else
    #define CPP_REFLECTION_API IMPORT
#endif
