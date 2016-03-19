/**
 * @file varmng-private.h
 * @brief Declarations for VarMng class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARMNG_PRIVATE_H_INCLUDE
#define GUARD_VARMNG_PRIVATE_H_INCLUDE

#include <varmng/varmng-config.h>

#ifdef _MSC_VER
#   define __func__ __FUNCTION__
#endif

#if 1
#    define VARMNG_DEBUGM printf
#else
#    define VARMNG_DEBUGM black_hole
#endif

#if 0
#    define VARMNG_TRACE_ENTRY printf("VARMNG ENTRY %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define VARMNG_TRACE_ENTRY
#endif

#if 0
#    define VARMNG_TRACE_EXIT printf("VARMNG EXIT %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define VARMNG_TRACE_EXIT
#endif


static inline void black_hole (...)
{}

/**
 * @def TMP_A
 * @brief C style string from QString.
 * @internal
 */
#ifndef TMP_A
#   define TMP_A(__s__) __s__.toLatin1 ().constData ()
#endif

#endif // GUARD_VARMNG_PRIVATE_H_INCLUDE
