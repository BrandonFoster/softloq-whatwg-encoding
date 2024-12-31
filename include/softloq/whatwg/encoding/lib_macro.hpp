/**
 * @file lib_macro.hpp
 * @author Brandon Foster (https://github.com/BrandonFoster)
 * @brief Contains the macros for building and using the Softloq WHATWG Encoding library correctly.
 * @version 1.0.0 */

#ifndef SOFTLOQ_WHATWG_ENCODING_LIB_MACRO_HPP
#define SOFTLOQ_WHATWG_ENCODING_LIB_MACRO_HPP

// Build Macros //

#if defined(_MSC_VER)
    #define SOFTLOQ_WHATWG_ENCODING_EXPORT __declspec(dllexport)
    #define SOFTLOQ_WHATWG_ENCODING_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    #define SOFTLOQ_WHATWG_ENCODING_EXPORT __attribute__((visibility("default")))
    #define SOFTLOQ_WHATWG_ENCODING_IMPORT
#endif

//--------------//

// Standalone Build //

#if defined(SOFTLOQ_WHATWG_ENCODING_NO_API)
    #define SOFTLOQ_WHATWG_ENCODING_API
#elif defined(SOFTLOQ_WHATWG_ENCODING_BUILD_API)
    #define SOFTLOQ_WHATWG_ENCODING_API SOFTLOQ_WHATWG_ENCODING_EXPORT
#elif defined(SOFTLOQ_WHATWG_ENCODING_USE_API)
    #define SOFTLOQ_WHATWG_ENCODING_API SOFTLOQ_WHATWG_ENCODING_IMPORT
#endif

//------------------//

// Monolithic Build //

#ifndef SOFTLOQ_WHATWG_ENCODING_API
    #if defined(SOFTLOQ_NO_API)
        #define SOFTLOQ_WHATWG_ENCODING_API
    #elif defined(SOFTLOQ_BUILD_API)
        #define SOFTLOQ_WHATWG_ENCODING_API SOFTLOQ_WHATWG_ENCODING_EXPORT
    #elif defined(SOFTLOQ_USE_API)
        #define SOFTLOQ_WHATWG_ENCODING_API SOFTLOQ_WHATWG_ENCODING_IMPORT
    #endif
#endif

//------------------//

// Default Values and Documentation //

#ifndef SOFTLOQ_WHATWG_ENCODING_EXPORT
    /** @brief Library Export Macro */
    #define SOFTLOQ_WHATWG_ENCODING_EXPORT
#endif

#ifndef SOFTLOQ_WHATWG_ENCODING_IMPORT
    /** @brief Library Import Macro */
    #define SOFTLOQ_WHATWG_ENCODING_IMPORT
#endif

#ifndef SOFTLOQ_WHATWG_ENCODING_API
    /** @brief Build Macro */
    #define SOFTLOQ_WHATWG_ENCODING_API
#endif

//----------------------------------//

#endif