/**
 * @file varmng.h
 * @brief Declarations for VarMng class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARMNG_H_INCLUDE
#define GUARD_VARMNG_H_INCLUDE

#include <varmng/varmng-config.h>
#include <varmng/vardef_inmem.h>
#include <QObject>

class IVarDef;
class IVarValue;
class IVarCtx;
class IVarValueFactory;
class IVarCtxFactory;
class IVarDefFactory;

//! Manages variable definition tree and variable instantiations.
class VARMNG_EXPORT VarMng : public QObject {
    Q_OBJECT
public:

    //! Default constructor.
    VarMng (
            QObject * parent = NULL);

    //! Destructor.
    virtual ~VarMng ();

    //! Get the number of definitions in the manager.
    int
    definitionsCount () const {
        return def_root_.varKidsCount ();
    }

    //! Append a definition to the internal list.
    bool
    appendDefinition (
            IVarDef * def) {
        return def_root_.appendKidVarDef (def);
    }

    //! Get the variable with this name; optionally,create if not found.
    IVarDef *
    getDefinition (
            const QString & s_name,
            bool b_create = false);

    //! Internal definition at the top of the hierarchy.
    VarDef *
    rootVarDef () {
        return &def_root_;
    }


    //! Creates a variable definition.
    IVarDef *
    createVarDef (
            const QString & name = QString (),
            const QString & label = QString (),
            const QString & description = QString (),
            IVarDef * parent = NULL);

    //! Creates a value associated with a variable definition.
    IVarValue *
    createVarValue (
            IVarDef * def,
            IVarCtx * ctx,
            const QString & s_value);

    //! Creates a context.
    IVarCtx *
    createVarCtx (
            const QString & name = QString (),
            const QString & label = QString ());

    //! Creates and populates a context from environment variables.
    IVarCtx *
    createEnvVarCtx ();

    //! Changing the value through the manager also signals the change.
    bool
    changeValue (
            IVarValue * val,
            const QString & s_value);

    //! Change the definition associated with a value.
    bool
    setValueDefinition (
            IVarValue * val,
            IVarDef * def);

signals:

    //! A definition was created and added to the manager.
    void
    definitionCreated (
            IVarDef * def);

    //! A definition was created and added to a context.
    void
    valueCreated (
            IVarValue * val);

    //! A context was created and added to the manager.
    void
    contextCreated (
            IVarCtx * def);

    //! A variable was assigned a new value.
    void
    valueChanged (
            IVarValue * def);

private:
    VarDef def_root_; /**< the host for all definitions in this instance */
    IVarValueFactory * value_factory_; /**< factory for values */
    IVarCtxFactory * context_factory_; /**< factory for contexts */
    IVarDefFactory * def_factory_; /**< factory for definitions */
};

#endif // GUARD_VARMNG_H_INCLUDE
