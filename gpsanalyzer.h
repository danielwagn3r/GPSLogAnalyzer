#ifndef __GPSANALYZER_H__
#define __GPSANALYZER_H__


#include <stdbool.h>
#include <stdio.h>


struct global_args_t {
	bool coordinates;           /* -c option */
	bool timestamp;				/* -t option */
    bool satellites;            /* -s option */
	const char *input_filename;	/* -f option */
	FILE *input_file;
    unsigned int verbosity;		/* -v option */
} global_args;


static const char *opt_string = "cf:hstv?";

int main(int argc, char** argv);

void usage();


#endif