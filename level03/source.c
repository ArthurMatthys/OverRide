
void clear_stdin(void)

{
  int iVar1;

  do {
    iVar1 = getchar();
    if ((char)iVar1 == '\n') {
      return;
    }
  } while ((char)iVar1 != -1);
  return;
}

/* WARNING: Removing unreachable block (ram,0x08048698) */

int decrypt(EVP_PKEY_CTX *ctx,uchar *out,size_t *outlen,uchar *in,size_t inlen)

{
	char cVar1;
	uint uVar2;
	int iVar3;
	unsigned int *puVar4;
	byte *pbVar5;
	int in_GS_OFFSET;
	bool bVar6;
	bool bVar7;
	uint local_2c;
	unsigned int local_21;
	unsigned int local_1d;
	unsigned int local_19;
	unsigned int local_15;
	undefined local_11;
	int local_10;

	local_10 = *(int *)(in_GS_OFFSET + 0x14);
	local_21 = 0x757c7d51;
	local_1d = 0x67667360;
	local_19 = 0x7b66737e;
	local_15 = 0x33617c7d;
	local_11 = 0;
	uVar2 = 0xffffffff;
	puVar4 = &local_21;
	while (cVar1 != 0)
	{
		if (uVar2 == 0) 
			break;
		uVar2 = uVar2 - 1;
		cVar1 = *(char *)puVar4;
		puVar4 = (undefined4 *)((int)puVar4 + 1);
	}
	local_2c = 0;
	while( true ) {
		bVar6 = local_2c < ~uVar2 - 1;
		bVar7 = local_2c == ~uVar2 - 1;
		if (!bVar6) 
			break;
		*(byte *)((int)&local_21 + local_2c) = (byte)ctx ^ *(byte *)((int)&local_21 + local_2c);
		local_2c = local_2c + 1;
	}
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
	if ((!bVar6 && !bVar7) == bVar6) { // -> We need bVar6 == 0 and bVar7 == 1 
		iVar3 = system("/bin/sh");
	}
	else {
		iVar3 = puts("\nInvalid Password");
	}
	if (local_10 == *(int *)(in_GS_OFFSET + 0x14)) {
		return iVar3;
	}
	/* WARNING: Subroutine does not return */
	__stack_chk_fail();
}




void test(int param_1,int param_2)

{
  EVP_PKEY_CTX *ctx;
  uchar *out;
  size_t *outlen;
  uchar *in;
  size_t inlen;

  ctx = (EVP_PKEY_CTX *)(param_2 - param_1);
  switch(ctx) {
  default:
    ctx = (EVP_PKEY_CTX *)rand();
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x1:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x2:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x3:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x4:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x5:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x6:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x7:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x8:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x9:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x10:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x11:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x12:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x13:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x14:
    decrypt(ctx,out,outlen,in,inlen);
    break;
  case (EVP_PKEY_CTX *)0x15:
    decrypt(ctx,out,outlen,in,inlen);
  }
  return;
}

/* WARNING: Removing unreachable block (ram,0x08048868) */

int main(void)

{
  uint __seed;
  
  __seed = time((time_t *)0x0);
  srand(__seed);
  puts("***********************************");
  puts("*\t\tlevel03\t\t**");
  puts("***********************************");
  printf("Password:");
  __isoc99_scanf();
  test();
  return 0;
}

//return an unsigned int that was scanned
unsigned get_unum(void)

{
  unsigned local_10 [3];
  
  local_10[0] = 0;
  fflush(stdout);
  __isoc99_scanf(&DAT_080489c0,local_10); // -> %u
  clear_stdin();
  return local_10[0];
}


void prog_timeout(void)

{
  code *pcVar1;

  // return carriage is a syscall
  pcVar1 = (code *)swi(0x80);
  (*pcVar1)();
  return;
}
