#include <critical_section.h>

int pri_mask = 0;

void Critical_Section_Start() {
    pri_mask = store_PRIMASK();
}

void Critical_Section_End() {
    restore_PRIMASK(pri_mask);
}
