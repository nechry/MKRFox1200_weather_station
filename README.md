# MKRFox1200_weather_station
MKRFox1200 Weather Station

Simple weather station connected with Sigfox using a Arduino MKR Fox 1200.

## what is Sigfox?
Sigfox is a Low Power Wide Area network that allows objects to communicate through Internet.
Sensor can operate for years because of its very low battery consumption.

Sigfox communications supports up to 140 uplink messages a day, each of which can carry a payload of 12 Bytes (Excluding message header and transmission information) and up to 4 downlink messages per day, each of which can carry a payload of 8 Bytes.

# Callback

## Custom Callback

## payload config
moduleTemp::int:16:little-endian sensorTemp::int:16:little-endian sensorHum::uint:16:little-endian lastMsg::uint:8

## Subriscription URL
<YOUR_SUBSCRIPTION_URL>?id={device}&data={data}&moduleTemp={customData#moduleTemp}&sensorTemp={customData#sensorTemp}&sensorHum={customData#sensorHum}&lastMsg={customData#lastMsg}

HTTP "POST" method Content type: application/x-www-form-urlencoded
