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
    kids_(kids)
{
    VARMNG_TRACE_ENTRY;

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

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarDef::setVarName (const QString &name)
{
    name_ = name;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarDef::setVarLabel (const QString &label)
{
    label_ = label;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarDef::setVarDescription (const QString &description)
{
    description_ = description;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarDef::setVarKids (const QList<IVarDef *> &kids)
{
    kids_ = kids;
}
/* ========================================================================= */
