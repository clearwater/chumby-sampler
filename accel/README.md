accel demo
==========

Demonstrates i2c access to the accelerometer.

The readaccel demo repeatedly reads and displays the X,Y,Z values
from the accelerometer.

Note: this code was originally posted in the [AdaFruit tutorial](http://www.ladyada.net/learn/chumby/i2c.html).

Build and Run
-------------
Assuming you are using the [chumby-oe](https://github.com/clearwater/chumby-oe) development image, and you have this code on your chumby, you can build and run as follows.

```
# cd accel
# make
cc    -c -o readaccel.o readaccel.c
cc   readaccel.o   -o readaccel
# ./readaccel
X = -6  Y = -17 Z = 64
X = -6  Y = -17 Z = 64
X = -6  Y = -17 Z = 64
X = -6  Y = -17 Z = 64
...
```

Schematics
----------

<img src="/clearwater/chumby-sampler/raw/master/images/accel-schematics.png" />
