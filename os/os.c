#include "./os.h"
#include "./config.h"
#include "./task.h"
#include "./io.h"

#define SYSTICK_LOAD (CONFIG_OS_TICK_TIME_US * CONFIG_OS_SYSTICK_CLK - 1)

void PendSV_init() {
	NVIC_SetPriority(PendSV_IRQn, 0xFF);
}

void SysTick_init() {
	SysTick->LOAD  = SYSTICK_LOAD;
	SysTick->VAL   = 0;
	SysTick->CTRL  |= // SysTick_CTRL_CLKSOURCE_Msk |
				      SysTick_CTRL_TICKINT_Msk   |
				      SysTick_CTRL_ENABLE_Msk	|
					  0; 
	NVIC_SetPriority(SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
}


void os_init() {	
    init_task();
	init_memory();
	init_io();
}

void os_start() {
    PendSV_init();
    SysTick_init();
}

void delay(uint32_t us) {
	uint8_t old_switch_task_enable = task_switch_enable;
	uint32_t old_SysTick_val = SysTick->VAL;
	task_switch_enable = 0;

	const uint32_t load = us * CONFIG_OS_SYSTICK_CLK - 1;
	SysTick->LOAD = load;
	
	while (SysTick->VAL) {
	}
	
	task_switch_enable = old_switch_task_enable;
	SysTick->LOAD = SYSTICK_LOAD;
	SysTick->VAL = 0;
}
