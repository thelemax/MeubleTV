#!/bin/bash
sudo avrdude -c linuxgpio -p atmega328p -v -U flash:w:build-uno/arduino-dev.hex:i