/**
 * @file varctx_interface.cc
 * @brief Definitions for IVarCtx class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varctx_inmem.h"
#include "vardef_inmem.h"
#include "varvalue_inmem.h"
#include "varmng-private.h"
#include "assert.h"

/**
 * @class VarCtx
 *
 */

/* ------------------------------------------------------------------------- */
/**
 */
VarCtx::VarCtx (
        VarMng *mng,
        const QString & name, const QString & label,
        const QList<IVarValue*> & vars) :
    IVarCtx (mng),
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

/* ------------------------------------------------------------------------- */
bool VarCtx::insertValue (int position, IVarValue *pdef)
{
    VARMNG_TRACE_ENTRY;
    if (vars_.contains (pdef))
        return false;

    if ((position == -1) || (position >= vars_.count ())) {
        vars_.append (pdef);
    } else {
        vars_.insert (position, pdef);
    }

    VARMNG_TRACE_EXIT;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtx::removeValue (int position, IVarValue *pdef)
{
    VARMNG_TRACE_ENTRY;
    IVarValue * ivd = takeValue (position, pdef);
    if (ivd == NULL)
        return false;
    delete ivd;
    VARMNG_TRACE_EXIT;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue * VarCtx::takeValue (int position, IVarValue *pdef)
{
    VARMNG_TRACE_ENTRY;
    if (position < 0) {
        if (pdef == NULL)
            return NULL;
        position = vars_.indexOf (pdef);
        if (position == -1)
            return NULL;
    } else if (position >= vars_.count ()) {
        return NULL;
    } else if (pdef == NULL) {
        pdef = vars_.at (position);
    } else {
        assert(vars_.at (position) == pdef);
    }

    vars_.removeAt (position);
    VARMNG_TRACE_EXIT;
    return pdef;
}
/* ========================================================================= */
