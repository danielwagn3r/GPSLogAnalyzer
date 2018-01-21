
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpsanalyzer.h"

struct args_t {
	bool coordinates;           /* -c option */
	bool help;					/* -h option */
	bool timestamp;				/* -t option */
    bool satellites;            /* -s option */
    unsigned int verbosity;		/* -v option */
	const char *input_filename;	/* -f option */
	FILE *input_file;
};


int main(int argc, char** argv)
{
    args_t args;
    bool args_valid = false;

    args_valid = parse_args(argc, argv, &args);

    if (!args_valid || args.help)
    {
        usage();
        return EXIT_FAILURE;
    }
	
	return EXIT_SUCCESS;
}

bool parse_args(int argc, char** argv, args_t* args)
{
	int opt = 0;

	args->coordinates = false;
	args->satellites = false;
	args->timestamp = false;
	args->input_file = NULL;
	args->input_filename = NULL;
    args->help = false;
	
	opt = getopt( argc, argv, opt_string );
    
	while( opt != -1 ) {
        switch( opt ) {
            case 'c':
                args->coordinates = true; /* true */
                break;
                 
            case 's':
                args->satellites = true;
                break;
                 
            case 't':
                args->timestamp = true;
                break;

            case 'f':
                args->input_filename = optarg;
                break;
                 
            case 'v':
                args->verbosity++;
                break;
                 
            case 'h':   /* fall-through is intentional */
            case '?':
				args->help = true;
                break;
                 
            default:
				return false;
                break;
        }
         
        opt = getopt( argc, argv, opt_string );
    }

    return true;
}

void usage()
{
	fputs("Usage: gpsanalyzer [options]\n", stdout);
	fputs("Options:\n", stdout);
	fputs("  -h			Print this message and exit.\n", stdout);
	fputs("  -c			Print coordinates.\n", stdout);
	fputs("  -s			Print satellites.\n", stdout);
	fputs("  -t			Print timestamp.\n", stdout);
	fputs("  -f FILE		Read FILE as inputfile.\n", stdout);
}

