	.file	"t2.c"
	.text
	.p2align 4
	.globl	test1
	.type	test1, @function
test1:
.LFB5284:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	andq	$-32, %rsp
	subq	$512, %rsp
	.cfi_offset 3, -24
	vmovdqa	.LC2(%rip), %ymm0
	vmovdqa	.LC1(%rip), %ymm5
	movq	%fs:40, %rax
	movq	%rax, 504(%rsp)
	xorl	%eax, %eax
	vmovdqa	.LC9(%rip), %ymm3
	leaq	160(%rsp), %rbx
	leaq	320(%rsp), %r11
	vmovdqa	%ymm0, 32(%rsp)
	vmovdqa	.LC3(%rip), %ymm0
	movq	%rbx, %rdx
	vmovdqa	%ymm3, 288(%rsp)
	vpalignr	$8, %ymm3, %ymm5, %ymm3
	vmovdqa	%ymm0, 64(%rsp)
	vmovdqa	.LC4(%rip), %ymm0
	vmovdqa	%ymm5, 160(%rsp)
	vmovdqa	%ymm0, 96(%rsp)
	vmovdqa	.LC5(%rip), %ymm0
	vmovdqa	%ymm0, 128(%rsp)
	vmovdqa	.LC6(%rip), %ymm0
	vmovdqa	%ymm0, 192(%rsp)
	vmovdqa	.LC7(%rip), %ymm0
	vmovdqa	%ymm0, 224(%rsp)
	vmovdqa	.LC8(%rip), %ymm0
	vmovdqa	%ymm0, 256(%rsp)
	cmpq	$4, %rax
	je	.L2
.L15:
	vmovdqa	32(%rdx), %ymm6
	movq	%rax, %rcx
	vpalignr	$8, (%rdx), %ymm6, %ymm0
	addq	$1, %rax
	salq	$5, %rcx
	addq	$32, %rdx
	vmovdqa	%ymm0, (%rcx,%r11)
	cmpq	$4, %rax
	jne	.L15
.L2:
	vmovdqa	.LC0(%rip), %ymm2
	movq	%rsp, %r9
	vmovdqa	%ymm3, 448(%rsp)
	leaq	Z(%rip), %rcx
	xorl	%r8d, %r8d
	leaq	160(%rbx), %rsi
	leaq	448(%rsp), %rdi
	vpxor	%xmm4, %xmm4, %xmm4
.L10:
	vmovdqa	%ymm2, %ymm1
	movq	%rbx, %rdx
	vpshufd	$68, %ymm2, %ymm2
	movq	%rcx, %rax
	vmovdqa	%ymm5, %ymm0
.L7:
	vpmuludq	%ymm0, %ymm2, %ymm0
	addq	$32, %rdx
	addq	$32, %rax
	vpaddq	-32(%rax), %ymm0, %ymm0
	vmovdqa	%ymm0, -32(%rax)
	cmpq	%rdx, %rsi
	je	.L6
	vmovdqa	(%rdx), %ymm0
	jmp	.L7
	.p2align 4,,10
	.p2align 3
.L6:
	leaq	32(%rcx), %r10
	vpshufd	$238, %ymm1, %ymm1
	movq	%r11, %rdx
	movq	%r10, %rax
.L8:
	vpmuludq	(%rdx), %ymm1, %ymm0
	vpaddq	(%rax), %ymm0, %ymm0
	addq	$32, %rdx
	addq	$32, %rax
	vmovdqa	%ymm0, -32(%rax)
	cmpq	%rdx, %rdi
	jne	.L8
	vpmuludq	%ymm3, %ymm1, %ymm1
	addl	$1, %r8d
	addq	$32, %r9
	vpblendd	$51, %ymm4, %ymm1, %ymm0
	vpblendd	$204, %ymm4, %ymm1, %ymm1
	vpaddq	(%rcx), %ymm0, %ymm0
	vpaddq	160(%rcx), %ymm1, %ymm1
	vmovdqa	%ymm0, (%rcx)
	vmovdqa	%ymm1, 160(%rcx)
	cmpl	$5, %r8d
	je	.L9
	vmovdqa	(%r9), %ymm2
	movq	%r10, %rcx
	jmp	.L10
	.p2align 4,,10
	.p2align 3
.L9:
	movq	504(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L16
	leaq	Z(%rip), %rax
	vzeroupper
	movq	-8(%rbp), %rbx
	leave
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L16:
	.cfi_restore_state
	vzeroupper
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE5284:
	.size	test1, .-test1
	.comm	C_D,160,32
	.comm	A_B,160,32
	.globl	Z
	.bss
	.align 32
	.type	Z, @object
	.size	Z, 320
Z:
	.zero	320
	.section	.rodata.cst32,"aM",@progbits,32
	.align 32
# A_B[0]
.LC0:
	.quad	542542
	.quad	3454
	.quad	34134
	.quad	561654
	.align 32
# C_D[0]
.LC1:
	.quad	542542
	.quad	34554
	.quad	344134
	.quad	24254
	.align 32
# A_B[1]
.LC2:
	.quad	5015684
	.quad	40823
	.quad	305623
	.quad	452542
	.align 32
.LC3:
	.quad	55160
	.quad	416450
	.quad	3550
	.quad	4524545
	.align 32
.LC4:
	.quad	50231
	.quad	40515
	.quad	30551
	.quad	42452
	.align 32
.LC5:
	.quad	502391
	.quad	405195
	.quad	30581
	.quad	42492
	.align 32
.LC6:
	.quad	542542
	.quad	38454
	.quad	344134
	.quad	25454
	.align 32
.LC7:
	.quad	542542
	.quad	348754
	.quad	341354
	.quad	24254
	.align 32
.LC8:
	.quad	542542
	.quad	34854
	.quad	341934
	.quad	24454
	.align 32
# C_D[4]
.LC9:
	.quad	542542
	.quad	34854
	.quad	3417834
	.quad	24574
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
