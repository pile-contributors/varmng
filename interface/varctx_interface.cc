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
#include "../varmng.h"
#include <QProcessEnvironment>

/**
 * @class IVarCtx
 *
 *
 */

/* ------------------------------------------------------------------------- */
/**
 */
IVarCtx::IVarCtx (
        VarMng *mng) :
    mng_(mng)
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
int IVarCtx::loadEnvVariables ()
{
    int result = 0;
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment ();
    foreach (const QString & s_key, env.keys ()) {
        // Find or create the definition.
        QString s_value = env.value (s_key);
        IVarDef * def = mng_->getDefinition (s_key, true);
        // def->setVarDescription (Object::tr ("Environment variable"));

        IVarValue * val = mng_->createVarValue (def, s_value);
        appendValue (val);
        ++result;
    }
    return result;
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

/* ------------------------------------------------------------------------- */
IVarValue * IVarCtx::createVarValue (
        IVarDef *def, const QString &s_value, int i)
{
    IVarValue * val = mng_->createVarValue (def, s_value);
    if (val != NULL) {
        insertValue (i, val);
    }
    return val;
}
/* ========================================================================= */
