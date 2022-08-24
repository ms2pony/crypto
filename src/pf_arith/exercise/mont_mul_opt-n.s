	.file	"mont_mul_opt.c"
	.text
	.p2align 4
	.globl	mont_mul_opt
	.type	mont_mul_opt, @function
mont_mul_opt:
.LFB119:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	16+T(%rip), %rax 	# rax->T[2]
	movq	72+T(%rip), %r11 	# 9
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	64+T(%rip), %rdi 	# 8
	leaq	72(%rax), %r15		# r15->T[2+9]=T[11]
	movq	40+T(%rip), %r14	# 5
	movq	32+T(%rip), %r10	# 4
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	48+T(%rip), %r13	# 6
	movq	24+T(%rip), %rdx	# 3
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	16+T(%rip), %rsi	# 2
	movq	56+T(%rip), %r12	# 7
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	T(%rip), %r8		# 0
	movq	8+T(%rip), %rbp		# 1
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	80+T(%rip), %rbx	# 10
	movq	%r13, -8(%rsp)		# T[6]=>(rsp-8)
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L9:
	movq	%r9, %rsi			# rsi=T[2]
	movq	%rcx, %rdi			# rdi=T[8]
	andl	$67108863, %r9d		# r9d=T[2]&67108863
	addq	$8, %rax			# rax->T[3]
	shrq	$26, %rsi			# rsi=T[2]>>26
	shrq	$26, %rdi			# rdi=T[8]>>26
	andl	$67108863, %ecx		# ecx=T[8]&67108863
	movq	%r9, -8(%rax)
	addq	%r13, %rsi			# rsi=T[3]+T[2]>>26, rsi->T[3]
	addq	%r8, %rdi			# rdi=T[9]+T[8]>>26, rdi->T[9]
	movq	%rbp, %r8			# r8=T[1]
	movq	%rcx, 40(%rax)		# T[8]=T[8] 感觉是无用功
	movq	%rsi, %rdx			# rdx=T[3]
	movq	%rdi, %r11			# r11=T[9]
	andl	$67108863, %esi		# esi=T[3]&67108863
	andl	$67108863, %edi		# edi=T[9]&67108863
	shrq	$26, %rdx			# rdx=T[3]>>26
	shrq	$26, %r11			# r11=T[9]>>26
	leaq	96+T(%rip), %rbp	# rbp->T[12]
	movq	%rsi, (%rax)		# T[3]=rsi=T[3]
	addq	%r10, %rdx			
	addq	%rbx, %r11
	movq	%rdi, 48(%rax)
	movq	%rdx, %r10
	movq	%r11, %rbx
	andl	$67108863, %edx
	andl	$67108863, %r11d
	shrq	$26, %r10
	shrq	$26, %rbx
	addq	64(%rax), %rbx
	movq	%rdx, 8(%rax)
	addq	%r14, %r10
	movq	%rbx, 64(%rax)
	movq	-8(%rsp), %r14
	movq	%r10, 16(%rax)
	movq	%r11, 56(%rax)
	movq	%r12, -8(%rsp)
	# cmpq	%rbp, %rax
	# je	.L8
	movq	%r9, %rbp
	movq	%rcx, %r12
.L3:
	movq	%r8, %rcx				# T[0]=>rcx
	movq	%r8, %r9				# T[0]=>r9
	movabsq	$17592186044416, %r13	# (1<<44)=>r13
	subq	$262144, %r10			# T[4]-=(1<<18) <= r10=T[4], r10-=(1<<18), 
	salq	$18, %rcx				# rcx=T[0], T[0]~T2[3], T2[3]=T[0]<<18, rcx->T2[3]
	salq	$12, %r9				# r9=T[0], r9=<<12, 
	movq	%r10, 16(%rax)			# 16(rax)=T[4]= T[4]-=(1<<18)
	subq	%rcx, %r13				# (1<<44)-T2[3]=>r13
	addq	%rsi, %r9				# T[0]<<12+T[2]=>r9	r9->T[2]
	movabsq	$4398046511104, %rcx	# (1<<42)=>rcx
	addq	%rdx, %r13				# (1<<44)-T2[3]+T[3]=>r13 => T[3]=-T2[3];T[3]+=(1<<44)
	movq	%r8, %rdx				# T[0]=>rdx
	salq	$22, %r8				# T[0]<<22=>r8
	movq	%r9, (%rax)				# T[2]=r9
	salq	$16, %rdx				# rdx=T[0]<<16
	leaq	-65536(%r11,%r8), %r8	# T[0]<<22+T[9]-1<<16=>r8, r8->T[9]
	movq	%r13, 8(%rax)			# T[3]=r13
	subq	%rdx, %rcx				# rcx=(1<<42)-T[0]<<16
	movq	%r8, 56(%rax)			# T[9]=r8
	addq	%rdi, %rcx				# rcx=(1<<42)-T[0]<<16+T[8]=T[8]-T2[8]+1<<42 rcx->T[8]
	movq	%rcx, 48(%rax)			# T[8]=rcx
	cmpq	%r15, %rax				# addr(T[2])-addr(T[11])
	jne	.L9
	movq	88+T(%rip), %rdi
	movq	136+T(%rip), %rsi
	movq	%rdi, %rdx
	andl	$67108863, %edi
	shrq	$26, %rdx
	addq	96+T(%rip), %rdx
	movq	%rdx, %rax
	movq	%rdx, %rcx
	shrq	$26, %rax
	addq	104+T(%rip), %rax
	andl	$67108863, %ecx
	movq	%rax, %r9
	andl	$67108863, %eax
	movq	%rax, %rdx
	movq	%rsi, %rax
	shrq	$26, %r9
	andl	$67108863, %esi
	shrq	$26, %rax
	addq	144+T(%rip), %rax
	addq	112+T(%rip), %r9
	movq	%rax, %r8
	andl	$67108863, %eax
	shrq	$26, %r8
	addq	152+T(%rip), %r8
.L4:
	movq	80+T(%rip), %r11
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	movq	%r11, %r10
	andl	$67108863, %r11d
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	shrq	$26, %r10
	movq	%r11, 80+T(%rip)
	popq	%r15
	.cfi_def_cfa_offset 8
	addq	%rdi, %r10
	movq	%r10, %rdi
	andl	$67108863, %r10d
	shrq	$26, %rdi
	movq	%r10, 88+T(%rip)
	addq	%rcx, %rdi
	movq	%rdi, %rcx
	andl	$67108863, %edi
	shrq	$26, %rcx
	movq	%rdi, 96+T(%rip)
	addq	%rdx, %rcx
	movq	%rcx, %rdx
	andl	$67108863, %ecx
	shrq	$26, %rdx
	movq	%rcx, 104+T(%rip)
	addq	%r9, %rdx
	movq	%rdx, %rcx
	andl	$67108863, %edx
	shrq	$26, %rcx
	addq	120+T(%rip), %rcx
	movq	%rdx, 112+T(%rip)
	movq	%rcx, %rdx
	andl	$67108863, %ecx
	shrq	$26, %rdx
	addq	128+T(%rip), %rdx
	movq	%rcx, 120+T(%rip)
	movq	%rdx, %rcx
	andl	$67108863, %edx
	shrq	$26, %rcx
	movq	%rdx, 128+T(%rip)
	addq	%rsi, %rcx
	movq	%rcx, %rdx
	andl	$67108863, %ecx
	shrq	$26, %rdx
	movq	%rcx, 136+T(%rip)
	addq	%rdx, %rax
	movq	%rax, %rdx
	andl	$67108863, %eax
	shrq	$26, %rdx
	movq	%rax, 144+T(%rip)
	addq	%r8, %rdx
	movq	%rdx, 152+T(%rip)
	ret
# .L8:
# 	.cfi_restore_state
# 	movq	88+T(%rip), %rdi
# 	movq	96+T(%rip), %rcx
# 	movq	104+T(%rip), %rdx
# 	movq	112+T(%rip), %r9
# 	movq	136+T(%rip), %rsi
# 	movq	144+T(%rip), %rax
# 	movq	152+T(%rip), %r8
# 	jmp	.L4
# 	.cfi_endproc
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
