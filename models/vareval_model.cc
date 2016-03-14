/**
 * @file vareval_model.cc
 * @brief Definitions for VarEvalModel class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "vareval_model.h"
#include "varmng-private.h"
#include <QAbstractItemView>

/**
 * @class VarEvalModel
 *
 * Detailed description.
 */

/* ------------------------------------------------------------------------- */
/**
 * The pointer to the definition is stored internally and can be retrieved by
 * using the definition () method.
 */
VarEvalModel::VarEvalModel (QObject *parent) :
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
VarEvalModel::~VarEvalModel()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarEvalModel::toIndex (void *item)
{
    return QModelIndex ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void * VarEvalModel::fromIndex (const QModelIndex &idx) const
{
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarEvalModel::validateIndex (const QModelIndex &idx) const
{

    return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void * VarEvalModel::getSelectedItem (QAbstractItemView *view)
{
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarEvalModel::index (
        int row, int column, const QModelIndex &parent) const
{
    return QModelIndex ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarEvalModel::parent (const QModelIndex &child) const
{

    return QModelIndex ();
}
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
Qt::ItemFlags VarEvalModel::flags (const QModelIndex &idx) const
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
bool VarEvalModel::removeRows (int row, int count, const QModelIndex &)
{

    return false;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant VarEvalModel::data (const QModelIndex & idx, int role) const
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
QVariant VarEvalModel::headerData (
        int section, Qt::Orientation orientation, int role) const
{
    for (;;) {

        break;
    }
    return QAbstractItemModel::headerData (section, orientation, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarEvalModel::setData (
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
int VarEvalModel::rowCount (const QModelIndex &) const
{
    return 0;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarEvalModel::columnCount (const QModelIndex &) const
{
    return 0;
}
/* ========================================================================= */

