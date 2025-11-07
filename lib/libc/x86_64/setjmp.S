    .section .text
	.global setjmp
setjmp:
	mov 0(%rsp), %rdx // return address

	mov %rdx, 0(%rdi)
	mov %rbx, 8(%rdi)
	mov %rsp, 16(%rdi)
	mov %rbp, 24(%rdi)
	mov %r12, 32(%rdi)
	mov %r13, 40(%rdi)
	mov %r14, 48(%rdi)
	mov %r15, 56(%rdi)

	xor %rax, %rax
	ret