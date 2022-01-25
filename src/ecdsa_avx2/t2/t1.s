.text
.align	64
.Lpoly:
.quad	0xffffffffffffffff, 0x00000000ffffffff, 0x0000000000000000, 0xffffffff00000001

.globl __ecp_nistz256_mul_montx
.type	__ecp_nistz256_mul_montx,@function
.align	32
__ecp_nistz256_mul_montx:
.cfi_startproc	
	push	%rbp

	movl	$111, %ebx
	.byte	0x64, 0x67, 0x90
	mulxq	%r9,%r8,%r9 # rdx=>b[0], r9=>a[0]*b[0][high]
	mulxq	%r10,%rcx,%r10 # r10=>a[1]*b[0]
	movq	$32,%r14
	xorq	%r13,%r13
	mulxq	%r11,%rbp,%r11 # r11=>a[2]*b[0][high]
	movq	.Lpoly+24(%rip),%r15 # r15=>p[0]
	adcq	%rcx,%r9 # r9=>res[1]
	mulxq	%r12,%rcx,%r12 # r12=>a[3]*b[0]
	movq	%r8,%rdx # rdx=>a[0]*b[0][low]
	adcq	%rbp,%r10 # r10=>res[2]
	shlxq	%r14,%r8,%rbp # rbp=>r8<<32
	adcq	%rcx,%r11 # r11=>res[3]
	shrxq	%r14,%r8,%rcx # rcx=>r8>>32
	adcq	$0,%r12
	movl	$222, %ebx
	.byte	0x64, 0x67, 0x90




	addq	%rbp,%r9
	adcq	%rcx,%r10

	mulxq	%r15,%rcx,%rbp
	adcq	%rcx,%r11
	adcq	%rbp,%r12
	adcq	$0,%r13
	xorq	%r8,%r8



	mulxq	0+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r9
	adoxq	%rbp,%r10

	mulxq	8+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r10
	adoxq	%rbp,%r11

	mulxq	16+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r11
	adoxq	%rbp,%r12

	mulxq	24+128(%rsi),%rcx,%rbp
	movq	%r9,%rdx
	adcxq	%rcx,%r12
	shlxq	%r14,%r9,%rcx
	adoxq	%rbp,%r13
	shrxq	%r14,%r9,%rbp

	adcxq	%r8,%r13
	adoxq	%r8,%r8
	adcq	$0,%r8



	addq	%rcx,%r10
	adcq	%rbp,%r11

	mulxq	%r15,%rcx,%rbp
	adcq	%rcx,%r12
	adcq	%rbp,%r13
	adcq	$0,%r8
	xorq	%r9,%r9



	mulxq	0+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r10
	adoxq	%rbp,%r11

	mulxq	8+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r11
	adoxq	%rbp,%r12

	mulxq	16+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r12
	adoxq	%rbp,%r13

	mulxq	24+128(%rsi),%rcx,%rbp
	movq	%r10,%rdx
	adcxq	%rcx,%r13
	shlxq	%r14,%r10,%rcx
	adoxq	%rbp,%r8
	shrxq	%r14,%r10,%rbp

	adcxq	%r9,%r8
	adoxq	%r9,%r9
	adcq	$0,%r9



	addq	%rcx,%r11
	adcq	%rbp,%r12

	mulxq	%r15,%rcx,%rbp
	adcq	%rcx,%r13
	adcq	%rbp,%r8
	adcq	$0,%r9
	xorq	%r10,%r10



	mulxq	0+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r11
	adoxq	%rbp,%r12

	mulxq	8+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r12
	adoxq	%rbp,%r13

	mulxq	16+128(%rsi),%rcx,%rbp
	adcxq	%rcx,%r13
	adoxq	%rbp,%r8

	mulxq	24+128(%rsi),%rcx,%rbp
	movq	%r11,%rdx
	adcxq	%rcx,%r8
	shlxq	%r14,%r11,%rcx
	adoxq	%rbp,%r9
	shrxq	%r14,%r11,%rbp

	adcxq	%r10,%r9
	adoxq	%r10,%r10
	adcq	$0,%r10



	addq	%rcx,%r12
	adcq	%rbp,%r13

	mulxq	%r15,%rcx,%rbp
	movq	%r12,%rbx
	movq	.Lpoly+8(%rip),%r14
	adcq	%rcx,%r8
	movq	%r13,%rdx
	adcq	%rbp,%r9
	adcq	$0,%r10



	xorl	%eax,%eax
	movq	%r8,%rcx
	sbbq	$-1,%r12
	sbbq	%r14,%r13
	sbbq	$0,%r8
	movq	%r9,%rbp
	sbbq	%r15,%r9
	sbbq	$0,%r10

	cmovcq	%rbx,%r12
	cmovcq	%rdx,%r13
	movq	%r12,0(%rdi)
	cmovcq	%rcx,%r8
	movq	%r13,8(%rdi)
	cmovcq	%rbp,%r9
	movq	%r8,16(%rdi)
	movq	%r9,24(%rdi)

	pop		%rbp

	.byte	0xf3,0xc3
.cfi_endproc	
.size	__ecp_nistz256_mul_montx,.-__ecp_nistz256_mul_montx
