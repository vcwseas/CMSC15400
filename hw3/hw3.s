	.section	__TEXT,__text,regular,pure_instructions
	.globl	_funcQ
	.align	4, 0x90
_funcQ:                                 ## @funcQ
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	12(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	%ecx, -4(%ebp)
	movl	%eax, -8(%ebp)
	imull	$3, -8(%ebp), %eax
	addl	-4(%ebp), %eax
	addl	$8, %esp
	popl	%ebp
	ret

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	movl	$0, %eax
	popl	%ebp
	ret


.subsections_via_symbols
