/**
 * @file vardef_interface.h
 * @brief Declarations for IVarDef class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARDEF_INTERFACE_INCLUDE
#define GUARD_VARDEF_INTERFACE_INCLUDE

#include <varmng/varmng-config.h>
#include <QString>
#include <QList>

//! Interface for variable (or group of variables) definition.
class VARMNG_EXPORT IVarDef {

public:

    //! Default constructor.
    IVarDef ();

    //! Destructor.
    virtual ~IVarDef ();

    //! The name of the variable.
    virtual QString
    varName () const = 0;

    //! The user visible name of the variable (may be translated, for example).
    virtual QString
    varLabel () const {
        return varName ();
    }

    //! The description of the variable.
    virtual QString
    varDescription () const = 0;


    //! The group where the variable belongs.
    virtual IVarDef *
    varGroup () const {
        return NULL;
    }

    //! The group where the variable belongs.
    virtual QList<IVarDef *>
    varKids () const {
        return QList<IVarDef *>();
    }
};

#endif // GUARD_VARDEF_INTERFACE_INCLUDE
