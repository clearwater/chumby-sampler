#include <unistd.h>
#include "imx233.h"
#include "gpio.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    GPIO gpio;
    gpio.open();

    // The following is based in part on
    //   http://forum.chumby.com/viewtopic.php?id=6672

    //----------------------------------------------------------------------
    // To turn on the LED's on the hacker board you need 
    // to turn on the transistor grounding the LEDs and 
    // then turn on the relevant LEDs.
    //----------------------------------------------------------------------

    // See i.MX23 Table 37-10
    // HW_PINCTRL_MUXSEL1 bits 7:6 
    //   00 = gpmi_ready0
    //   01 = reserved
    //   10 = ssp2_detect
    //   11 = GPIO
    // To set GPIO mode we set bits 6:7, 1100 0000 = 0xC0 
    gpio.set(HW_PINCTRL_MUXSEL1_SET, 0x000000c0);

    // See i.MX23 section 37.4.35
    // The PINCTRL Bank 0 Output Enable Register controls 
    // the output enable signal for all pins in bank 0 that 
    // are configured for GPIO mode
    // Bank 0, pin 19 to output, 2^19 = 0x080000
    // Enable output on Turn on 
    gpio.set(HW_PINCTRL_DOE0_SET, 0x00080000);

    // See i.MX23 section 37.4.29
    // The Bank 0 Data Output register provides data for all
    // pins in bank 0 that are configured for GPIO output mode
    // Bank 0, pin 19 to high, 2^19 = 0x080000
    gpio.set(HW_PINCTRL_DOUT0_SET, 0x00080000);

    //----------------------------------------------------------------------
    // Now configure the 4 pins driving the LEDs
    // to GPIO mode, 12mA output, output enabled.
    //----------------------------------------------------------------------

    // set all 4 LEDs to GPIO mode, 2 bits per led
    gpio.set(HW_PINCTRL_MUXSEL0_SET, 0xFF);
    // set all 4 pins to 12mA output, 4 bits per led
    gpio.set(HW_PINCTRL_DRIVE0_SET,0x03030303);
    // set all 4 pins to output
    gpio.set(HW_PINCTRL_DOE0_SET, 0x0F);
    // turn all 4 pins on (briefly, not required)
    gpio.set(HW_PINCTRL_DOUT0_SET, 0x0F);

    //----------------------------------------------------------------------
    // We can now control the individual pins through the low 4 bits
    // using one of these addresses:
    // HW_PINCTRL_DOUT0_SET : turns specified pins high 
    // HW_PINCTRL_DOUT0_CLR : turns specified pins high 
    // HW_PINCTRL_DOUT0_TOG : toggles specified pins
    //----------------------------------------------------------------------

    // low 4 bits of mask control 4 leds
    unsigned int mask = 0x01;
    unsigned int last_mask = 0x0F;
    for (int i=0;i<400;i++) {

        // use TOG to toggle leds to new pattern
        gpio.set(HW_PINCTRL_DOUT0_TOG, mask^last_mask);

        // You could eqivalently do this in two calls
        // if you didn't know the previous state of the leds.
        // gpio.set(HW_PINCTRL_DOUT0_SET, mask);
        // gpio.set(HW_PINCTRL_DOUT0_CLR, 0x0F^mask);

        // cycle mask 1 bit left, reset at 0x10
        last_mask = mask;
        mask = mask<<1;
        if (mask==0x10) mask=1;

        // sleep for 50 milliseconds
        usleep(50000);
    }
    gpio.close();
    return 0;
}
