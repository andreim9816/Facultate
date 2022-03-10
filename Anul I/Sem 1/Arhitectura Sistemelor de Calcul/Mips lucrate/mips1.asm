.data
x: .word 5
y: .word 10

.text

main:
lw $t0,x
lw $t1,y

add $t0,$t0,$t1

move $a0,$t0 # a0=t0

li $v0,1
syscall

li $v0,10
syscall 