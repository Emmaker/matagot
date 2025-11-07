    .section .text
	.global longjmp
longjmp:
	mov 56(%rdi), %r15
	mov 48(%rdi), %r14
	mov 40(%rdi), %r13
	mov 32(%rdi), %r12
	mov 24(%rdi), %rbp
	mov 16(%rdi), %rsp
	mov 8(%rdi), %rbx

	jmp *0(%rdi)