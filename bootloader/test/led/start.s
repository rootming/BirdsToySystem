.global _start

_start:
        /* Disable Watchdog */
    ldr r0, =0xE2700000
    /* ldr r0, =ELFIN_WATCHDOG_BASE */
    mov r1, #0
    str r1, [r0]
    ldr sp, =0xD0030000

    b main 
