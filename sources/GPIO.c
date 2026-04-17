#include "GPIO.h"

/*
 
    Description: initializes the GPIO subsystem
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
    // Assign the gpio array positions to the STM32 GPIOs
    gpio[0] = GPIOA;
    gpio[1] = GPIOB;
    gpio[2] = GPIOC;
    gpio[3] = GPIOD;
    gpio[4] = GPIOE;
    gpio[5] = GPIOH;
}



/*
 
    Description: Initializes a specific GPIO port
    Functional Requirements: 
        FR-2: The system shall enable clocking for the specified port 
 
        Initialize a specific GPIO port, start its clock

    The function shall receive an input number that will be interpreted by the ENUM
    This will indicate to the gpio array which STM32 GPIO to work with
 */

void gpio_initPort(port_t p)
{
    
    
    // If not within the range of the Micro's GPIOs, exit
    if(p < 0 || p > 6)
    {
        return;
    }
    else if(p == H || p == 5)
    {
        p = 7; 
    }
    
    gpio_init(); 
    
    // Enable the clock for the selected Port
    RCC->AHB1ENR |= (1UL << p);   

}


 
/*
    Description: Configures the mode of a specific pin.
    Functional Requirements: 
        FR-3: The system shall allow configuration of pin direction and mode. 

    The function receives the following parameters: 

    1. A number that will be interpreted by the ENUM as the GPIOx to work with
    2. An unsigned int indicating which pin within the GPIO to modify
    3. An unsigned int indicating which mode to assign to the GPIOx pin
 */

void gpio_setPinMode(port_t p, uint8_t pin, uint8_t mode)
{
    // If not within the range of the Micro's GPIOs, exit
    if(p < 0 || p > 6 || mode > 3 || pin > 15)
    {
        return;
    }

    // If mode exceeds the number of options in MODER 
    if(mode > 3)
    {
        return; 
    }

    // If the pin exceeds the number of pins in GPIOx
    if(pin > 15)
    {
        return; 
    }
    
    // First clear what is in the GPIOx MODER
    gpio[p]->MODER &= ~(3 << (pin*2));
    
    // Assign the entered mode to the entered pin
    // Pin is multiplied by two because each pin uses two bits in MODE to indicate which mode to set
    // To modify each pin, you have to consider that each pin uses two bits
    gpio[p]->MODER |= (mode << (pin*2)); 
}



/*
    Description: Sets a pin to logic high.
    Functional Requirements: 
        FR-4: The system shall drive the specified pin to a high state.

    The function receives the following parameters: 
    1. A number that will be interpreted by the ENUM as the GPIOx to work with
    2. An unsigned int indicating which pin within the GPIO to modify
 */

void gpio_setPin(port_t p, uint8_t pin)
{
    // If not within the range of the Micro's GPIOs, exit
    if(p < 0 || p > 6)
    {
        return;
    }
    // If the pin exceeds the number of pins in GPIOx
    if(pin > 15)
    {
        return; 
    }
    
    // Use the lower Bit set registers to set the indicated pin of GPIOx to 1
    gpio[p]->BSRR = (1 << pin); 
}



/*
 
    Description: Clears a pin to logic low.
    Functional Requirements: 
        FR-5: The system shall drive the specified pin to a low state.
    
    The function receives the following parameters: 
    1. A number that will be interpreted by the ENUM as the GPIOx to work with
    2. An unsigned int indicating which pin within the GPIO to modify
 */

void gpio_clearPin(port_t p, uint8_t pin)
{
    // If not within the range of the Micro's GPIOs, exit
    if(p < 0 || p > 6)
    {
        return;
    }
    // If the pin exceeds the number of pins in GPIOx
    if(pin > 15)
    {
        return; 
    }

    // Use the upper Bit set registers to set the indicated pin of GPIOx to 1
    // so 16 is added to the entered pin because that's how BSRR works
    gpio[p]->BSRR = (1 << (pin + 16)); 
}



/*
 
    Description: Toggles the state of a pin.
    Functional Requirements: 
        FR-6: The system shall invert the current state of the specified pin.
    The function receives the following parameters: 
        1. A number that will be interpreted by the ENUM as the GPIOx to work with
        2. An unsigned int indicating which pin within the GPIO to modify
 */

void gpio_togglePin(port_t p, uint8_t pin)
{
    // If not within the range of the Micro's GPIOs, exit
    if(p < 0 || p > 6)
    {
        return;
    }
    // If the pin exceeds the number of pins in GPIOx
    if(pin > 15)
    {
        return; 
    }
    // XOR the pin value to change it from 0 to 1 and 1 to 0
    gpio[p]->ODR ^= (1 << pin);
}



/*
 
    Description: Reads the current state of a pin.
    Functional Requirements: 
        FR-7: The system shall return the digital state of the specified pin.
    The function receives the following parameters: 
        1. A number that will be interpreted by the ENUM as the GPIOx to work with
        2. An unsigned int indicating which pin within the GPIO to modify
 */

uint8_t gpio_readPin(port_t p, uint8_t pin)
{
    // If within the range of the Micro's GPIOs and pins, exit
    if(0 < p && p < 6 && pin < 16)
    {
        // Check if the selected pin in IDR is 1
        if(gpio[p]->IDR & (1 << pin))
        {
            return 1; // Returns 1 if it is 1
        } 
        else 
        {
            return 0; // Returns 0 if it is 0
        }
    }
    else
    {
        return; 
    }
}