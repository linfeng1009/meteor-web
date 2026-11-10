0058e430 MOV EAX,ECX
0058e432 PUSH EBX
0058e433 PUSH EBP
0058e434 PUSH ESI
0058e435 LEA EDX,[EAX + 0x48]
0058e438 XOR ECX,ECX
0058e43a MOV ESI,0x3f800000
0058e43f MOV EBX,EDX
0058e441 MOV dword ptr [EAX + 0x14],ECX
0058e444 MOV dword ptr [EAX + 0x18],ECX
0058e447 MOV dword ptr [EAX + 0x1c],ECX
0058e44a MOV dword ptr [EAX + 0x20],ECX
0058e44d MOV byte ptr [EAX + 0x24],CL
0058e450 MOV byte ptr [EAX + 0x25],CL
0058e453 MOV byte ptr [EAX + 0x26],CL
0058e456 MOV dword ptr [EAX + 0x28],0x1
0058e45d MOV dword ptr [EAX + 0x2c],ECX
0058e460 MOV dword ptr [EAX + 0x30],ESI
0058e463 MOV dword ptr [EAX + 0x34],ECX
0058e466 MOV dword ptr [EAX + 0x38],0xb
0058e46d PUSH EDI
0058e46e MOV dword ptr [EAX + 0x50],ESI
0058e471 MOV dword ptr [EAX + 0x4c],ESI
0058e474 MOV dword ptr [EDX],ESI
0058e476 MOV EBP,dword ptr [EBX]
0058e478 LEA EDI,[EAX + 0x54]
0058e47b MOV dword ptr [EAX],0x5b250c
0058e481 MOV dword ptr [EAX + 0x3c],ECX
0058e484 MOV dword ptr [EDI],EBP
0058e486 MOV EBP,dword ptr [EBX + 0x4]
0058e489 MOV dword ptr [EAX + 0x9c],ECX
0058e48f MOV byte ptr [EAX + 0x4],CL
0058e492 MOV EBX,dword ptr [EBX + 0x8]
0058e495 MOV dword ptr [EDI + 0x4],EBP
0058e498 MOV dword ptr [EAX + 0x44],ECX
0058e49b MOV dword ptr [EDI + 0x8],EBX
0058e49e MOV EBX,EDX
0058e4a0 LEA EDI,[EAX + 0x60]
0058e4a3 MOV EBP,dword ptr [EBX]
0058e4a5 MOV dword ptr [EDI],EBP
0058e4a7 MOV EBP,dword ptr [EBX + 0x4]
0058e4aa MOV dword ptr [EDI + 0x4],EBP
0058e4ad MOV EBX,dword ptr [EBX + 0x8]
0058e4b0 MOV dword ptr [EDI + 0x8],EBX
0058e4b3 LEA EDI,[EAX + 0x6c]
0058e4b6 MOV EBX,ESI
0058e4b8 MOV dword ptr [EDI],EBX
0058e4ba MOV EBX,dword ptr [EDX + 0x4]
0058e4bd MOV EDX,dword ptr [EDX + 0x8]
0058e4c0 MOV dword ptr [EDI + 0x4],EBX
0058e4c3 MOV dword ptr [EDI + 0x8],EDX
0058e4c6 MOV dword ptr [EAX + 0x78],ECX
0058e4c9 MOV dword ptr [EAX + 0x7c],ECX
0058e4cc MOV dword ptr [EAX + 0x84],ESI
0058e4d2 MOV dword ptr [EAX + 0x80],ESI
0058e4d8 POP EDI
0058e4d9 MOV EDX,0x1
0058e4de POP ESI
0058e4df POP EBP
0058e4e0 MOV byte ptr [EAX + 0x88],CL
0058e4e6 MOV byte ptr [EAX + 0x8b],CL
0058e4ec MOV byte ptr [EAX + 0x8a],CL
0058e4f2 MOV byte ptr [EAX + 0x89],CL
0058e4f8 MOV byte ptr [EAX + 0x8c],CL
0058e4fe MOV dword ptr [EAX + 0xa0],EDX
0058e504 MOV dword ptr [EAX + 0xa4],ECX
0058e50a MOV dword ptr [EAX + 0x90],ECX
0058e510 MOV dword ptr [EAX + 0x94],ECX
0058e516 MOV dword ptr [EAX + 0x98],EDX
0058e51c MOV dword ptr [EAX + 0x14],ECX
0058e51f MOV dword ptr [EAX + 0x18],ECX
0058e522 MOV byte ptr [EAX + 0x25],CL
0058e525 MOV dword ptr [EAX + 0x40],ECX
0058e528 POP EBX
0058e529 RET
