#ifndef OS_IO_H
#define OS_IO_H

#include <stdint.h>

void init_io(void);

void putchar(uint8_t ch);

void puts(uint8_t str[]);

#endif //OS_IO_H
