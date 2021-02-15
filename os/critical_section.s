    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

store_PRIMASK PROC
    EXPORT store_PRIMASK
        
    MRS     R0, PRIMASK
    CPSID   I
    
    ; return
    BX LR

    ENDP

restore_PRIMASK PROC
    EXPORT restore_PRIMASK
        
    MSR     PRIMASK, R0
    
    ; return
    BX LR

    ENDP

    END
