	IMPORT tcb_list
	IMPORT current_TCB
	IMPORT current_task_id
	IMPORT next_task_id
	IMPORT max_task_num
	IMPORT switch_current_TCB
	IMPORT is_first_switch_task
		
	IMPORT now_tick

	PRESERVE8
	THUMB
		
	AREA CODE, CODE, READONLY

PendSV_Handler PROC	
	EXPORT PendSV_Handler
		
; turn off all interrupt
    CPSID I


; check PSP, if PSP == 0, this is the first task switch
; so we can skip 'save context' and 'select next TCB' step
    MRS R0, PSP
    ; if r0 == 0, jump to restore_context
	; LDR R1, =is_first_switch_task
    CBZ R0, restore_context

save_context
    MRS R0, PSP
    STMDB R0!, {R4-R11}
    LDR R1, =current_TCB
    LDR R1, [R1]
    STR R0, [R1]

select_next_TCB
	PUSH {LR}
    BL switch_current_TCB
	POP {LR}

restore_context
    LDR R0, =current_TCB
    LDR R0, [R0]
    LDR R0, [R0]
    LDMIA R0!, {R4-R11}
    MSR PSP, R0
	ORR LR, LR, #0x4 ; R1 |= 0x04 : lr |= 32'b0000_0000_0000_0100

; turn on all interrupt
    CPSIE I

; return
    BX LR

	ENDP
	
	NOP
	
	END