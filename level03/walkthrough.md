Looking into the code, there is a randomizer of addresses, so it seems impossible to exploit a buffer overflow or a string format.
So, in order to have a shell here, we need to enter this if statement :

```c
	if ((!bVar6 && !bVar7) == bVar6) { // -> We need bVar6 == 0 and bVar7 == 1 
		iVar3 = system("/bin/sh");
    }
```

So let's start from the end. As we added, we are focusing on two variables.
With a simple equivalence table, we see that we want:

```mathematica
A	B	(!A and !B)		((!A and !B) == A)
0	0		 1					0
0	1		 0					1
1	0		 0					0
1	1		 0					0
Here :
A = bVar6 must be 0
B = bVar7 must be 1
```

If we go further back, we got 

```c
	iVar3 = 0x11;
	puVar4 = &local_21;
	pbVar5 = (byte *)"Congratulations!";
	while (bVar7)
	{
		if (iVar3 == 0)
			break;
		iVar3 = iVar3 + -1;
		bVar6 = *(byte *)puVar4 < *pbVar5;
		bVar7 = *(byte *)puVar4 == *pbVar5;
		puVar4 = (undefined4 *)((int)puVar4 + 1);
		pbVar5 = pbVar5 + 1;
	}
```

From here, we can easily see that to go outside the `while` loop while having bVar7 = 1, we need to reach the break statement, that means that we need to loop 11 times, and this statement must be always true : `*(byte *)puVar4 == *pbVar5`, that means that the first 11 bytes of puVar4 and pbVar5 must be equals.
We know that pbVar5 is a string containing `Congratulations!`, so let's focus on puVar4, and in particular, local_21.

```c
	unsigned int local_21;
	unsigned int local_1d;
	unsigned int local_19;
	unsigned int local_15;

	local_21 = 0x757c7d51;
	local_1d = 0x67667360;
	local_19 = 0x7b66737e;
	local_15 = 0x33617c7d;

	local_2c = 0;
	while( true ) {
		bVar6 = local_2c < ~uVar2 - 1;
		bVar7 = local_2c == ~uVar2 - 1;
		if (!bVar6) break;
		*(byte *)((int)&local_21 + local_2c) = (byte)ctx ^ *(byte *)((int)&local_21 + local_2c);
		local_2c = local_2c + 1;
	}

```

Here is the important part. There is some kind of encryption. There is a loop going over 20 bytes of memory that have been pre-defined. And for each byte, there is a `xor` with `ctx`. So if we could manipulate ctx, it would be perfect.

Digging into the function `test` that call `decrypt`, there is a switch:

```c
void test(int param_1,int param_2)

{
  EVP_PKEY_CTX *ctx;
  uchar *out;
  size_t *outlen;
  uchar *in;
  size_t inlen;

  ctx = (EVP_PKEY_CTX *)(param_2 - param_1);
  switch(ctx) {
	default -> randomize of ctx then call to decrypt(ctx)
	0x1 to 0x9  and 0x10 to 0x15-> call of decrypt(ctx)
```

It's easy to guess that if we any of the value of ctx can give us an access to the promt, it will be a fix state.
So we need to know what's param_1 and param_2.

```assembly
level03@OverRide:~$ gdb -q level03 
Reading symbols from /home/users/level03/level03...(no debugging symbols found)...done.
(gdb) disas main
Dump of assembler code for function main:
[...]
   0x080488c6 <+108>:	mov    0x1c(%esp),%eax
   0x080488ca <+112>:	movl   $0x1337d00d,0x4(%esp)
   0x080488d2 <+120>:	mov    %eax,(%esp)
   0x080488d5 <+123>:	call   0x8048747 <test>
   0x080488da <+128>:	mov    $0x0,%eax

```

Here, we can see the two arguments of test : 
the first one is the result of `scanf` id-est our input and the second one a fix value, `0x8048747` (= 322424845)
It's easy to check while in gdb with a breakpoint here :

```assembly
   0x08048760 <+25>:	ja     0x804884a <test+259>
```

And looking at the content of eax.
From here, you could automate the process, but there is only 15 possibilities.
So after 30 seconds of trying :

```bash
level03@OverRide:~$ ./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

```bash
su level04
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```

