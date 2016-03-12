VarMng
=======

Variable management, storage and evaluation.

The pile defines an interface for a variable definition in IVarDef.
The definition is expected to have a name and a (possibly different) label
to allow for user-friendliness. The definition also has a description and
may be used as a group, thus allowing the user to create a tree structure
where the nodes are groups and leafs are definitions.

An assigned variable (a variable associated with a value)
is defined by the IVarValue interface
that stores the link to the variable definition internally.
The implementation is expected to provide the value as a string.
Assigned variable are part of a context - IVarCtx - that
may also have a name and label. A variable may appear only once in a context.

VarEval takes care of evaluating a list of contexts. A variable is allowed
to appear in more than one context but it should only appear once in any
given context. The final value of the variable is determined by iterating
all contexts, with the last context having the final saying in the result.
