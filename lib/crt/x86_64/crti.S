    .section .init
    .global _init
_init:
    subq $8, %rax

    .section .fini
    .global _fini
_fini:
    subq $8, %rax