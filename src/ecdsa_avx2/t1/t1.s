	.file	"t1.c"
	.text
	.globl	Z
	.bss
	.align 32
	.type	Z, @object
	.size	Z, 320
Z:
	.zero	320
	.comm	A_B,160,32
	.comm	C_D,160,32
	.text
	.globl	computer_256
	.type	computer_256, @function
computer_256:
.LFB4006:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	andq	$-32, %rsp
	subq	$3200, %rsp
	movq	%rdi, 40(%rsp)
	movq	%rsi, 32(%rsp)
	movq	%rdx, 24(%rsp)
	movq	%rcx, 16(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 3192(%rsp)
	xorl	%eax, %eax
	movq	$0, 96(%rsp)
	movq	$0, 104(%rsp)
	movq	$0, 112(%rsp)
	movq	$0, 120(%rsp)
	movq	96(%rsp), %rax
	movq	104(%rsp), %rdx
	vmovq	%rdx, %xmm2
	vpinsrq	$1, %rax, %xmm2, %xmm1
	movq	112(%rsp), %rax
	movq	120(%rsp), %rdx
	vmovq	%rdx, %xmm3
	vpinsrq	$1, %rax, %xmm3, %xmm0
	vinserti128	$0x1, %xmm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 128(%rsp)
	movq	16(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movq	32(%rsp), %rax
	vmovdqa	(%rax), %ymm0
	movq	32(%rsp), %rax
	addq	$32, %rax
	vmovdqa	(%rax), %ymm1
	vpalignr	$8, %ymm0, %ymm1, %ymm0
	vmovdqa	%ymm0, 2688(%rsp)
	movq	32(%rsp), %rax
	addq	$32, %rax
	vmovdqa	(%rax), %ymm0
	movq	32(%rsp), %rax
	addq	$64, %rax
	vmovdqa	(%rax), %ymm1
	vpalignr	$8, %ymm0, %ymm1, %ymm0
	vmovdqa	%ymm0, 2720(%rsp)
	movq	32(%rsp), %rax
	addq	$64, %rax
	vmovdqa	(%rax), %ymm0
	movq	32(%rsp), %rax
	addq	$96, %rax
	vmovdqa	(%rax), %ymm1
	vpalignr	$8, %ymm0, %ymm1, %ymm0
	vmovdqa	%ymm0, 2752(%rsp)
	movq	32(%rsp), %rax
	addq	$96, %rax
	vmovdqa	(%rax), %ymm0
	movq	32(%rsp), %rax
	subq	$-128, %rax
	vmovdqa	(%rax), %ymm1
	vpalignr	$8, %ymm0, %ymm1, %ymm0
	vmovdqa	%ymm0, 2784(%rsp)
	movq	32(%rsp), %rax
	subq	$-128, %rax
	vmovdqa	(%rax), %ymm0
	movq	32(%rsp), %rax
	vmovdqa	(%rax), %ymm1
	vpalignr	$8, %ymm0, %ymm1, %ymm0
	vmovdqa	%ymm0, 2816(%rsp)
	movq	16(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2496(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	$0, 52(%rsp)
	jmp	.L3
.L73:
	leaq	2496(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$68, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$352, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 56(%rsp)
	jmp	.L4
.L7:
	movl	56(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	32(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$352, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 320(%rsp)
	vmovdqa	%ymm0, 352(%rsp)
	vmovdqa	352(%rsp), %ymm0
	vmovdqa	320(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	56(%rsp), %eax
	addl	%edx, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	56(%rsp), %eax
	addl	%edx, %eax
	vmovdqa	%ymm0, 256(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 288(%rsp)
	vmovdqa	256(%rsp), %ymm1
	vmovdqa	288(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 56(%rsp)
.L4:
	cmpl	$4, 56(%rsp)
	jle	.L7
	leaq	2496(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2528(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$238, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 60(%rsp)
	jmp	.L8
.L11:
	movl	60(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$512, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 448(%rsp)
	vmovdqa	%ymm0, 480(%rsp)
	vmovdqa	480(%rsp), %ymm0
	vmovdqa	448(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	60(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	60(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	vmovdqa	%ymm0, 384(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 416(%rsp)
	vmovdqa	384(%rsp), %ymm1
	vmovdqa	416(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 60(%rsp)
.L8:
	cmpl	$3, 60(%rsp)
	jle	.L11
	leaq	2528(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	vmovdqa	2816(%rsp), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 640(%rsp)
	vmovdqa	%ymm0, 672(%rsp)
	vmovdqa	672(%rsp), %ymm0
	vmovdqa	640(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$51, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 192(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$204, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 224(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	vmovdqa	%ymm0, 576(%rsp)
	vmovdqa	192(%rsp), %ymm0
	vmovdqa	%ymm0, 608(%rsp)
	vmovdqa	576(%rsp), %ymm1
	vmovdqa	608(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	52(%rsp), %eax
	addl	$5, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %eax
	addl	$5, %eax
	vmovdqa	%ymm0, 512(%rsp)
	vmovdqa	224(%rsp), %ymm0
	vmovdqa	%ymm0, 544(%rsp)
	vmovdqa	512(%rsp), %ymm1
	vmovdqa	544(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 52(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$68, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rsi
	addq	%rsi, %rax
	subq	$352, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 64(%rsp)
	jmp	.L15
.L18:
	movl	64(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	32(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rdi
	addq	%rdi, %rax
	subq	$352, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 768(%rsp)
	vmovdqa	%ymm0, 800(%rsp)
	vmovdqa	800(%rsp), %ymm0
	vmovdqa	768(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	64(%rsp), %eax
	addl	%edx, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	64(%rsp), %eax
	addl	%edx, %eax
	vmovdqa	%ymm0, 704(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 736(%rsp)
	vmovdqa	704(%rsp), %ymm1
	vmovdqa	736(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 64(%rsp)
.L15:
	cmpl	$4, 64(%rsp)
	jle	.L18
	leaq	2528(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2560(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$238, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 68(%rsp)
	jmp	.L19
.L22:
	movl	68(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rsi
	addq	%rsi, %rax
	subq	$512, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rdi
	addq	%rdi, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 896(%rsp)
	vmovdqa	%ymm0, 928(%rsp)
	vmovdqa	928(%rsp), %ymm0
	vmovdqa	896(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	68(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	68(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	vmovdqa	%ymm0, 832(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 864(%rsp)
	vmovdqa	832(%rsp), %ymm1
	vmovdqa	864(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 68(%rsp)
.L19:
	cmpl	$3, 68(%rsp)
	jle	.L22
	leaq	2560(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	vmovdqa	2816(%rsp), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 1088(%rsp)
	vmovdqa	%ymm0, 1120(%rsp)
	vmovdqa	1120(%rsp), %ymm0
	vmovdqa	1088(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$51, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 192(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$204, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 224(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	vmovdqa	%ymm0, 1024(%rsp)
	vmovdqa	192(%rsp), %ymm0
	vmovdqa	%ymm0, 1056(%rsp)
	vmovdqa	1024(%rsp), %ymm1
	vmovdqa	1056(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	52(%rsp), %eax
	addl	$5, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %eax
	addl	$5, %eax
	vmovdqa	%ymm0, 960(%rsp)
	vmovdqa	224(%rsp), %ymm0
	vmovdqa	%ymm0, 992(%rsp)
	vmovdqa	960(%rsp), %ymm1
	vmovdqa	992(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	$0, 48(%rsp)
	jmp	.L26
.L27:
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 48(%rsp)
.L26:
	cmpl	$6, 48(%rsp)
	jle	.L27
	leaq	2560(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2592(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	addl	$1, 52(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$68, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rsi
	addq	%rsi, %rax
	subq	$352, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 72(%rsp)
	jmp	.L28
.L31:
	movl	72(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	32(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rdi
	addq	%rdi, %rax
	subq	$352, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 1216(%rsp)
	vmovdqa	%ymm0, 1248(%rsp)
	vmovdqa	1248(%rsp), %ymm0
	vmovdqa	1216(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	72(%rsp), %eax
	addl	%edx, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	72(%rsp), %eax
	addl	%edx, %eax
	vmovdqa	%ymm0, 1152(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 1184(%rsp)
	vmovdqa	1152(%rsp), %ymm1
	vmovdqa	1184(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 72(%rsp)
.L28:
	cmpl	$4, 72(%rsp)
	jle	.L31
	leaq	2592(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movl	$0, 48(%rsp)
	jmp	.L32
.L33:
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 48(%rsp)
.L32:
	cmpl	$14, 48(%rsp)
	jle	.L33
	leaq	2592(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2624(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$238, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 76(%rsp)
	jmp	.L34
.L37:
	movl	76(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rsi
	addq	%rsi, %rax
	subq	$512, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rdi
	addq	%rdi, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 1344(%rsp)
	vmovdqa	%ymm0, 1376(%rsp)
	vmovdqa	1376(%rsp), %ymm0
	vmovdqa	1344(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	76(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	76(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	vmovdqa	%ymm0, 1280(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 1312(%rsp)
	vmovdqa	1280(%rsp), %ymm1
	vmovdqa	1312(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 76(%rsp)
.L34:
	cmpl	$3, 76(%rsp)
	jle	.L37
	leaq	2624(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movl	$0, 48(%rsp)
	jmp	.L38
.L39:
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 48(%rsp)
.L38:
	cmpl	$30, 48(%rsp)
	jle	.L39
	movq	16(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2656(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	vmovdqa	2816(%rsp), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 1536(%rsp)
	vmovdqa	%ymm0, 1568(%rsp)
	vmovdqa	1568(%rsp), %ymm0
	vmovdqa	1536(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$51, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 192(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$204, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 224(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	vmovdqa	%ymm0, 1472(%rsp)
	vmovdqa	192(%rsp), %ymm0
	vmovdqa	%ymm0, 1504(%rsp)
	vmovdqa	1472(%rsp), %ymm1
	vmovdqa	1504(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	52(%rsp), %eax
	addl	$5, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %eax
	addl	$5, %eax
	vmovdqa	%ymm0, 1408(%rsp)
	vmovdqa	224(%rsp), %ymm0
	vmovdqa	%ymm0, 1440(%rsp)
	vmovdqa	1408(%rsp), %ymm1
	vmovdqa	1440(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	$0, 48(%rsp)
	jmp	.L43
.L44:
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 48(%rsp)
.L43:
	cmpl	$127, 48(%rsp)
	jle	.L44
	leaq	2624(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2656(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	addl	$1, 52(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$68, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rsi
	addq	%rsi, %rax
	subq	$352, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 80(%rsp)
	jmp	.L45
.L48:
	movl	80(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	32(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rdi
	addq	%rdi, %rax
	subq	$352, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 1664(%rsp)
	vmovdqa	%ymm0, 1696(%rsp)
	vmovdqa	1696(%rsp), %ymm0
	vmovdqa	1664(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	80(%rsp), %eax
	addl	%edx, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	80(%rsp), %eax
	addl	%edx, %eax
	vmovdqa	%ymm0, 1600(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 1632(%rsp)
	vmovdqa	1600(%rsp), %ymm1
	vmovdqa	1632(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 80(%rsp)
.L45:
	cmpl	$4, 80(%rsp)
	jle	.L48
	movl	$0, 48(%rsp)
	jmp	.L49
.L50:
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 48(%rsp)
.L49:
	cmpl	$31, 48(%rsp)
	jle	.L50
	leaq	2624(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2656(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$238, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 84(%rsp)
	jmp	.L51
.L54:
	movl	84(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rsi
	addq	%rsi, %rax
	subq	$512, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rdi
	addq	%rdi, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 1792(%rsp)
	vmovdqa	%ymm0, 1824(%rsp)
	vmovdqa	1824(%rsp), %ymm0
	vmovdqa	1792(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	84(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	84(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	vmovdqa	%ymm0, 1728(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 1760(%rsp)
	vmovdqa	1728(%rsp), %ymm1
	vmovdqa	1760(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 84(%rsp)
.L51:
	cmpl	$3, 84(%rsp)
	jle	.L54
	movl	$0, 48(%rsp)
	jmp	.L55
.L56:
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 48(%rsp)
.L55:
	cmpl	$15, 48(%rsp)
	jle	.L56
	leaq	2592(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2656(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	vmovdqa	2816(%rsp), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 1984(%rsp)
	vmovdqa	%ymm0, 2016(%rsp)
	vmovdqa	2016(%rsp), %ymm0
	vmovdqa	1984(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$51, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 192(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$204, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 224(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	vmovdqa	%ymm0, 1920(%rsp)
	vmovdqa	192(%rsp), %ymm0
	vmovdqa	%ymm0, 1952(%rsp)
	vmovdqa	1920(%rsp), %ymm1
	vmovdqa	1952(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	52(%rsp), %eax
	addl	$5, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %eax
	addl	$5, %eax
	vmovdqa	%ymm0, 1856(%rsp)
	vmovdqa	224(%rsp), %ymm0
	vmovdqa	%ymm0, 1888(%rsp)
	vmovdqa	1856(%rsp), %ymm1
	vmovdqa	1888(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	$0, 48(%rsp)
	jmp	.L60
.L61:
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 48(%rsp)
.L60:
	cmpl	$7, 48(%rsp)
	jle	.L61
	leaq	2560(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2656(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	addl	$1, 52(%rsp)
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$68, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rsi
	addq	%rsi, %rax
	subq	$352, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 88(%rsp)
	jmp	.L62
.L65:
	movl	88(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	32(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rdi
	addq	%rdi, %rax
	subq	$352, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 2112(%rsp)
	vmovdqa	%ymm0, 2144(%rsp)
	vmovdqa	2144(%rsp), %ymm0
	vmovdqa	2112(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	88(%rsp), %eax
	addl	%edx, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	88(%rsp), %eax
	addl	%edx, %eax
	vmovdqa	%ymm0, 2048(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 2080(%rsp)
	vmovdqa	2048(%rsp), %ymm1
	vmovdqa	2080(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 88(%rsp)
.L62:
	cmpl	$4, 88(%rsp)
	jle	.L65
	leaq	2528(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2656(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	40(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$238, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 92(%rsp)
	jmp	.L66
.L69:
	movl	92(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rsi
	addq	%rsi, %rax
	subq	$512, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rdi
	addq	%rdi, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 2240(%rsp)
	vmovdqa	%ymm0, 2272(%rsp)
	vmovdqa	2272(%rsp), %ymm0
	vmovdqa	2240(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	movl	52(%rsp), %edx
	movl	92(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	92(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	vmovdqa	%ymm0, 2176(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 2208(%rsp)
	vmovdqa	2176(%rsp), %ymm1
	vmovdqa	2208(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 92(%rsp)
.L66:
	cmpl	$3, 92(%rsp)
	jle	.L69
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	2496(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2656(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	vmovdqa	2816(%rsp), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	3200(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 2432(%rsp)
	vmovdqa	%ymm0, 2464(%rsp)
	vmovdqa	2464(%rsp), %ymm0
	vmovdqa	2432(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 160(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$51, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 192(%rsp)
	vmovdqa	128(%rsp), %ymm1
	vmovdqa	160(%rsp), %ymm0
	vpblendd	$204, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 224(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	vmovdqa	%ymm0, 2368(%rsp)
	vmovdqa	192(%rsp), %ymm0
	vmovdqa	%ymm0, 2400(%rsp)
	vmovdqa	2368(%rsp), %ymm1
	vmovdqa	2400(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	52(%rsp), %eax
	addl	$5, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %eax
	addl	$5, %eax
	vmovdqa	%ymm0, 2304(%rsp)
	vmovdqa	224(%rsp), %ymm0
	vmovdqa	%ymm0, 2336(%rsp)
	vmovdqa	2304(%rsp), %ymm1
	vmovdqa	2336(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	2656(%rsp), %rdx
	leaq	2656(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movq	16(%rsp), %rdx
	leaq	2656(%rsp), %rcx
	leaq	2656(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	2656(%rsp), %rcx
	movq	24(%rsp), %rax
	movl	$32, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	addl	$1, 52(%rsp)
.L3:
	cmpl	$4, 52(%rsp)
	jle	.L73
	leaq	Z(%rip), %rax
	movq	3192(%rsp), %rsi
	xorq	%fs:40, %rsi
	je	.L75
	call	__stack_chk_fail@PLT
.L75:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4006:
	.size	computer_256, .-computer_256
	.globl	computer_256_1
	.type	computer_256_1, @function
computer_256_1:
.LFB4007:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	andq	$-32, %rsp
	subq	$1376, %rsp
	movq	%rdi, 24(%rsp)
	movq	%rsi, 16(%rsp)
	movq	%rdx, 8(%rsp)
	movq	%rcx, (%rsp)
	movq	%fs:40, %rax
	movq	%rax, 1368(%rsp)
	xorl	%eax, %eax
	movq	(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movq	(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	672(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	672(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	672(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	704(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	704(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	704(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	736(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	736(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movl	$0, 44(%rsp)
	jmp	.L77
.L78:
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 44(%rsp)
.L77:
	cmpl	$6, 44(%rsp)
	jle	.L78
	leaq	736(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	768(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	768(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movl	$0, 44(%rsp)
	jmp	.L79
.L80:
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 44(%rsp)
.L79:
	cmpl	$14, 44(%rsp)
	jle	.L80
	leaq	768(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	800(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	800(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movl	$0, 44(%rsp)
	jmp	.L81
.L82:
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 44(%rsp)
.L81:
	cmpl	$30, 44(%rsp)
	jle	.L82
	movq	(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	832(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	$0, 44(%rsp)
	jmp	.L83
.L84:
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 44(%rsp)
.L83:
	cmpl	$127, 44(%rsp)
	jle	.L84
	leaq	800(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	832(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	$0, 44(%rsp)
	jmp	.L85
.L86:
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 44(%rsp)
.L85:
	cmpl	$31, 44(%rsp)
	jle	.L86
	leaq	800(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	832(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	$0, 44(%rsp)
	jmp	.L87
.L88:
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 44(%rsp)
.L87:
	cmpl	$15, 44(%rsp)
	jle	.L88
	leaq	768(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	832(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	movl	$0, 44(%rsp)
	jmp	.L89
.L90:
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	addl	$1, 44(%rsp)
.L89:
	cmpl	$7, 44(%rsp)
	jle	.L90
	leaq	736(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	832(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	704(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	832(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	672(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	832(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	leaq	832(%rsp), %rdx
	leaq	832(%rsp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_sqr_mont@PLT
	movq	(%rsp), %rdx
	leaq	832(%rsp), %rcx
	leaq	832(%rsp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	ecp_nistz256_mul_mont@PLT
	leaq	832(%rsp), %rcx
	movq	8(%rsp), %rax
	movl	$32, %edx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	memcpy@PLT
	movq	$0, 64(%rsp)
	movq	$0, 72(%rsp)
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	movq	64(%rsp), %rax
	movq	72(%rsp), %rdx
	vmovq	%rdx, %xmm2
	vpinsrq	$1, %rax, %xmm2, %xmm1
	movq	80(%rsp), %rax
	movq	88(%rsp), %rdx
	vmovq	%rdx, %xmm3
	vpinsrq	$1, %rax, %xmm3, %xmm0
	vinserti128	$0x1, %xmm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 96(%rsp)
	movl	$0, 48(%rsp)
	jmp	.L92
.L95:
	cmpl	$3, 48(%rsp)
	jg	.L93
	movl	48(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	16(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	movl	48(%rsp), %eax
	cltq
	addq	$1, %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	16(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm1
	vpalignr	$8, %ymm0, %ymm1, %ymm0
	movl	48(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	1376(%rsp), %rcx
	addq	%rcx, %rax
	subq	$512, %rax
	vmovdqa	%ymm0, (%rax)
	jmp	.L94
.L93:
	movq	16(%rsp), %rax
	subq	$-128, %rax
	vmovdqa	(%rax), %ymm0
	movq	16(%rsp), %rax
	vmovdqa	(%rax), %ymm1
	vpalignr	$8, %ymm0, %ymm1, %ymm0
	movl	48(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	1376(%rsp), %rcx
	addq	%rcx, %rax
	subq	$512, %rax
	vmovdqa	%ymm0, (%rax)
.L94:
	addl	$1, 48(%rsp)
.L92:
	cmpl	$4, 48(%rsp)
	jle	.L95
	movl	$0, 52(%rsp)
	jmp	.L96
.L108:
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	24(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$68, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	1376(%rsp), %rcx
	addq	%rcx, %rax
	subq	$352, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 56(%rsp)
	jmp	.L97
.L100:
	movl	56(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	16(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	1376(%rsp), %rcx
	addq	%rcx, %rax
	subq	$352, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 288(%rsp)
	vmovdqa	%ymm0, 320(%rsp)
	vmovdqa	320(%rsp), %ymm0
	vmovdqa	288(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 128(%rsp)
	movl	52(%rsp), %edx
	movl	56(%rsp), %eax
	addl	%edx, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	56(%rsp), %eax
	addl	%edx, %eax
	vmovdqa	%ymm0, 224(%rsp)
	vmovdqa	128(%rsp), %ymm0
	vmovdqa	%ymm0, 256(%rsp)
	vmovdqa	224(%rsp), %ymm1
	vmovdqa	256(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 56(%rsp)
.L97:
	cmpl	$4, 56(%rsp)
	jle	.L100
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	movq	24(%rsp), %rax
	addq	%rdx, %rax
	vmovdqa	(%rax), %ymm0
	vpshufd	$238, %ymm0, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	1376(%rsp), %rcx
	addq	%rcx, %rax
	subq	$192, %rax
	vmovdqa	%ymm0, (%rax)
	movl	$0, 60(%rsp)
	jmp	.L101
.L104:
	movl	60(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	1376(%rsp), %rcx
	addq	%rcx, %rax
	subq	$512, %rax
	vmovdqa	(%rax), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	1376(%rsp), %rsi
	addq	%rsi, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 416(%rsp)
	vmovdqa	%ymm0, 448(%rsp)
	vmovdqa	448(%rsp), %ymm0
	vmovdqa	416(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 128(%rsp)
	movl	52(%rsp), %edx
	movl	60(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %edx
	movl	60(%rsp), %eax
	addl	%edx, %eax
	addl	$1, %eax
	vmovdqa	%ymm0, 352(%rsp)
	vmovdqa	128(%rsp), %ymm0
	vmovdqa	%ymm0, 384(%rsp)
	vmovdqa	352(%rsp), %ymm1
	vmovdqa	384(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 60(%rsp)
.L101:
	cmpl	$3, 60(%rsp)
	jle	.L104
	vmovdqa	992(%rsp), %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	leaq	1376(%rsp), %rdi
	addq	%rdi, %rax
	subq	$192, %rax
	vmovdqa	(%rax), %ymm1
	vmovdqa	%ymm1, 608(%rsp)
	vmovdqa	%ymm0, 640(%rsp)
	vmovdqa	640(%rsp), %ymm0
	vmovdqa	608(%rsp), %ymm1
	vpmuludq	%ymm0, %ymm1, %ymm0
	nop
	vmovdqa	%ymm0, 128(%rsp)
	vmovdqa	96(%rsp), %ymm1
	vmovdqa	128(%rsp), %ymm0
	vpblendd	$51, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 160(%rsp)
	vmovdqa	96(%rsp), %ymm1
	vmovdqa	128(%rsp), %ymm0
	vpblendd	$204, %ymm1, %ymm0, %ymm0
	vmovdqa	%ymm0, 192(%rsp)
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	vmovdqa	%ymm0, 544(%rsp)
	vmovdqa	160(%rsp), %ymm0
	vmovdqa	%ymm0, 576(%rsp)
	vmovdqa	544(%rsp), %ymm1
	vmovdqa	576(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	movl	52(%rsp), %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	movl	52(%rsp), %eax
	addl	$5, %eax
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	(%rdx,%rax), %ymm0
	movl	52(%rsp), %eax
	addl	$5, %eax
	vmovdqa	%ymm0, 480(%rsp)
	vmovdqa	192(%rsp), %ymm0
	vmovdqa	%ymm0, 512(%rsp)
	vmovdqa	480(%rsp), %ymm1
	vmovdqa	512(%rsp), %ymm0
	vpaddq	%ymm0, %ymm1, %ymm0
	nop
	cltq
	salq	$5, %rax
	movq	%rax, %rdx
	leaq	Z(%rip), %rax
	vmovdqa	%ymm0, (%rdx,%rax)
	addl	$1, 52(%rsp)
.L96:
	cmpl	$4, 52(%rsp)
	jle	.L108
	leaq	Z(%rip), %rax
	movq	1368(%rsp), %rcx
	xorq	%fs:40, %rcx
	je	.L110
	call	__stack_chk_fail@PLT
.L110:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4007:
	.size	computer_256_1, .-computer_256_1
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
