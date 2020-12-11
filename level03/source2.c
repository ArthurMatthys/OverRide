/* r2dec pseudo code output */
/* /Users/home/Downloads/level03 @ 0x80486b2 */
#include <stdint.h>
 
void decrypt (int32_t arg_8h) {
    int32_t var_2ch;
    int32_t var_28h;
    uint32_t var_24h;
    int32_t var_1dh;
    int32_t var_19h;
    int32_t var_15h;
    int32_t var_11h;
    int32_t var_dh;
    int32_t canary;
    eax = *(gs:0x14);
    canary = *(gs:0x14);
    eax = 0;
    var_1dh = 0x757c7d51;
    var_19h = 0x67667360;
    var_15h = 0x7b66737e;
    var_11h = 0x33617c7d;
    var_dh = 0;
    eax = 0;
    if (? != ?) {
    }
    eax = &var_1dh;
    var_2ch = 0xffffffff;
    edx = eax;
    eax = 0;
    ecx = var_2ch;
    edi = edx;
    __asm ("repne scasb al, byte es:[edi]");
    eax = ecx;
    eax = ~eax;
    eax--;
    var_24h = eax;
    var_28h = 0;
    while (eax < var_24h) {
        eax = &var_1dh;
        eax += var_28h;
        eax = *(eax);
        edx = eax;
        eax = arg_8h;
        eax ^= edx;
        edx = eax;
        eax = &var_1dh;
        eax += var_28h;
        *(eax) = dl;
        var_28h++;
        eax = var_28h;
    }
    eax = &var_1dh;
    edx = eax;
    eax = "Congratulations!";
    ecx = 0x11;
    esi = edx;
    edi = eax;
    __asm ("repe cmpsb byte [esi], byte ptr es:[edi]");
    dl = (eax > var_24h) ? 1 : 0;
    al = (eax < var_24h) ? 1 : 0;
    ecx = edx;
    cl -= al;
    eax = ecx;
    eax = (int32_t) al;
    if (eax == 0) {
        system ("/bin/sh");
    } else {
        puts ("\nInvalid Password");
    }
    esi = canary;
    esi ^= *(gs:0x14);
    if (eax != 0) {
        stack_chk_fail ();
    }
}




/* r2dec pseudo code output */
/* /Users/home/Downloads/level03 @ 0x8048747 */
#include <stdint.h>
 
int32_t test (int32_t arg_8h, int32_t arg_ch) {
    uint32_t var_ch;
    eax = arg_8h;
    edx = arg_ch;
    ecx = arg_ch;
    ecx -= eax;
    eax = ecx;
    var_ch = ecx;
    if (var_ch <= 0x15) {
        eax = var_ch;
        eax <<= 2;
        eax += 0x80489f0;
        eax = *(eax);
        void (*eax)() ();
    }
    eax = rand ();
    decrypt (eax);
    return eax;
}


/* r2dec pseudo code output */
/* /Users/home/Downloads/level03 @ 0x804885a */
#include <stdint.h>
 
int32_t main (void) {
    int32_t var_4h;
    int32_t var_4h_2;
    int32_t var_1ch;
    int32_t var_1ch_2;
    eax = 0;
    if (? != ?) {
    }
    eax = time (0);
    srand (eax);
    puts (0x8048a48);
    puts ("*\t\tlevel03\t\t**");
    puts (0x8048a48);
    eax = "Password:";
    printf (eax);
    eax = 0x8048a85;
    edx = &var_1ch;
    isoc99_scanf (eax, edx);
    eax = var_1ch;
    test (eax, 0x1337d00d);
    eax = 0;
}

