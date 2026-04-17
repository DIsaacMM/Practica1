#include <stdint.h>
#include "push_button.c"
#include "LED.c"

/* ================== MAIN ================== */
int main(void)
{
    // 1. Inicializar boton y led
        button_init(); 
        led_init(); 

        delay(); 
        led_off(); 
            
    while (1)
    {


        // 2. Revisar si el boton esta presionado 
        if(button_get_state() == 1)
        {
            led_toggle(); // Cambiar el estado del LED (De apagado a prendido o viceversa)
        }
    }
    return 0; 
}