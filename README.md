# a-simple-compiler-for-my-custom-cpu
This is a simple compiler that compiles this new language thats simmilar to c into my assembly language.
For now i only made variables work but i plan on adding loops, if/else statements and maybe functions.

# variables
For now there is only one type of variable unsigned 8-bit intager.
I've implemented expressions so we can do longer expressions on one line and save the result to a variables RAM address.
Variables are stored in the second half of RAM.

Example:
var a = 7
var b = 5+3-1

This code pushes 1, 3 and 5 to the stack and executes the instructions in order with the arguments from the stack, it also pushes the result of every instruction to the stack, so this code would compile to this:


; Making a definition for the address of variable: a

#define a 8388608

add 7 0 stk

; Storing to the variable a at the address: 8388608

add a.Low 0 r7

add a.Mid 0 r8

add a.High 0 r9

add stk 0 ram

; Making a definition for the address of variable: b

#define b 8388609

add 1 0 stk

add 3 0 stk

add 5 0 stk

add stk 0 r1

add stk 0 r2

add r1 r2 stk

add stk 0 r1

add stk 0 r2

sub r1 r2 stk

; Storing to the variable b at the address: 8388609

add b.Low 0 r7

add b.Mid 0 r8

add b.High 0 r9

add stk 0 ram


# operators
The language supports the following operators for expressions:

'+' - add

'-' - sub

'|' - or

'/' - nor

'&' - and

'$' - nand

'^' - xor

'#' - xnor

'>' - shr


# future additions
I plan on adding the ability to use variables in expressions, constant and bool variables, while and for loops, if/else statements and maybe functions and switch statements.
