0058e150 MOV EAX,ECX
0058e152 MOV EDX,0x3f800000
0058e157 MOV dword ptr [EAX],0x5b24f8
0058e15d MOV ECX,dword ptr [0x0072c180]
0058e163 INC ECX
0058e164 MOV dword ptr [0x0072c180],ECX
0058e16a MOV ECX,0x40a00000
0058e16f MOV dword ptr [EAX + 0x60],ECX
0058e172 MOV dword ptr [EAX + 0x64],ECX
0058e175 MOV ECX,0xbf800000
0058e17a MOV dword ptr [EAX + 0x4],0xffffffff
0058e181 MOV dword ptr [EAX + 0xc],ECX
0058e184 MOV dword ptr [EAX + 0x8],ECX
0058e187 XOR ECX,ECX
0058e189 MOV dword ptr [EAX + 0x10],ECX
0058e18c MOV dword ptr [EAX + 0x18],ECX
0058e18f MOV dword ptr [EAX + 0x1c],ECX
0058e192 MOV dword ptr [EAX + 0x20],ECX
0058e195 MOV dword ptr [EAX + 0x2c],ECX
0058e198 MOV dword ptr [EAX + 0x28],ECX
0058e19b MOV dword ptr [EAX + 0x24],ECX
0058e19e MOV dword ptr [EAX + 0x30],ECX
0058e1a1 MOV dword ptr [EAX + 0x34],ECX
0058e1a4 MOV dword ptr [EAX + 0x38],ECX
0058e1a7 MOV dword ptr [EAX + 0x3c],EDX
0058e1aa MOV dword ptr [EAX + 0x48],EDX
0058e1ad MOV dword ptr [EAX + 0x44],EDX
0058e1b0 MOV dword ptr [EAX + 0x40],EDX
0058e1b3 MOV EDX,dword ptr [ESP + 0x4]
0058e1b7 CMP EDX,ECX
0058e1b9 MOV dword ptr [EAX + 0x14],EDX
0058e1bc JZ 0x0058e1ee
0058e1be MOV ECX,dword ptr [EDX + 0x1ec]
0058e1c4 MOV EDX,dword ptr [ECX + 0x80]
0058e1ca ADD ECX,0x38
0058e1cd MOV dword ptr [EAX + 0x4c],EDX
0058e1d0 MOV EDX,dword ptr [ECX + 0x4c]
0058e1d3 MOV dword ptr [EAX + 0x50],EDX
0058e1d6 MOV EDX,dword ptr [ECX + 0x50]
0058e1d9 MOV dword ptr [EAX + 0x54],EDX
0058e1dc MOV EDX,dword ptr [ECX + 0x80]
0058e1e2 MOV dword ptr [EAX + 0x58],EDX
0058e1e5 MOV ECX,dword ptr [ECX + 0x84]
0058e1eb MOV dword ptr [EAX + 0x5c],ECX
0058e1ee RET 0x4
