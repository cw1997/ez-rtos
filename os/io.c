#include "./io.h"
#include "./os.h"
#include "../Drivers/usart.h"

#include <stdint.h>

#define COLUMN_COUNT 80
#define LINE_COUNT 30

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

int column = 0;
int line = 0;

void init_io(void) {
    usart_init(115200, 72000000);
}

uint16_t char_index = 0;
void putchar(uint8_t ch) {
    Critical_Section_Start();
    usart_send_char(ch);
    usart_send_char(char_index & 0x000000FF);
    usart_send_char(char_index >> 8);
    if (char_index == COLUMN_COUNT * LINE_COUNT - 1) {
        char_index = 0;
    } else {
        ++char_index;
    }
    Critical_Section_End();
}

void puts(uint8_t str[]) {
    Critical_Section_Start();
    uint32_t index = 0;
    do {
        putchar(str[index]);
    } while (str[++index] != 0);
    Critical_Section_End();
}
