# GPS LOG Analyzer

Write a GPS LOG File Analyzer that extracts relevant information out of a given GPS log-file. Relevant information could be longitude, latitude, number of visible satellites, time-stamp, etc. Choose one or two NMEA messages contained in the log and extract the relevant information (e.g.: RMC or GSV).

Detailed information on how to interpret NMEA messages can be found here.

The program shall support the following command-line interface:

```
$ gpsanalyzer [-c] [-f] [-h] [-s] [-f FILENAME]
```

[![Build Status](https://travis-ci.org/kwaxi/GPSLogAnalyzer.svg?branch=master)](https://travis-ci.org/kwaxi/GPSLogAnalyzer)