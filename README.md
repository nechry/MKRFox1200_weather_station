# MKRFox1200 Weather Station

Simple weather station connected with Sigfox using a Arduino MKR Fox 1200.

## what is Sigfox?
Sigfox is a Low Power Wide Area network that allows objects to communicate through Internet.
Sensor can operate for years because of its very low battery consumption.

Sigfox communications supports up to 140 uplink messages a day, each of which can carry a payload of 12 Bytes (Excluding message header and transmission information) and up to 4 downlink messages per day, each of which can carry a payload of 8 Bytes.

# Callback

## Custom Callback

## payload config
moduleTemperature::int:16:little-endian sensorTemperature::int:16:little-endian sensorHumidity::uint:16:little-endian lastMessageStatus::uint:8

## Subriscription URL
<YOUR_SUBSCRIPTION_URL>?id={device}&data={data}&moduleTemperature={customData#moduleTemperature}&sensorTemperature={customData#sensorTemperature}&sensorHumidity={customData#sensorHumidity}&lastMessageStatus={customData#lastMessageStatus}

HTTP "POST" method Content type: application/x-www-form-urlencoded
