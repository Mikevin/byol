//
// Created by mikev on 31/05/2019.
//

#ifndef BYOL_EVAL_H
#define BYOL_EVAL_H

#include "../lib/mpc.h"

long eval(mpc_ast_t *t);

long eval_op(long x, char *op, long y);

#endif //BYOL_EVAL_H
