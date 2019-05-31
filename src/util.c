//
// Created by mikev on 31/05/2019.
//

#include <signal.h>
#include <string.h>
#include "../lib/mpc.h"
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

static char buffer[2048];

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