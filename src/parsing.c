#include <stdio.h>
#include <stdlib.h>
#include "../lib/mpc.h"

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32

#include <string.h>
#include <signal.h>
/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

mpc_parser_t *Number;
mpc_parser_t *Operator;
mpc_parser_t *Expr;
mpc_parser_t *Lispy;

void create_parser() {
    /* Create Some Parsers */

    Number = mpc_new("number");
    Operator = mpc_new("operator");
    Expr = mpc_new("expr");
    Lispy = mpc_new("lispy");

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
              "                                         \
            number   : /-?[0-9]+(\\.[0-9]*)?/ ;                 \
            operator : '+' | '-' | '*' | '/' | '%' | \"mul\"  | \"sub\" | \"add\" | \"div\" ;             \
            expr     : <number> | '(' <operator> <expr>+ ')' ;  \
            lispy    : /^/ <operator> <expr>+ /$/ ;             \
  ",
              Number, Operator, Expr, Lispy);

}

void destroy_parser() {
    mpc_cleanup(4, Number, Operator, Expr, Lispy);
}

int parse(char *input, mpc_result_t *result) {
    /* Attempt to Parse the user Input */
    if (mpc_parse("<stdin>", input, Lispy, result)) {
        /* On Success Print the AST */
        return 1;
    } else {
        return 0;
    }
}