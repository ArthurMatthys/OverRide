
undefined8 main(int iParm1,undefined8 *puParm2)

{
	char cVar1;
	int __fd;
	int iVar2;
	FILE *pFVar3;
	FILE *__stream;
	ulong uVar4;
	undefined8 *puVar5;
	long in_FS_OFFSET;
	byte bVar6;
	char local_79;
	undefined8 local_78;
	undefined2 local_70;
	char local_6e;
	long local_10;

	bVar6 = 0;
	local_10 = *(long *)(in_FS_OFFSET + 0x28);
	local_79 = -1;
	if (iParm1 != 2) {
		printf("Usage: %s filename\n",*puParm2,*puParm2);
	}
	pFVar3 = fopen("./backups/.log","w");
	if (pFVar3 == (FILE *)0x0) {
		printf("ERROR: Failed to open %s\n","./backups/.log");
		/* WARNING: Subroutine does not return */
		exit(1);
	}
	log_wrapper(pFVar3,"Starting back up: ",puParm2[1]);
	__stream = fopen((char *)puParm2[1],"r");
	if (__stream == (FILE *)0x0) {
		printf("ERROR: Failed to open %s\n",puParm2[1],puParm2[1]);
		/* WARNING: Subroutine does not return */
		exit(1);
	}
	local_78 = 0x70756b6361622f2e;
	local_70 = 0x2f73;
	local_6e = 0;
	uVar4 = 0xffffffffffffffff;
	puVar5 = &local_78;
	do {
		if (uVar4 == 0) break;
		uVar4 = uVar4 - 1;
		cVar1 = *(char *)puVar5;
		puVar5 = (undefined8 *)((long)puVar5 + (ulong)bVar6 * -2 + 1);
	} while (cVar1 != 0);
	strncat((char *)&local_78,(char *)puParm2[1],99 - (~uVar4 - 1));
	__fd = open((char *)&local_78,0xc1,0x1b0);
	if (__fd < 0) {
		printf("ERROR: Failed to open %s%s\n","./backups/",puParm2[1]);
		/* WARNING: Subroutine does not return */
		exit(1);
	}
	while( true ) {
		iVar2 = fgetc(__stream);
		local_79 = (char)iVar2;
		if (local_79 == -1) break;
		write(__fd,&local_79,1);
	}
	log_wrapper(pFVar3,"Finished back up ",puParm2[1]);
	fclose(__stream);
	close(__fd);
	if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
		/* WARNING: Subroutine does not return */
		__stack_chk_fail();
	}
	return 0;
}


