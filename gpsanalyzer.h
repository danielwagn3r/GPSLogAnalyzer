#ifndef __GPSANALYZER_H__
#define __GPSANALYZER_H__

#include <stdbool.h>
#include <stdio.h>

struct args_t;

typedef struct args_t args_t;

bool parse_args(int argc, char **argv, args_t *args);

int main(int argc, char **argv);

void usage();


#endif