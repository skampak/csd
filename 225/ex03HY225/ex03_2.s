    .data
str_xyz: .asciiz "xyz"
    .text
    .globl main
main:
    la $20, str_xyz	#fortonoume sthn mnhmh to "xyz" ston kataxwrhth 20
    lw $20, ($20)	#fortonoume to "xyz" apo thn mnhmnh ston 20
    addi    $2, $0, 1	# system call code for print_int
    add     $4, $20, $0	
    syscall	
    j main
