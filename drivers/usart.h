#ifndef OS_USART_H
#define OS_USART_H

#include <stdint.h>

void usart_init(uint32_t bps, uint32_t PLCK2);

void usart_send(uint8_t str[]);

void usart_send_char(uint8_t ch);

#endif //OS_USART_H
