#include "./usart.h"
#include <stdint.h>
#include <os.h>
    

uint32_t usart_calc_brr(uint32_t bps, uint32_t PLCK2) {
	// 625 / 16 == 39.025
    float usart_div = (float)(PLCK2 / bps) / 16;
	// 39
    uint32_t mantissa = usart_div;
	//0x01
    uint32_t fraction = (float)(usart_div - mantissa) * 16;
    uint32_t brr = (mantissa << 4) + fraction;
	//0x27
    return brr;
}

void usart_send_char(uint8_t ch) {
	while((USART1->SR & USART_SR_TC) == 0);
	USART1->DR = ch;
} 

void usart_send(uint8_t str[]) {
    Critical_Section_Start();
	uint32_t index = 0;
	do {
        usart_send_char(str[index]);
	} while (str[++index] != 0);
    Critical_Section_End();
}

void usart_init(uint32_t bps, uint32_t PLCK2) {
    // enable port A clock
    RCC->APB2ENR |= 1 << 2;
    // enable usart clock
    RCC->APB2ENR |= 1 << 14;
    // PORT A9 is USART1_RX
    // float input
	GPIOA->CRH &= 0XFFFFF00F;
	GPIOA->CRH |= 0X000008B0;
    RCC->APB2RSTR |= 1 << 14;
    RCC->APB2RSTR &= ~(1 << 14);
    // set brr
    USART1->BRR = usart_calc_brr(bps, PLCK2);
    // set control 1
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE;
    // USART1->CR2 = USART_CR2_CLKEN;
	
//	uint8_t str[] = "cw1997";
//	usart_send(str);
}
