//
// Created by mikev on 31/05/2019.
//

#ifndef BYOL_PARSING_H
#define BYOL_PARSING_H

#include "../lib/mpc.h"

void create_parser();

void destroy_parser();

int parse(char *input, mpc_result_t *result);

#endif //BYOL_PARSING_H
