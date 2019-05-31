#include <stdio.h>
#include <stdlib.h>
#include "../lib/mpc.h"
#include "util.h"
#include "parsing.h"

/* If we are compiling on Windows compile these functions */
#ifdef _WIN32

#include <string.h>
#include <signal.h>


volatile sig_atomic_t stop;

void sighandler(int signum) {
    stop = 1;
}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char **argv) {

    /* Handle signals */
    signal(SIGINT, sighandler);
    create_parser();

    puts("Lispy Version 0.0.0.0.1");
    puts("Implementation by Mike van Leeuwen");
    puts("Press Ctrl+c to Exit\n");

    while (!stop) {

        /* Now in either case readline will be correctly defined */
        char *input = readline("Mike's lispy> ");
        add_history(input);

        /* Attempt to Parse the user Input */
        mpc_result_t r;
        if (parse(input, &r)) {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);

    }

    /* Undefine and Delete our Parsers */
    destroy_parser();
    return 0;
}