# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

	.section .data	# 
N:	.long 1000	    # 
S:	.long 0		    # 
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	# 
.globl main
main:	
	pushl %ebp	    #push ebp at main's stack frame
	movl %esp, %ebp	#move value of ebp into esp

 	# initialize
    movl N, %ebx	#move value of ebx into N 

 	# compute sum
L1:
	addl %ebx, S	#add S to ebx
	decl %ebx       #substruct one from the ebx 
	cmpl $0, %ebx   #compare the value of ebx with 0
	jng  L2	    	#Jump to L2 if
    movl $L1, %eax	#move value of eax into L1 pointer 
    jmp *%eax   	#jump to eax pointer

L2:
	# print result
	pushl S	    	#push global var S to stack 
	pushl N	        #push global var N to stack
	pushl $Msg  	# 
	call printf 	#
	popl %eax   	#pop Msg from main stack 
	popl %eax   	#pop N from main stack
	popl %eax   	#pop G from main stack 

	# exit
	movl $0, %eax  	#value of eax is 0 
    leave	    	#
 	ret             #

