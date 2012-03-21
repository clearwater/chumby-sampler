leds demo
=========

Shows how to control the 4 green LEDs connected to
GPMI_D00, GPMI_D01, GPMI_D02 and GPMI_D03.  
The ledcycle program will rapidly cycle the 4 leds on the CHB.

This example uses a GPIO class to manage
the memory-mapped registers much like the ```regutil``` tool.

The references to i.MX23 in the documentation refer to the 
[iMX233 reference manual](http://www.freescale.com/files/dsp/doc/ref_manual/IMX23RM.pdf).

Build and Run
-------------
Assuming you are using the [chumby-oe](https://github.com/clearwater/chumby-oe] development image, and you have this code on your chumby, you can build and run as follows.

```
# cd leds
# make
g++    -c -o ledcycle.o ledcycle.cpp
g++    -c -o gpio.o gpio.cpp
cc   ledcycle.o gpio.o   -o ledcycle
# ./ledcycle
```

Schematics
----------
<img src="/clearwater/chumby-sampler/raw/master/images/led-schematics.png" />

