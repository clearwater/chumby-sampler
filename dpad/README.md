dpad demo
=========

Reads the 5 switches on the joystick dpad at SW400
using GPIO.  

The joystick has 5 switches A,B,C,D and E, as
shown in the [datasheet](http://clearwater.github.com/chumby-oe/resources/ATR0000CE9.pdf).

On the Chumby Hackers Board these are connected to GPIO pins as follows:

 - A : GPMI CE0n : BANK2_PIN28
 - B : GPMI WPn : BANK0_PIN23
 - C : GPMI WRn : BANK0_PIN24
 - D : GPMI RDn : BANK0_PIN25
 - E : PWM4 : BANK_1_PIN30

In all cases the pins are input will read high (1) when 
the switch is open, and low (0) when the switch is closed.

The GPIO register values in the documentation are taken from the
[iMX233 reference manual](http://www.freescale.com/files/dsp/doc/ref_manual/IMX23RM.pdf).

Build and Run
-------------
Assuming you are using the [chumby-oe](https://github.com/clearwater/chumby-oe) development image, and you have this code on your chumby, you can build and run as follows.

```
# cd dpad
d# make
g++  -Wall  -c -o dpad.o dpad.cpp
g++  -Wall  -c -o gpio.o gpio.cpp
cc   dpad.o gpio.o   -o dpad
# ./dpad
```

The output shows which of the switches A through E are closed
as follows:

```
# ./dpad
dpad: - - - - -
dpad: - - - - e
dpad: - - - - -
dpad: - - - d -
dpad: a - - - e
dpad: - - - - e
dpad: - b - - -
dpad: - - - d -
dpad: - - c - -
dpad: - - - - -
```

Note that the code does NOT run for ever, it exits after a few seconds.
Change the loop in ```dpad.cpp``` if you want it to run longer.

Schematics
----------
<img src="/clearwater/chumby-sampler/raw/master/images/dpad-schematics.png" />

