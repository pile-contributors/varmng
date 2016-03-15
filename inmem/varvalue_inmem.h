/**
 * @file varvalue_interface.h
 * @brief Declarations for IVarValue class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARVALUE_INMEM_INCLUDE
#define GUARD_VARVALUE_INMEM_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/varvalue_interface.h>
#include <QString>

//! A variable associated with a value.
class VARMNG_EXPORT VarValue  : public IVarValue {

public:

    //! Default constructor.
    VarValue (
            IVarDef * def,
            const QString & s_value);

    //! Destructor.
    virtual ~VarValue ();


    /* == == == == == == == == == == == == == == == == == */
    /** @name IVarValue interface
     */
    ///@{
public:

    //! Get the value in this instance.
    virtual QString
    varValue () const {
        return s_value_;
    }

    //! Change the value of the variable.
    virtual bool
    setVarValue (
            const QString & s_value);

    ///@}
    /* == == == == == == == == == == == == == == == == == */

private:
    QString s_value_;
};

#endif // GUARD_VARVALUE_INMEM_INCLUDE
