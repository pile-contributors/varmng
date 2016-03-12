/**
 * @file varvalue_interface.h
 * @brief Declarations for IVarValue class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARVALUE_INTERFACE_INCLUDE
#define GUARD_VARVALUE_INTERFACE_INCLUDE

#include <varmng/varmng-config.h>

class IVarDef;

//! A variable associated with a value.
class VARMNG_EXPORT IVarValue {

public:

    //! Default constructor.
    IVarValue (
            IVarDef * def);

    //! Destructor.
    virtual ~IVarValue ();

    //! The definition for this variable.
    IVarDef *
    definition () const {
        return def_;
    }


    /* == == == == == == == == == == == == == == == == == */
    /** @name IVarValue interface
     */
    ///@{
public:

    //! Get the value in this instance.
    virtual QString
    varValue () const = 0;

    ///@}
    /* == == == == == == == == == == == == == == == == == */


private:
    IVarDef * def_; /**< the definition for this variable */
};

#endif // GUARD_VARVALUE_INTERFACE_INCLUDE
