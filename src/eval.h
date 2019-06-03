//
// Created by mikev on 31/05/2019.
//

#ifndef BYOL_EVAL_H
#define BYOL_EVAL_H

#include "../lib/mpc.h"
#include "lval.h"



lval eval(mpc_ast_t *t);

lval eval_op(lval x, char *op, lval y);


#endif //BYOL_EVAL_H
