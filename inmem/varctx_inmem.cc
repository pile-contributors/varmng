/**
 * @file varctx_interface.cc
 * @brief Definitions for IVarCtx class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varctx_inmem.h"
#include "varmng-private.h"

/**
 * @class VarCtx
 *
 */

/* ------------------------------------------------------------------------- */
/**
 */
VarCtx::VarCtx (
        const QString & name, const QString & label,
        const QList<IVarValue*> & vars) :
    IVarCtx (),
    name_ (name),
    label_ (label),
    vars_ (vars)
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 */
VarCtx::~VarCtx()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */
