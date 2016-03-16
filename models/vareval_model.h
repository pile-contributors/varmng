/**
 * @file vareval_model.h
 * @brief Declarations for VarEvalModel class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VAREVAL_MODEL_INCLUDE
#define GUARD_VAREVAL_MODEL_INCLUDE

#include <varmng/varmng-config.h>
#include <QAbstractItemModel>


QT_BEGIN_NAMESPACE
class QAbstractItemView;
QT_END_NAMESPACE


//! A model to present the results of evaluation.
class VARMNG_EXPORT VarEvalModel : public QAbstractItemModel {
    Q_OBJECT
public:

    //! Default constructor.
    VarEvalModel (
            QObject *parent = 0);

    //! Destructor.
    virtual ~VarEvalModel ();

    //! Create the model index for an item pointer.
    QModelIndex
    toIndex (
            void * item);

    //! Convert a model index into an item pointer.
    void *
    fromIndex (
            const QModelIndex & idx) const;

    //! Tell if an index is valid for this model.
    bool
    validateIndex (
            const QModelIndex & idx) const;

    //! Get the item that is selected in provided view.
    void *
    getSelectedItem (
            QAbstractItemView * view);


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

    int
    rowCount (
        const QModelIndex &parent = QModelIndex()) const;

    int
    columnCount (
        const QModelIndex &parent = QModelIndex()) const;

    ///@}
    /* == == == == == == == == == == == == == == == == */


}; // class VarEvalModel

#endif // GUARD_VAREVAL_MODEL_INCLUDE
