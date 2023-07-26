.section .text
.global _start

_start:
    ldr r0, mark
    b .

mark: .word 0xDEADBEEF
