A simple use of ghidra on this level, and we see that it's the same as the level0 of rainfall but with a different password.

```c
  if (local_14[0] != 0x149c) {
    puts("\nInvalid Password!");
  }
  else {
    puts("\nAuthenticated!");
    system("/bin/sh");

```



> level00@OverRide:~$ ./level00 
> Password:5276
> Authenticated!
> $ whoami
> level01
> $ cat /home/users/level01/.pass
> uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL

```bash
su level01
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```

