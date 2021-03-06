/**
 * @file vardef_model.h
 * @brief Declarations for VarDefModel class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARDEF_MODEL_INCLUDE
#define GUARD_VARDEF_MODEL_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/varbase_interface.h>
#include <QAbstractItemModel>

QT_BEGIN_NAMESPACE
class QDataStream;
class QAbstractItemView;
QT_END_NAMESPACE

class IVarDef;
class VarMng;

//! Model for definitions available in a manager instance.
class VARMNG_EXPORT VarDefModel : public QAbstractItemModel, public IVarBase  {
    Q_OBJECT
public:

    //! Default constructor.
    VarDefModel (
            VarMng * mng,
            QObject *parent = 0);

    //! Destructor.
    virtual ~VarDefModel ();

    //! The manager instance used as source for the data.
    VarMng *
    manager () const {
        return mng_;
    }

    //! Get the item that is selected in provided view.
    IVarDef *
    getSelectedItem (
            QAbstractItemView *view);

    //! Create the model index for an item pointer.
    QModelIndex
    toIndex (
            IVarDef * item);

    //! Convert a model index into an item pointer.
    IVarDef *
    fromIndex (
            const QModelIndex & idx) const;

    //! Tell if an index is valid for this model.
    bool
    validateIndex (
            const QModelIndex &idx,
            IVarDef *pdef = NULL) const;

    //! Convenience method to insert a new definition as a kid to provided item.
    IVarDef *
    insertVarDef (
            const QString & name = QString (),
            const QString & label = QString (),
            const QString & description = QString (),
            int row = -1,
            const QModelIndex & parent = QModelIndex ());

    //! A numeric value indicating the type of this class.
    virtual int
    vmTyId () const {
        return DefinitionModel;
    }

public slots:

    //! Reset the model.
    void
    reload ();

    /* == == == == == == == == == == == == == == == == */
    /** @name QAbstractItemModel
    *  Reimplemented methods from QAbstractItemModel.
    */
    ///@{

public:

    virtual QModelIndex
    index (
            int row,
            int column,
            const QModelIndex &parent = QModelIndex()) const;

    virtual QModelIndex
    parent (
            const QModelIndex &child) const;

    Qt::ItemFlags
    flags (
        const QModelIndex &index) const;

    QVariant
    data (
        const QModelIndex &idx,
        int role = Qt::DisplayRole) const;

    QVariant
    headerData (
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;

    bool
    setData (
        const QModelIndex &index,
        const QVariant &value,
        int role = Qt::EditRole);

    //! Remove a number of rows
    bool
    removeRows (
        int row,
        int count,
        const QModelIndex &parent = QModelIndex());

    //! Allows creating new definitions on the fly.
    virtual bool
    insertRows (
        int row,
        int count,
        const QModelIndex &parent = QModelIndex());

    int
    rowCount (
        const QModelIndex &parent = QModelIndex()) const;

    int
    columnCount (
        const QModelIndex &parent = QModelIndex()) const;

    virtual Qt::DropActions
    supportedDropActions() const;

    virtual Qt::DropActions
    supportedDragActions() const;

    virtual bool
    moveRows (
            const QModelIndex &sourceParent,
            int sourceRow,
            int count,
            const QModelIndex &destinationParent,
            int destinationChild);

    virtual bool
    dropMimeData (
            const QMimeData *data,
            Qt::DropAction action,
            int row,
            int column,
            const QModelIndex &parent);

    virtual QStringList
    mimeTypes () const;

    virtual QMimeData *
    mimeData (
            const QModelIndexList &indexes) const;

    virtual bool
    canDropMimeData (
            const QMimeData *data,
            Qt::DropAction action,
            int row,
            int column,
            const QModelIndex &parent) const;

    ///@}
    /* == == == == == == == == == == == == == == == == */

protected:

    //! Encode data as application/x-vardef-explicit.
    void
    encodeDataExplicit (
            const QModelIndexList &indexes,
            QDataStream &stream) const;

public:

    //! Decode data encoded as application/x-vardef-explicit.
    static bool
    decodeDataExplicit (
            QDataStream &stream,
            QString & name,
            QString & label,
            QString & description,
            QString & path);

private:


    void
    encodeData (
            const QModelIndexList &indexes,
            QDataStream &stream) const;

    QModelIndexList
    decodeData (
            QDataStream &stream) const;

    bool
    decodeData (
            int row,
            int column,
            const QModelIndex &parent,
            QDataStream &stream) const;

private:

    VarMng * mng_; /**< the manager instance that we're representing */

}; // class VarDefModel

#endif // GUARD_VARDEF_MODEL_INCLUDE
