//
// This file was generated by the Retargetable Decompiler
// Website: https://retdec.com
// Copyright (c) Retargetable Decompiler <info@retdec.com>
//

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ------------------------ Structures ------------------------

struct _IO_FILE {
    int32_t e0;
};

// ------------------- Function Prototypes --------------------

int64_t __do_global_ctors_aux(void);
int64_t __do_global_dtors_aux(void);
int64_t __libc_csu_fini(void);
int64_t __libc_csu_init(int64_t a1, int64_t a2, int64_t a3);
int64_t _fini(void);
int64_t _init(void);
int64_t _start(int64_t a1, int64_t a2, int64_t a3, int64_t a4);
int64_t call_gmon_start(void);
int64_t frame_dummy(void);
char * function_720(char * dest, char * src, int32_t n);
int32_t function_730(char * s);
int32_t function_740(char * command);
int32_t function_750(char * format, ...);
int32_t function_760(int64_t main2, int32_t argc, char ** ubp_av, void (*init)(), void (*fini)(), void (*rtld_fini)());
char * function_770(char * s, int32_t n, struct _IO_FILE * stream);
int64_t function_780(int64_t a1);
int64_t handle_msg(void);
int64_t secret_backdoor(void);
int64_t set_msg(int64_t * str2);
int64_t set_username(int64_t * a1);

// --------------------- Global Variables ---------------------

int64_t g1 = -1; // 0x201df8
int64_t g2 = -1; // 0x201e08
int64_t g3 = 0; // 0x201e10
int64_t g4 = 0; // 0x201e18
void (*g5)() = (void (*)())2912; // 0x201fb0
int64_t g6 = 0; // 0x201fb8
int64_t g7 = 0; // 0x201fc0
void (*g8)() = (void (*)())2768; // 0x201fc8
int64_t g9 = 2728; // 0x201fd0
int64_t g10 = 0; // 0x201fd8
int64_t g11 = 0; // 0x201fe0
char g12 = 0; // 0x202060
int64_t g13 = 0; // 0x202068
int32_t g14 = 0x202048; // 0x400
int32_t g15;

// ------------------------ Functions -------------------------

// Address range: 0x6f0 - 0x708
int64_t _init(void) {
    // 0x6f0
    call_gmon_start();
    frame_dummy();
    return __do_global_ctors_aux();
}

// Address range: 0x720 - 0x726
char * function_720(char * dest, char * src, int32_t n) {
    // 0x720
    return strncpy(dest, src, n);
}

// Address range: 0x730 - 0x736
int32_t function_730(char * s) {
    // 0x730
    return puts(s);
}

// Address range: 0x740 - 0x746
int32_t function_740(char * command) {
    // 0x740
    return system(command);
}

// Address range: 0x750 - 0x756
int32_t function_750(char * format, ...) {
    // 0x750
    return printf(format);
}

// Address range: 0x760 - 0x766
int32_t function_760(int64_t main2, int32_t argc, char ** ubp_av, void (*init)(), void (*fini)(), void (*rtld_fini)()) {
    // 0x760
    return __libc_start_main(main2, argc, ubp_av, init, fini, rtld_fini);
}

// Address range: 0x770 - 0x776
char * function_770(char * s, int32_t n, struct _IO_FILE * stream) {
    // 0x770
    return fgets(s, n, stream);
}

// Address range: 0x780 - 0x786
int64_t function_780(int64_t a1) {
    // 0x780
    return __cxa_finalize();
}

// Address range: 0x790 - 0x7ba
int64_t _start(int64_t a1, int64_t a2, int64_t a3, int64_t a4) {
    // 0x790
    int64_t v1; // 0x790
    __libc_start_main(g9, (int32_t)a4, (char **)&v1, g8, g5, (void (*)())a3);
    __asm_hlt();
    // UNREACHABLE
}

// Address range: 0x7bc - 0x7d3
int64_t call_gmon_start(void) {
    int64_t result = 0; // 0x7ca
    if (g7 != 0) {
        // 0x7cc
        __gmon_start__();
        result = &g15;
    }
    // 0x7ce
    return result;
}

// Address range: 0x7e0 - 0x857
int64_t __do_global_dtors_aux(void) {
    // 0x7e0
    if (g12 != 0) {
        // 0x852
        int64_t result; // 0x7e0
        return result;
    }
    // 0x7f0
    if (g11 != 0) {
        // 0x7fa
        function_780(*(int64_t *)0x202040);
    }
    int64_t result2 = g13; // 0x829
    if (g13 < ((int64_t)&g3 - (int64_t)&g2 >> 3) - 1) {
        uint64_t v1 = g13 + 1;
        result2 = v1 > ((int64_t)&g3 - (int64_t)&g2 >> 3) - 1 ? v1 : ((int64_t)&g3 - (int64_t)&g2 >> 3) - 1;
        g13 = result2;
    }
    // 0x84b
    g12 = 1;
    // 0x852
    return result2;
}

// Address range: 0x860 - 0x88a
int64_t frame_dummy(void) {
    // 0x860
    if (g4 == 0) {
        // 0x888
        int64_t result; // 0x860
        return result;
    }
    // 0x86e
    if (g10 == 0) {
        // 0x888
        return 0;
    }
    // 0x87a
    return _Jv_RegisterClasses(&g4);
}

// Address range: 0x88c - 0x8c0
int64_t secret_backdoor(void) {
    // 0x88c
    int64_t str; // bp-136, 0x88c
    fgets((char *)&str, 128, (struct _IO_FILE *)*(int64_t *)g6);
    return system((char *)&str);
}

// Address range: 0x8c0 - 0x932
int64_t handle_msg(void) {
    // 0x8c0
    int64_t v1; // bp-200, 0x8c0
    set_username(&v1);
    set_msg(&v1);
    return puts(">: Msg sent!");
}

// Address range: 0x932 - 0x9cd
int64_t set_msg(int64_t * str2) {
    // 0x932
    int64_t str; // bp-1032, 0x932
    __asm_rep_stosq_memset((char *)&str, 0, 128);
    puts(">: Msg @Unix-Dude");
    printf(">>: ");
    int64_t stream = *(int64_t *)g6; // 0x988
    fgets((char *)&str, (int32_t)&g14, (struct _IO_FILE *)stream);
    int32_t n = *(int32_t *)((int64_t)str2 + 180); // 0x9a9
    return (int64_t)strncpy((char *)str2, (char *)&str, n);
}

// Address range: 0x9cd - 0xaa8
int64_t set_username(int64_t * a1) {
    // 0x9cd
    int64_t str; // bp-152, 0x9cd
    __asm_rep_stosq_memset((char *)&str, 0, 16);
    puts(">: Enter your username");
    printf(">>: ");
    fgets((char *)&str, 128, (struct _IO_FILE *)*(int64_t *)g6);
    int64_t v1 = (int64_t)a1 + 140;
    int32_t v2 = 0;
    int64_t v3 = v2; // 0xa73
    int64_t v4; // bp-8, 0x9cd
    char v5 = *(char *)((int64_t)&v4 - 144 + v3); // 0xa75
    while (v5 != 0) {
        // 0xa46
        *(char *)(v1 + v3) = v5;
        if (v2 > 39) {
            // break -> 0xa81
            break;
        }
        v2++;
        v3 = v2;
        v5 = *(char *)((int64_t)&v4 - 144 + v3);
    }
    // 0xa81
    return printf(">: Welcome, %s", (char *)v1);
}

// Address range: 0xaa8 - 0xac4
int main(int argc, char ** argv) {
    // 0xaa8
    puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n--------------------------------------------");
    handle_msg();
    return 0;
}

// Address range: 0xad0 - 0xb59
int64_t __libc_csu_init(int64_t a1, int64_t a2, int64_t a3) {
    // 0xad0
    return _init();
}

// Address range: 0xb60 - 0xb62
int64_t __libc_csu_fini(void) {
    // 0xb60
    int64_t result; // 0xb60
    return result;
}

// Address range: 0xb70 - 0xba6
int64_t __do_global_ctors_aux(void) {
    // 0xb70
    if (g1 == -1) {
        // 0xb9f
        return -1;
    }
    int64_t v1 = &g1; // 0xb84
    v1 -= 8;
    int64_t result = *(int64_t *)v1; // 0xb96
    while (result != -1) {
        // 0xb90
        v1 -= 8;
        result = *(int64_t *)v1;
    }
    // 0xb9f
    return result;
}

// Address range: 0xba8 - 0xbb6
int64_t _fini(void) {
    // 0xba8
    return __do_global_dtors_aux();
}

// --------------- Dynamically Linked Functions ---------------

// int64_t __cxa_finalize(void);
// void __gmon_start__(void);
// int __libc_start_main(int *(main)(int, char **, char **), int argc, char ** ubp_av, void(* init)(void), void(* fini)(void), void(* rtld_fini)(void), void(* stack_end));
// int64_t _Jv_RegisterClasses(int64_t * a1);
// char * fgets(char * restrict s, int n, FILE * restrict stream);
// int printf(const char * restrict format, ...);
// int puts(const char * s);
// char * strncpy(char * restrict dest, const char * restrict src, size_t n);
// int system(const char * command);

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (4.6.3)
// Detected functions: 21
