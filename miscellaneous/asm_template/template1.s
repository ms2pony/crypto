	.text
	.section	.rodata
.LD0:
	.string	"hello world! number is %d\n"

.text
.globl	main
.type	main, @function
main:
	.L1:
		pushq	%rbp
		movq	%rsp, %rbp
		leaq	.LD0(%rip), %rdi
		mov		$30, %rsi
		add		$0xffffffffffffffff, %rsi
		call	printf
		movl	$0, %eax
		popq	%rbp
		ret
