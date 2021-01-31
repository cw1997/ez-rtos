#include <os.h>

uint32_t System_Core_Clock = 72; // unit: MHz
uint32_t Clock_Div = 8;

void SysTick_init(uint32_t us) {
	SysTick->LOAD  = us * System_Core_Clock / Clock_Div - 1;
	SysTick->VAL   = 0;
	SysTick->CTRL  = // SysTick_CTRL_CLKSOURCE_Msk |
				     SysTick_CTRL_TICKINT_Msk   |
				     SysTick_CTRL_ENABLE_Msk	|
					 0; 
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
}


void os_init() {	
    init_task();
}

void os_start() {
    SysTick_init(10);
}
