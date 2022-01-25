	.file	"t2.c"
	.text
	.p2align 4
	.globl	computer_256
	.type	computer_256, @function
computer_256:
.LFB5284:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	andq	$-32, %rsp
	subq	$192, %rsp
	vmovdqa	(%rsi), %ymm7
	vmovdqa	32(%rsi), %ymm2
	vpshufd	$68, (%rdi), %ymm1
	vpalignr	$8, 128(%rsi), %ymm7, %ymm0
	vmovdqa	96(%rsi), %ymm3
	movq	%fs:40, %rax
	movq	%rax, 184(%rsp)
	xorl	%eax, %eax
	vpalignr	$8, %ymm7, %ymm2, %ymm6
	vpmuludq	%ymm7, %ymm1, %ymm7
	vmovdqa	64(%rsi), %ymm2
	vpaddq	Z(%rip), %ymm7, %ymm7
	vpalignr	$8, 32(%rsi), %ymm2, %ymm4
	vpalignr	$8, %ymm2, %ymm3, %ymm3
	vmovdqa	128(%rsi), %ymm2
	vpalignr	$8, 96(%rsi), %ymm2, %ymm2
	vmovdqa	%ymm7, Z(%rip)
	vpmuludq	32(%rsi), %ymm1, %ymm10
	vpaddq	32+Z(%rip), %ymm10, %ymm10
	vmovdqa	%ymm10, 32+Z(%rip)
	vpmuludq	64(%rsi), %ymm1, %ymm9
	vpaddq	64+Z(%rip), %ymm9, %ymm9
	vmovdqa	%ymm9, 64+Z(%rip)
	vpmuludq	96(%rsi), %ymm1, %ymm8
	vpaddq	96+Z(%rip), %ymm8, %ymm8
	vmovdqa	%ymm8, 96+Z(%rip)
	vpmuludq	128(%rsi), %ymm1, %ymm1
	vpaddq	128+Z(%rip), %ymm1, %ymm5
	vmovdqa	%ymm5, 128+Z(%rip)
	vpshufd	$238, (%rdi), %ymm1
	vpmuludq	%ymm6, %ymm1, %ymm11
	vpaddq	%ymm10, %ymm11, %ymm10
	vpmuludq	%ymm4, %ymm1, %ymm11
	vmovdqa	%ymm10, 32+Z(%rip)
	vpaddq	%ymm9, %ymm11, %ymm9
	vpmuludq	%ymm3, %ymm1, %ymm11
	vmovdqa	%ymm9, 64+Z(%rip)
	vpaddq	%ymm8, %ymm11, %ymm8
	vpmuludq	%ymm2, %ymm1, %ymm11
	vpmuludq	%ymm0, %ymm1, %ymm1
	vmovdqa	%ymm8, 96+Z(%rip)
	vpaddq	%ymm5, %ymm11, %ymm11
	vpxor	%xmm5, %xmm5, %xmm5
	vpblendd	$51, %ymm5, %ymm1, %ymm12
	vmovdqa	%ymm11, 128+Z(%rip)
	vpblendd	$204, %ymm5, %ymm1, %ymm1
	vpaddq	%ymm12, %ymm7, %ymm7
	vmovdqa	%ymm7, Z(%rip)
	vpaddq	160+Z(%rip), %ymm1, %ymm1
	vmovdqa	%ymm1, 160+Z(%rip)
	vpshufd	$68, 32(%rdi), %ymm7
	vpmuludq	(%rsi), %ymm7, %ymm12
	vpaddq	%ymm10, %ymm12, %ymm10
	vmovdqa	%ymm10, 32+Z(%rip)
	vpmuludq	32(%rsi), %ymm7, %ymm12
	vpaddq	%ymm9, %ymm12, %ymm9
	vmovdqa	%ymm9, 64+Z(%rip)
	vpmuludq	64(%rsi), %ymm7, %ymm12
	vpaddq	%ymm8, %ymm12, %ymm8
	vmovdqa	%ymm8, 96+Z(%rip)
	vpmuludq	96(%rsi), %ymm7, %ymm12
	vpaddq	%ymm11, %ymm12, %ymm11
	vmovdqa	%ymm11, 128+Z(%rip)
	vpmuludq	128(%rsi), %ymm7, %ymm7
	vpaddq	%ymm1, %ymm7, %ymm7
	vmovdqa	%ymm7, 160+Z(%rip)
	vpshufd	$238, 32(%rdi), %ymm1
	vpmuludq	%ymm6, %ymm1, %ymm12
	vpaddq	%ymm9, %ymm12, %ymm9
	vpmuludq	%ymm4, %ymm1, %ymm12
	vmovdqa	%ymm9, 64+Z(%rip)
	vpaddq	%ymm8, %ymm12, %ymm8
	vpmuludq	%ymm3, %ymm1, %ymm12
	vmovdqa	%ymm8, 96+Z(%rip)
	vpaddq	%ymm11, %ymm12, %ymm11
	vpmuludq	%ymm2, %ymm1, %ymm12
	vpmuludq	%ymm0, %ymm1, %ymm1
	vmovdqa	%ymm11, 128+Z(%rip)
	vpaddq	%ymm7, %ymm12, %ymm12
	vpblendd	$51, %ymm5, %ymm1, %ymm7
	vpblendd	$204, %ymm5, %ymm1, %ymm1
	vpaddq	192+Z(%rip), %ymm1, %ymm1
	vmovdqa	%ymm12, 160+Z(%rip)
	vpaddq	%ymm7, %ymm10, %ymm10
	vmovdqa	%ymm1, 192+Z(%rip)
	vmovdqa	%ymm10, 32+Z(%rip)
	vpshufd	$68, 64(%rdi), %ymm7
	vpmuludq	(%rsi), %ymm7, %ymm10
	vpaddq	%ymm9, %ymm10, %ymm9
	vmovdqa	%ymm9, 64+Z(%rip)
	vpmuludq	32(%rsi), %ymm7, %ymm10
	vpaddq	%ymm8, %ymm10, %ymm8
	vmovdqa	%ymm8, 96+Z(%rip)
	vpmuludq	64(%rsi), %ymm7, %ymm10
	vpaddq	%ymm11, %ymm10, %ymm11
	vmovdqa	%ymm11, 128+Z(%rip)
	vpmuludq	96(%rsi), %ymm7, %ymm10
	vpaddq	%ymm12, %ymm10, %ymm12
	vmovdqa	%ymm12, 160+Z(%rip)
	vpmuludq	128(%rsi), %ymm7, %ymm7
	vpaddq	%ymm1, %ymm7, %ymm7
	vmovdqa	%ymm7, 192+Z(%rip)
	vpshufd	$238, 64(%rdi), %ymm1
	vpmuludq	%ymm6, %ymm1, %ymm10
	vpaddq	%ymm8, %ymm10, %ymm8
	vpmuludq	%ymm4, %ymm1, %ymm10
	vmovdqa	%ymm8, 96+Z(%rip)
	vpaddq	%ymm11, %ymm10, %ymm11
	vpmuludq	%ymm3, %ymm1, %ymm10
	vmovdqa	%ymm11, 128+Z(%rip)
	vpaddq	%ymm12, %ymm10, %ymm12
	vpmuludq	%ymm2, %ymm1, %ymm10
	vpmuludq	%ymm0, %ymm1, %ymm1
	vmovdqa	%ymm12, 160+Z(%rip)
	vpaddq	%ymm7, %ymm10, %ymm10
	vpblendd	$51, %ymm5, %ymm1, %ymm7
	vpblendd	$204, %ymm5, %ymm1, %ymm1
	vpaddq	224+Z(%rip), %ymm1, %ymm1
	vmovdqa	%ymm10, 192+Z(%rip)
	vpaddq	%ymm7, %ymm9, %ymm9
	vmovdqa	%ymm1, 224+Z(%rip)
	vmovdqa	%ymm9, 64+Z(%rip)
	vpshufd	$68, 96(%rdi), %ymm7
	vpmuludq	(%rsi), %ymm7, %ymm9
	vpaddq	%ymm8, %ymm9, %ymm8
	vmovdqa	%ymm8, 96+Z(%rip)
	vpmuludq	32(%rsi), %ymm7, %ymm13
	vpaddq	%ymm11, %ymm13, %ymm11
	vmovdqa	%ymm11, 128+Z(%rip)
	vpmuludq	64(%rsi), %ymm7, %ymm9
	vpaddq	%ymm12, %ymm9, %ymm12
	vmovdqa	%ymm12, 160+Z(%rip)
	vpmuludq	96(%rsi), %ymm7, %ymm9
	vpaddq	%ymm10, %ymm9, %ymm10
	vmovdqa	%ymm10, 192+Z(%rip)
	vpmuludq	128(%rsi), %ymm7, %ymm7
	vpaddq	%ymm1, %ymm7, %ymm7
	vmovdqa	%ymm7, 224+Z(%rip)
	vpshufd	$238, 96(%rdi), %ymm1
	vpmuludq	%ymm3, %ymm1, %ymm9
	vpmuludq	%ymm6, %ymm1, %ymm13
	vpaddq	%ymm10, %ymm9, %ymm10
	vpaddq	%ymm11, %ymm13, %ymm13
	vpmuludq	%ymm2, %ymm1, %ymm9
	vpmuludq	%ymm4, %ymm1, %ymm11
	vpmuludq	%ymm0, %ymm1, %ymm1
	vmovdqa	%ymm13, 128+Z(%rip)
	vmovdqa	%ymm10, 192+Z(%rip)
	vpaddq	%ymm7, %ymm9, %ymm9
	vpblendd	$51, %ymm5, %ymm1, %ymm7
	vpblendd	$204, %ymm5, %ymm1, %ymm1
	vpaddq	256+Z(%rip), %ymm1, %ymm1
	vmovdqa	%ymm9, 224+Z(%rip)
	vpaddq	%ymm12, %ymm11, %ymm12
	vpaddq	%ymm7, %ymm8, %ymm8
	vmovdqa	%ymm12, 160+Z(%rip)
	vmovdqa	%ymm1, 256+Z(%rip)
	vmovdqa	%ymm8, 96+Z(%rip)
	vpshufd	$68, 128(%rdi), %ymm7
	vpmuludq	(%rsi), %ymm7, %ymm8
	vpaddq	%ymm13, %ymm8, %ymm8
	vmovdqa	%ymm8, 128+Z(%rip)
	vpmuludq	32(%rsi), %ymm7, %ymm11
	vpaddq	%ymm12, %ymm11, %ymm11
	vmovdqa	%ymm11, 160+Z(%rip)
	vpmuludq	64(%rsi), %ymm7, %ymm12
	vpaddq	%ymm10, %ymm12, %ymm10
	vmovdqa	%ymm10, 192+Z(%rip)
	vpmuludq	96(%rsi), %ymm7, %ymm12
	vpaddq	%ymm9, %ymm12, %ymm9
	vmovdqa	%ymm9, 224+Z(%rip)
	vpmuludq	128(%rsi), %ymm7, %ymm7
	vpaddq	%ymm1, %ymm7, %ymm1
	vmovdqa	%ymm1, 256+Z(%rip)
	vpshufd	$238, 128(%rdi), %ymm7
	vpmuludq	%ymm2, %ymm7, %ymm2
	vpmuludq	%ymm0, %ymm7, %ymm0
	vpmuludq	%ymm6, %ymm7, %ymm6
	vpmuludq	%ymm4, %ymm7, %ymm4
	vpmuludq	%ymm3, %ymm7, %ymm3
	vpaddq	%ymm1, %ymm2, %ymm1
	vmovdqa	%ymm1, 256+Z(%rip)
	vpaddq	%ymm11, %ymm6, %ymm6
	vpaddq	%ymm10, %ymm4, %ymm4
	vpblendd	$51, %ymm5, %ymm0, %ymm1
	vpblendd	$204, %ymm5, %ymm0, %ymm0
	vpaddq	%ymm9, %ymm3, %ymm3
	vpaddq	288+Z(%rip), %ymm0, %ymm0
	vmovdqa	%ymm6, 160+Z(%rip)
	vpaddq	%ymm1, %ymm8, %ymm8
	vmovdqa	%ymm4, 192+Z(%rip)
	vmovdqa	%ymm3, 224+Z(%rip)
	vmovdqa	%ymm8, 128+Z(%rip)
	vmovdqa	%ymm0, 288+Z(%rip)
	movq	184(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L5
	leaq	Z(%rip), %rax
	vzeroupper
	leave
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L5:
	.cfi_restore_state
	vzeroupper
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE5284:
	.size	computer_256, .-computer_256
	.comm	C_D,160,32
	.comm	A_B,160,32
	.globl	Z
	.bss
	.align 32
	.type	Z, @object
	.size	Z, 320
Z:
	.zero	320
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
