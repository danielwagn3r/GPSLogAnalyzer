#include <stdlib.h>
#include <string.h>

#include "nmea.h"

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
        "GPRMC"
    };

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

/**
 * \brief Calculate control sum of binary buffer
 * @param data a constant character pointer of packet buffer.
 * @param data_sz buffer size.
 * @return The calculated control sum
 */
unsigned int nmea_calculate_crc(const char *data, size_t data_sz)
{
    unsigned int crc = 0;
    size_t i;

    for (i = 0; i < data_sz; ++i)
    {
        crc ^= (unsigned int)data[i];
    }

    return crc;
}
