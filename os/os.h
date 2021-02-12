#ifndef OS_H
#define OS_H

#include <stm32f10x.h>
#include "./task.h"
#include "./critical_section.h"
#include "./memory.h"
#include "./io.h"

void os_init(void);
void os_start(void);

void delay(uint32_t us);

#endif //OS_H
