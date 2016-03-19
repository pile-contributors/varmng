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
VarMng::VarMng (QObject * parent) : QObject (parent),
    def_root_ (this),
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
    IVarDef * def = def_factory_->createVarDef(name, label, description, parent);
    if (def != NULL) {
        emit definitionCreated (def);
    }
    return def;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue *VarMng::createVarValue (
        IVarDef *def, IVarCtx * ctx, const QString &s_value)
{
    IVarValue * val = value_factory_->createVarValue (def, ctx, s_value);
    if ((val != NULL) && (val->definition() != NULL)) {
        emit valueCreated (val);
    }
    return val;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarCtx *VarMng::createVarCtx (const QString &name, const QString &label)
{
    IVarCtx * ctx = context_factory_->createVarCtx (this, name, label);
    if (ctx != NULL) {
        emit contextCreated (ctx);
    }
    return ctx;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarCtx * VarMng::createEnvVarCtx ()
{
    IVarCtx * ctx = VarFactory::instance ()->createEnvVarCtx (this);
    if (ctx != NULL) {
        emit contextCreated (ctx);
    }
    return ctx;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarMng::changeValue (IVarValue *val, const QString &s_value)
{
    bool result = val->setVarValue (s_value);
    if (result) {
        emit valueChanged (val);
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarMng::setValueDefinition (IVarValue *val, IVarDef *def)
{
    bool b_ret = false;
    IVarDef *def_prev = val->definition ();
    if (val->setVarDefinition (def)) {
        if (def_prev != NULL) {
            // hack to trigger a  full reload
            emit definitionCreated (def);
        } else {
            emit valueChanged (val);
        }
        b_ret = true;
    }
    return b_ret;
}
/* ========================================================================= */
