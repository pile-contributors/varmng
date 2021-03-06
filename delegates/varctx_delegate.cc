/**
 * @file varctx_delegate.cc
 * @brief Definitions for IVarCtx class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varctx_delegate.h"
#include "../varmng-private.h"
#include "../models/vardef_model.h"
#include "../models/varctx_model.h"
#include "../interface/varctx_interface.h"
#include "../varmng.h"

#include <QStyleOptionViewItem>
#include <QCompleter>
#include <QLineEdit>
#include <QTreeView>
#include <QSortFilterProxyModel>

/**
 * @class VarCtxDeleg
 *
 */

/* ------------------------------------------------------------------------- */
/**
 */
VarCtxDeleg::VarCtxDeleg (QObject * parent) :
    QStyledItemDelegate (parent), IVarBase ()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 */
VarCtxDeleg::~VarCtxDeleg()
{
    VARMNG_TRACE_ENTRY;

    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarCtxDeleg::installInto (QTreeView *tv)
{
    tv->setItemDelegateForColumn (0, new VarCtxDeleg (tv));
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QWidget * VarCtxDeleg::createEditor (
        QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
{
    QWidget * w = QStyledItemDelegate::createEditor (
                parent, option, index);

    const VarCtxModel * m = qobject_cast<const VarCtxModel*>(
                index.model ());
    for (;;) {
        if (m == NULL) {
            break;
        }

        IVarValue * value = m->fromIndex (index);
        if (value == NULL) {
            break;
        }

        switch (index.column ()) {
        case 0: {
            QLineEdit * le = qobject_cast<QLineEdit *>(w);
            if (le != NULL) {
                VarDefModel * mdl = new VarDefModel (m->manager(), w);
                QCompleter * cpl = new QCompleter (mdl, w);
                cpl->setCaseSensitivity (Qt::CaseInsensitive);
                cpl->setCompletionColumn (0);
                le->setCompleter (cpl);
                QTreeView * tv = qobject_cast<QTreeView*>(
                            parent->parentWidget ());
                if (tv != NULL) {
                    le->setMinimumWidth (
                                tv->columnWidth (index.column ()));
                }
            }
            break;}
        }

        break;
    }
    if (m != NULL) {
    }
    return w;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarCtxDeleg::setModelData (
        QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const
{
    const VarCtxModel * m = qobject_cast<const VarCtxModel*>(
                model);
    if (m == NULL) {
        const QSortFilterProxyModel * msp = qobject_cast<const QSortFilterProxyModel*>(
                    model);
        if (msp == NULL)
            return;
        m = qobject_cast<const VarCtxModel*>(
                    msp->sourceModel ());
        if (m == NULL)
            return;
    }
    VarMng * mng = m->manager ();
    QLineEdit * le = qobject_cast<QLineEdit *>(editor);

    // Create the definition if it does not already exists.
    /*IVarDef * def = */mng->getDefinition (le->text (), true);

    QStyledItemDelegate::setModelData (editor, model, index);
}
/* ========================================================================= */
