
/* WARNING: Removing unreachable block (ram,0x08048782) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

//scan_int = 0 if we didn't give an int in serial and 1 otherwise

int auth(char *login, int scan_int)

{
	size_t sVar1;
	undefined4 uVar2;
	long lVar3;
	int local_18;
	uint local_14;

	sVar1 = strcspn(login,"\n");
	login[sVar1] = 0;
	sVar1 = strnlen(login,0x20);
	if ((int)sVar1 < 6) {
		uVar2 = 1;
	}
	else {
		lVar3 = ptrace(PTRACE_TRACEME);
		if (lVar3 == -1) {
			puts("\x1b[32m.---------------------------.");
			puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
			puts("\x1b[32m\'---------------------------\'");
			uVar2 = 1;
		}
		else {
			local_14 = ((int)login[3] ^ 0x1337U) + 0x5eeded;
			local_18 = 0;
			while (local_18 < (int)sVar1) {
				if (login[local_18] < ' ') {
					return 1;
				}
				local_14 = local_14 + ((int)login[local_18] ^ local_14) % 0x539;
				local_18 = local_18 + 1;
			}
			if (scan_int == local_14) {
				uVar2 = 0;
			}
			else {
				uVar2 = 1;
			}
		}
	}
	return uVar2;
}
/* WARNING: Removing unreachable block (ram,0x0804889a) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

uint main(void)

{
	int iVar1;
	int in_GS_OFFSET;
	char local_34 [32];
	int local_14;

	local_14 = *(int *)(in_GS_OFFSET + 0x14);
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(local_34,0x20,stdin);
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	__isoc99_scanf();
	iVar1 = auth();
	if (iVar1 == 0) {
		puts("Authenticated!");
		system("/bin/sh");
	}
	if (local_14 != *(int *)(in_GS_OFFSET + 0x14)) {
		/* WARNING: Subroutine does not return */
		__stack_chk_fail();
	}
	return (uint)(iVar1 != 0);
}


