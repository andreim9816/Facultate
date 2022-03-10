.data
n: .word 12
ok: .space 4
.text
main:

 li $t0, 2 #i=2
 lw $t1, n
 div $t1,$t0
 mflo $t2 # t2=n/2

for:
 bgt $t0,$t2,prim
  div $t1,$t0
  mfhi $t3 # t3=t1%t0   t3=n%i
  beq $t3,$0,neprim #t3 == 0
  addi $t0,$t0,1
  j for
prim:
 li $t0,1
 sw $t0,ok
 j iesire
neprim:
 sw $0,ok
iesire:
 li $v0,10
 syscall