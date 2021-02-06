#include <os.h>

#define STACK_SIZE 32

stack_t stack_0[STACK_SIZE];
stack_t stack_1[STACK_SIZE];

#define DELAY_US 500000

int *i0;
int *i1;

int n0 = 0;
void task_blink_led_0() {
    for (;;) {
		// if GPIOB.5 == 1 then GPIOB.5 = 0
		if ((GPIOB->IDR & (1 << 5)) == (1 << 5)) {
			*i0 = 0;
		} else {
			// else GPIOB.5 = 1 
			*i0 = 1;
		}
		// if GPIOB.5 == 1 then GPIOB.5 = 0
		if (*i0 == 0) {
			GPIOB->ODR &= (~(1 << 5));
		} else {
			// else GPIOB.5 = 1 
			GPIOB->ODR |= 1 << 5;
		}
		n0 = n0 == 0 ? 1 : 0;
		sleep(DELAY_US);
	}
}

int n1 = 1;
void task_blink_led_1() {
    for (;;) {
		// if GPIOE.5 == 1 then GPIOE.5 = 0 
		if ((GPIOE->IDR & (1 << 5)) == (1 << 5)) {
			*i1 = 0;
		} else {
			// else GPIOE.5 = 1 
			*i1 = 1;
		}
		// if GPIOE.5 == 1 then GPIOE.5 = 0 
		if (*i1 == 0) {
			GPIOE->ODR &= (~(1 << 5));
		} else {
			// else GPIOE.5 = 1 
			GPIOE->ODR |= 1 << 5;
		}
		n1 = n1 == 0 ? 1 : 0;
		sleep(DELAY_US);
	}
}

void LED_init() {
	Critical_Section_Start();
	
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
	
	Critical_Section_End();
}

int main(void) {
    os_init();

    LED_init();
	
	void *m0 = malloc(1024);
	free(m0);
	void *m1 = malloc(2048);
	free(m1);
	void *m2 = malloc(2048);
	free(m2);
	
	// dynamic alloc 4byte (int32_t) to point *i0
	i0 = malloc(4);
	free(i0);
	i0 = malloc(sizeof(int));
	
	void *m3 = malloc(256);
	void *m4 = malloc(512);
	free(m3);
	
	// dynamic alloc 4byte (int32_t) to point *i1
	i1 = malloc(4);
	free(i1);
	i1 = malloc(sizeof(int));

    create_task(task_blink_led_0, 0, stack_0, STACK_SIZE);
    create_task(task_blink_led_1, 0, stack_1, STACK_SIZE);

	os_start();
	
    for (;;);
}
