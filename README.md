This is a small program to read NMEA data from a serially connected GPS unit and then to make that data available for other programs in a simple format. Filtering is available to limit the amount of data transmitted. This filtering is based on distance moved and time elapsed. This program expects that the NMEA sentences GGA and RMC are being transmitted by the GPS module, all else is ignored.

The programs that are expected to consume the GPS data must have APRS enabled as well as the MobileGPS portion of the configuration. This is an example:

```
[Mobile GPS]
Enable=1
Address=127.0.0.1
Port=7834
```

The examples in the respository have MobileGPS switched off, but if enabled should work out of the box provided that they all run on the same system.
