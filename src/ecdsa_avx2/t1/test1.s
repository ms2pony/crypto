	.text
	.p2align 4
	# .globl	test1
	# .type	test1, @function

# test1:
# 	pushq	%rbp
# 	movq	%rsp, %rbp
# 	andq	$-32, %rsp
# 	subq	$192, %rsp
# 	vmovdqa	(%rsi), %ymm7
# 	vmovdqa	32(%rsi), %ymm2
# 	vpshufd	$68, (%rdi), %ymm1
# 	vpalignr	$8, 128(%rsi), %ymm7, %ymm0
# 	# .rep 100	
# 		# mov $5, %rbx	# 添加
# 		# mov $2, %rdx	# 添加
# 		# mov $12, %r8	# 添加
# 		# mov $12, %r9	# 添加
# 		vmovdqa	96(%rsi), %ymm3
# 		movq	%fs:40, %rax
# 		movq	%rax, 184(%rsp)
# 		xorl	%eax, %eax
# 		vpalignr	$8, %ymm7, %ymm2, %ymm6
# 		vpmuludq	%ymm7, %ymm1, %ymm7
# 		vmovdqa	64(%rsi), %ymm2
# 		# add %rbx, %rdx	# 添加
# 		# sub %rbx, %r9	# 添加
# 		vpaddq	Z(%rip), %ymm7, %ymm7	# 1
# 		vpalignr	$8, 32(%rsi), %ymm2, %ymm4
# 		vpalignr	$8, %ymm2, %ymm3, %ymm3
# 		vmovdqa	128(%rsi), %ymm2
# 		# sub %rbx, %r8	# 添加
# 		# add %rdx, %rbx	# 添加
# 		# mov $9, %rbx	# 添加
# 		vpalignr	$8, 96(%rsi), %ymm2, %ymm2	# 0
# 		vmovdqa	%ymm7, Z(%rip)
# 		vpmuludq	32(%rsi), %ymm1, %ymm10
# 		# add %rbx, %rdx	# 添加
# 		# sub %rbx, %r9	# 添加
# 		vpaddq	32+Z(%rip), %ymm10, %ymm10	# 0
# 		vmovdqa	%ymm10, 32+Z(%rip)
# 		vpmuludq	64(%rsi), %ymm1, %ymm9
# 		# sub %rbx, %r8	# 添加
# 		# add %rdx, %rbx	# 添加
# 		# mov $9, %rbx	# 添加
# 		vpaddq	64+Z(%rip), %ymm9, %ymm9	# 0
# 		vmovdqa	%ymm9, 64+Z(%rip)
# 		vpmuludq	96(%rsi), %ymm1, %ymm8
# 		# add %rbx, %rdx	# 添加
# 		# sub %rbx, %r9	# 添加
# 		vpaddq	96+Z(%rip), %ymm8, %ymm8	# 0
# 		vmovdqa	%ymm8, 96+Z(%rip)
# 		vpmuludq	128(%rsi), %ymm1, %ymm1
# 		# sub %rbx, %r8	# 添加
# 		# add %rdx, %rbx	# 添加
# 		# mov $9, %rbx	# 添加
# 		vpaddq	128+Z(%rip), %ymm1, %ymm5	# 0
# 		vmovdqa	%ymm5, 128+Z(%rip)
# 		vpshufd	$238, (%rdi), %ymm1
# 		# add %rbx, %rdx	# 添加
# 		# sub %rbx, %r9	# 添加
# 		vpmuludq	%ymm6, %ymm1, %ymm11	# 0
# 		# add %rbx, %r8	# 添加
# 		# inc %rdx		# 添加
# 		vpaddq	%ymm10, %ymm11, %ymm10		# 0
# 		vpmuludq	%ymm4, %ymm1, %ymm11
# 	# .endr
# 	ret



# 	.globl	test2
# 	.type	test2, @function
# test2:
# 	endbr64
# 	pushq	%rbp
# 	movq	%rsp, %rbp
# 	andq	$-32, %rsp
# 	subq	$192, %rsp
# 	vmovdqa	(%rsi), %ymm7
# 	vmovdqa	32(%rsi), %ymm2
# 	vpshufd	$68, (%rdi), %ymm1
# 	vpalignr	$8, 128(%rsi), %ymm7, %ymm0
# 	# .rep 100
		
# 		vmovdqa	96(%rsi), %ymm3
# 		movq	%fs:40, %rax
# 		movq	%rax, 184(%rsp)
# 		xorl	%eax, %eax
# 		vpalignr	$8, %ymm7, %ymm2, %ymm6
# 		vpmuludq	%ymm7, %ymm1, %ymm7
# 		vmovdqa	64(%rsi), %ymm2
		
# 		vpaddq	Z(%rip), %ymm7, %ymm7	# 1
# 		vpalignr	$8, 32(%rsi), %ymm2, %ymm4
# 		vpalignr	$8, %ymm2, %ymm3, %ymm3
# 		vmovdqa	128(%rsi), %ymm2
		
# 		vpalignr	$8, 96(%rsi), %ymm2, %ymm2	# 0
# 		vmovdqa	%ymm7, Z(%rip)
# 		vpmuludq	32(%rsi), %ymm1, %ymm10
		
# 		vpaddq	32+Z(%rip), %ymm10, %ymm10	# 0
# 		vmovdqa	%ymm10, 32+Z(%rip)
# 		vpmuludq	64(%rsi), %ymm1, %ymm9
		
# 		vpaddq	64+Z(%rip), %ymm9, %ymm9	# 0
# 		vmovdqa	%ymm9, 64+Z(%rip)
# 		vpmuludq	96(%rsi), %ymm1, %ymm8
		
# 		vpaddq	96+Z(%rip), %ymm8, %ymm8	# 0
# 		vmovdqa	%ymm8, 96+Z(%rip)
# 		vpmuludq	128(%rsi), %ymm1, %ymm1
		
# 		vpaddq	128+Z(%rip), %ymm1, %ymm5	# 0
# 		vmovdqa	%ymm5, 128+Z(%rip)
# 		vpshufd	$238, (%rdi), %ymm1
		
# 		vpmuludq	%ymm6, %ymm1, %ymm11	# 0
		
# 		vpaddq	%ymm10, %ymm11, %ymm10		# 0
# 		vpmuludq	%ymm4, %ymm1, %ymm11
# 		mov $5, %rbx	# 添加
# 		mov $2, %rdx	# 添加
# 		mov $12, %r8	# 添加
# 		mov $12, %r9	# 添加
# 		add %rbx, %rdx	# 添加
# 		sub %rbx, %r9	# 添加
# 		sub %rbx, %r8	# 添加
# 		add %rdx, %rbx	# 添加
# 		mov $9, %rbx	# 添加
# 		add %rbx, %rdx	# 添加
# 		sub %rbx, %r9	# 添加
# 		sub %rbx, %r8	# 添加
# 		add %rdx, %rbx	# 添加
# 		mov $9, %rbx	# 添加
# 		add %rbx, %rdx	# 添加
# 		sub %rbx, %r9	# 添加
# 		sub %rbx, %r8	# 添加
# 		add %rdx, %rbx	# 添加
# 		mov $9, %rbx	# 添加
# 		add %rbx, %rdx	# 添加
# 		sub %rbx, %r9	# 添加
# 		add %rbx, %r8	# 添加
# 		inc %rdx		# 添加
# 	# .endr
# 	ret



	.globl	test1
	.type	test1, @function
test1:
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
	.rep 20	
		mov $5, %rbx	# 添加
		mov $2, %rdx	# 添加
		mov $12, %r8	# 添加
		mov $12, %r9	# 添加
	vmovdqa	96(%rsi), %ymm3
	movq	%fs:40, %rax
	movq	%rax, 184(%rsp)
	xorl	%eax, %eax
	vpalignr	$8, %ymm7, %ymm2, %ymm6
	vpmuludq	%ymm7, %ymm1, %ymm7
	vmovdqa	64(%rsi), %ymm2
		add %rbx, %rdx	# 添加
		sub %rbx, %r9	# 添加
	vpaddq	Z(%rip), %ymm7, %ymm7
	vpalignr	$8, 32(%rsi), %ymm2, %ymm4
	vpalignr	$8, %ymm2, %ymm3, %ymm3
	vmovdqa	128(%rsi), %ymm2
	sub %rbx, %r8	# 添加
		add %rdx, %rbx	# 添加
		mov $9, %rbx	# 添加
	vpalignr	$8, 96(%rsi), %ymm2, %ymm2
	vmovdqa	%ymm7, Z(%rip)
	vpmuludq	32(%rsi), %ymm1, %ymm10
	add %rbx, %rdx	# 添加
		sub %rbx, %r9	# 添加
	vpaddq	32+Z(%rip), %ymm10, %ymm10
	vmovdqa	%ymm10, 32+Z(%rip)
	vpmuludq	64(%rsi), %ymm1, %ymm9
	sub %rbx, %r8	# 添加
		add %rdx, %rbx	# 添加
		mov $9, %rbx	# 添加
	vpaddq	64+Z(%rip), %ymm9, %ymm9
	vmovdqa	%ymm9, 64+Z(%rip)
	vpmuludq	96(%rsi), %ymm1, %ymm8
	add %rbx, %rdx	# 添加
		sub %rbx, %r9	# 添加
	vpaddq	96+Z(%rip), %ymm8, %ymm8
	vmovdqa	%ymm8, 96+Z(%rip)
	vpmuludq	128(%rsi), %ymm1, %ymm1
	sub %rbx, %r8	# 添加
	add %rdx, %rbx	# 添加
	mov $9, %rbx	# 添加
	vpaddq	128+Z(%rip), %ymm1, %ymm5
	vmovdqa	%ymm5, 128+Z(%rip)
	vpshufd	$238, (%rdi), %ymm1
	add %rbx, %rdx	# 添加
	sub %rbx, %r9	# 添加
	vpmuludq	%ymm6, %ymm1, %ymm11
	add %rbx, %r8	# 添加
	inc %rdx		# 添加
	vpaddq	%ymm10, %ymm11, %ymm10
	vpmuludq	%ymm4, %ymm1, %ymm11
	.endr
	vmovdqa	%ymm10, 32+Z(%rip)
	vpaddq	%ymm9, %ymm11, %ymm9
	vpmuludq	%ymm3, %ymm1, %ymm11
	vmovdqa	%ymm9, 64+Z(%rip)
	vpaddq	%ymm8, %ymm11, %ymm8
	vpmuludq	%ymm2, %ymm1, %ymm11
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


	.globl	test2
	.type	test2, @function
test2:
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
	.rep 20	
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
	.endr
	vmovdqa	%ymm10, 32+Z(%rip)
	vpaddq	%ymm9, %ymm11, %ymm9
	vpmuludq	%ymm3, %ymm1, %ymm11
	vmovdqa	%ymm9, 64+Z(%rip)
	vpaddq	%ymm8, %ymm11, %ymm8
	vpmuludq	%ymm2, %ymm1, %ymm11
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
	.rep 20
		mov $5, %rbx	# 添加
		mov $2, %rdx	# 添加
		mov $12, %r8	# 添加
		mov $12, %r9	# 添加
		add %rbx, %rdx	# 添加
		sub %rbx, %r9	# 添加
		sub %rbx, %r8	# 添加
		add %rdx, %rbx	# 添加
		mov $9, %rbx	# 添加
		add %rbx, %rdx	# 添加
		sub %rbx, %r9	# 添加
		sub %rbx, %r8	# 添加
		add %rdx, %rbx	# 添加
		mov $9, %rbx	# 添加
		add %rbx, %rdx	# 添加
		sub %rbx, %r9	# 添加
		sub %rbx, %r8	# 添加
		add %rdx, %rbx	# 添加
		mov $9, %rbx	# 添加
		add %rbx, %rdx	# 添加
		sub %rbx, %r9	# 添加
		add %rbx, %r8	# 添加
		inc %rdx		# 添加
	.endr

	ret
.L6:
	.cfi_restore_state
	vzeroupper
	call	__stack_chk_fail@PLT
	.cfi_endproc



	.globl	test3
	.type	test3, @function
test3:
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
	.rep 20	
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
	.endr
	vmovdqa	%ymm10, 32+Z(%rip)
	vpaddq	%ymm9, %ymm11, %ymm9
	vpmuludq	%ymm3, %ymm1, %ymm11
	vmovdqa	%ymm9, 64+Z(%rip)
	vpaddq	%ymm8, %ymm11, %ymm8
	vpmuludq	%ymm2, %ymm1, %ymm11
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
.L7:
	.cfi_restore_state
	vzeroupper
	call	__stack_chk_fail@PLT
	.cfi_endproc




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



