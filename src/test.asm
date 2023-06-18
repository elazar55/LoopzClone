; ------------------------------------------------------------------------------
; This is a Win64 console program.
; To assemble and run:
; nasm -fwin64 hello.asm && gcc hello.obj && a
; ------------------------------------------------------------------------------
        global  assembly
        section .text

assembly:
        mov eax, ecx
        ret