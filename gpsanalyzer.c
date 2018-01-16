
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpsanalyzer.h"

int main(int argc, char** argv)
{
	int opt = 0;

	global_args.coordinates = false;
	global_args.satellites = false;
	global_args.timestamp = false;
	global_args.input_file = NULL;
	global_args.input_filename = NULL;
	
	opt = getopt( argc, argv, opt_string );
    
	while( opt != -1 ) {
        switch( opt ) {
            case 'c':
                global_args.coordinates = true; /* true */
                break;
                 
            case 's':
                global_args.satellites = true;
                break;
                 
            case 't':
                global_args.timestamp = true;
                break;

            case 'f':
                global_args.input_filename = optarg;
                break;
                 
            case 'v':
                global_args.verbosity++;
                break;
                 
            case 'h':   /* fall-through is intentional */
            case '?':
                usage();
				return EXIT_FAILURE;
                break;
                 
            default:
				return EXIT_FAILURE;
                break;
        }
         
        opt = getopt( argc, argv, opt_string );
    }
	
	return EXIT_SUCCESS;
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

