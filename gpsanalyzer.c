#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "gpsanalyzer.h"
#include "nmea.h"

struct args_t
{
    bool coordinates;           /* -c option */
    bool help;                  /* -h option */
    bool timestamp;             /* -t option */
    bool satellites;            /* -s option */
    unsigned int verbosity;     /* -v option */
    const char *input_filename; /* -f option */
    FILE *input_file;
};

int main(int argc, char **argv)
{
    args_t args;
    bool args_valid = false;

    args_valid = parse_args(argc, argv, &args);

    if (!args_valid || args.help || !args.input_filename)
    {
        usage();
        return EXIT_FAILURE;
    }

    args.input_file = fopen(args.input_filename, "r");

    if (args.input_file == NULL)
    {
        fputs("Error opening inputfile", stdout);
        return EXIT_FAILURE;
    }

    char line[512];

    while (fgets(line, sizeof line, args.input_file) != NULL)
    {
        nmea_sentence_t t = nmea_get_sentence_type(line + 1, (sizeof line) - 1);
        /* fprintf(stdout, "%s (type: %#x)\n", line, t); */

        switch (t)
        {
            case GPGSV:
                {
                    nmea_parse_gsv_sentence(line,(sizeof line), args.satellites);
                    break;
                }

            case GPRMC:
                {
                    nmea_parse_rmc_sentence(line,(sizeof line), args.timestamp, args.coordinates);
                    break;
                }

            default:
                break;
        }
    }

    fclose(args.input_file);

    return EXIT_SUCCESS;
}

bool parse_args(int argc, char **argv, args_t *args)
{
    int opt = 0;
    const char *opt_string = "cf:hstv?";

    args->coordinates = false;
    args->satellites = false;
    args->timestamp = false;
    args->input_file = NULL;
    args->input_filename = NULL;
    args->help = false;

    opt = getopt(argc, argv, opt_string);

    while (opt != -1)
    {
        switch (opt)
        {
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

        case 'h': /* fall-through is intentional */
        case '?':
            args->help = true;
            break;

        default:
            return false;
            break;
        }

        opt = getopt(argc, argv, opt_string);
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
