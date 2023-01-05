These are the legal operations in the language:

push $
pop $
mov $ $K
add $ $K
sub $ $K
mul $ $K
div $ $K
jmp @
jgt @ $K
jlt @ $K
jle @ $K
jge @ $K
jal @
ret

These are the meaning of the argument symbols:

$: reg
r0 -> r4, sp, pc, ra

@: label

K: constant

