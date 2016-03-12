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

class VarDef;

//! Evaluate the value of context based variables.
class VARMNG_EXPORT VarEval {

public:

    //! Default constructor.
    VarEval ();

    //! Destructor.
    virtual ~VarEval ();


}; // class VarEval

#endif // GUARD_VAREVAL_INCLUDE
