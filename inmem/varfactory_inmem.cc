/**
 * @file varfactory_inmem.cc
 * @brief Definitions for IVarValue class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varfactory_inmem.h"
#include "../varmng.h"
#include "../varmng-private.h"
#include "../interface/varvalue_interface.h"
#include "varctx_inmem.h"
#include "vardef_inmem.h"
#include "varvalue_inmem.h"
#include <QString>
#include <QObject>
#include <QProcessEnvironment>

/**
 * @class VarFactory
 *
 *
 */

VarFactory VarFactory::instance_;

/* ------------------------------------------------------------------------- */
IVarCtx * VarFactory::createVarCtx (
        VarMng *mng, const QString &name, const QString &label)
{
    return new VarCtx (mng, name, label);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarCtx * VarFactory::createEnvVarCtx (VarMng * mng)
{
    IVarCtx * result = createVarCtx (
                mng,
                QLatin1String ("EnvVar"),
                QObject::tr ("Environment Variables"));
    result->loadEnvVariables ();
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue * VarFactory::createVarValue (
        IVarDef *def, IVarCtx * ctx, const QString &s_value)
{
    return new VarValue (def, ctx, s_value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * VarFactory::createVarDef (
        const QString &name, const QString &label,
        const QString &description, IVarDef * parent)
{
    IVarDef * result = new VarDef (name, label, description, parent);
    if (parent != NULL)
        parent->appendKidVarDef (result);
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
VarFactory * VarFactory::instance ()
{
    return &instance_;
}
/* ========================================================================= */

