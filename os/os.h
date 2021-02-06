#ifndef OS_H
#define OS_H

#include <stm32f10x.h>
#include "./task.h"
#include "./critical_section.h"
#include "./memory.h"

void os_init(void);
void os_start(void);

#endif //OS_H
