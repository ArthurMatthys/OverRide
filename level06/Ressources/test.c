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


	pop = auth(arv[1], 0);
	return (1);
}
