undefined4 read_number(int param_1)

{
	int iVar1;

	printf(" Index: ");
	iVar1 = get_unum();
	printf(" Number at data[%u] is %u\n",iVar1,*(undefined4 *)(iVar1 * 4 + param_1));
	return 0;
}


undefined4 store_number(int param_1)

{
	uint uVar1;
	uint uVar2;
	undefined4 uVar3;

	printf(" Number: ");
	uVar1 = get_unum();
	printf(" Index: ");
	uVar2 = get_unum();
	if ((uVar2 % 3 == 0) || (uVar1 >> 0x18 == 0xb7)) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		uVar3 = 1;
	}
	else {
		*(uint *)(uVar2 * 4 + param_1) = uVar1;
		uVar3 = 0;
	}
	return uVar3;
}

undefined4 main(undefined4 param_1,char **param_2,char **param_3)

{
	char cVar1;
	int iVar2;
	uint uVar3;
	undefined4 *puVar4;
	char *pcVar5;
	byte *pbVar6;
	int in_GS_OFFSET;
	bool bVar7;
	bool bVar8;
	bool bVar9;
	byte bVar10;
	char **local_1c8;
	char **local_1c4;
	undefined4 local_1bc [100];
	int local_2c;
	undefined4 local_28;
	undefined4 local_24;
	undefined4 local_20;
	undefined4 local_1c;
	undefined4 local_18;
	int local_14;

	bVar10 = 0;
	local_1c4 = param_2;
	local_1c8 = param_3;
	local_14 = *(int *)(in_GS_OFFSET + 0x14);
	local_2c = 0;
	local_28 = 0;
	local_24 = 0;
	local_20 = 0;
	local_1c = 0;
	local_18 = 0;
	iVar2 = 100;
	puVar4 = local_1bc;
	while (iVar2 != 0) {
		iVar2 = iVar2 + -1;
		*puVar4 = 0;
		puVar4 = puVar4 + 1;
	}
	// memset to 0 of argv and env variables
	puts(
			"----------------------------------------------------\n\
			Welcome to wil\'s crappy numberstorage service!   \n\
			----------------------------------------------------\n\ 
			Commands:                                         \n\
			store - store a number into the data storage    \n\
			read  - read a number from the data storage     \n\
			quit  - exit the program                       \n\
			----------------------------------------------------\n\
			wil has reserved some storage :>                 \n\
			----------------------------------------------------\n"
			);
	while true {
		printf("Input command: ");
		local_2c = 1;
		fgets((char *)&buff,0x14,stdin);
		uVar3 = 0xffffffff;
		while (cVar1 != 0);
		{
			if (uVar3 == 0) break;
			uVar3 = uVar3 - 1;
			cVar1 = *(char *)puVar4;
			puVar4 = (undefined4 *)((int)puVar4 + (uint)bVar10 * -2 + 1);
		} 
		uVar3 = ~uVar3;
		bVar7 = uVar3 == 1;
		bVar9 = uVar3 == 2;
		*(undefined *)((int)&local_2c + uVar3 + 2) = 0;
		if (!strcmp(buff, "store")) {
			local_2c = store_number(local_1bc);
		}
		else {
			if (!strcmp(buff, "read")) {
				local_2c = read_number(local_1bc);
			}
			else {
				if (!strcmp(buff, "quit")) {
					if (local_14 == *(int *)(in_GS_OFFSET + 0x14)) {
						return 0;
					}
					/* WARNING: Subroutine does not return */
					__stack_chk_fail();
				}
			}
		}
		if (local_2c == 0) {
			printf(" Completed %s command successfully\n",buff);
		}
		else {
			printf(" Failed to do %s command\n",buff);
		}
		local_28 = 0;
		local_24 = 0;
		local_20 = 0;
		local_1c = 0;
		local_18 = 0;
	}
}


