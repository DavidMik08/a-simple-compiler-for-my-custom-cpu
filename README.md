# a-simple-compiler-for-my-custom-cpu
This is a simple compiler that compiles this new language thats simmilar to c into my assembly language.

# variables
For now there is only one type of variable unsigned 8-bit intager.
I've implemented expressions so we can do longer expressions on one line and save the result to a variables RAM address.
Variables are stored in the second half of RAM.

Example:
```
var a = 7
var b = 5+3-1
```

This code pushes 1, 3 and 5 to the stack and executes the instructions in order with the arguments from the stack, it also pushes the result of every instruction to the stack, so this code would compile to this:

```
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
```

# operators
The language supports the following operators for expressions:
```
+ - add
- - sub
| - or
/ - nor
& - and
$ - nand
^ - xor
# - xnor
>> - shr
> - grater than
>= - grater than or equal to
< - less than
<= - less than or equal to
== - equal to
```

# if/else statements
The language supports both inline and noinline if/else statements.

They follow a syntax simmilar to c:
```
if(condition;) // some code
else // some other code
```
Examples:

Inline:
```
if(a>b;) c = 6;
else c = 1;
```
Noinline:
```
if(a<b;) {
  d = 9;
} else {
  d = 53;
}
```

The inline example would be compile to something like this:
```
ifSetup:
  ; Push the value of variable b to the stack
  add b.Low 0 r7
  add b.Mid 0 r8
  add b.High 0 r9
  add ram 0 stk

  ; Push the value of variable a to the stack
  add a.Low 0 r7
  add a.Mid 0 r8
  add a.High 0 r9
  add ram 0 stk
  
ifCondition:
  add stk 0 r1
  add stk 0 r2
  add ifTrue.Low 0 r7
  add ifTrue.Mid 0 r8
  add ifTrue.High 0 r9
  sub r2 r1 r0
  bic 0 0 r0

  add ifFalse.Low 0 r7
  add ifFalse.Mid 0 r8
  add ifFalse.High 0 r9
  bnc 0 0 r0

ifTrue:
  add c.Low 0 r7
  add c.Mid 0 r8
  add c.High 0 r9
  add 6 0 ram
  add ifMerge.Low 0 r7
  add ifMerge.Mid 0 r8
  add ifMerge.High 0 r9
  bnc 0 0 r0

ifFalse:
  add c.Low 0 r7
  add c.Mid 0 r8
  add c.High 0 r9
  add 1 0 ram
  add ifMerge.Low 0 r7
  add ifMerge.Mid 0 r8
  add ifMerge.High 0 r9
  bnc 0 0 r0

ifMerge:
  // the rest of the code...
```

# while loops
The language supports both inline and noinline while loops.

They follow a synax simmilar to c:
```
while(condition;) // some code
```

Examples:

Inline:
```
while(a<10;) a = a + 1;
```
Noinline:
```
while(b>4;) {
  b = b - 1;
}
```

The inline example would be compile to something like this:
```
whileSetup:
  add 10 0 stk
  add a.Low 0 r7
  add a.Mid 0 r8
  add a.High 0 r9
  add ram 0 stk

whileCondition:
  add stk 0 r1
  add stk 0 r2
  add whileTrue.Low 0 r7
  add whileTrue.Mid 0 r8
  add whileTrue.High 0 r9
  sub r2 r1 0
  bic 0 0 r0
  
  add whileFalse.Low 0 r7
  add whileFalse.Mid 0 r8
  add whileFalse.High 0 r9
  bnc 0 0 r0

whileTrue:
  add 1 0 stk

  add a.Low 0 r7
  add a.Mid 0 r8
  add a.High 0 r9
  add ram stk

  add stk 0 r1
  add stk 0 r2

  add r1 r2 stk

  add a.Low 0 r7
  add a.Mid 0 r8
  add a.High 0 r9
  add stk 0 ram

  add whileSetup.Low 0 r7
  add whileSetup.Mid 0 r8
  add whileSetup.High 0 r9
  bnc 0 0 r0

whileFalse:
  // the rest of the code...
```

# future additions
I plan on adding the ability to use variables in expressions, constant and bool variables, for loops, and maybe functions and switch statements.
