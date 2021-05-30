        AREA    RESET, DATA, READONLY
        EXPORT  __Vectors
__Vectors
        DCD     0x10001800     ; Dirección inicio del stack
        DCD     Reset_Handler  ; Vector de reset

        ALIGN
        AREA    MI_PROGRAMA, CODE, READONLY
        EXPORT  Reset_Handler
Reset_Handler

        LDR     R0,   =0X10000000

; Initialize memory
        LDR     R1,   =0X6AD6C7F0
        STR     R1, [R0]
        LDR     R1,   =0XFB88233D
        STR     R1, [R0,#4]
        LDR     R1,   =0XDEAD5E15
        STR     R1, [R0,#8]
        LDR     R1,   =0X13FB1102
        STR     R1, [R0,#12]
        LDR     R1,   =0X81D9B93C
        STR     R1, [R0,#16]
        LDR     R1,   =0XB44A60CC
        STR     R1, [R0,#20]
        LDR     R1,   =0X0001EEE5
        STR     R1, [R0,#24]
        LDR     R1,   =0X00002531
        STR     R1, [R0,#28]
        LDR     R1,   =0X00000000
        STR     R1, [R0,#32]
        STR     R1, [R0,#36]
        STR     R1, [R0,#40]
        LDR     R1,   =0X00003677
        STR     R1, [R0,#44]
; end of memory initialitazion

        LDR     R2,  =0X0000FFFF
        LDR     R3,  =0X00000000
        LDR     R4,  =0X0000DEAD
loop
        LDRH    R1, [R0]
        CMP     R1, R4
forever
        BEQ     forever
        CMP     R1, R2
        BHS     nomin
        MOV     R2, R1
nomin
        CMP     R1, R3
        BLS     inc
        MOV     R3, R1
inc
        ADDS    R0, #2
        B       loop

        END