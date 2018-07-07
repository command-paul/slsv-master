	.file	"sync.c"
	.option nopic
	.text
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-16
	sd	s0,8(sp)
	addi	s0,sp,16
.L2:
	j	.L2
	.size	main, .-main
	.ident	"GCC: (GNU) 8.1.0"
