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

    //! Constructor for a root definition  (used with VarMng).
    VarDef (
        VarMng * mng);


    //! Destructor.
    virtual ~VarDef ();

    //! A numeric value indicating the type of this class.
    virtual int
    vmTyId () const {
        return MemoryDefinition;
    }

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

    //! Change the name of the variable.
    virtual bool
    setVarName (
            const QString &name);

    //! Change the label of the variable.
    virtual bool
    setVarLabel (
            const QString &label);

    //! Change the description of the variable.
    virtual bool
    setVarDescription (
            const QString &description);

    //! Set the kids of a group.
    virtual bool
    setVarKids (
            const QList<IVarDef *> &kids);

    //! The group where the variable belongs.
    virtual IVarDef *
    varGroup () const {
        return group_;
    }

    //! Change the group where the variable belongs.
    virtual bool
    setVarGroup (IVarDef * value) {
        group_ = value;
        return true;
    }

    //! The group where the variable belongs.
    virtual QList<IVarDef *>
    varKids () const {
        return kids_;
    }

    //! The group where the variable belongs.
    virtual IVarDef *
    varKid (
            int idx) const {
        return kids_.at (idx);
    }

    //! Tell if this instance is a node or a leaf.
    virtual bool
    isVarNode () const {
        return kids_.count () == 0;
    }

    //! Number of kids in this node (leafs return 0).
    virtual int
    varKidsCount () const {
        return kids_.count ();
    }

    //! Insert a definition inside this node.
    virtual bool
    insertKidVarDef (
            int position,
            IVarDef * pdef);

    //! Remove a definition from inside this node and delete it.
    virtual bool
    removeKidVarDef (
            int position = -1,
            IVarDef * pdef = NULL);

    //! Remove a definition inside this node and return it to the caller.
    virtual IVarDef *
    takeKidVarDef (
            int position = -1,
            IVarDef * pdef = NULL);

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
