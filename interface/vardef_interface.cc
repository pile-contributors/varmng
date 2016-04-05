/**
 * @file vardef_interface.cc
 * @brief Definitions for IVarDef class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "vardef_interface.h"
#include "../varmng-private.h"
#include <QStringList>

/**
 * @class IVarDef
 *
 * The definitions for variables may be arranged in a tree structure by
 * using the varKids() and varGroup() methods.
 */

/* ------------------------------------------------------------------------- */
/**
 * .
 */
IVarDef::IVarDef (VarMng *mng) : IVarBase (),
    mng_(mng)
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * .
 */
IVarDef::~IVarDef()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * IVarDef::findVarKid (const QString &s_name) const
{
    return const_cast<IVarDef *>(this)->findVarKid (s_name, NULL);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * IVarDef::findVarKid (const QStringList &sl_path) const
{
    return const_cast<IVarDef *>(this)->findVarKid (sl_path, NULL);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * IVarDef::findLocalVarKid (const QString &s_name) const
{
    return const_cast<IVarDef *>(this)->findLocalVarKid (s_name, NULL);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString IVarDef::varPath () const
{
    return varPathSL().join (QChar ('/'));
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList IVarDef::varPathSL () const
{
    QStringList result;
    const IVarDef * iter = this;
    const IVarDef * iter_parent;
    while (iter != NULL) {
        iter_parent = iter->varGroup ();
        if (iter_parent == NULL)
            break;
        result.prepend (iter->varName ());
        iter = iter_parent;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The provided string is spited into components and provided to
 * base method.
 * @param sl_path name of each node and name of the leaf to retrieve
 * @param factory used to create a new instance if not found inside
 * @return found item
 */
IVarDef * IVarDef::findVarKid (
        const QString &s_name, IVarDefFactory * factory)
{
    return findVarKid (s_name.split (QChar ('/')), factory);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Each name in provided list represents the name of a node, with the last one
 * being the name of the leaf.
 *
 * @param sl_path name of each node and name of the leaf to retrieve
 * @param factory used to create a new instance if not found inside
 * @return found item
 */
IVarDef * IVarDef::findVarKid (
        const QStringList & sl_path, IVarDefFactory * factory)
{
    IVarDef * found = NULL;
    IVarDef * crt_item = const_cast<IVarDef *>(this);
    foreach (const QString & s_name, sl_path) {
        found = crt_item->findLocalVarKid (s_name);
        if (found == NULL) {
            // If the item does not exist either create a new one or fail.
            if (factory == NULL) {
                break;
            } else {
                found = factory->createVarDef (
                            s_name, s_name, QString(), crt_item);
            }
        }
        crt_item = found;
    }
    return found;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The method iterates all child variables and compares provided name
 * with each one. If not found and a factory is provided the
 * function will create a new item and append it to the internal list.
 *
 * The method does not allow path separators and it only inspects
 * direct descendants in contrast to findVarKid() methods.
 *
 * @param s_name case sensitive name of the variable to locate (or create)
 * @param factory used to create a new instance if not found inside
 * @return found item
 */
IVarDef * IVarDef::findLocalVarKid (
        const QString &s_name, IVarDefFactory *factory)
{
    foreach (IVarDef * iter, varKids()) {
        if (iter->varName () == s_name) {
            return iter;
        }
    }
    IVarDef * result = NULL;
    if (factory != NULL) {
        result = factory->createVarDef (s_name, s_name, QString(), this);
    }
    return result;
}
/* ========================================================================= */

int IVarDefFactory::vmTyId() const {
    return BasicDefinitionFactory;
}
