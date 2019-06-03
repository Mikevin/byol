//
// Created by mikev on 31/05/2019.
//

#include "eval.h"


lval eval(mpc_ast_t *t) {

    if (strstr(t->tag, "number")) {
        /* Check if there is some error in conversion */
        errno = 0;
        long x = strtol(t->contents, NULL, 10);
        return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }

    char *op = t->children[1]->contents;
    lval x = eval(t->children[2]);

    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}

/* Use operator string to see which operation to perform */
lval eval_op(lval x, char *op, lval y) {

    /* If either value is an error return it */
    if (x.type == LVAL_ERR) { return x; }
    if (y.type == LVAL_ERR) { return y; }

    if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
    if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
    if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
    if (strcmp(op, "/") == 0) {
        /* If second operand is zero return error */
        return y.num == 0
               ? lval_err(LERR_DIV_ZERO)
               : lval_num(x.num / y.num);
    }
    if (strcmp(op, "%") == 0) { return lval_num(x.num % y.num); }
    if (strcmp(op, "^") == 0) { return lval_num(pow(x.num, y.num)); }

    return lval_err(LERR_BAD_OP);
}




