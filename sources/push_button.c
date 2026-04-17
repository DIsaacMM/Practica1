#include "push_button.h"
#include "GPIO.c"

#define BUTTON_PORT C
#define BUTTON_PIN 13
#define BUTTON_INPUT_MODE 0 
#define DEBOUNCE_DELAY 20000

/*
Push Button: 
    B1 USER: the user button is connected to the I/O PC13 (pin 2) of the STM32
    microcontroller.

    Funciones a implementar en el Push Button
        button_init
        button_get_state
    Utilizar las funciones del GPIO para detectar el estado del boton.
*/

// función para delay antirrebote
static void delay()
{
    for(volatile int i = 0; i < DEBOUNCE_DELAY; i++);
}

/*
    La funcion debe inicializar el boton Push Button
        B1 USER: the user button is connected to the I/O PC13 (pin 2) of the STM32
        microcontroller.
*/

void button_init() 
{
    gpio_initPort(BUTTON_PORT);
    gpio_setPinMode(BUTTON_PORT, BUTTON_PIN, BUTTON_INPUT_MODE);
}

uint8_t button_get_state() 
{
    // 1. Verifica si el botón está presionado (LOW = 0)
    if (gpio_readPin(BUTTON_PORT, BUTTON_PIN) == 0) 
    {
        // 2. Espera un tiempo para evitar rebotes
        delay();

        // 3. Si el boton se libero se regresa el 0 
        if (gpio_readPin(BUTTON_PORT, BUTTON_PIN) == 1)
        {
            return 0;
        }
            

        // 4. Mientras el boton se mantenga presionado 
        while (gpio_readPin(BUTTON_PORT, BUTTON_PIN) == 0)
        {
            delay(); // Esperar hasta que se suelte el boton
            
        }   
        
        // 5. Botón fue presionado y liberado
        return 1;
    }

    return 0;
}