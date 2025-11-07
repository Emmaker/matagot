    .section .text
	.global sigsetjmp
sigsetjmp:
	call setjmp

	testq %rsi, %rsi
	jz 1f // skip if savemask is 0

	push %rdi // save pointer
	mov $1, %rdi // SIG_BLOCK
	mov $1, %rsi // (sigset_t *) set
	lea 64(%rcx), %rdx // (sigset_t *) oldset

	call sigprocmask
	pop %rdi
1:
	ret