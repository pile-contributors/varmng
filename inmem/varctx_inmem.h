/**
 * @file varctx_interface.h
 * @brief Declarations for IVarCtx class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARCTX_INMEM_INCLUDE
#define GUARD_VARCTX_INMEM_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/varctx_interface.h>
#include <QString>
#include <QList>


//! An evaluation context that may contain a number of variables and their values.
class VARMNG_EXPORT VarCtx : public IVarCtx {

public:

    //! Default constructor.
    VarCtx (
            const QString & name = QString (),
            const QString & label = QString (),
            const QList<IVarValue *> & vars = QList<IVarValue *> ());

    //! Destructor.
    virtual ~VarCtx ();



    /* == == == == == == == == == == == == == == == == == */
    /** @name IVarCtx interface
     */
    ///@{
public:

    //! The name of the context.
    virtual QString
    contextName () const {
        return name_;
    }

    //! The user visible name of the context (may be translated, for example).
    virtual QString
    contextLabel () const {
        return label_;
    }

    //! The list of variables associated with this context.
    virtual QList<IVarValue *>
    contextVariables () const {
        return vars_;
    }

    //! The list of variables associated with this context.
    virtual IVarValue *
    value (
            int idx) const {
        return vars_.at (idx);
    }

    //! The name of the context.
    virtual bool
    setContextName (
            const QString & s_value) {
        name_ = s_value;
        return true;
    }

    //! The user visible name of the context (may be translated, for example).
    virtual bool
    setContextLabel (
            const QString & s_value) {
        name_ = s_value;
        return true;
    }

    //! The list of variables associated with this context.
    virtual bool
    setContextVariables (
            const QList<IVarValue *> & values) {
        vars_ = values;
        return true;
    }

    //! Number of assigned variables in this context.
    virtual int
    valuesCount () const {
        return vars_.count ();
    }

    //! The index of a value inside this context.
    virtual int
    valueIndex (
            IVarValue * pdef) const {
        return vars_.indexOf (pdef);
    }

    //! Insert a value inside this context.
    virtual bool
    insertValue (
            int position,
            IVarValue * pdef);

    //! Remove a value from inside this context and delete it.
    virtual bool
    removeValue (
            int position = -1,
            IVarValue * pdef = NULL);

    //! Remove a value inside this context and return it to the caller.
    virtual IVarValue *
    takeValue (
            int position = -1,
            IVarValue * pdef = NULL);

    ///@}
    /* == == == == == == == == == == == == == == == == == */

private:
    QString name_;
    QString label_;
    QList<IVarValue *> vars_;
};

#endif // GUARD_VARCTX_INMEM_INCLUDE
