#ifndef OS_TASK_H
#define OS_TASK_H

#define CONFIG_MAX_TASK_NUM 8


#include <stdint.h>

typedef int stack_t;
typedef struct {
    void *stack;
    uint32_t delay_ticks;
} Task_Control_Block_t;

extern Task_Control_Block_t tcb_list[];

extern Task_Control_Block_t *current_TCB;
extern int max_task_num;
extern int current_task_id;
extern int next_task_id;
extern int is_first_switch_task;

extern uint32_t now_tick;


// proc from asm
extern void switch_task(void);

// proc from c
extern void init_task(void);

extern int create_task(void *function, void *arguements, stack_t *stack, int stack_size);

extern void switch_current_TCB(void);

extern void SysTick_Handler(void);

extern void delay(uint32_t us);

extern void task_idle(void);

#endif //OS_TASK_H
