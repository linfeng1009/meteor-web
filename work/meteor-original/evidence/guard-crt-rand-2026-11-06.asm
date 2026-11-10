            0x0050a8de      e890460000     call 0x50ef73
            0x0050a8e3      8b4814         mov ecx, dword [eax + 0x14]
            0x0050a8e6      69c9fd430300   imul ecx, ecx, 0x343fd
            0x0050a8ec      81c1c39e2600   add ecx, 0x269ec3
            0x0050a8f2      894814         mov dword [eax + 0x14], ecx
            0x0050a8f5      8bc1           mov eax, ecx
            0x0050a8f7      c1e810         shr eax, 0x10
            0x0050a8fa      25ff7f0000     and eax, 0x7fff
            0x0050a8ff      c3             ret
