/**
 * @file varmng.cc
 * @brief Definitions for VarMng class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varmng.h"
#include "varmng-private.h"
#include "inmem/varfactory_inmem.h"
#include <QObject>

/**
 * @class VarMng
 *
 * The manager class tracks definitions of variables and
 * provides methods for adding, removing and listing
 * them. Definitions must implement IVarDef interface.
 *
 * Creating new elements is based on a set of factories,
 * each providing a specific type of object. By default
 * the factories that create simple - in memory - objects
 * are installed.
 */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for constructor.
 */
VarMng::VarMng () :
    def_root_ (),
    value_factory_ (VarFactory::instance ()),
    context_factory_ (VarFactory::instance ()),
    def_factory_ (VarFactory::instance ())
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
VarMng::~VarMng ()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * VarMng::getDefinition (const QString & s_name, bool b_create)
{
    return def_root_.findVarKid (
                s_name, b_create ? VarFactory::instance () : NULL);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef *VarMng::createVarDef (
        const QString &name, const QString &label,
        const QString &description, IVarDef *parent)
{
    return def_factory_->createVarDef(name, label, description, parent);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue *VarMng::createVarValue (IVarDef *def, const QString &s_value)
{
    return value_factory_->createVarValue (def, s_value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarCtx *VarMng::createVarCtx (const QString &name, const QString &label)
{
    return context_factory_->createVarCtx (name, label);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarCtx * VarMng::createEnvVarCtx ()
{
    return VarFactory::instance ()->createEnvVarCtx (this);
}
/* ========================================================================= */
