#include "LED.h"
#include "push_button.c"

#define LED_PORT A
#define LED_PIN 5
#define LED_OUTPUT_MODE 1 

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

void led_init()
{
    gpio_initPort(LED_PORT);                                // Se inicializa el puerto del LED
    gpio_setPinMode(LED_PORT, LED_PIN, LED_OUTPUT_MODE);    // Se pone el LED en modo de salida
    led_on();                                               // El led comienza apagado
}

void led_on()
{
    gpio_setPin(LED_PORT, LED_PIN);                         // Se pone el LED en alto (Se prende)
}

void led_off()
{
    gpio_clearPin(LED_PORT, LED_PIN);                       // Se pone el LED en bajo (Se apaga)
}

void led_toggle()                                              
{
    gpio_togglePin(LED_PORT, LED_PIN);                      // Se cambia el LED del valor en el que este
}
