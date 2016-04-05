/**
 * @file varvalue_interface.cc
 * @brief Definitions for IVarValue class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2016 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "varvalue_interface.h"
#include "vardef_interface.h"
#include "../varmng-private.h"
#include "../varmng.h"

/**
 * @class IVarValue
 *
 */

/* ------------------------------------------------------------------------- */
/**
 * The pointer to the definition is stored internally and can be retrieved by
 * using the definition () method.
 */
IVarValue::IVarValue (IVarDef *def, IVarCtx * ctx) : IVarBase (),
    def_(def),
    ctx_(ctx)
{
    VARMNG_TRACE_ENTRY;
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
IVarValue::~IVarValue()
{
    VARMNG_TRACE_ENTRY;
    VARMNG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
VarMng *IVarValue::manager () const
{
    if (def_ == NULL) {
        return NULL;
    } else {
        return def_->manager ();
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Instead of directly setting the value in this instance the method uses
 * the manager to set the value which, in turn, uses the setVarValue() method
 * and it also emits a signal in case of success.
 * @param s_value new value
 * @return true if the value was changed
 */
bool IVarValue::setValue (const QString &s_value)
{
    if (def_ == NULL) {
        return false;
    } else {
        VarMng * m = def_->manager ();
        if (m == NULL) {
            return false;
        } else {
            return m->changeValue (this, s_value);
        }
    }
}
/* ========================================================================= */

int IVarValueFactory::vmTyId() const {
    return BasicValueFactory;
}
