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
#include <varmng/varbase_interface.h>
#include <QAbstractItemModel>


QT_BEGIN_NAMESPACE
class QAbstractItemView;
QT_END_NAMESPACE

class VarEval;
class IVarValue;
class IVarDef;
class IVarCtx;
class EvalValue;
class EvalItem;

//! A model to present the results of evaluation.
class VARMNG_EXPORT VarEvalModel : public QAbstractItemModel, public IVarBase {
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
            EvalItem * item,
            int column = 0);

    //! Convert a model index into an item pointer.
    EvalItem *
    fromIndex (
            const QModelIndex & idx) const;

    //! Tell if an index is valid for this model.
    bool
    validateIndex (
            const QModelIndex & idx,
            EvalItem *pdef = NULL) const;

    //! Get the item that is selected in provided view.
    EvalItem *
    getSelectedItem (
            QAbstractItemView * view);

    //! Get the evaluator instance.
    VarEval *
    evaluator () const {
        return  evaluator_;
    }

    //! Change the evaluator instance (implies reload()).
    void
    setEvaluator (
            VarEval * eval);

    //! Is this the extended model or the simple one?
    bool
    isExtended () const {
        return assoc_sources_;
    }

    //! Switch between extended and simple subtypes.
    void
    setExtended (
            bool b_extended = true);

    //! Switch between extended and simple subtypes.
    void
    setSimple () {
        setExtended (false);
    }

    //! A numeric value indicating the type of this class.
    virtual int
    vmTyId () const {
        return EvaluationModel;
    }

public slots:

    //! Remove all cached items.
    void
    clear();

    //! Scan the evaluator all over again.
    void
    reload ();

private slots:

    //! A value for a variable has changed.
    void
    valueChanged (
            IVarValue * val);

protected:

    int
    kidsCount (
            EvalItem * item) const;

private:

    //! Find internal item associated with a definition.
    EvalItem *
    findItem (
            IVarDef * def) const;

    //! Find internal item associated with a value.
    EvalItem *
    findItem (
            IVarValue * def) const;

    //! Find internal item associated with a variable name.
    EvalItem *
    findItem (
            const QString & name) const;


    IVarValue *
    reloadVariable (
            EvalValue *defv,
            IVarDef *def,
            const QList<IVarCtx *> & ctxs);

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

    int
    rowCount (
        const QModelIndex &parent = QModelIndex()) const;

    int
    columnCount (
        const QModelIndex &parent = QModelIndex()) const;

    ///@}
    /* == == == == == == == == == == == == == == == == */

private:

    VarEval * evaluator_;
    QList<EvalValue*> values_; /**< the list of values */
    bool assoc_sources_; /**< just list variables or list values in each context */

}; // class VarEvalModel

#endif // GUARD_VAREVAL_MODEL_INCLUDE
