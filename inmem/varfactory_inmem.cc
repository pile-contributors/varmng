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

/**
 * @class VarFactory
 *
 *
 */

VarFactory VarFactory::instance_;

IVarCtx * VarFactory::createVarCtx (
        const QString &name, const QString &label)
{
    return new VarCtx (name, label);
}

IVarValue * VarFactory::createVarValue (
        IVarDef *def, const QString &s_value)
{
    return new VarValue (def, s_value);
}

IVarDef * VarFactory::createVarDef (
        const QString &name, const QString &label,
        const QString &description, IVarDef * parent)
{
    return new VarDef (name, label, description, parent);
}

VarFactory * VarFactory::instance ()
{
    return &instance_;
}
