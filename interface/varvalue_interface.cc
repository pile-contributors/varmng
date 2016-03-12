/**
 * @file varvalue_interface.cc
 * @brief Definitions for IVarValue class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varvalue_interface.h"
#include "varmng-private.h"

/**
 * @class IVarValue
 *
 */

/* ------------------------------------------------------------------------- */
/**
 * The pointer to the definition is stored internally and can be retrieved by
 * using the definition () method.
 */
IVarValue::IVarValue (IVarDef *def) :
    def_(def)
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
IVarValue::~IVarValue()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */
