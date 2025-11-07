    .section .text
	.global siglongjmp
siglongjmp:
	mov %rdi, %rdx
	push %rdi
	push %rsi

	mov $3, %rdi // SIG_SETMASK
	lea 64(%rdx), %rsi // (sigset_t *) set
	mov $0, %rdx // (sigset_t *) oldset

	call sigprocmask

	pop %rsi
	pop %rdi

	call longjmp