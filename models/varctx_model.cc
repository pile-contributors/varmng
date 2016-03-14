/**
 * @file varctx_model.cc
 * @brief Definitions for VarCtxModel class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varctx_model.h"
#include "varmng-private.h"
#include <QAbstractItemView>

/**
 * @class VarCtxModel
 *
 * Detailed description.
 */

/* ------------------------------------------------------------------------- */
/**
 * The pointer to the definition is stored internally and can be retrieved by
 * using the definition () method.
 */
VarCtxModel::VarCtxModel (QObject *parent) :
    QAbstractItemModel (parent)
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
VarCtxModel::~VarCtxModel()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue * VarCtxModel::getSelectedItem (QAbstractItemView *view)
{

    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarCtxModel::toIndex (IVarValue *item)
{
    return QModelIndex ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue * VarCtxModel::fromIndex (const QModelIndex &idx) const
{
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtxModel::validateIndex (const QModelIndex &idx) const
{

    return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarCtxModel::index (
        int row, int column, const QModelIndex &parent) const
{
    return QModelIndex ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarCtxModel::parent (const QModelIndex &child) const
{

    return QModelIndex ();
}
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
Qt::ItemFlags VarCtxModel::flags (const QModelIndex &idx) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags (idx);
    for (;;) {
        if (!validateIndex (idx))
            break;

        break;
    }

    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtxModel::removeRows (int row, int count, const QModelIndex &)
{

    return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant VarCtxModel::data (const QModelIndex & idx, int role) const
{
    for (;;) {

        if (!validateIndex (idx))
            break;


        break;
    }
    return QVariant ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant VarCtxModel::headerData (
        int section, Qt::Orientation orientation, int role) const
{
    for (;;) {

        break;
    }
    return QAbstractItemModel::headerData (section, orientation, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtxModel::setData (
        const QModelIndex & idx, const QVariant &value, int role)
{
    for (;;) {

        if (!validateIndex (idx))
            break;

        if (!(flags (idx) & Qt::ItemIsEditable))

        break;
    }
    return QAbstractItemModel::setData (idx, value, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarCtxModel::rowCount (const QModelIndex &) const
{
    return 0;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarCtxModel::columnCount (const QModelIndex &) const
{
    return 0;
}
/* ========================================================================= */
