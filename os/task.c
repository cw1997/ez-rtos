#include <task.h>

Task_Control_Block_t tcb_list[CONFIG_MAX_TASK_NUM];

Task_Control_Block_t *current_TCB = tcb_list;
int max_task_num = CONFIG_MAX_TASK_NUM;
int current_task_id = 0;
int next_task_id = 0;
int is_first_switch_task = 1;

void init_task() {
}

void switch_current_TCB() {
    if (current_task_id == next_task_id - 1) {
        current_task_id = 0;
    } else {
        ++current_task_id;
    }
    current_TCB = &tcb_list[current_task_id];
}


int create_task(void *function, void *arguements, stack_t *stack, int stack_size) {
    if (next_task_id > CONFIG_MAX_TASK_NUM) {
        return -1;
    }

    stack_t *stack_top = &stack[stack_size];
    // auto save by Cortex-M3
    *(--stack_top) = (stack_t)0x01000000u; // xPSR bit 24 = 1
    *(--stack_top) = (stack_t)function; // R15 PC function entry point
    *(--stack_top) = (stack_t)0x14141414u; // R14 LR
    *(--stack_top) = (stack_t)0x12121212u; // R12
    *(--stack_top) = (stack_t)0x03030303u; // R3
    *(--stack_top) = (stack_t)0x02020202u; // R2
    *(--stack_top) = (stack_t)0x01010101u; // R1
    *(--stack_top) = (stack_t)arguements; // R0
    // manual save by developer
    *(--stack_top) = (stack_t)0x11111111u; // R11
    *(--stack_top) = (stack_t)0x10101010u; // R10
    *(--stack_top) = (stack_t)0x09090909u; // R9
    *(--stack_top) = (stack_t)0x08080808u; // R8
    *(--stack_top) = (stack_t)0x07070707u; // R7
    *(--stack_top) = (stack_t)0x06060606u; // R6
    *(--stack_top) = (stack_t)0x05050505u; // R5
    *(--stack_top) = (stack_t)0x04040404u; // R4
    tcb_list[next_task_id].stack = stack_top;

    return next_task_id++;
}
