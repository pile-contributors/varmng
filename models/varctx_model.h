/**
 * @file varctx_model.h
 * @brief Declarations for VarCtxModel class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARCTX_MODEL_INCLUDE
#define GUARD_VARCTX_MODEL_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/varbase_interface.h>

#include <QAbstractItemModel>

QT_BEGIN_NAMESPACE
class QAbstractItemView;
QT_END_NAMESPACE

class VarDef;
class IVarValue;
class IVarCtx;

//! Evaluate the value of context based variables.
class VARMNG_EXPORT VarCtxModel : public QAbstractItemModel, public IVarBase {
    Q_OBJECT
public:

    //! Default constructor.
    VarCtxModel (
            IVarCtx * context,
            QObject *parent = 0);

    //! Destructor.
    virtual ~VarCtxModel ();

    //! The context that we're wrapping.
    IVarCtx *
    context () const {
        return context_;
    }

    //! Get the item that is selected in provided view.
    IVarValue *
    getSelectedItem (
            QAbstractItemView *view);

    //! Create the model index for an item pointer.
    QModelIndex
    toIndex (
            IVarValue * item,
            int column = 0);

    //! Convert a model index into an item pointer.
    IVarValue *
    fromIndex (
            const QModelIndex & idx) const;

    //! Tell if an index is valid for this model.
    bool
    validateIndex (
            const QModelIndex &idx,
            IVarValue *pdef = NULL) const;

    //! Find the item that has no definition associated.
    QModelIndex
    editItem ();

    //! A numeric value indicating the type of this class.
    virtual int
    vmTyId () const {
        return ContextModel;
    }

public slots:

    //! Remove all values from the model.
    void
    clear ();


    //! Read all values again.
    void
    reload ();

private slots:

    //! A value for a variable has changed.
    void
    valueChanged (
            IVarValue * val);

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

    virtual Qt::ItemFlags
    flags (
        const QModelIndex &index) const;

    virtual QVariant
    data (
        const QModelIndex &idx,
        int role = Qt::DisplayRole) const;

    virtual QVariant
    headerData (
        int section,
        Qt::Orientation orientation,
        int role = Qt::DisplayRole) const;

    virtual bool
    setData (
        const QModelIndex &index,
        const QVariant &value,
        int role = Qt::EditRole);

    //! Remove a number of rows
    virtual bool
    removeRows (
        int row,
        int count,
        const QModelIndex &parent = QModelIndex());

    virtual int
    rowCount (
        const QModelIndex &parent = QModelIndex()) const;

    virtual int
    columnCount (
        const QModelIndex &parent = QModelIndex()) const;

    virtual bool
    insertRows (
            int row,
            int count = 1,
            const QModelIndex &parent = QModelIndex ());

    Qt::DropActions
    supportedDropActions () const;

    Qt::DropActions
    supportedDragActions () const;

    bool
    canDropMimeData (
            const QMimeData *data,
            Qt::DropAction action,
            int, int,
            const QModelIndex &parent) const;

    bool
    dropMimeData (
            const QMimeData *data,
            Qt::DropAction action,
            int row, int,
            const QModelIndex &parent);

    ///@}
    /* == == == == == == == == == == == == == == == == */

private:
    IVarCtx * context_; /**< the context that we're wrapping */

}; // class VarCtxModel

#endif // GUARD_VARCTX_MODEL_INCLUDE
