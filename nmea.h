#ifndef __NMEA_H__
#define __NMEA_H__

#include <stdbool.h>

#define NMEA_SATINPACK (4)

typedef enum _nmea_sentence {
    GPNON = 0x0000, /* Unknown packet type. */
    GPGSV = 0x0001, /* GSV - Number of SVs in view, PRN numbers, elevation, azimuth & SNR values. */
    GPRMC = 0x0002, /* RMC - Recommended Minimum Specific GPS/TRANSIT Data. */
} nmea_sentence_t;

/**
 * Date and time data
 * @see nmea_time_now
 */
typedef struct _nmea_time
{
    int year; /**< Years since 1900 */
    int mon;  /**< Months since January - [0,11] */
    int day;  /**< Day of the month - [1,31] */
    int hour; /**< Hours since midnight - [0,23] */
    int min;  /**< Minutes after the hour - [0,59] */
    int sec;  /**< Seconds after the minute - [0,59] */
    int hsec; /**< Hundredth part of second - [0,99] */

} nmea_time_t;

/**
 * Information about satellite
 * @see nmeaSATINFO
 * @see nmeaGPGSV
 */
typedef struct _nmea_satellite
{
    int id;      /**< Satellite PRN number */
    int in_use;  /**< Used in position fix */
    int elv;     /**< Elevation in degrees, 90 maximum */
    int azimuth; /**< Azimuth, degrees from true north, 000 to 359 */
    int sig;     /**< Signal, 00-99 dB */

} nmea_satellite_t;

/**
 * GSV packet information structure (Satellites in view)
 */
typedef struct _nmea_gsv
{
    int pack_count; /**< Total number of messages of this type in this cycle */
    int pack_index; /**< Message number */
    int sat_count;  /**< Total number of satellites in view */
    nmea_satellite_t sat_data[NMEA_SATINPACK];

} nmea_gsv_t;

/**
 * RMC packet information structure (Recommended Minimum sentence C)
 */
typedef struct _nmea_gprmc
{
    nmea_time_t utc;    /**< UTC of position */
    char status;        /**< Status (A = active or V = void) */
    double lat;         /**< Latitude in NDEG - [degree][min].[sec/60] */
    char ns;            /**< [N]orth or [S]outh */
    double lon;         /**< Longitude in NDEG - [degree][min].[sec/60] */
    char ew;            /**< [E]ast or [W]est */
    double speed;       /**< Speed over the ground in knots */
    double direction;   /**< Track angle in degrees True */
    double declination; /**< Magnetic variation degrees (Easterly var. subtracts from true course) */
    char declin_ew;     /**< [E]ast or [W]est */
    char mode;          /**< Mode indicator of fix type (A = autonomous, D = differential, E = estimated, N = not valid, S = simulator) */

} nmea_gprmc_t;

void parse(const char *data, size_t data_sz);

nmea_sentence_t nmea_get_sentence_type(const char *data, size_t data_sz);

void nmea_parse_rmc_sentence(const char *data, size_t data_sz, bool timestamp, bool coordinates);

void nmea_parse_gsv_sentence(const char *data, size_t data_sz, bool satellites);

unsigned int nmea_calculate_crc(const char *data, size_t data_sz);

#endif