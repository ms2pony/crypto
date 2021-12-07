	.file	"t1.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB4006:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	andq	$-32, %rsp
	movq	$20, -64(%rsp)
	movq	$30, -56(%rsp)
	movq	$40, -48(%rsp)
	movq	$50, -40(%rsp)
	movq	-64(%rsp), %rax
	movq	-56(%rsp), %rdx
	vmovq	%rdx, %xmm2
	vpinsrq	$1, %rax, %xmm2, %xmm1
	movq	-48(%rsp), %rax
	movq	-40(%rsp), %rdx
	vmovq	%rdx, %xmm3
	vpinsrq	$1, %rax, %xmm3, %xmm0
	vinserti128	$0x1, %xmm1, %ymm0, %ymm0
	vmovdqa	%ymm0, -32(%rsp)
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4006:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
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
