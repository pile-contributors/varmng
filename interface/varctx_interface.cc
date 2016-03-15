/**
 * @file varctx_interface.cc
 * @brief Definitions for IVarCtx class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varctx_interface.h"
#include "varvalue_interface.h"
#include "vardef_interface.h"
#include "varmng-private.h"

/**
 * @class IVarCtx
 *
 *
 */

/* ------------------------------------------------------------------------- */
/**
 */
IVarCtx::IVarCtx ()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
IVarCtx::~IVarCtx()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue * IVarCtx::findValue (const QString &s_name)
{
    int i = 0;
    foreach (IVarValue * val, contextVariables ()) {
        if (val->definition ()->varName () == s_name) {
            return val;
        }
        ++i;
    }
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int IVarCtx::valueIndex (IVarDef *pdef) const
{
    int i = 0;
    foreach (IVarValue * val, contextVariables ()) {
        if (val->definition () == pdef) {
            return i;
        }
        ++i;
    }
    return -1;
}
/* ========================================================================= */
