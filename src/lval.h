//
// Created by mike on 6/3/2019.
//

#ifndef BYOL_LVAL_H
#define BYOL_LVAL_H



enum {
    LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR
};


enum {
    LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM
};

typedef struct lval {
    int type;  // one of     LVAL_ERR, LVAL_NUM, LVAL_SYM, LVAL_SEXPR
    long num; // actual value
    /* Error and Symbol types have some string data */
    char *err;
    char *sym;
    /* Count and Pointer to a list of "lval*" */
    int count;
    struct lval **cell;
} lval;

lval *lval_num(long x);

lval *lval_err(char *m);

lval* lval_sym(char* s);

lval* lval_sexpr(void);

void lval_print(lval v);

void lval_println(lval v);


#endif //BYOL_LVAL_H
