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
#include "../interface/varvalue_interface.h"
#include "../interface/vardef_interface.h"
#include "../interface/varctx_interface.h"
#include "../varmng.h"
#include "../varmng-const.h"
#include "vardef_model.h"

#include <QAbstractItemView>
#include <QMimeData>

/**
 * @class VarCtxModel
 *
 *
 */

#define CTX_MODEL_COLUMN_COUNT 3

/* ------------------------------------------------------------------------- */
/**
 * The pointer to the context is stored internally and can be retrieved by
 * using the context () method.
 */
VarCtxModel::VarCtxModel (IVarCtx *context, QObject *parent) :
    QAbstractItemModel (parent),
    context_ (context)
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
    IVarValue * result = NULL;
    for (;;) {
        if (view == NULL)
            break;
        QItemSelectionModel * sm = view->selectionModel ();
        if (sm == NULL)
            break;
        result = fromIndex (sm->currentIndex ());
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarCtxModel::toIndex (IVarValue *item)
{
    QModelIndex result;
    for (;;) {
        if (item == NULL)
            break;
        int row = context_->valueIndex (item);
        if (row == -1)
            break;

        result = createIndex (row, 0, item);
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue * VarCtxModel::fromIndex (const QModelIndex &idx) const
{
    IVarValue * result = NULL;
    for (;;) {
        if (!idx.isValid ())
            break;
        result = static_cast<IVarValue *>(idx.internalPointer ());
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtxModel::validateIndex (
        const QModelIndex &idx, IVarValue * pdef) const
{
    bool b_ret = false;
    for (;;) {
        if (!idx.isValid ())
            break;

        if ((idx.column () < 0) || (idx.column () >= CTX_MODEL_COLUMN_COUNT))
            break;

        IVarValue * def = pdef;
        if (def == NULL) {
            def = static_cast<IVarValue *> (idx.internalPointer());
            if (def == NULL)
                break;
        }

        if ((idx.row () < 0) || (idx.row () >= context_->valuesCount ()))
            break;

        b_ret = true;
        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarCtxModel::clear()
{
    beginResetModel ();
    context_->clearValues ();
    endResetModel ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarCtxModel::index (
        int row, int column, const QModelIndex &parent) const
{
    QModelIndex result;
    for (;;) {
        if (parent.isValid ()) {
            break;
        }

        if ((column < 0) || (column >= CTX_MODEL_COLUMN_COUNT))
            break;

        if ((row < 0) || (row >= context_->valuesCount ()))
            break;

        result = createIndex (row, column, context_->value (row));
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarCtxModel::parent (const QModelIndex &/*child*/) const
{
    return QModelIndex ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::ItemFlags VarCtxModel::flags (const QModelIndex &idx) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags (idx);

    switch (idx.column ()) {
    case 0:
    case 1:
        result = Qt::ItemIsEditable | result;
        break;
    }

    if (idx.isValid())
        result = Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | result;
    else
        result = Qt::ItemIsDropEnabled | result;

    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtxModel::removeRows (int row, int count, const QModelIndex &parent)
{
    bool b_ret = false;
    for (;;) {
        if (parent.isValid())
            break;
        if (row < 0)
            break;
        if (row + count > context_->valuesCount ())
            break;

        beginRemoveRows (parent, row, row+count-1);
        for (int i = 0; i < count; ++i) {
            context_->removeValue (row);
        }
        endRemoveRows();

        b_ret = true;
        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtxModel::insertRows (int row, int count, const QModelIndex &parent)
{
    bool b_ret = false;
    for (;;) {
        if (parent.isValid())
            break;
        if (row < 0)
            row = context_->valuesCount ();

        b_ret = true;
        beginInsertRows (parent, row, row+count-1);
        for (int i = 0; i < count; ++i) {
            IVarValue * newv = context_->createVarValue (
                        NULL, QString ());
            if (newv == NULL)
                break;
        }
        endInsertRows();

        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant VarCtxModel::data (const QModelIndex & idx, int role) const
{
    for (;;) {

        if (!validateIndex (idx))
            break;

        if ((role != Qt::DisplayRole) && (role != Qt::EditRole))
            break;

        IVarValue * val = static_cast<IVarValue *> (idx.internalPointer());
        IVarDef * pdef = val->definition ();

        switch (idx.column ()) {
        case 0:
            return pdef == NULL ? QString() : pdef->varLabel ();
        case 1:
            return val->varValue ();
        case 2:
            return pdef == NULL ? QString() : pdef->varDescription ();
        }

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
        if (orientation == Qt::Vertical)
            break;
        if ((role != Qt::DisplayRole) && (role != Qt::EditRole))
            break;

        switch (section) {
        case 0:
            return tr ("Variable");
        case 1:
            return tr ("Value");
        case 2:
            return tr ("Description");
        }

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

        if ((role != Qt::DisplayRole) && (role != Qt::EditRole))
            break;

        IVarValue * val = static_cast<IVarValue *>(idx.internalPointer());

        switch (idx.column ()) {
        case 0: {
            IVarDef * def = context_->manager()->getDefinition (
                        value.toString (), false);
            if (def != NULL) {
                val->setVarDefinition (def);
                dataChanged (
                            createIndex (idx.row(), 0),
                            createIndex (idx.row(), 2));
            }
            break;}
        case 1: {
            val->setVarValue (value.toString ());
            dataChanged (
                        createIndex (idx.row(), 1),
                        createIndex (idx.row(), 1));
            break;}
        }

        break;
    }
    return QAbstractItemModel::setData (idx, value, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarCtxModel::rowCount (const QModelIndex & parent) const
{
    if (parent.isValid ())
        return 0;
    else
        return context_->valuesCount ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarCtxModel::columnCount (const QModelIndex &parent) const
{
    if (parent.isValid ())
        return 0;
    else
        return CTX_MODEL_COLUMN_COUNT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::DropActions VarCtxModel::supportedDropActions() const
{
    return Qt::CopyAction;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::DropActions VarCtxModel::supportedDragActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtxModel::canDropMimeData (
        const QMimeData *data, Qt::DropAction action,
        int /* row */, int /* column */, const QModelIndex &/* parent */) const
{
    if (!data || !(action == Qt::CopyAction || action == Qt::MoveAction))
        return false;
    QString format = MIME_VARMNG_DEF;
    if (!data->hasFormat(format)) {
        return false;
    } else {
        return true;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarCtxModel::dropMimeData (
        const QMimeData *data, Qt::DropAction action,
        int /*row*/, int /* column */, const QModelIndex &parent)
{
    bool b_ret = false;
    if (!data || !(action == Qt::CopyAction || action == Qt::MoveAction))
        return false;
    QStringList types = mimeTypes();
    if (types.isEmpty())
        return false;
    QString format = MIME_VARMNG_DEF;
    if (!data->hasFormat(format))
        return false;
    QByteArray encoded = data->data (format);
    QDataStream stream (&encoded, QIODevice::ReadOnly);

    QString name;
    QString label;
    QString description;
    QString path;

    b_ret = true;
    while (!stream.atEnd()) {
        VarDefModel::decodeDataExplicit (
                    stream, name, label, description, path);
        if (context_->findValue (name) != NULL) {
            // already inside
        } else {
            IVarDef * def = context_->manager ()->getDefinition (path, false);
            if (def == NULL) {
                def = context_->manager ()->getDefinition (path, true);
                def->setVarLabel (label);
                def->setVarDescription (description);
                if (!def) {
                    VARMNG_DEBUGM ("Could not create the definition for "
                                   "%s variable\n", TMP_A(name));
                    continue;
                }
            }
            int r = parent.row () + 1;
            beginInsertRows (parent, r, r);
            /*IVarValue * newv = */ context_->createVarValue (
                        def, QString (), r);
            endInsertRows();
        }
    }

    return b_ret;
}
/* ========================================================================= */
