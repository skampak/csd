.data
strnl: .asciiz "\n"
strt:  .asciiz "\t"
  .text
  .globl main

main:
    jal	node_alloc      #creating a new node
	sw	$0, ($2)       	#data=0,$2=v0
	sw	$0, 4($2)      	#nxtPtr=0 creating dummy node
	add	$16, $2, $0    	#head
	add	$17, $2, $0    	#tail
ask7_4:
    jal	read_int        #read int
	beq	$2, $0, ask7_5  #if int==0 or negative go to ask7_5
	add	$18, $2, $0    	# $18 stores user's input(int)
	jal	node_alloc      # create a node
	sw	$18, ($2)      	# initialize data= to input(int)
	sw	$0, 4($2)      	# initialize nxtPtr to 0
	sw	$2, 4($17)     	# new nod=tail
	add	$17, $0, $2    	# neo tail
	j	ask7_4

ask7_5:
    jal	read_int        # read int to compare
	add	$4, $16, $0     # storing the head
	add	$5, $2, $0     	# storing users input
	jal	search_list     # scan for smaller numbers than user's input(int)
	j	ask7_5
	
read_int:
	addi $29, $29, -4       #29=sp=stack_pointer
	sw	 $31, ($29)    
	addi $2, $0, 5      	# syscall readint
	syscall
	lw	$31, ($29)
	addi $29,$29, 4
	jr	$31
node_alloc:
	addi $29, $29, -4
	sw	$31, ($29)
	addi	$4, $0, 8       # bytes to allocate
	addi	$2, $0, 9      	# o kataxwritis 2 periexei to neo block mnhmhs
	syscall                 #syscall code for sbrk
	lw	$31, ($29)
	addi	$29, $29, 4
	jr	$31
print_node:
    addi $29, $29, -4       #-4 ton stack_pointer giati xreiazomaste 4 theseis mnhmhs
	sw	 $31, ($29)      	#fortonoume ston 32 thn nea address
	lw	 $8, ($4)        	#$8=t0 stores data for printing
	slt	 $9, $8, $17    	#comparing the two numbers(int)
	beq	 $9, $0, continue   # if $8>$17 don't print
	addi	$2, $0, 1      	# syscall for printint
	add	$4, $0, $8
	syscall
	addi	$2, $0, 4     	#syscall for print_str
	la	$4, strt         
	syscall                 #printing
continue:
	lw	$31, ($29)
	addi	$29, $29, 4
	jr	$31
search_list:
	addi $29, $29, -4
	sw	$31, ($29)
	add	$18, $0, $4     	#$18 stores head
	add	$17, $0, $5     	#$17 stores input
search:
	lw	$8, 4($18)		    #$8 = nxtPtr
	add	$4, $18, $0		    #print_node argument
	add	$18, $8, $0
	jal	print_node
	bne	$18, $0, search  	#oso nextPtr!=0
	addi	$2, $0, 4      	#syscall for print_str
	la	$4, strnl         
	syscall                 
	lw	 $31, ($29)
	addi $29, $29, 4
	jr	 $31
	
