#include <os.h>

#define STACK_SIZE 32

stack_t stack_0[STACK_SIZE];
stack_t stack_1[STACK_SIZE];
stack_t stack_2[STACK_SIZE];
stack_t stack_3[STACK_SIZE];

int i0 = 0;
void task_0() {
    for (;;) {
        i0 = i0 == 0 ? 1 : 0;
    }
}

int i1 = 0;
void task_1() {
    for (;;) {
        i1 = i1 == 0 ? 1 : 0;
    }
}

int i2 = 0;
void task_2() {
    for (;;) {
        i2 = i2 == 0 ? 1 : 0;
    }
}

int i3 = 0;
void task_3() {
    for (;;) {
        i3 = i3 == 0 ? 1 : 0;
    }
}

int main(void) {
    os_init();

    create_task(task_0, 0, stack_0, STACK_SIZE);
    create_task(task_1, 0, stack_1, STACK_SIZE);
    create_task(task_2, 0, stack_2, STACK_SIZE);
    create_task(task_3, 0, stack_3, STACK_SIZE);

	os_start();
	
    for (;;);
}
