#ifndef __NMEA_H__
#define __NMEA_H__

#include <stdbool.h>

    typedef enum _nmea_sentence {
    GPNON = 0x0000, /* Unknown packet type. */
    GPGSV = 0x0001, /* GSV - Number of SVs in view, PRN numbers, elevation, azimuth & SNR values. */
    GPRMC = 0x0002, /* RMC - Recommended Minimum Specific GPS/TRANSIT Data. */
} nmea_sentence_t;

void parse(const char *data, size_t data_sz);

nmea_sentence_t nmea_get_sentence_type(const char *data, size_t data_sz);

void nmea_parse_rmc_sentence(const char *data, size_t data_sz, bool timestamp, bool coordinates);

void nmea_parse_gsv_sentence(const char *data, size_t data_sz, bool satellites);

unsigned int nmea_calculate_crc(const char *data, size_t data_sz);

#endif