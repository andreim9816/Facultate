.data
v: .word 5,6,10,12
n: .word 4
max: .word 0
.text
main:
lw $t3,n
li $t0,4
mul $t3,$t3,$t0 #t3 = t3*4 = 4*n
li $t4,0 #i
for:
 beq $t4,$t3,iesire
 lw $t0,v($t4)
 lw $t1,max
 bgt $t0,$t1,actualizare
 continua:
  addi $t4,$t4,4
 j for
 actualizare:
 sw $t0,max
 j continua
iesire: 
li $v0,10
syscall

