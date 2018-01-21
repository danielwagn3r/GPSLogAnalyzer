cmake_minimum_required (VERSION 3.0)

project(GPSLogAnalyzer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SOURCE
  gpsanalyzer.c
  nmea.c
)

set(HEADERS
  gpsanalyzer.h
  nmea.h
)

add_executable(gpsanalyzer ${SOURCE} ${HEADERS})