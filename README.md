Arduino Doorbell
================

These are mostly notes for myself so I don't forget how did it work.

QH-09BCE
--------

* -GND is connected directly to GND on Uno
* 3V is connected to 3.3V via breadboard; can be directly but we need +3V for Ethernet adapter
* LED+ goes to A3 (can be any analogue pin)

ENC28J60
--------

* 3.3V and GND are connected to the breadboard and directly second GND respectively
* SO pin 12
* SI pin 11
* SCK pin 13
* CS pin 8
