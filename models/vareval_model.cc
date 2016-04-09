/**
 * @file vareval_model.cc
 * @brief Definitions for VarEvalModel class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "vareval_model.h"
#include "../varmng.h"
#include "../varmng-private.h"
#include "../interface/varctx_interface.h"
#include "../interface/vardef_interface.h"
#include "../interface/varvalue_interface.h"
#include "../vareval.h"
#include <QAbstractItemView>
#include <QApplication>
#include <QFont>
#include <QDebug>

#define EVAL_MODEL_COLUMN_COUNT 3


enum EvalType {
    ValueType = -4,
    ContextType = -3
};

class EvalValue;
class EvalCtx;

class EvalItem {

public:

    ~EvalItem() {}

    //! The type of this item.
    virtual EvalType
    type () const = 0;

    //! The number of kids.
    virtual int
    kidsCount () const = 0;

    //! Convert to value if possible
    EvalValue *
    toValue ();

    //! Convert to value if possible
    EvalCtx *
    toContext ();

};

class EvalValue : public EvalItem {

public:
    EvalValue (IVarValue * val = NULL) :
        EvalItem (),
        val_(val),
        ctx_()
    {
        VARMNG_TRACE_ENTRY;
        VARMNG_TRACE_EXIT;
    }

    ~EvalValue() {
        qDeleteAll (ctx_);
    }

    //! The type of this item.
    virtual EvalType
    type () const {
        return ValueType;
    }

    //! The number of kids.
    int
    kidsCount () const {
        return ctx_.count ();
    }

    //! The name for this variable.
    QString
    varName () const {
        return definition ()->varName ();
    }

    //! The label for this variable.
    QString
    varLabel () const {
        return definition ()->varLabel ();
    }

    //! The description for this variable.
    QString
    varDescription () const {
        return definition ()->varDescription ();
    }

    //! The label for this variable.
    QString
    varValue () const {
        return val_->varValue ();
    }

    //! The definition for this variable.
    IVarDef *
    definition () const {
        return val_->definition ();
    }

    //! The value for this variable.
    IVarValue *
    value () const {
        return val_;
    }

    //! Get the index of a context in this item.
    int
    indexOf (
            const EvalCtx * it) const {
        return ctx_.indexOf (const_cast<EvalCtx *>(it));
    }

    //! Find the instance associated with a context.
    EvalCtx *
    findContext (
            IVarCtx * ctx);

    IVarValue * val_;
    QList<EvalCtx*> ctx_;
};

class EvalCtx : public EvalItem {

public:
    EvalCtx (EvalValue * parent, IVarCtx * context, IVarValue * value) :
        EvalItem (),
        parent_(parent),
        context_(context),
        value_(value)
    {
        VARMNG_TRACE_ENTRY;
        VARMNG_TRACE_EXIT;
    }

    //! The type of this item.
    virtual EvalType
    type () const {
        return ContextType;
    }

    //! The number of kids.
    int
    kidsCount () const {
        return 0;
    }

    EvalValue *
    parent () const {
        return parent_;
    }

    IVarCtx *
    context () const {
        return context_;
    }

    IVarValue *
    value () const {
        return value_;
    }

    //! The name for this context.
    QString
    contextName () const {
        return context ()->contextName ();
    }

    //! The label for this context.
    QString
    contextLabel () const {
        return context ()->contextLabel ();
    }

    //! The value for the variable in this this context.
    QString
    varValue () const {
        return value_->varValue ();
    }


    int
    indexInParent () const {
        return parent_->indexOf (this);
    }

    EvalValue * parent_;
    IVarCtx * context_;
    IVarValue * value_;
};

/**
 * @class VarEvalModel
 *
 * .
 */

/* ------------------------------------------------------------------------- */
/**
 */
VarEvalModel::VarEvalModel (QObject *parent) :
    QAbstractItemModel (parent), IVarBase (),
    evaluator_(NULL),
    values_(),
    assoc_sources_(true)
{
    VARMNG_TRACE_ENTRY;
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 */
VarEvalModel::~VarEvalModel()
{
    VARMNG_TRACE_ENTRY;
    clear ();
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarEvalModel::clear ()
{
    VARMNG_TRACE_ENTRY;
    qDeleteAll (values_);
    values_.clear();
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarEvalModel::toIndex (EvalItem *item, int column)
{
    if (item->type () == ContextType) {
        EvalCtx * ctxit = item->toContext ();
        return createIndex (ctxit->indexInParent (), column, item);
    } else if (item->type () == ValueType) {
        EvalValue * valit = item->toValue ();
        return createIndex (values_.indexOf (valit), column, item);
    } else {
        return QModelIndex ();
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EvalItem * VarEvalModel::fromIndex (const QModelIndex &idx) const
{
    if (idx.isValid()) {
        return static_cast<EvalItem*>(idx.internalPointer ());
    } else {
        return NULL;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool VarEvalModel::validateIndex (const QModelIndex &idx, EvalItem *pdef) const
{
    VARMNG_TRACE_ENTRY;
    bool b_ret = false;
    for (;;) {

        if (!idx.isValid())
            break;

        if ((idx.column () < 0) || (idx.column () >= EVAL_MODEL_COLUMN_COUNT))
            break;

        EvalItem * def = pdef;
        if (def == NULL) {
            def = static_cast<EvalItem *> (idx.internalPointer());
            if (def == NULL)
                break;
        }

        if (def->type() == ValueType) {
            // EvalValue * evalv = def->toValue ();
            if ((idx.row () < 0) || (idx.row () >= values_.count()))
                break;
        } else if (def->type() == ContextType) {
            EvalCtx * evalc = def->toContext ();
            EvalValue * evalv = evalc->parent ();
            if ((idx.row () < 0) || (idx.row () >= evalv->kidsCount()))
                break;
        } else {
            break;
        }

        b_ret = true;
        break;
    }
    VARMNG_TRACE_EXIT;
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EvalItem * VarEvalModel::getSelectedItem (QAbstractItemView *view)
{
    VARMNG_TRACE_ENTRY;
    EvalItem * result = NULL;
    for (;;) {
        if (view == NULL)
            break;
        QItemSelectionModel * sm = view->selectionModel ();
        if (sm == NULL)
            break;
        result = fromIndex (sm->currentIndex ());
        break;
    }
    VARMNG_TRACE_EXIT;
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarEvalModel::setEvaluator (VarEval *eval)
{
    VARMNG_TRACE_ENTRY;

    if ((evaluator_ != NULL) && (evaluator_->manager() != NULL)) {
        disconnect(evaluator_->manager (), &VarMng::valueChanged,
                this, &VarEvalModel::valueChanged);
        disconnect(evaluator_->manager (), &VarMng::valueCreated,
                this, &VarEvalModel::reload);
    }

    evaluator_ = eval;

    if ((evaluator_ != NULL) && (evaluator_->manager() != NULL)) {
        connect(evaluator_->manager (), &VarMng::valueChanged,
                this, &VarEvalModel::valueChanged);
        connect(evaluator_->manager (), &VarMng::valueCreated,
                this, &VarEvalModel::reload);
    }

    reload ();
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
IVarValue * VarEvalModel::reloadVariable (
        EvalValue * defv, IVarDef * def, const QList<IVarCtx*> & ctxs)
{
    if (defv->ctx_.count() > 0) {
        beginRemoveRows (toIndex (defv), 0, defv->ctx_.count()-1);
        qDeleteAll (defv->ctx_);
        defv->ctx_.clear ();
        endRemoveRows ();
    }

    IVarValue * v = NULL;
    QList<EvalCtx*>  newins;
    foreach(IVarCtx * iter, ctxs) {
        IVarValue * vtmp = iter->value (def);
        if (vtmp != NULL) {
            v = vtmp;
            if (assoc_sources_) {
                EvalCtx * defc = new EvalCtx (defv, iter, v);
                newins.append (defc);
            }
        }
    }

    if (assoc_sources_) {
        beginInsertRows (toIndex (defv), 0, newins.count()-1);
        defv->ctx_ = newins;
        endInsertRows ();
    }
    return v;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarEvalModel::reload ()
{
    VARMNG_TRACE_ENTRY;
    beginResetModel ();
    clear ();
    if (evaluator_ != NULL) {
        QList<IVarDef*> defs = evaluator_->collectDefinitions ();
        QList<IVarCtx*> ctxs = evaluator_->contexts ();

        foreach (IVarDef * def, defs) {
            EvalValue * defv = new EvalValue ();
            IVarValue * v = reloadVariable (defv, def, ctxs);

            if (v == NULL) {
                delete defv;
            } else {
                defv->val_ = v;
                values_.append (defv);
            }
        }
    }

    endResetModel ();
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarEvalModel::valueChanged (IVarValue *val)
{
    if (val != NULL) {
        EvalItem * it = findItem (val->definition()->varName ());
        if (it != NULL) {
            EvalValue * defv = it->toValue ();
            QModelIndex mi (toIndex (defv, 1));
            EvalCtx * ctx = defv->findContext (val->context ());
            if (ctx != NULL) {
                QModelIndex mi = toIndex (ctx, 1);
                dataChanged (mi, mi);
            } else if (assoc_sources_) {
                QList<IVarCtx*> ctxs = evaluator_->contexts ();
                defv->val_ = reloadVariable (
                            defv, defv->definition(), ctxs);
            }
            dataChanged (mi, mi);
        }
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void VarEvalModel::setExtended (bool b_extended)
{
    if (assoc_sources_ != b_extended) {
        assoc_sources_ = b_extended;
        reload ();
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * For now this method simple calls reload thus generating a full recompute.
 * In the future it can be smarter.
 *
 * @param ctx The context that changed.
 * @param val A value that belongs to that context (optional)
 */
void VarEvalModel::contextChanged (IVarCtx *ctx, IVarValue *val)
{
    reload ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarEvalModel::kidsCount (EvalItem *item) const
{
    if (item == NULL) {
        return values_.count ();
    } else {
        return item->kidsCount ();
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EvalItem *VarEvalModel::findItem (IVarDef *def) const
{
    foreach (EvalValue*iter, values_) {
        if (iter->value ()->definition() == def) {
            return iter;
        }
    }
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EvalItem *VarEvalModel::findItem (IVarValue *def) const
{
    foreach (EvalValue*iter, values_) {
        if (iter->value () == def) {
            return iter;
        }
    }
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EvalItem *VarEvalModel::findItem (const QString & name) const
{
    foreach (EvalValue*iter, values_) {
        if (iter->value ()->definition()->varName () == name) {
            return iter;
        }
    }
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarEvalModel::index (
        int row, int column, const QModelIndex &parent) const
{
    VARMNG_TRACE_ENTRY;
    QModelIndex result;
    for (;;) {

        EvalItem * pdef = static_cast<EvalItem *>(parent.internalPointer());
        if (!parent.isValid ()) {
            pdef = NULL;
        } else if (!validateIndex (parent, pdef)) {
            break;
        }

        if ((column < 0) || (column >= EVAL_MODEL_COLUMN_COUNT))
            break;

        if ((row < 0) || (row >= kidsCount (pdef)))
            break;

        if (pdef == NULL) {
            result = createIndex (row, column,
                                  static_cast<EvalItem *>(values_.at (row)));
        } else if (pdef->type () == ValueType) {
            result = createIndex (row, column,
                                  static_cast<EvalItem *>(
                                      pdef->toValue()->ctx_.at (row)));
        } else {
            // no kids for context
        }
        break;
    }
    VARMNG_TRACE_EXIT;
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QModelIndex VarEvalModel::parent (const QModelIndex &child) const
{
    VARMNG_TRACE_ENTRY;
    QModelIndex result;
    for (;;) {
        if (!validateIndex (child))
            break;
        EvalItem * def = static_cast<EvalItem *> (child.internalPointer());
        if (def == NULL)
            break;

        if (def->type () == ValueType) {
            break;
        } else if (def->type () == ContextType) {
            EvalValue * defv = def->toContext ()->parent ();
            result = createIndex (values_.indexOf (defv), 0,
                                  static_cast<EvalItem *>(defv));
        }
        break;
    }
    VARMNG_TRACE_EXIT;
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
Qt::ItemFlags VarEvalModel::flags (const QModelIndex &idx) const
{
    return QAbstractItemModel::flags (idx);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant VarEvalModel::data (const QModelIndex & idx, int role) const
{
    VARMNG_TRACE_ENTRY;
    QVariant result;
    for (;;) {
        if (!validateIndex (idx)) {
            break;
        }

        if (
                (role != Qt::DisplayRole) &&
                (role != Qt::EditRole) &&
                (role != Qt::FontRole)) {
            break;
        }

        EvalItem * pdef = static_cast<EvalItem *> (idx.internalPointer());
        if (pdef->type () == ValueType) {
            if (role == Qt::FontRole)
                break;
            EvalValue * defv = pdef->toValue ();
            switch (idx.column ()) {
            case 0:
                result = defv->varLabel ();
                break;
            case 1:
                result = defv->varValue ();
                break;
            case 2:
                result = defv->varDescription ();
                break;
            }
        } else if (pdef->type () == ContextType) {
            EvalCtx * defc = pdef->toContext ();
            if (role == Qt::FontRole) {
                if (idx.row () == defc->parent ()->kidsCount() - 1) {
                    break;
                }
                QFont fnt (QApplication::font ());
                fnt.setStrikeOut (true);
                result = fnt;
            } else {
                switch (idx.column ()) {
                case 0:
                    result = defc->contextLabel ();
                    break;
                case 1:
                    result = defc->varValue ();
                }
            }
        }

        break;
    }
    VARMNG_TRACE_EXIT;
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QVariant VarEvalModel::headerData (
        int section, Qt::Orientation orientation, int role) const
{
    VARMNG_TRACE_ENTRY;
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
    VARMNG_TRACE_EXIT;
    return QAbstractItemModel::headerData (section, orientation, role);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarEvalModel::rowCount (const QModelIndex & parent) const
{
    int result = 0;
    for (;;) {
        EvalItem * pdef = static_cast<EvalItem *>(
                    parent.internalPointer());
        result = kidsCount (pdef);
        break;
    }
    return result;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
int VarEvalModel::columnCount (const QModelIndex &) const
{
    return EVAL_MODEL_COLUMN_COUNT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EvalValue *EvalItem::toValue()
{
    if (type () == ValueType) {
        return static_cast<EvalValue *>(this);
    } else {
        return NULL;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EvalCtx *EvalItem::toContext()
{
    if (type () == ContextType) {
        return static_cast<EvalCtx *>(this);
    } else {
        return NULL;
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
EvalCtx * EvalValue::findContext (IVarCtx *ctx)
{
    foreach(EvalCtx * iter,  ctx_) {
        if (iter->context () == ctx) {
            return iter;
        }
    }
    return NULL;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
