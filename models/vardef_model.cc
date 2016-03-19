/**
 * @file vardef_model.cc
 * @brief Definitions for VarDefModel class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "vardef_model.h"
#include "../varmng-private.h"
#include "../varmng.h"
#include "../varmng-const.h"

#include <QAbstractItemView>
#include <QMimeData>

/**
 * @class VarDefModel
 *
 *
 */

#define DEF_MODEL_COLUMN_COUNT 3

/* ------------------------------------------------------------------------- */
/**
 * The pointer to the definition is stored internally and can be retrieved by
 * using the definition () method.
 */
VarDefModel::VarDefModel (VarMng * mng, QObject *parent) :
    QAbstractItemModel (parent),
    mng_ (mng)
{
    VARMNG_TRACE_ENTRY;
    connect(mng_, &VarMng::definitionCreated,
            this, &VarDefModel::reload);
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
VarDefModel::~VarDefModel ()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * VarDefModel::getSelectedItem (QAbstractItemView *view)
{
    IVarDef * result = NULL;
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
QModelIndex VarDefModel::toIndex (IVarDef *item)
{
    QModelIndex result;
    for (;;) {
        if (item == NULL)
            break;
        IVarDef * pitem = item->varGroup ();
        if (pitem == NULL)
            break;
        int row = pitem->varKidIndex (item);

        result = createIndex (row, 0, item);
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * VarDefModel::fromIndex (const QModelIndex & idx) const
{
    IVarDef * result = NULL;
    for (;;) {
        if (!idx.isValid ())
            break;
        result = static_cast<IVarDef *>(idx.internalPointer ());
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::validateIndex (const QModelIndex &idx, IVarDef * pdef) const
{
    bool b_ret = false;
    for (;;) {
        if (!idx.isValid())
            break;

        if ((idx.column () < 0) || (idx.column () >= DEF_MODEL_COLUMN_COUNT))
            break;

        IVarDef * def = pdef;
        if (def == NULL) {
            def = static_cast<IVarDef *> (idx.internalPointer());
            if (def == NULL)
                break;
        }
        pdef = def->varGroup ();
        if (pdef == NULL)
            break;

        if ((idx.row () < 0) || (idx.row () >= pdef->varKidsCount ()))
            break;

        b_ret = true;
        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarDef * VarDefModel::insertVarDef (
        const QString &name, const QString &label,
        const QString &description, int row, const QModelIndex &parent)
{
    IVarDef * result = NULL;
    for (;;) {

        IVarDef * pdef = static_cast<IVarDef *>(parent.internalPointer());
        if (!parent.isValid ()) {
            pdef = mng_->rootVarDef ();
        } else if (!validateIndex (parent, pdef)) {
            break;
        }

        if (row == -1)
            row = pdef->varKidsCount ();

        beginInsertRows (parent, row, row);
        result = mng_->createVarDef (name, label, description, pdef);
        bool b_ret = pdef->insertKidVarDef (row, result);
        if (!b_ret) {
            delete result;
            result = NULL;
        }
        endInsertRows();

        break;
    }

    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarDefModel::reload()
{
    beginResetModel ();
    endResetModel ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarDefModel::index (
        int row, int column, const QModelIndex &parent) const
{
    QModelIndex result;
    for (;;) {

        IVarDef * pdef = static_cast<IVarDef *>(parent.internalPointer());
        if (!parent.isValid ()) {
            pdef = mng_->rootVarDef ();
        } else if (!validateIndex (parent, pdef)) {
            break;
        }

        if ((column < 0) || (column >= DEF_MODEL_COLUMN_COUNT))
            break;

        if ((row < 0) || (row >= pdef->varKidsCount ()))
            break;

        result = createIndex (row, column, pdef->varKid (row));
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarDefModel::parent (const QModelIndex & child) const
{
    QModelIndex result;
    for (;;) {
        if (!validateIndex (child))
            break;
        IVarDef * def = static_cast<IVarDef *> (child.internalPointer());
        IVarDef * pdef = def->varGroup ();
        if (pdef == NULL)
            break;
        IVarDef * ppdef = pdef->varGroup ();
        if (ppdef == NULL)
            ppdef = mng_->rootVarDef ();

        int row = ppdef->varKidIndex (pdef);
        if (row == -1)
            break;

        result = createIndex (row, 0, pdef);
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::ItemFlags VarDefModel::flags (const QModelIndex &idx) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags (idx);

    //    if (!validateIndex (idx))
    //        break;

    if (idx.isValid())
        result = Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | result;
    else
        result = Qt::ItemIsDropEnabled | result;

    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::removeRows (int row, int count, const QModelIndex &parent)
{
    bool b_ret = false;
    for (;;) {

        IVarDef * pdef = static_cast<IVarDef *>(parent.internalPointer());
        if (!parent.isValid ()) {
            pdef = mng_->rootVarDef ();
        } else if (!validateIndex (parent, pdef)) {
            break;
        }

        beginRemoveRows (parent, row, row+count-1);
        for (int i = 0; i < count; ++i) {
            pdef->removeKidVarDef (row);
        }
        endRemoveRows();

        b_ret = true;
        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::insertRows (int row, int count, const QModelIndex &parent)
{
    bool b_ret = false;
    for (;;) {

        IVarDef * pdef = static_cast<IVarDef *>(parent.internalPointer());
        if (!parent.isValid ()) {
            pdef = mng_->rootVarDef ();
        } else if (!validateIndex (parent, pdef)) {
            break;
        }
        if (row < 0)
            row = pdef->varKidsCount ();

        b_ret = true;
        beginInsertRows (parent, row, row+count-1);
        for (int i = 0; i < count; ++i) {
            IVarDef * newv = mng_->createVarDef (
                        QLatin1String ("NewVariable"),
                        tr ("NewVariable"),
                        QString(), pdef);
            b_ret = pdef->insertKidVarDef (row, newv);
            if (!b_ret)
                break;
        }
        endInsertRows();

        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant VarDefModel::data (const QModelIndex & idx, int role) const
{
    for (;;) {

        if (!validateIndex (idx))
            break;

        if ((role != Qt::DisplayRole) && (role != Qt::EditRole))
            break;

        IVarDef * pdef = static_cast<IVarDef *> (idx.internalPointer());

        switch (idx.column ()) {
        case 0:
            return pdef->varName ();
        case 1:
            return pdef->varLabel ();
        case 2:
            return pdef->varDescription ();
        }

        break;
    }
    return QVariant ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant VarDefModel::headerData (
        int section, Qt::Orientation orientation, int role) const
{
    for (;;) {
        if (orientation == Qt::Vertical)
            break;
        if ((role != Qt::DisplayRole) && (role != Qt::EditRole))
            break;

        switch (section) {
        case 0:
            return tr ("Name");
        case 1:
            return tr ("Label");
        case 2:
            return tr ("Description");
        }

        break;
    }
    return QAbstractItemModel::headerData (section, orientation, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::setData (
        const QModelIndex & idx, const QVariant &value, int role)
{
    for (;;) {

        if (!validateIndex (idx))
            break;

        if (!(flags (idx) & Qt::ItemIsEditable))
            break;

        if ((role != Qt::DisplayRole) && (role != Qt::EditRole))
            break;

        IVarDef * pdef = static_cast<IVarDef *>(idx.internalPointer());

        switch (idx.column ()) {
        case 0:
            pdef->setVarName (value.toString ());
            break;
        case 1:
            pdef->setVarLabel (value.toString ());
            break;
        case 2:
            pdef->setVarDescription (value.toString ());
            break;
        }

        break;
    }
    return QAbstractItemModel::setData (idx, value, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarDefModel::rowCount (const QModelIndex & parent) const
{
    int result = 0;
    for (;;) {
        IVarDef * pdef = static_cast<IVarDef *>(parent.internalPointer());
        if (!parent.isValid ()) {
            pdef = mng_->rootVarDef ();
        }

        result = pdef->varKidsCount ();
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarDefModel::columnCount (const QModelIndex &) const
{
    return DEF_MODEL_COLUMN_COUNT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::DropActions VarDefModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::DropActions VarDefModel::supportedDragActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::moveRows (
        const QModelIndex &sourceParent, int sourceRow, int count,
        const QModelIndex &destinationParent, int destinationChild)
{
    bool b_ret = false;
    for (;;) {
        // Validate source portion of the input.
        IVarDef * psource = static_cast<IVarDef *>(sourceParent.internalPointer());
        if (!sourceParent.isValid ()) {
            psource = mng_->rootVarDef ();
        } else if (!validateIndex (sourceParent, psource)) {
            break;
        }
        if ((sourceRow < 0) || (sourceRow >= psource->varKidsCount()))
            break;
        if (sourceRow + count > psource->varKidsCount())
            break;

        // Validate destination portion of the input.
        IVarDef * pdestin = static_cast<IVarDef *>(destinationParent.internalPointer());
        if (!destinationParent.isValid ()) {
            pdestin = mng_->rootVarDef ();
        } else if (!validateIndex (destinationParent, pdestin)) {
            break;
        }
        if ((destinationChild < 0) || (destinationChild >= psource->varKidsCount()))
            destinationChild = psource->varKidsCount();

        // Remove from source.
        beginRemoveRows (sourceParent, sourceRow, sourceRow+count-1);
        QList<IVarDef *> transfer;
        for (int i = 0; i < count; ++i) {
            IVarDef * k = psource->takeKidVarDef (sourceRow);
            if (k != NULL) {
                transfer.append (k);
            }
        }
        endRemoveRows ();

        // Insert into destination.
        beginInsertRows (destinationParent,
                         destinationChild, destinationChild+count-1);
        int j = destinationChild;
        foreach(IVarDef * k, transfer) {
            pdestin->insertKidVarDef (j++, k);
        }
        endInsertRows ();

        b_ret = true;
        break;
    }
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QStringList VarDefModel::mimeTypes() const
{
    QStringList types;
    types << MIME_VARMNG_INTERNAL_ROW_MOVE << MIME_VARMNG_DEF;
    return types;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QMimeData * VarDefModel::mimeData (const QModelIndexList &indexes) const
{
    if (indexes.count() <= 0)
        return NULL;
    QStringList types = mimeTypes ();
    if (types.isEmpty())
        return 0;

    QMimeData *data = new QMimeData ();

    {
        QString format = MIME_VARMNG_INTERNAL_ROW_MOVE;
        QByteArray encoded;
        QDataStream stream (&encoded, QIODevice::WriteOnly);
        encodeData(indexes, stream);
        data->setData(format, encoded);
    }

    {
        QString format = MIME_VARMNG_DEF;
        QByteArray encoded;
        QDataStream stream (&encoded, QIODevice::WriteOnly);
        encodeDataExplicit (indexes, stream);
        data->setData(format, encoded);
    }


    return data;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::canDropMimeData (
        const QMimeData *data, Qt::DropAction action,
        int /*row*/, int /*column*/, const QModelIndex &parent) const
{
    if (!data || !(action == Qt::CopyAction || action == Qt::MoveAction))
        return false;
    QStringList types = mimeTypes();
    if (types.isEmpty())
        return false;
    QString format = MIME_VARMNG_INTERNAL_ROW_MOVE;
    if (!data->hasFormat(format)) {
        return false;
    }
    QByteArray encoded = data->data(format);
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    // Make sure that the parent chain is not one of
    // the items listed here.
    QModelIndexList ml = decodeData (stream);
    bool b_ret = true;
    QModelIndex iter = parent;
    while (iter.isValid ()) {
        if (ml.contains (iter)) {
            b_ret = false;
            break;
        }
        iter = iter.parent ();
    }

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarDefModel::encodeData (
        const QModelIndexList &indexes, QDataStream &stream) const
{
    QModelIndexList::ConstIterator it = indexes.begin();
    for (; it != indexes.end(); ++it)
        stream << (*it).row() << (*it).internalId ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarDefModel::encodeDataExplicit (
        const QModelIndexList &indexes, QDataStream &stream) const
{
    QModelIndexList::ConstIterator it = indexes.begin();
    QMap<int,bool> rows;
    for (; it != indexes.end(); ++it) {
        int r = (*it).row();
        if (!rows.contains (r)) {
            IVarDef * pdestin = static_cast<IVarDef *>((*it).internalPointer());
            stream << pdestin->varName ()
                   << pdestin->varLabel ()
                   << pdestin->varDescription ()
                   << pdestin->varPath ();
            rows.insert (r, true);
        }
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::decodeDataExplicit (
        QDataStream &stream, QString &name, QString &label,
        QString &description, QString &path)
{
    stream >> name >> label >> description >> path;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::decodeData (
        int /*row*/, int /*column*/, const QModelIndex &/*parent*/,
        QDataStream &stream) const
{
    /*QModelIndexList result =*/ decodeData (stream);
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndexList VarDefModel::decodeData (QDataStream &stream) const
{
    QModelIndexList result;
    while (!stream.atEnd()) {
        int r;
        quintptr v;
        stream >> r >> v;

        bool already_in = false;
        foreach (const QModelIndex & iter, result) {
            if (iter.row () == r) {
                already_in = true;
                break;
            }
        }
        if (!already_in) {
            result.append (createIndex (r, 0, v));
        }
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarDefModel::dropMimeData (
        const QMimeData *data, Qt::DropAction action,
        int row, int /*column*/, const QModelIndex &parent)
{
    if (!data || !(action == Qt::CopyAction || action == Qt::MoveAction))
        return false;
    QStringList types = mimeTypes();
    if (types.isEmpty())
        return false;
    QString format = MIME_VARMNG_INTERNAL_ROW_MOVE;
    if (!data->hasFormat(format))
        return false;
    QByteArray encoded = data->data(format);
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    QModelIndexList ml = decodeData (stream);
    bool b_ret = true;
    if (action == Qt::MoveAction) {
        foreach (const QModelIndex & iter, ml) {
            b_ret = b_ret & moveRows (
                        iter.parent(), iter.row (), 1, parent, row++);
        }
    } else {
        foreach (const QModelIndex & iter, ml) {
            IVarDef * def = static_cast<IVarDef *>(iter.internalPointer());
            b_ret = b_ret & (NULL != insertVarDef (
                        def->varName(), def->varLabel (),
                        def->varDescription(), row++, parent));
        }
    }
    return false;
}
/* ========================================================================= */
