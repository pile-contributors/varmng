/**
 * @file vardef_inmem.h
 * @brief Declarations for IVarDef class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARDEF_INMAIN_INCLUDE
#define GUARD_VARDEF_INMAIN_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/vardef_interface.h>

//! Interface for variable (or group of variables) definition.
class VARMNG_EXPORT VarDef : public IVarDef {

public:

    //! Default constructor.
    VarDef (
        const QString & name = QString (),
        const QString & label = QString (),
        const QString & description = QString (),
        IVarDef * group = NULL,
        const QList<IVarDef *> & kids = QList<IVarDef *> ());

    //! Destructor.
    virtual ~VarDef ();

    //! Change the name of the variable.
    void
    setVarName (
            const QString &name);

    //! Change the label of the variable.
    void
    setVarLabel (
            const QString &label);

    //! Change the description of the variable.
    void
    setVarDescription (
            const QString &description);

    //! Set the kids of a group.
    void
    setVarKids (
            const QList<IVarDef *> &kids);



    /* == == == == == == == == == == == == == == == == == */
    /** @name IVarDef interface
     */
    ///@{
public:

    //! The name of the variable.
    virtual QString
    varName () const {
        return name_;
    }

    //! The user visible name of the variable (may be translated, for example).
    virtual QString
    varLabel () const {
        return label_;
    }

    //! The description of the variable.
    virtual QString
    varDescription () const {
        return description_;
    }


    //! The group where the variable belongs.
    virtual IVarDef *
    varGroup () const {
        return group_;
    }

    //! The group where the variable belongs.
    virtual QList<IVarDef *>
    varKids () const {
        return kids_;
    }

    ///@}
    /* == == == == == == == == == == == == == == == == == */



private:
    QString name_;
    QString label_;
    QString description_;
    IVarDef * group_;
    QList<IVarDef *> kids_;
};

#endif // GUARD_VARDEF_INMAIN_INCLUDE
