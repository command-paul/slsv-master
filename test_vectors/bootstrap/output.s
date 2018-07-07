
	.text
	.align	4
	.globl	main
	.type	main, @function
main:
  slsv: j slsv

.size	main, .-main
.section ".tohost","aw",@progbits
.align 4
.globl tohost
tohost: .word 0
.align 4
.globl fromhost
fromhost: .word 0
