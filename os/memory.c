#include "./memory.h"
#include "./config.h"


struct memory_node {
    int size;
    int offset;
    char used;
    struct memory_node *prev;
    struct memory_node *next;
};

typedef struct memory_node memory_node_t;
    
char heap[CONFIG_OS_HEAP_SIZE + sizeof(memory_node_t)];

//// init linkedlist
//memory_node_t memory_table;
// all heap is a free memory block
memory_node_t *memory_all;

void init_memory() {
    memory_all = (memory_node_t *)heap;
    memory_all->size = CONFIG_OS_HEAP_SIZE;
    memory_all->offset = 0;
    memory_all->used = 0;
    memory_all->prev = 0;
    memory_all->next = 0;
}

void *malloc(int size) {
    memory_node_t *node = memory_all;
    while (node) {		
        if (node->used == 0) {
            int size_with_info = size + sizeof(memory_node_t);
            int remain = node->size - size_with_info;
            if (remain >= 0) {
                node->size = size;
                node->used = 1;
                if (remain > sizeof(memory_node_t)) {
                    int info_offset = node->offset + size_with_info;
                    memory_node_t *next_memory_node = (memory_node_t *)&heap[info_offset];
                    next_memory_node->size = remain - sizeof(memory_node_t);
                    next_memory_node->offset = info_offset + sizeof(memory_node_t);
                    next_memory_node->used = 0;
                    
                    next_memory_node->next = node->next;
                    next_memory_node->prev = node;
                    
                    node->next = next_memory_node;
                }

                void *new_memory = (void *)&heap[node->offset + sizeof(memory_node_t)];
                return new_memory;
            }
        }
        node = node->next;
    }
    return 0;
}

int free(void *point) {
    memory_node_t *memory_node = (memory_node_t *)(point - sizeof(memory_node_t));
    if (memory_node < 0) {
        return 1;
    }
    
    memory_node_t *prev = memory_node->prev;
    memory_node_t *next = memory_node->next;
    if (prev && prev->used == 0 && next && next->used == 0) {
        prev->size += memory_node->size + next->size + 2 * sizeof(memory_node_t);
        prev->next = next;
        if (next->next) {
            next->next->prev = prev;
        }
    } else if (prev && prev->used == 0) {
        prev->size += memory_node->size + sizeof(memory_node_t);
        prev->next = next;
        next->prev = prev;
    } else if (next && next->used == 0) {
        memory_node->size += next->size + sizeof(memory_node_t);
        memory_node->next = next->next;
        memory_node->used = 0;
    } else {
        memory_node->used = 0;
    }

    return 0;
}
