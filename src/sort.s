	.file	"sort.c"
	.text
	.p2align 4
	.globl	sort
	.type	sort, @function
sort:
.LFB1:
	.cfi_startproc
	endbr64
	cmpq	$1, %rsi
	jbe	.L1
	movq	%rdi, %r9
	movl	$1, %r10d
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%r9, %r8
	addq	$8, %r9
	movq	%r10, %rdx
	movq	%r9, %rax
	.p2align 4,,10
	.p2align 3
.L5:
	movq	(%r8), %rcx
	movq	(%rax), %rdi
	cmpq	%rdi, %rcx
	jle	.L4
	cmpq	%rax, %r8
	je	.L4
	movq	%rdi, (%r8)
	movq	%rcx, (%rax)
.L4:
	addq	$1, %rdx
	addq	$8, %rax
	cmpq	%rdx, %rsi
	ja	.L5
	addq	$1, %r10
	cmpq	%r10, %rsi
	jne	.L3
.L1:
	ret
	.cfi_endproc
.LFE1:
	.size	sort, .-sort
	.ident	"GCC: (Ubuntu 9.3.0-10ubuntu2) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
