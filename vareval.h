/**
 * @file vareval.h
 * @brief Declarations for VarEval class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VAREVAL_INCLUDE
#define GUARD_VAREVAL_INCLUDE

#include <varmng/varmng-config.h>
#include <QList>
#include <QMap>

class VarDef;
class VarMng;
class IVarCtx;
class IVarDef;
class IVarValue;

//! Evaluate the value of context based variables.
class VARMNG_EXPORT VarEval {

public:

    //! Default constructor.
    VarEval ();

    //! Destructor.
    virtual ~VarEval ();

    //! The manager where we're assigned (NULL if empty).
    VarMng *
    manager () const;


    //! Append a context inside this list.
    bool
    appendCtx (
            IVarCtx * ctx) {
        return insertCtx (-1, ctx);
    }

    //! Append a context inside this list.
    bool
    insertCtx (
            int idx,
            IVarCtx * ctx);

    //! Find a context given its name.
    IVarCtx *
    findCtxInst (
            const QString & s_name);

    //! Find the index of a context given its name.
    int
    findCtx (
            const QString & s_name);

    //! Find the index of a context.
    int
    findCtx (
            IVarCtx * inst);

    const QList<IVarCtx*> &
    contexts () const {
        return ctx_list_;
    }

    //! Get all unique definitions.
    QList<IVarDef*>
    collectDefinitions ();

    //! Get all definitions.
    QMap<QString,QString>
    collectValues ();

    //! Get values for a list of definitions.
    QMap<QString,QString>
    collectValues (
            const QList<IVarDef*> & defs);



private:
    QList<IVarCtx*> ctx_list_;
}; // class VarEval

#endif // GUARD_VAREVAL_INCLUDE
