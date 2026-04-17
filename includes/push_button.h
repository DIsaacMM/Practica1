/**
 * @file push_button.h
 * @brief Module that manipulates a push for a STM23
 * 
 * The header file defines a set a functions to initialize a push button from a STM32 to use it as an input
 *
 * @author David Mijares, Ximena, Xavier
 * @date 
 *
 */

#include <stdint.h>
#include "stm32f4xx.h" 

// Inicializa el botón usando las funciones del driver GPIO
void button_init();

// Lee el botón, aplica antirrebote y devuelve 1 si hubo un clic válido, o 0 si no
uint8_t button_get_state();
