/**
 * @file varctx_delegate.h
 * @brief Declarations for IVarCtx class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARCTX_DELEGATE_INCLUDE
#define GUARD_VARCTX_DELEGATE_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/varctx_interface.h>
#include <varmng/varbase_interface.h>
#include <QString>
#include <QStyledItemDelegate>

class IVarCtx;

QT_BEGIN_NAMESPACE
class QTreeView;
QT_END_NAMESPACE

//! An evaluation context that may contain a number of variables and their values.
class VARMNG_EXPORT VarCtxDeleg : public QStyledItemDelegate, public IVarBase  {
    Q_OBJECT
public:

    //! Default constructor.
    VarCtxDeleg (
            QObject * parent = NULL);

    //! Destructor.
    virtual ~VarCtxDeleg ();


    //! Install this completer to a treeview hosting a context.
    static void
    installInto (
            QTreeView * tv);


    //! A numeric value indicating the type of this class.
    virtual int
    vmTyId () const {
        return ContextDelegate;
    }

    /* == == == == == == == == == == == == == == == == == */
    /** @name QStyledItemDelegate interface
     */
    ///@{
public:

    QWidget *
    createEditor (
            QWidget *parent,
            const QStyleOptionViewItem &option,
            const QModelIndex &index) const;

    void
    setModelData (
            QWidget *editor,
            QAbstractItemModel *model,
            const QModelIndex &index) const;

    ///@}
    /* == == == == == == == == == == == == == == == == == */

};

#endif // GUARD_VARCTX_DELEGATE_INCLUDE
