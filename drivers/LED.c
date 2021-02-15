#include "./LED.h"

void LED_init() {
    // open GPIOB clock
    RCC->APB2ENR |= 1 << 3;
    // open GPIOE clock
    RCC->APB2ENR |= 1 << 6;
            
    GPIOB->CRL &= 0xff0fffff;
    // set GPIOB.5 type = push-pull output
    GPIOB->CRL |= 0x00300000; 
    // set GPIOB.5 level = high, it means turn off LED
    //GPIOB->ODR |= 1 << 5;
                                              
    GPIOE->CRL &= 0xff0fffff;
    // set GPIOE.5 type = push-pull output
    GPIOE->CRL |= 0x00300000;
    // set GPIOE.5 level = high, it means turn off LED
    GPIOE->ODR |= 1 << 5;
}
