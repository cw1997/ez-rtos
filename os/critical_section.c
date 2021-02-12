#include "./critical_section.h"
#include <stdint.h>

uint8_t pri_mask = 0;

uint8_t count = 0;

void Critical_Section_Start() {
	__asm("CPSID I");
	++count;
    // pri_mask = store_PRIMASK();
}

void Critical_Section_End() {
	--count;
	if (count == 0) {
		__asm("CPSIE I");
	}
    // restore_PRIMASK(pri_mask);
}
