When we arrive on this level, we manage to see that some protections are enabled :

```bash
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
Partial RELRO   Canary found      NX enabled    No PIE          No RPATH   No RUNPATH   /home/users/level06/level06
```

A Canary is found, which means we won't be able to overflow, and NX is enabled too, meaning that some memory segment are non executable. This gives us a hint : we better be looking at reverse engineering this binary !

At first run, we see that this program behaviors like most serial protected binaries : we enter a login/key and the programs expects a corresponding serial

```bash
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login:
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial:
```

After decompiling, we manage to see that the expected serial is computed inside the `auth` function :

```c
// Returns an int, not undefined. 1 is failure, 0 if success
undefined4 auth(char *s1, int32_t arg_ch)
{
    int32_t iVar1;
    undefined4 uVar2;
    int32_t iVar3;
    int32_t var_14h;
    uint32_t var_10h;
    undefined4 var_ch;
    
    iVar1 = strcspn();
    s1[iVar1] = '\0';
    iVar1 = strnlen();
    if (iVar1 < 6) {
        uVar2 = 1;
    } else {
        iVar3 = ptrace();
        if (iVar3 == -1) {
            puts();
            puts();
            puts();
            uVar2 = 1;
        } else {
          // COMPUTING OF THE SERIAL BELOW
            var_10h = ((int32_t)s1[3] ^ 0x1337U) + 0x5eeded;
            var_14h = 0;
            while (var_14h < iVar1) {
                if (s1[var_14h] < ' ') {
                    return 1;
                }
                var_10h = var_10h + ((int32_t)s1[var_14h] ^ var_10h) % 0x539;
                var_14h = var_14h + 1;
            }
          // Comparison here, to check wether they're the same, even though ghidra is not totally clear
            if (arg_ch == var_10h) {
                uVar2 = 0;
            } else {
                uVar2 = 1;
            }
        }
    }
    return uVar2;
}
```

So, as the function was quite clean, the easier was to directly copy this code, add a main and put a printf right before the only return 0, case of success, on the `var_10h` variable.

That's what we did :

* clean the code for incoherence
* remove ptrace protection and unnecessary parts of the code, create a main and run it

```c
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// WARNING: Removing unreachable block (ram,0x08048782)
// signed

int auth(char *s1, int32_t arg_ch)
{
    int32_t iVar1;
    int32_t uVar2;
    int32_t iVar3;
    int32_t var_14h;
    uint32_t var_10h;
   int32_t var_ch;

    iVar1 = strlen(s1);
    if (iVar1 < 6) {
        uVar2 = 1;
    } else {
            var_10h = ((int32_t)s1[3] ^ 0x1337U) + 0x5eeded;
            var_14h = 0;
            while (var_14h < iVar1) {
                if (s1[var_14h] < ' ') {
                    return 1;
                }
                var_10h = var_10h + ((int32_t)s1[var_14h] ^ var_10h) % 0x539;
                var_14h = var_14h + 1;
            }
	printf("deb: %d", var_10h);
            if (arg_ch == var_10h) {
                uVar2 = 0;
            } else {
                uVar2 = 1;
            }
        }
    return uVar2;
}

int main(int argc, char **arv){
	int pop = -1;
	char str[32] = "bonjour";
	if (argc != 2)
	{
		return (0);
	}
	if (strlen(arv[1]) > 31)
	{
		return (0);
	}


	pop = auth(str, 0);
	return (1);
}
```

We just built our own Keygen, very common in software cracking !

Run the program with a str > 6 as ARGV1, you'll get your corresponding serial :

```bash
$ gcc test.c
$ ./a.out hackagain
deb: 6234673%
```

Let's try it :

```bash
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: hackagain
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6234673
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```

```bash
su level07
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```

