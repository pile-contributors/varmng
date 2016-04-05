/**
 * @file varvalue_interface.h
 * @brief Declarations for IVarValue class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_VARBASE_INTERFACE_INCLUDE
#define GUARD_VARBASE_INTERFACE_INCLUDE

#include <varmng/varmng-config.h>

class IVarDef;
class IVarCtx;
class VarMng;

//! Common ground for all objects in this pile.
class VARMNG_EXPORT IVarBase {

public:

    //! Values used with
    enum PredefinedType {
        InvalidType = -1,

        /* The manager and delegates */

        BasicManager,
        ContextDelegate,
        Evaluator,

        /* Building blocks */

        BasicDefinition,
        BasicValue,
        BasicContext,

        MemoryDefinition,
        MemoryValue,
        MemoryContext,

        DatabaseDefinition,
        DatabaseValue,
        DatabaseContext,

        /* factories */

        BasicDefinitionFactory,
        BasicValueFactory,
        BasicContextFactory,

        MemoryFactory,

        /* Models */

        ContextModel,
        DefinitionModel,
        EvaluationModel,


        /* user defined value should be at least this large */
        UserDefinedType = 1000
    };

    //! Destructor.
    virtual ~IVarBase () {}

    //! A numeric value indicating the type of the class.
    virtual int
    vmTyId () const = 0;


}; // IVarValue


#endif // GUARD_VARBASE_INTERFACE_INCLUDE
