����� ������� 3221 5� ������ ��255



a) �� ��������� ������� �� ���� "The sum from 0 to 1000 is 500500"
d) o ������� ������� ��� main ����� 3 (�� assembly)
   o ������� bytes ��� ������� ��� main ����� 16
   �� offset ����� 28
2. 

  a)�� ��������� ������� ������ "The sum from 0 to 1000 is 500500"
  b)��� ������ sum.s � main ���� 11 �������
  d) o ������� ������� ��� main ����� 28
     o ������� bytes ��� ������� ��� main ����� 96
     �� offset ����� 12
  e) Sum=500500
     &Sum = 0x8049704
     n = -1
     &n = 0x80496fc
     ������ ���� �� ���� ���������� The sum from 0 to 1000 is 500500
     

3. a)�� ��������� ������� "The sum from 0 to 1000 is 500500"
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
     ��� � main ���� 8 ������� assembly
   c)�� ��������� ������� "The sum from 0 to 1000 is 500500"


     