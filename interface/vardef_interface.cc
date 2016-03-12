/**
 * @file vardef_interface.cc
 * @brief Definitions for IVarDef class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "vardef_interface.h"
#include "varmng-private.h"

/**
 * @class IVarDef
 *
 * The definitions for variables may be arranged in a tree structure by
 * using the varKids() and varGroup() methods.
 */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for constructor.
 */
IVarDef::IVarDef()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
IVarDef::~IVarDef()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */
