/**
 * @file varctx_interface.h
 * @brief Declarations for IVarCtx class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARCTX_INTERFACE_INCLUDE
#define GUARD_VARCTX_INTERFACE_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/varbase_interface.h>
#include <QString>
#include <QList>

class IVarDef;
class IVarValue;
class IVarDefFactory;
class IVarValueFactory;
class VarMng;

//! An evaluation context that may contain a number of variables and their values.
class VARMNG_EXPORT IVarCtx : public IVarBase {

public:

    //! Default constructor.
    IVarCtx (
            VarMng *mng);

    //! Destructor.
    virtual ~IVarCtx ();

    //! Append a value inside this context.
    bool
    appendValue (
            IVarValue * value) {
        return insertValue (-1, value);
    }

    //! Find an assigned variable by its name (or create a new one).
    IVarValue *
    findValue (
            const QString & s_name);

    //! The manager where this context is rooted.
    VarMng *
    manager () const {
        return mng_;
    }

    //! Load environment variables to this context.
    int
    loadEnvVariables ();

    //! Shortcut for creating a value through the manager.
    IVarValue *
    createVarValue (
            IVarDef * def,
            const QString & s_value,
            int i = -1);

    //! Find first item that has no associated definition.
    IVarValue *
    firstDegenerate () const;


    //! A numeric value indicating the type of this class.
    virtual int
    vmTyId () const {
        return BasicContext;
    }

protected:

    //! Set the manager where this context is rooted.
    void
    setManager (
            VarMng * mng) {
        mng_ = mng;
    }


    /* == == == == == == == == == == == == == == == == == */
    /** @name IVarCtx interface
     */
    ///@{

public:

    //! The name of the context.
    virtual QString
    contextName () const = 0;

    //! The user visible name of the context (may be translated, for example).
    virtual QString
    contextLabel () const {
        return contextName ();
    }

    //! The list of variables associated with this context.
    virtual QList<IVarValue *>
    contextVariables () const = 0;

    //! The value at a particular index.
    virtual IVarValue *
    value (
            int idx) const {
        return contextVariables ().at (idx);
    }

    //! The value for a definition.
    virtual IVarValue *
    value (
            IVarDef * pdef) const;

    //! The name of the context.
    virtual bool
    setContextName (
            const QString & /* s_value */) {
        return false;
    }

    //! The user visible name of the context (may be translated, for example).
    virtual bool
    setContextLabel (
            const QString & /* s_value */) {
        return false;
    }

    //! The list of variables associated with this context.
    virtual bool
    setContextVariables (
            const QList<IVarValue *> & /* values */) {
        return false;
    }

    //! Number of assigned variables in this context.
    virtual int
    valuesCount () const {
        return contextVariables ().count ();
    }

    //! The index of a definition inside this context.
    virtual int
    valueIndex (
            IVarDef * pdef) const;

    //! The index of a value inside this context.
    virtual int
    valueIndex (
            IVarValue * value) const;

    //! Insert a value inside this context.
    virtual bool
    insertValue (
            int /* position */,
            IVarValue * /* pdef */) {
        return false;
    }

    //! Remove a value from inside this context and delete it.
    virtual bool
    removeValue (
            int /* position */ = -1,
            IVarValue * /* pdef */ = NULL) {
        return false;
    }

    //! Remove all variables from this context.
    virtual void
    clearValues () {
        for (int i = valuesCount () - 1; i >= 0; ++i) {
            removeValue (i);
        }
    }

    ///@}
    /* == == == == == == == == == == == == == == == == == */


private:
    VarMng * mng_;
}; // class IVarCtx


//! Factory class for creating contexts for values associated with variables.
class VARMNG_EXPORT IVarCtxFactory : public IVarBase {
public:

    //! A numeric value indicating the type of this class.
    virtual int
    vmTyId () const;

    //! Creates a context.
    virtual IVarCtx *
    createVarCtx (
            VarMng *mng,
            const QString & name = QString (),
            const QString & label = QString ()) = 0;

}; // class IVarCtxFactory


#endif // GUARD_VARCTX_INTERFACE_INCLUDE
