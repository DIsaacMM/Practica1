#include "GPIO.h"

/*
 
    Description: initializes de GPIO subsytem
    Functional Requirements: 
        FR-1: The system shall configure all GPIO ports to a default state. 
 
 */


typedef enum port
 {
    A, 
    B, 
    C, 
    D, 
    E, 
    H, 
    size
 }port_t; 

  GPIO_TypeDef* gpio[size]; 

void gpio_init()
{
    // Se asignan los espacios del array gpio a los GPIOs del STM32
    gpio[0] = GPIOA;
    gpio[1] = GPIOB;
    gpio[2] = GPIOC;
    gpio[3] = GPIOD;
    gpio[4] = GPIOE;
    gpio[5] = GPIOH;
}



/*
 
    Description: Initializes a specifit GPIO port
    Functional Requirements: 
        FR-2: The system shall enable clockinf for the specified port 
 
        Inicializar un puerto (GPIO) en especifico, iniciar su reloj 

    La funcion debera recibir un numero de entrada que sera interpretado por el ENUM
    Este le indicara al array gpio que GPIO del STM32 se quiere trabajar
 */

void gpio_initPort(port_t p)
{
    // Si no esta en el rango de los GPIOs del Micro se sale
    if(p < 0 || p > 6)
    {
        return;
    }
    else if(p == H || p == 5)
    {
        p = 7; 
    }

    // Habilitar el reloj del Puerto elegido
    RCC->AHB1ENR |= (1UL << p);   

}


 
/*
    Description: Configures the mode of a specific pin.
    Functional Requirements: 
        FR-3: The system shall allow configuration of pin direction and mode. 

    La funcion recibe los siguientes parametros: 

    1. Un numero que sera interpretado por el ENUM como el GPIOx que se quiere trabajar
    2. Un unsigned int que indicara que pin dentro del GPIO se quiere modificar
    3. Un unsinged int que indicara que modo se le asignara al pin del GPIOx 
 */

void gpio_setPinMode(port_t p, uint8_t pin, uint8_t mode)
{
    
    gpio[p]->MODER &= ~(3 << (pin*2));
    // Se le asigna el mode ingresado al pin ingresado
    // Pin se multiplica por dos ya que como en Mode cada pin ocupa dos bits para indicar que modo ponerle
    // Para modificar cada pin se tiene que considerar que cada pin usa dos bits
    gpio[p]->MODER |= (mode << (pin*2)); 
}



/*
    Description: Sets a pin to logic high.
    Functional Requirements: 
        FR-4: The system shall drive the specified pin to a high state.

    La funcion recibe los siguientes parametros> 
    1. Un numero que sera interpretado por el ENUM como el GPIOx que se quiere trabajar
    2. Un unsigned int que indicara que pin dentro del GPIO se quiere modificar
 */

void gpio_setPin(port_t p, uint8_t pin)
{
    // Se utiliza el los Bit set registers inferiores para poner el pin indicado del GPIOx en 1
    gpio[p]->BSRR = (1 << pin); 
}



/*
 
    Description: Clears a pin to logic low.
    Functional Requirements: 
        FR-5: The system shall drive the specified pin to a low state.
    
    La funcion recibe los siguientes parametros> 
    1. Un numero que sera interpretado por el ENUM como el GPIOx que se quiere trabajar
    2. Un unsigned int que indicara que pin dentro del GPIO se quiere modificar
 */

void gpio_clearPin(port_t p, uint8_t pin)
{
        // Se utiliza el los Bit set registers superiores para poner el pin indicado del GPIOx en 1
        // por lo que se le suma 16 al pin ingresado ya que asi funciona el BSRR
    gpio[p]->BSRR = (1 << (pin + 16)); 
}



/*
 
    Description: Toggles the state of a pin.
    Functional Requirements: 
        FR-6: The system shall invert the current state of the specified pin.
    La funcion recibe los siguientes parametros> 
        1. Un numero que sera interpretado por el ENUM como el GPIOx que se quiere trabajar
        2. Un unsigned int que indicara que pin dentro del GPIO se quiere modificar
 */

void gpio_togglePin(port_t p, uint8_t pin)
{
    // Se hace un XOR al valor del pin para cambiarlo de 0 a 1 y de 1 a 0
    gpio[p]->ODR ^= (1 << pin);
}



/*
 
    Description: Reads the current state of a pin.
    Functional Requirements: 
        FR-7: The system shall return the digital state of the specified pin.
    La funcion recibe los siguientes parametros> 
        1. Un numero que sera interpretado por el ENUM como el GPIOx que se quiere trabajar
        2. Un unsigned int que indicara que pin dentro del GPIO se quiere modificar
 */

uint8_t gpio_readPin(port_t p, uint8_t pin)
{
    // Revisa si el pin seleccionado en el IDR esta en 1
    if(gpio[p]->IDR & (1 << pin))
    {
        return 1; // Regresa 1 si esta en 1
    } 
    else 
    {
        return 0; // Regresa 0 si esta en 0
    }
}