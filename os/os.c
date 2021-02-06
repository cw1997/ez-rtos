#include "./os.h"
#include "./config.h"

void PendSV_init() {
	NVIC_SetPriority(PendSV_IRQn, 0xFF);
}

void SysTick_init(uint32_t us) {
	SysTick->LOAD  = CONFIG_OS_TICK_TIME_US * CONFIG_OS_SYSTICK_CLK - 1;
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
}

void os_start() {
    PendSV_init();
    SysTick_init(CONFIG_OS_TICK_TIME_US);
}
