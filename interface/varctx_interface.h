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
#include <QString>
#include <QList>

class IVarValue;

//! An evaluation context that may contain a number of variables and their values.
class VARMNG_EXPORT IVarCtx {

public:

    //! Default constructor.
    IVarCtx ();

    //! Destructor.
    virtual ~IVarCtx ();


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

    ///@}
    /* == == == == == == == == == == == == == == == == == */


private:

}; // class IVarCtx


//! Factory class for creating contexts for values associated with variables.
class VARMNG_EXPORT IVarCtxFactory {
public:

    //! Creates a contexts.
    virtual IVarCtx *
    createVarCtx (
            const QString & name = QString (),
            const QString & label = QString ()) = 0;

}; // class IVarCtxFactory


#endif // GUARD_VARCTX_INTERFACE_INCLUDE
