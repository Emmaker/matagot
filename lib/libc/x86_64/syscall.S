    .section .text
	.global syscall
	.global __syscall
	.global scall
syscall:
__syscall:
	mov %rdi, %rax
	mov %rsi, %rdi
	mov %rdx, %rsi
	mov %rcx, %rdx
	mov %r8, %r10
	mov %r9, %r8
	mov 8(%rsp), %r9

	syscall
	ret

/*
 * This "safe" wrapper automatically handles
 * any error return values by setting errno
 * accordingly, returning -1 if there is an
 * error.
 */
scall:
	call syscall
	// test if the return value is error
	cmp $-4095, %rax
	jb 1f // skip errno if no error

	/*
	 * call __errno_location to get the addr
	 * of errno, and move the (neg) ret val
	 */
	neg %rax
	pushq %rax
	call __errno_location
	mov %rax, %rdi
	popq %rax
	mov %rdi, (%rax)
	mov $-1, %rax
1:
	ret

// I'm not using an executable stack mooom
.section .note.GNU-stack,"",@progbits
