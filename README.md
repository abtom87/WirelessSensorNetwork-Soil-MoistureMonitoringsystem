# Wireless sensor network- Soilmoisture monitoring system

## Summary
This project consists of two parts, one part is the sensor node which measures
and processes sensor data and sends it to the cordinator node which sends data to LCD
indicating the stataus of available moisture in the soil. 

## Description
Soilmoisture Sensornode - Soil moisture sensor is connected to an Arduino UNO, which is connected to an XBEE S1 unit, that transmits the measured data
via the Zigbee Protocol. The XBEE connected to this Arduino is configured via the XCTU Tool. The parameters needed to be configured are Coordinator/Endpoint
(in this case its configured as Endpoint),  PAN ID, Baudrate and Destination address. The rest of the parameters were not changed. 
 
Receiver/Coordinator node - The second XBEE is connected to another Arduino and configured as Coordinator, the other parameters like PAN ID, Baudrate, 
Destination address should be same as endpoint. The Coordinator receives the payload and displays the value to LCD. The received data provides information to
user as to how much moist/humid the soil is.
 
