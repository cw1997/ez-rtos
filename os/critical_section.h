#ifndef OS_CRITICAL_SECTION_H
#define OS_CRITICAL_SECTION_H

int store_PRIMASK(void);
        
void restore_PRIMASK(int PRIMASK);

extern void Critical_Section_Start(void);
        
extern void Critical_Section_End(void);

#endif //OS_CRITICAL_SECTION_H
