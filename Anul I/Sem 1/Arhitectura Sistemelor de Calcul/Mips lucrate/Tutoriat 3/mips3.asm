.data
n: .word 12
ok: .space 4
s: .word 0
.text
main:

 li $t0, 2 #i=2
 lw $t1, n
 div $t1,$t0
 mflo $t2 # t2=n/2

for:

 bgt $t0,$t2, iesire
  div $t1,$t0
  mfhi $t3 # t3=t1%t0   t3=n%i
  beq $t3,$0,divizor #t3 == 0
  j continua
divizor:
 lw $t4,s
 add $t4,$t4,$t0
 sw $t4,s
 continua:
 addi $t0,$t0,1
 j for

iesire:
 lw $t4,s
 addi $t4,$t4,1
 add $t4,$t4,$t1
 sw $t4,s
 li $v0,10
 syscall
