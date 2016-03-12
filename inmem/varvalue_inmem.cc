/**
 * @file varvalue_interface.cc
 * @brief Definitions for IVarValue class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varvalue_inmem.h"
#include "varmng-private.h"
#include "../interface/varvalue_interface.h"

/**
 * @class IVarValue
 *
 */

/* ------------------------------------------------------------------------- */
/**
 * The pointer to the definition is stored internally and can be retrieved by
 * using the definition () method.
 */
VarValue::VarValue (IVarDef *def, const QString &s_value) :
    IVarValue (def),
    s_value_ (s_value)
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
VarValue::~VarValue()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarValue::setVarValue (const QString &s_value)
{
    s_value_ = s_value;
}
/* ========================================================================= */

