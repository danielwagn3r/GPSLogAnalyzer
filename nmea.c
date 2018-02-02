#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nmea.h"

/**
 * \brief Parse a chunk of memory with NMEA data in it.
 * @param data a constant character pointer of packet buffer.
 * @param data_sz buffer size.
 */
void parse(const char *data, size_t data_sz)
{
    if (data == NULL)
        return;
}

/**
 * \brief Define packet type by header (nmea_sentence_t).
 * @param data a constant character pointer of packet buffer.
 * @param data_sz buffer size.
 * @return The defined packet type
 * @see nmea_sentence_t
 */
nmea_sentence_t nmea_get_sentence_type(const char *data, size_t data_sz)
{
    static const char *sheads[] = {
        "GPGSV",
        "GPRMC"};

    if (data == NULL)
        return GPNON;

    if (data_sz < 5)
        return GPNON;
    else if (0 == memcmp(data, sheads[0], 5))
        return GPGSV;
    else if (0 == memcmp(data, sheads[1], 5))
        return GPRMC;

    return GPNON;
}

const char *nth_strchr(const char *s, int c, int n)
{
    const char *nth = s;
    /* assert(c != '\0'); */

    for (int i = 0; i < n; i++)
    {
        if ((nth = strchr(nth, c)) == 0)
            break;
        nth++;
    }

    return nth;
}

void nmea_parse_rmc_sentence(const char *data, size_t data_sz, bool timestamp, bool coordinates)
{
    char *time_s = nth_strchr(data, ',', 1);
    char *time_e = strchr(time_s, ',');

    char *date_s = nth_strchr(data, ',', 9);
    char *date_e = strchr(date_s, ',');

    char *coordinates_s = nth_strchr(data, ',', 3);
    char *coordinates_e = nth_strchr(data, ',', 7);

    time_e[0] = '\0';
    date_e[0] = '\0';
    coordinates_e[0] = '\0';

    if (timestamp)
    {
        printf("timestamp: %s %s\n", date_s, time_s);
    }

    if (coordinates)
    {
        printf("coordinates: %s\n", coordinates_s);
    }

    return;
}

void nmea_parse_gsv_sentence(const char *data, size_t data_sz, bool satellites)
{
    if (satellites)
    {
        char *satcount_s = nth_strchr(data, ',', 3);
        char *satcount_e = strchr(satcount_s, ',');

        satcount_e[0] = '\0';

        printf("count: %s\n", satcount_s);
    }
    return;
}
