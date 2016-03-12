/**
 * @file varmng-private.h
 * @brief Declarations for VarMng class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARMNG_PRIVATE_H_INCLUDE
#define GUARD_VARMNG_PRIVATE_H_INCLUDE

#include <varmng/varmng-config.h>

#if 0
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

#endif // GUARD_VARMNG_PRIVATE_H_INCLUDE
