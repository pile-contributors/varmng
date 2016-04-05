/**
 * @file varfactory_inmem.cc
 * @brief Declarations for IVarValue class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARFACTORY_INMEM_INCLUDE
#define GUARD_VARFACTORY_INMEM_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/varctx_interface.h>
#include <varmng/vardef_interface.h>
#include <varmng/varvalue_interface.h>

class VarMng;

//! Factory class that creates in memory instances.
class VARMNG_EXPORT VarFactory  :
        public IVarCtxFactory,
        public IVarDefFactory,
        public IVarValueFactory {

public:

    //! A numeric value indicating the type of this class.
    virtual int
    vmTyId () const {
        return MemoryFactory;
    }

    //! Creates a variable definition.
    virtual IVarDef *
    createVarDef (
            const QString & name = QString (),
            const QString & label = QString (),
            const QString & description = QString (),
            IVarDef * parent = NULL);

    //! Creates a value associated with a variable definition.
    virtual IVarValue *
    createVarValue (
            IVarDef * def,
            IVarCtx * ctx,
            const QString & s_value);

    //! Creates a contexts.
    virtual IVarCtx *
    createVarCtx (
            VarMng * mng,
            const QString & name = QString (),
            const QString & label = QString ());


    //! Creates a context for environment variables.
    virtual IVarCtx *
    createEnvVarCtx (
            VarMng *mng);

    //! Get the one and only instance.
    static VarFactory *
    instance ();

private:
    static VarFactory instance_; /**< the one and only instance */
};

#endif // GUARD_VARFACTORY_INMEM_INCLUDE
