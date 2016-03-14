/**
 * @file vardef_inmem.cc
 * @brief Definitions for IVarDef class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "vardef_inmem.h"
#include "varmng-private.h"
#include "assert.h"

/**
 * @class VarDef
 *
 */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for constructor.
 */
VarDef::VarDef (
        const QString & name, const QString & label, const QString & description,
        IVarDef * group, const QList<IVarDef *> & kids) :
    IVarDef (),
    name_(name),
    label_(label),
    description_(description),
    group_(group),
    kids_()
{
    VARMNG_TRACE_ENTRY;
    setVarKids (kids);
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
VarDef::~VarDef ()
{
    VARMNG_TRACE_ENTRY;

    qDeleteAll (kids_);
    kids_.clear ();

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDef::setVarName (const QString &name)
{
    name_ = name;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDef::setVarLabel (const QString &label)
{
    label_ = label;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDef::setVarDescription (const QString &description)
{
    description_ = description;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDef::setVarKids (const QList<IVarDef *> &kids)
{
    kids_ = kids;
    foreach(IVarDef * iter, kids) {
        iter->setVarGroup (this);
    }
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDef::insertKidVarDef (int position, IVarDef *pdef)
{
    if (kids_.contains (pdef))
        return false;

    if ((position == -1) || (position >= kids_.count ())) {
        kids_.append (pdef);
    } else {
        kids_.insert (position, pdef);
    }
    pdef->setVarGroup (this);

    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDef::removeKidVarDef (int position, IVarDef *pdef)
{
    IVarDef * ivd = takeKidVarDef (position, pdef);
    if (ivd == NULL)
        return false;
    delete ivd;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * VarDef::takeKidVarDef (int position, IVarDef *pdef)
{
    if (position < 0) {
        if (pdef == NULL)
            return NULL;
        position = kids_.indexOf (pdef);
        if (position == -1)
            return NULL;
    } else if (position >= kids_.count ()) {
        return NULL;
    } else if (pdef == NULL) {
        pdef = kids_.at (position);
    } else {
        assert(kids_.at (position) == pdef);
    }

    kids_.removeAt (position);
    pdef->setVarGroup (NULL);
    return pdef;
}
/* ========================================================================= */