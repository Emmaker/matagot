    .section .text
	.global syscall
syscall:
	mov %rdi, %rax
	mov %rsi, %rdi
	mov %rdx, %rsi
	mov %rcx, %rdx
	mov %r8, %r10
	mov %r9, %r8
	mov 8(%rsp), %r9

	syscall

	cmp $-4095, %rax
	jb 1f // skip errno if no error
	neg %rax
	mov %rax, %rdi
	call __set_errno
	mov $-1, %rax
1:
	ret