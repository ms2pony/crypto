	.file	"mont_mul_opt.c"
	.text
	.p2align 4
	.globl	mont_mul_opt
	.type	mont_mul_opt, @function
mont_mul_opt:
.LFB119:
	.cfi_startproc
	pushq	%r12	# 入栈
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	xorl	%r8d, %r8d
	movabsq	$17592186044416, %r10 # r10=2^44
	pushq	%rbp	# 入栈
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	leaq	T(%rip), %rbp	# rbp=T[0]
	movq	%rbp, %rax
	pushq	%rbx	# 入栈
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	leaq	80(%rbp), %r11
	movq	%rdi, %rbx	# rbx=&res
	movabsq	$4398046511104, %r9	# r9=2^42
	.p2align 4,,10
	.p2align 3
.L3:
# 约减
	movq	(%rax), %rdx		# rdx=T[0]
	movq	64(%rax), %r12		# r12=T[8]
	movq	%rdx, %rcx			# rcx=T[0]
	movq	24(%rax), %rsi		# rsi=T[3]
	salq	$16, %rcx			# rcx=<<16 => rcx=T[0]<<16
	movq	%rdx, %rdi			# rdi=T[0]
	subq	%rcx, %r12			# r12=T[8]-T[0]<<16
	movq	%rdx, %rcx			# rcx=T[0]
	salq	$18, %rdx			# rdx<<=18 => rdx=T[0]<<18
	subq	%rdx, %rsi			# rsi=T[3]-T[0]<<18
	leaq	(%rsi,%r10), %rdx	# rdx=T[3]-T[0]<<18+2^44
	salq	$22, %rcx			# rcx=<<22 => rcx=T[0]<<22
	addq	72(%rax), %rcx		# rcx=T[9]+T[0]<<22
	movq	%rdx, 24(%rax)		# T[3]=rdx	# 多余
	salq	$12, %rdi			# rdi=<<12 => rdi=T[0]<<12
	leaq	(%r12,%r9), %rdx	# rdx=T[8]-T[0]<<16+2^42
	movq	%rdx, 64(%rax)		# T[8]=rdx	rdx~T[8]	# 多余
	addq	16(%rax), %rdi		# rdi=T[2]+T[0]<<12
	leaq	-65536(%rcx), %rdx	# rdx=T[9]+T[0]<<22-2^16
	subq	$262144, 32(%rax)	# T[4]=T[4]-2^18	# 多余
	movq	%rdi, 16(%rax)		# T[2]=T[2]+T[0]<<12	# 多余
	movq	%rdx, 72(%rax)		# T[9]=T[9]+T[0]<<22-2^16	# 多余
	testl	%r8d, %r8d

# 规整, 9次
	je	.L2
	movq	8(%rax), %rdx
	movq	%rdx, %rcx
	shrq	$26, %rcx
	addq	%rdi, %rcx
	andl	$67108863, %edx
	movq	%rcx, 16(%rax)
	movq	%rdx, 8(%rax)
.L2:
	addq	$8, %rax
	incl	%r8d
	cmpq	%rax, %r11
	jne	.L3

# - 最后阶段规整, T[11]~T[18], 8次
	movq	88+T(%rip), %rdx	# rdx=T[11]
	movq	%rdx, %rax			
	shrq	$26, %rax
	addq	96+T(%rip), %rax	# rax=T[12]
	andl	$67108863, %edx
	movq	%rdx, 88+T(%rip)

	movq	%rax, %rdx
	shrq	$26, %rdx
	addq	104+T(%rip), %rdx	# rdx=T[13]
	andl	$67108863, %eax
	movq	%rax, 96+T(%rip)

	movq	%rdx, %rax
	shrq	$26, %rax
	addq	112+T(%rip), %rax	# rax=T[14]
	andl	$67108863, %edx
	movq	%rdx, 104+T(%rip)

	movq	%rax, %rdx
	shrq	$26, %rdx
	addq	120+T(%rip), %rdx	# rdx=T[15]
	andl	$67108863, %eax
	movq	%rax, 112+T(%rip)

	movq	%rdx, %rax
	shrq	$26, %rax
	addq	128+T(%rip), %rax	# rax=T[16]
	andl	$67108863, %edx
	andl	$67108863, %edx
	movq	%rdx, 120+T(%rip)

	movq	%rax, %rdx
	shrq	$26, %rdx
	addq	136+T(%rip), %rdx	# rdx=T[17]
	andl	$67108863, %eax
	movq	%rax, 128+T(%rip)

	movq	%rdx, %rax
	shrq	$26, %rax
	addq	144+T(%rip), %rax	# rax=T[18]
	andl	$67108863, %edx
	movq	%rdx, 136+T(%rip)

	movq	%rax, %rdx
	shrq	$26, %rdx
	andl	$67108863, %eax
	addq	%rdx, 152+T(%rip)	# T[19]=
	movq	%rax, 144+T(%rip)	# T[18]=
# - 

	movq	%rbp, (%rbx)		# (rbx)=res=addr(T[0])
	popq	%rbx				# 出栈
	.cfi_def_cfa_offset 24
	popq	%rbp				# 出栈
	.cfi_def_cfa_offset 16
	popq	%r12				# 出栈
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE119:
	.size	mont_mul_opt, .-mont_mul_opt
	.globl	T
	.data
	.align 32
	.type	T, @object
	.size	T, 160
T:
	.quad	22409285
	.quad	32103488
	.quad	58632258
	.quad	19837680
	.quad	39532235
	.quad	35044689
	.quad	49999819
	.quad	35938846
	.quad	58269607
	.quad	64254720
	.quad	2879735
	.quad	63732654
	.quad	6266677
	.quad	58942425
	.quad	58305999
	.quad	45452089
	.quad	9505350
	.quad	4614425
	.quad	35573532
	.quad	8308
	.ident	"GCC: (GNU) 12.1.0"
	.section	.note.GNU-stack,"",@progbits
