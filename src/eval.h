//
// Created by mikev on 31/05/2019.
//

#ifndef BYOL_EVAL_H
#define BYOL_EVAL_H

#include "../lib/mpc.h"

typedef struct {
    int type;
    long num;
    int err;
} lval;

lval eval(mpc_ast_t *t);

lval eval_op(lval x, char *op, lval y);

lval lval_num(long x);

lval lval_err(int x);

void lval_print(lval v);

void lval_println(lval v);

#endif //BYOL_EVAL_H
