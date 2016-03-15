/**
 * @file varfactory_inmem.cc
 * @brief Definitions for IVarValue class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varfactory_inmem.h"
#include "varmng-private.h"
#include "../interface/varvalue_interface.h"
#include "varctx_inmem.h"
#include "vardef_inmem.h"
#include "varvalue_inmem.h"
#include "../varmng.h"
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
        const QString &name, const QString &label)
{
    return new VarCtx (name, label);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarCtx * VarFactory::createEnvVarCtx (VarMng * mng)
{
    IVarCtx * result = createVarCtx (
                QLatin1String ("EnvVar"),
                QObject::tr ("Environment Variables"));

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment ();
    foreach (const QString & s_key, env.keys ()) {
        // Find or create the definition.
        QString s_value = env.value (s_key);
        IVarDef * def = mng->getDefinition (s_key, true);
        // def->setVarDescription (Object::tr ("Environment variable"));

        IVarValue * val = createVarValue (def, s_value);
        result->appendValue (val);
    }

    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue * VarFactory::createVarValue (
        IVarDef *def, const QString &s_value)
{
    return new VarValue (def, s_value);
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

