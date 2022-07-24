   .data
 a: .space 32
    .align 2
 str_n: .asciiz "Grapse 8 noumera"
 str_nl: .asciiz "\n"
 str_t: .asciiz "\t"
 str_l: .asciiz "eksaplasia me antistrofh seira"
   .text
   .globl main
   
main:  
       la $20, a #o register 20 periexei thn dieythinsi tou pinaka
	   addi $8, $0, 0 #temp
	   addi $11, $0, 0  #kataxwriths 11 krataei posous arithmous phra
       addi $12, $0, 8 #kataxwriths 12 krataei ton arithmo 8,toplhthos twn stoixei
prstr:
	   addi    $2, $0, 4       # system call code for print_string
       la      $4, str_n       # pseudo-instruction: address of string
       syscall
	   addi $2, $0, 4
	   la $4, str_nl
	   syscall
loopr:
      add $2,$0, 5  
      syscall
      add $8, $2, $0
      add $8, $8, $8   #i=i+i diplasio
      add $8, $8, $8   #i=i+i tetraplasio
      add $8, $8, $2   #i=i+ to int pou diabasame
      add $8, $8, $2    #i=i+ to int pou diabasame kai exoume to eksaplasio
      sw $8, ($20)  
	  addi $11, $11, 1  
      addi $20, $20, 4
      bne $11, $12, loopr
	  
	  addi $20, $20, -4  #pame sto swsto keli
      
	  addi $11, $0, 0   #counter=0
	  addi $2, $0 , 4
	  la $4, str_l
	  syscall
	  addi    $2, $0, 4       
      la      $4, str_nl       
      syscall           
looppr:	  
       lw $8, ($20)	    #fortono apo thn mnhmh ston kataxwrhth 8
       addi $2, $0, 1   #printing integer
       add $4, $8, $0
       syscall
       addi $20, $20, -4      #se kathe loop paei me antistrofh seira
       addi $11, $11, 1
       addi    $2, $0, 4       # syscall print_string
       la      $4, str_t     
       syscall                 
       bne $11, $12, looppr
       j main