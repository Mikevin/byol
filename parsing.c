#include <stdio.h>
#include <stdlib.h>
#include "lib/mpc.h"

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32

#include <string.h>
#include <signal.h>

static char buffer[2048];

volatile sig_atomic_t stop;

void sighandler(int signum) {
    stop = 1;
}

/* Fake readline function */
char *readline(char *prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char *cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy) - 1] = '\0';
    return cpy;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
/* Fake add_history function */
void add_history(char *unused) {}
#pragma clang diagnostic pop

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char **argv) {

    /* Handle signals */
    signal(SIGINT, sighandler);

    /* Create Some Parsers */
    mpc_parser_t *Number = mpc_new("number");
    mpc_parser_t *Operator = mpc_new("operator");
    mpc_parser_t *Expr = mpc_new("expr");
    mpc_parser_t *Lispy = mpc_new("lispy");

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
              "                                         \
    number   : /-?[0-9]+/ ;                             \
    operator : '+' | '-' | '*' | '/' | '%';                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;  \
    lispy    : /^/ <operator> <expr>+ /$/ ;             \
  ",
              Number, Operator, Expr, Lispy);


    puts("Lispy Version 0.0.0.0.1");
    puts("Implementation by Mike van Leeuwen");
    puts("Press Ctrl+c to Exit\n");

    while (!stop) {

        /* Now in either case readline will be correctly defined */
        char *input = readline("Mike's lispy> ");
        add_history(input);

        /* Attempt to Parse the user Input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            /* On Success Print the AST */
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            /* Otherwise Print the Error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);

    }

    /* Undefine and Delete our Parsers */
    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}