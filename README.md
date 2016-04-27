# Arduino-Capacitive-Sensor

This code is used in conjuction with the Raspberry Pi.  The Arduino itself simply serves as a data collection tool.
Sensor data is collected from from the Arduino via I2C and storred on the Pi.

For more information go [here](https://github.com/gdeshazer/PigPatrolRaspberryPi).

This code also works with a Beaglebone Black, however segment of code which flips the bytes will need to be commented out.
If you'd like to see the Beaglebone implementation, go [here](https://github.com/gdeshazer/PigPatrolBeaglebone/tree/master).
