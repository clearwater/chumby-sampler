#include <unistd.h>
#include "imx233.h"
#include "gpio.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    GPIO gpio;
    gpio.open();

    // E is on bank1, pin 30
    // Set GPIO mode
    gpio.set(HW_PINCTRL_MUXSEL3_SET, 0x30000000);
    // Disable output mode
    gpio.set(HW_PINCTRL_DOE1_CLR, 0x40000000);

    // B,C,D are on bank0, pins 23,24,25
    // Set GPIO mode
    gpio.set(HW_PINCTRL_MUXSEL1_SET, 0xFC000); // bits 14:15 16:17 and 18:19
    // Disable output mode
    gpio.set(HW_PINCTRL_DOE0_CLR, 0x3800000); // bits 23,24,25 set
 
    // A is on bank2, pin 28
    // Set GPIO mode
    gpio.set(HW_PINCTRL_MUXSEL5_SET, 0x3<<24); // bits 25:24
    // Disable output mode 
    gpio.set(HW_PINCTRL_DOE2_CLR, 0x1<<28);    // bit 28

    unsigned last_value = 0;
    for (int i=0;i<1000;i++) {
        unsigned abcde = 0;
        // Read value of A into low bit (bit 0) of abcde
        abcde |= gpio.get(HW_PINCTRL_DIN2, 0x1<<28) >> 28;
        // Read B,C,D into bits 1,2,3
        abcde |= gpio.get(HW_PINCTRL_DIN0, 0x3800000) >> (23-1);
        // Read E into bit 4
        abcde |= gpio.get(HW_PINCTRL_DIN1, 0x40000000) >> (30-4);

        // If value has changed since last pass, show value
        if (abcde != last_value) {
            printf("dpad: %s %s %s %s %s\n",
                abcde & 0x1  ? "-" : "a",
                abcde & 0x2  ? "-" : "b",
                abcde & 0x4  ? "-" : "c",
                abcde & 0x8  ? "-" : "d",
                abcde & 0x10 ? "-" : "e");
             last_value = abcde;
        } 
        // sleep for 50 milliseconds
        usleep(50000);
    }
    gpio.close();
    return 0;
}
