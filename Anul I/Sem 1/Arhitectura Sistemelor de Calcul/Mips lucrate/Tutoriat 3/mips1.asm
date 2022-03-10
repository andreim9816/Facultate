.data
n: .word 11
S: .word 0
.text
main:
lw $t0,S #S=0
li $t1,1 #i=1
lw $t2,n
for:
   bgt $t1,$t2,final # t1>t2 go to final       i>n go to final 
      add $t0,$t0,$t1# t0=t0+t1     s=s+i
      addi $t1,$t1,1# i=i+1
      j for
final:
    sw $t0,S
    li $v0,10
    syscall