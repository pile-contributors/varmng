/**
 * @file vareval.cc
 * @brief Definitions for VarEval class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "vareval.h"
#include "varmng-private.h"
#include "interface/varctx_interface.h"
#include "interface/vardef_interface.h"
#include "interface/varvalue_interface.h"

/**
 * @class VarEval
 *
 */

/* ------------------------------------------------------------------------- */
/**
 *
 */
VarEval::VarEval () :
    ctx_list_ ()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 */
VarEval::~VarEval()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
VarMng * VarEval::manager () const
{
    if (ctx_list_.isEmpty())
        return NULL;
    else
        return ctx_list_.at (0)->manager ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarEval::insertCtx (int idx, IVarCtx *ctx)
{
    bool b_ret = false;
    for (;;) {
        if (ctx == NULL)
            break;
        if (ctx_list_.contains (ctx))
            break;
        if ((idx < 0) || (idx >= ctx_list_.count())) {
            ctx_list_.append (ctx);
        } else {
            ctx_list_.insert (idx, ctx);
        }
        b_ret = true;
        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarCtx *VarEval::findCtxInst (const QString &s_name)
{
    foreach(IVarCtx * iter, ctx_list_) {
        if (iter->contextName () == s_name) {
            return iter;
        }
    }
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarEval::findCtx (const QString &s_name)
{
    int idx = 0;
    foreach(IVarCtx * iter, ctx_list_) {
        if (iter->contextName () == s_name) {
            return idx;
        }
        ++idx;
    }
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarEval::findCtx (IVarCtx *inst)
{
    return ctx_list_.indexOf (inst);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QList<IVarDef *> VarEval::collectDefinitions ()
{
    QList<IVarDef *> result;

    foreach(IVarCtx * iter, ctx_list_) {
        foreach(IVarValue * val, iter->contextVariables ()) {
            IVarDef * def = val->definition();
            if (!result.contains (def)) {
                result.append (def);
            }
        }
    }

    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QMap<QString,QString> VarEval::collectValues ()
{
    return collectValues (collectDefinitions ());
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QMap<QString,QString> VarEval::collectValues (
        const QList<IVarDef *> &defs)
{
    QMap<QString,QString> result;

    foreach(IVarDef * def, defs) {
        QString s_result;
        QString s_key = def->varName ();
        foreach(IVarCtx * iter, ctx_list_) {
            IVarValue * v = iter->value (def);
            if (v != NULL) {
                s_result = v->varValue ();
            }
        }
        result.insert (s_key, s_result);
    }

    return result;
}
/* ========================================================================= */
