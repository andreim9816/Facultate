.data
x: .word 11
y: .word 16

.text

main:

lw $t0,x
lw $t1,y

bge $t0,$t1 et1
li $a0,0
j final

et1: 
li $a0,1

final:
li $v0,1
syscall

li $v0,10
syscall