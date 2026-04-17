/**
 * @file LED.h
 * @brief Module that manipulates a LED from a STM23
 * 
 * The header file initializes a LED in an STM32 to show the output from a push button
 * 
 * @author David Mijares, Ximena, Xavier
 * @date 
 *
 */

#include <stdint.h>
#include "stm32f4xx.h" 

/*
LED: 
    User LD2: the green LED is a user LED connected to ARDUINO® signal D13 corresponding
    to STM32 I/O PA5 (pin 21) or PB13 (pin 34) depending on the STM32 target. Refer to
    Table 11 to Table 23 when:
        • the I/O is HIGH value, the LED is on
        • the I/O is LOW, the LED is off

    Funciones del LED
        led_init
        led_on
        led_off
        led_toggle

        Utilizar las funciones del GPIO internas
*/

void led_init();

void led_on();

void led_off();

void led_toggle();
