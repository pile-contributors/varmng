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

    //! Insert a definition inside this node.
    bool
    appendKidVarDef (
            IVarDef * pdef) {
        return insertKidVarDef (-1, pdef);
    }

    /* == == == == == == == == == == == == == == == == == */
    /** @name IVarDef interface
     */
    ///@{
public:

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


    //! Change the name of the variable.
    virtual bool
    setVarName (
            const QString &/*name*/) {
        return false;
    }

    //! Change the label of the variable.
    virtual bool
    setVarLabel (
            const QString &/*label*/) {
        return false;
    }

    //! Change the description of the variable.
    virtual bool
    setVarDescription (
            const QString &/*description*/) {
        return false;
    }

    //! Set the kids of a group.
    virtual bool
    setVarKids (
            const QList<IVarDef *> &/*kids*/) {
        return false;
    }

    //! The group where the variable belongs.
    virtual IVarDef *
    varGroup () const {
        return NULL;
    }

    //! Change the group where the variable belongs.
    virtual bool
    setVarGroup (IVarDef *) {
        return false;
    }

    //! The group where the variable belongs.
    virtual QList<IVarDef *>
    varKids () const {
        return QList<IVarDef *>();
    }

    //! The group where the variable belongs.
    virtual IVarDef *
    varKid (
            int idx) const {
        return varKids ().at (idx);
    }

    //! Number of kids in this node (leafs return 0).
    virtual int
    varKidsCount () const {
        return varKids ().count ();
    }

    //! Tell if this instance is a node or a leaf.
    virtual bool
    isVarNode () const {
        return varKidsCount () == 0;
    }

    //! Tell if this instance is at the top level or is part of a node.
    virtual bool
    isVarTopLevel () const {
        return varGroup () == NULL;
    }

    //! The index of a definition inside this node.
    virtual int
    varKidIndex (
            IVarDef * pdef) const {
        return varKids ().indexOf (pdef);
    }

    //! Tell if a definition is part of this node.
    virtual bool
    isVarKid (
            IVarDef * pdef) const {
        return varKidIndex (pdef) == -1;
    }

    //! Insert a definition inside this node.
    virtual bool
    insertKidVarDef (
            int /* position */,
            IVarDef * /* pdef */) {
        return false;
    }

    //! Remove a definition from inside this node and delete it.
    virtual bool
    removeKidVarDef (
            int /* position */ = -1,
            IVarDef * /* pdef */ = NULL) {
        return false;
    }

    //! Remove a definition inside this node and return it to the caller.
    virtual IVarDef *
    takeKidVarDef (
            int /* position */ = -1,
            IVarDef * /* pdef */ = NULL) {
        return NULL;
    }

    ///@}
    /* == == == == == == == == == == == == == == == == == */

}; // class IVarDef


//! Factory class for creating variable definitions.
class VARMNG_EXPORT IVarDefFactory {
public:

    //! Creates a variable definition.
    virtual IVarDef *
    createVarDef (
            const QString & name = QString (),
            const QString & label = QString (),
            const QString & description = QString (),
            IVarDef * parent = NULL) = 0;

}; // class IVarDefFactory


#endif // GUARD_VARDEF_INTERFACE_INCLUDE
