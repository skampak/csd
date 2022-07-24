Σοφία Καμπάκη 3221 5η ασκηση ΗΥ255



a) Το προγραμμα τυπώνει το εξής "The sum from 0 to 1000 is 500500"
d) o αριθμος εντολων της main ειναι 3 (σε assembly)
   o αριθμος bytes των εντολων της main ειναι 16
   το offset ειναι 28
2. 

  a)Το προγραμμα τυπωνει επισης "The sum from 0 to 1000 is 500500"
  b)Στο αρχείο sum.s η main εχει 11 εντολες
  d) o αριθμος εντολων της main ειναι 28
     o αριθμός bytes των εντολών της main ειναι 96
     το offset ειναι 12
  e) Sum=500500
     &Sum = 0x8049704
     n = -1
     &n = 0x80496fc
     Βγαζει ξανα το ίδιο αποτέλεσμα The sum from 0 to 1000 is 500500
     

3. a)Το πρόγραμμα τυπώνει "The sum from 0 to 1000 is 500500"
   b).cfi_startproc
        leal    4(%esp), %ecx
        .cfi_def_cfa 1, 0
        andl    $-16, %esp
        pushl   -4(%ecx)
        pushl   %ebp
        .cfi_escape 0x10,0x5,0x2,0x75,0
        movl    %esp, %ebp
        pushl   %ecx
        .cfi_escape 0xf,0x3,0x75,0x7c,0x6
        subl    $4, %esp
      #APP
       # 12 "x86sum.c" 1
        movl n, %ebx
     ’ρα η main εχει 8 εντολες assembly
   c)Το πρόγραμμα τυπώνει "The sum from 0 to 1000 is 500500"


     