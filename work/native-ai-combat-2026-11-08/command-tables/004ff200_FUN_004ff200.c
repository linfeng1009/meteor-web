/* Original Meteor.exe static export @ 004ff200; original sample not executed. */
/* XREF 004bf931 UNCONDITIONAL_CALL */

/* WARNING: Removing unreachable block (ram,0x00500549) */
/* WARNING: Removing unreachable block (ram,0x0050054b) */
/* WARNING: Removing unreachable block (ram,0x00500556) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ff200(void)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 local_64;
  undefined **local_60 [10];
  undefined **local_38 [6];
  undefined **local_20 [8];
  
  if (DAT_00666ca0 == '\0') {
    DAT_00666ca0 = '\x01';
    _DAT_00666a00 = 0;
    _DAT_00666a04 = 0x42700000;
    _DAT_00666a34 = 0;
    _DAT_00666a08 = 0x42200000;
    _DAT_00666a0c = 0x41f00000;
    _DAT_00666a38 = 0;
    _DAT_00666a3c = 0x42700000;
    _DAT_00666a6c = 0;
    _DAT_00666a40 = 0x42200000;
    _DAT_00666a44 = 0x41f00000;
    _DAT_00666a70 = 0x42c80000;
    _DAT_00666a74 = 0x44fa0000;
    _DAT_00666aa4 = 1;
    _DAT_00666a78 = 0x41f00000;
    _DAT_00666a7c = 0x41a00000;
    _DAT_00666aa8 = 0x42a00000;
    _DAT_00666aac = 0x447a0000;
    _DAT_00666adc = 1;
    _DAT_00666ab0 = 0x42480000;
    _DAT_00666ab4 = 0x41a00000;
    _DAT_00666ae0 = 0;
    _DAT_00666ae4 = 0x42700000;
    _DAT_00666b14 = 0;
    _DAT_00666ae8 = 0x42200000;
    _DAT_00666aec = 0x42700000;
    _DAT_00666b18 = 0;
    _DAT_00666b1c = 0x42700000;
    _DAT_00666b4c = 0;
    _DAT_00666b20 = 0x42200000;
    _DAT_00666b24 = 0x42700000;
    _DAT_00666b50 = 0x42a00000;
    _DAT_00666b54 = 0x43960000;
    _DAT_00666b84 = 1;
    _DAT_00666b58 = 0x42200000;
    _DAT_00666b5c = 0x41a00000;
    _DAT_00666b88 = 0;
    _DAT_00666b8c = 0x42700000;
    _DAT_00666bbc = 0;
    _DAT_00666b90 = 0x42200000;
    _DAT_00666b94 = 0x42480000;
    _DAT_00666bc0 = 0;
    _DAT_00666bc4 = 0x42700000;
    _DAT_00666bf4 = 0;
    _DAT_00666bc8 = 0x42200000;
    _DAT_00666bcc = 0x42480000;
    _DAT_00666bf8 = 0;
    _DAT_00666bfc = 0x42820000;
    _DAT_00666c2c = 0;
    _DAT_00666c00 = 0x42200000;
    _DAT_00666c04 = 0x42480000;
    _DAT_00666c30 = 0;
    _DAT_00666c34 = 0x425c0000;
    _DAT_00666c64 = 0;
    _DAT_00666c38 = 0x42200000;
    _DAT_00666c3c = 0x42480000;
    _DAT_00666c68 = 0;
    _DAT_00666c6c = 0x42700000;
    _DAT_00666c9c = 0;
    _DAT_00666c70 = 0x42200000;
    _DAT_00666c74 = 0x42480000;
    local_60[3] = (undefined **)&DAT_005c67e4;
    local_60[4] = (undefined **)&DAT_005ca230;
    local_60[5] = (undefined **)&DAT_005c67e8;
    local_60[6] = (undefined **)&DAT_005c67d0;
    local_20[0] = (undefined **)&DAT_005ca23c;
    local_20[1] = (undefined **)&DAT_005ca238;
    local_20[2] = (undefined **)&DAT_005ca22c;
    local_20[3] = (undefined **)&DAT_005ca228;
    local_20[4] = &PTR_DAT_005ca224;
    local_20[5] = (undefined **)&DAT_005ca220;
    local_20[6] = (undefined **)&DAT_005ca234;
    local_20[7] = &PTR_DAT_005ca21c;
    local_64 = 0;
    uVar2 = DAT_00666a14 - (int)DAT_00666a10 >> 2;
    if (uVar2 < 2) {
      FUN_005005c0(DAT_00666a14,1 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a10 + 1,DAT_00666a14);
    }
    local_64 = 0;
    *DAT_00666a10 = &DAT_005d5a24;
    uVar2 = DAT_00666a20 - DAT_00666a1c >> 2;
    if (uVar2 < 5) {
      FUN_005005c0(DAT_00666a20,4 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a1c + 0x10,DAT_00666a20);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666a1c) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x10);
    local_64 = 0;
    uVar2 = DAT_00666a2c - DAT_00666a28 >> 2;
    if (uVar2 < 9) {
      FUN_005005c0(DAT_00666a2c,8 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a28 + 0x20,DAT_00666a2c);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666a28) = *(undefined4 *)((int)local_20 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x20);
    local_60[0] = (undefined **)&DAT_005d5a24;
    local_60[1] = (undefined **)&DAT_005c67e4;
    uVar2 = DAT_00666a4c - DAT_00666a48 >> 2;
    local_60[3] = (undefined **)&DAT_005ca228;
    local_60[4] = (undefined **)&DAT_005c67e8;
    local_60[5] = (undefined **)&DAT_005c67d0;
    local_38[0] = (undefined **)&DAT_005ca230;
    local_38[1] = (undefined **)&DAT_005ca238;
    local_38[2] = (undefined **)&DAT_005ca23c;
    local_38[3] = &PTR_DAT_005ca224;
    local_64 = 0;
    if (uVar2 < 3) {
      FUN_005005c0(DAT_00666a4c,2 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a48 + 8,DAT_00666a4c);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666a48) = *(undefined4 *)((int)local_60 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 8);
    local_64 = 0;
    uVar2 = DAT_00666a58 - DAT_00666a54 >> 2;
    if (uVar2 < 4) {
      FUN_005005c0(DAT_00666a58,3 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a54 + 0xc,DAT_00666a58);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666a54) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0xc);
    local_64 = 0;
    uVar2 = DAT_00666a64 - DAT_00666a60 >> 2;
    if (uVar2 < 5) {
      FUN_005005c0(DAT_00666a64,4 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a60 + 0x10,DAT_00666a64);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666a60) = *(undefined4 *)((int)local_38 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x10);
    local_60[0] = (undefined **)&DAT_005c67e4;
    uVar2 = DAT_00666a84 - (int)DAT_00666a80 >> 2;
    local_60[1] = (undefined **)&DAT_005ca230;
    local_60[3] = (undefined **)&DAT_005ca238;
    local_60[4] = &PTR_DAT_005ca224;
    local_64 = 0;
    if (uVar2 < 2) {
      FUN_005005c0(DAT_00666a84,1 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a80 + 1,DAT_00666a84);
    }
    local_64 = 0;
    *DAT_00666a80 = &DAT_005d5a24;
    uVar2 = DAT_00666a90 - DAT_00666a8c >> 2;
    if (uVar2 < 3) {
      FUN_005005c0(DAT_00666a90,2 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a8c + 8,DAT_00666a90);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666a8c) = *(undefined4 *)((int)local_60 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 8);
    local_64 = 0;
    uVar2 = DAT_00666a9c - DAT_00666a98 >> 2;
    if (uVar2 < 3) {
      FUN_005005c0(DAT_00666a9c,2 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666a98 + 8,DAT_00666a9c);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666a98) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 8);
    local_60[3] = (undefined **)&DAT_005c67e4;
    local_60[4] = (undefined **)&DAT_005ca230;
    uVar2 = DAT_00666abc - (int)DAT_00666ab8 >> 2;
    local_60[0] = (undefined **)&DAT_005ca238;
    local_60[1] = &PTR_DAT_005ca224;
    local_64 = 0;
    if (uVar2 < 2) {
      FUN_005005c0(DAT_00666abc,1 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666ab8 + 1,DAT_00666abc);
    }
    local_64 = 0;
    *DAT_00666ab8 = &DAT_005d5a24;
    uVar2 = DAT_00666ac8 - DAT_00666ac4 >> 2;
    if (uVar2 < 3) {
      FUN_005005c0(DAT_00666ac8,2 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666ac4 + 8,DAT_00666ac8);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666ac4) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 8);
    local_64 = 0;
    uVar2 = DAT_00666ad4 - DAT_00666ad0 >> 2;
    if (uVar2 < 3) {
      FUN_005005c0(DAT_00666ad4,2 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666ad0 + 8,DAT_00666ad4);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666ad0) = *(undefined4 *)((int)local_60 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 8);
    local_38[1] = (undefined **)&DAT_005ca234;
    uVar2 = DAT_00666af4 - DAT_00666af0 >> 2;
    local_60[3] = (undefined **)&DAT_005d5a24;
    local_60[4] = (undefined **)&DAT_005c67e4;
    local_60[5] = (undefined **)&DAT_005ca230;
    local_60[0] = (undefined **)&DAT_005ca238;
    local_60[1] = (undefined **)&DAT_005ca228;
    local_60[2] = (undefined **)&DAT_005ca23c;
    local_38[0] = (undefined **)&DAT_005ca220;
    local_38[2] = &PTR_DAT_005ca218;
    local_38[3] = &PTR_DAT_005ca21c;
    local_38[4] = &PTR_DAT_005ca224;
    local_38[5] = &PTR_DAT_005ca214;
    local_64 = 0;
    if (uVar2 < 4) {
      FUN_005005c0(DAT_00666af4,3 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666af0 + 0xc,DAT_00666af4);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666af0) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0xc);
    local_64 = 0;
    uVar2 = DAT_00666b00 - DAT_00666afc >> 2;
    if (uVar2 < 4) {
      FUN_005005c0(DAT_00666b00,3 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666afc + 0xc,DAT_00666b00);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666afc) = *(undefined4 *)((int)local_60 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0xc);
    local_64 = 0;
    uVar2 = DAT_00666b0c - DAT_00666b08 >> 2;
    if (uVar2 < 7) {
      FUN_005005c0(DAT_00666b0c,6 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666b08 + 0x18,DAT_00666b0c);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666b08) = *(undefined4 *)((int)local_38 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x18);
    local_38[0] = (undefined **)&DAT_005c67e4;
    local_38[1] = (undefined **)&DAT_005ca230;
    uVar2 = DAT_00666b2c - (int)DAT_00666b28 >> 2;
    local_38[2] = (undefined **)&DAT_005c67e8;
    local_38[3] = (undefined **)&DAT_005c67d0;
    local_60[3] = (undefined **)&DAT_005ca228;
    local_60[4] = (undefined **)&DAT_005ca238;
    local_60[5] = (undefined **)&DAT_005ca23c;
    local_60[6] = (undefined **)&DAT_005ca220;
    local_60[7] = &PTR_DAT_005ca21c;
    local_60[8] = &PTR_DAT_005ca214;
    local_60[9] = &PTR_DAT_005ca218;
    local_64 = 0;
    if (uVar2 < 2) {
      FUN_005005c0(DAT_00666b2c,1 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666b28 + 1,DAT_00666b2c);
    }
    local_64 = 0;
    *DAT_00666b28 = &DAT_005d5a24;
    uVar2 = DAT_00666b38 - DAT_00666b34 >> 2;
    if (uVar2 < 5) {
      FUN_005005c0(DAT_00666b38,4 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666b34 + 0x10,DAT_00666b38);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666b34) = *(undefined4 *)((int)local_38 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x10);
    local_64 = 0;
    uVar2 = DAT_00666b44 - DAT_00666b40 >> 2;
    if (uVar2 < 8) {
      FUN_005005c0(DAT_00666b44,7 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666b40 + 0x1c,DAT_00666b44);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666b40) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x1c);
    local_60[3] = (undefined **)&DAT_005c67e4;
    local_60[4] = (undefined **)&DAT_005ca230;
    uVar2 = DAT_00666b64 - (int)DAT_00666b60 >> 2;
    local_60[0] = (undefined **)&DAT_005ca238;
    local_60[1] = &PTR_DAT_005ca224;
    local_64 = 0;
    if (uVar2 < 2) {
      FUN_005005c0(DAT_00666b64,1 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666b60 + 1,DAT_00666b64);
    }
    local_64 = 0;
    *DAT_00666b60 = &DAT_005d5a24;
    uVar2 = DAT_00666b70 - DAT_00666b6c >> 2;
    if (uVar2 < 3) {
      FUN_005005c0(DAT_00666b70,2 - uVar2,&local_64);
    }
    else {
      FUN_004fe330(DAT_00666b6c + 8,DAT_00666b70);
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666b6c) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar4 = DAT_00666b7c;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 8);
    local_64 = 0;
    uVar2 = DAT_00666b7c - DAT_00666b78 >> 2;
    if (uVar2 < 3) {
      FUN_005005c0(DAT_00666b7c,2 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666b78 + 8;
      FUN_004a8b00(DAT_00666b7c,DAT_00666b7c,iVar3);
      DAT_00666b7c = DAT_00666b7c + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666b78) = *(undefined4 *)((int)local_60 + iVar3);
      iVar4 = DAT_00666b9c;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 8);
    local_38[0] = (undefined **)&DAT_005ca230;
    local_38[1] = (undefined **)&DAT_005c67e4;
    uVar2 = DAT_00666b9c - (int)DAT_00666b98 >> 2;
    local_38[2] = (undefined **)&DAT_005ca234;
    local_38[3] = (undefined **)&DAT_005ca23c;
    local_20[0] = (undefined **)&DAT_005ca238;
    local_20[1] = (undefined **)&DAT_005ca228;
    local_20[2] = (undefined **)&DAT_005ca220;
    local_20[3] = &PTR_DAT_005ca214;
    local_20[4] = &PTR_DAT_005ca21c;
    local_20[5] = &PTR_DAT_005ca210;
    local_20[6] = &PTR_DAT_005ca218;
    local_20[7] = &PTR_DAT_005ca224;
    local_64 = 0;
    if (uVar2 < 2) {
      FUN_005005c0(DAT_00666b9c,1 - uVar2,&local_64);
    }
    else {
      puVar1 = DAT_00666b98 + 1;
      FUN_004a8b00(DAT_00666b9c,DAT_00666b9c,puVar1);
      DAT_00666b9c = DAT_00666b9c + (iVar4 - (int)puVar1 >> 2) * -4;
    }
    local_64 = 0;
    *DAT_00666b98 = &DAT_005d5a24;
    iVar3 = DAT_00666ba8;
    uVar2 = DAT_00666ba8 - DAT_00666ba4 >> 2;
    if (uVar2 < 5) {
      FUN_005005c0(DAT_00666ba8,4 - uVar2,&local_64);
    }
    else {
      iVar4 = DAT_00666ba4 + 0x10;
      FUN_004a8b00(DAT_00666ba8,DAT_00666ba8,iVar4);
      DAT_00666ba8 = DAT_00666ba8 + (iVar3 - iVar4 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666ba4) = *(undefined4 *)((int)local_38 + iVar3);
      iVar4 = DAT_00666bb4;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x10);
    local_64 = 0;
    uVar2 = DAT_00666bb4 - DAT_00666bb0 >> 2;
    if (uVar2 < 9) {
      FUN_005005c0(DAT_00666bb4,8 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666bb0 + 0x20;
      FUN_004a8b00(DAT_00666bb4,DAT_00666bb4,iVar3);
      DAT_00666bb4 = DAT_00666bb4 + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666bb0) = *(undefined4 *)((int)local_20 + iVar3);
      iVar4 = DAT_00666bd4;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x20);
    local_60[3] = (undefined **)&DAT_005d5a24;
    local_60[4] = (undefined **)&DAT_005c67e4;
    uVar2 = DAT_00666bd4 - DAT_00666bd0 >> 2;
    local_60[0] = (undefined **)&DAT_005c67d0;
    local_60[1] = (undefined **)&DAT_005c67e8;
    local_60[2] = (undefined **)&DAT_005ca220;
    local_38[0] = (undefined **)&DAT_005ca238;
    local_38[1] = (undefined **)&DAT_005ca230;
    local_38[2] = (undefined **)&DAT_005ca228;
    local_38[3] = &PTR_DAT_005ca214;
    local_38[4] = &PTR_DAT_005ca21c;
    local_38[5] = &PTR_DAT_005ca20c;
    local_64 = 0;
    if (uVar2 < 3) {
      FUN_005005c0(DAT_00666bd4,2 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666bd0 + 8;
      FUN_004a8b00(DAT_00666bd4,DAT_00666bd4,iVar3);
      DAT_00666bd4 = DAT_00666bd4 + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666bd0) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar4 = DAT_00666be0;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 8);
    local_64 = 0;
    uVar2 = DAT_00666be0 - DAT_00666bdc >> 2;
    if (uVar2 < 4) {
      FUN_005005c0(DAT_00666be0,3 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666bdc + 0xc;
      FUN_004a8b00(DAT_00666be0,DAT_00666be0,iVar3);
      DAT_00666be0 = DAT_00666be0 + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666bdc) = *(undefined4 *)((int)local_60 + iVar3);
      iVar4 = DAT_00666bec;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0xc);
    local_64 = 0;
    uVar2 = DAT_00666bec - DAT_00666be8 >> 2;
    if (uVar2 < 7) {
      FUN_005005c0(DAT_00666bec,6 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666be8 + 0x18;
      FUN_004a8b00(DAT_00666bec,DAT_00666bec,iVar3);
      DAT_00666bec = DAT_00666bec + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666be8) = *(undefined4 *)((int)local_38 + iVar3);
      iVar4 = DAT_00666c0c;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x18);
    local_20[5] = (undefined **)&DAT_005ca23c;
    local_20[6] = (undefined **)&DAT_005ca228;
    local_38[0] = (undefined **)&DAT_005ca228;
    local_38[1] = (undefined **)&DAT_005ca23c;
    local_20[0] = (undefined **)&DAT_005d5a24;
    local_20[1] = (undefined **)&DAT_005c67e4;
    uVar2 = DAT_00666c0c - DAT_00666c08 >> 2;
    local_20[2] = (undefined **)&DAT_005ca230;
    local_20[3] = (undefined **)&DAT_005c67e8;
    local_20[4] = (undefined **)&DAT_005c67d0;
    local_38[2] = &PTR_DAT_005ca21c;
    local_38[3] = &PTR_DAT_005ca218;
    local_60[3] = (undefined **)&DAT_005ca238;
    local_60[4] = (undefined **)&DAT_005ca22c;
    local_60[5] = &PTR_DAT_005ca214;
    local_64 = 0;
    if (uVar2 < 8) {
      FUN_005005c0(DAT_00666c0c,7 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666c08 + 0x1c;
      FUN_004a8b00(DAT_00666c0c,DAT_00666c0c,iVar3);
      DAT_00666c0c = DAT_00666c0c + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666c08) = *(undefined4 *)((int)local_20 + iVar3);
      iVar4 = DAT_00666c18;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x1c);
    local_64 = 0;
    uVar2 = DAT_00666c18 - DAT_00666c14 >> 2;
    if (uVar2 < 5) {
      FUN_005005c0(DAT_00666c18,4 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666c14 + 0x10;
      FUN_004a8b00(DAT_00666c18,DAT_00666c18,iVar3);
      DAT_00666c18 = DAT_00666c18 + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666c14) = *(undefined4 *)((int)local_38 + iVar3);
      iVar4 = DAT_00666c24;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x10);
    local_64 = 0;
    uVar2 = DAT_00666c24 - DAT_00666c20 >> 2;
    if (uVar2 < 4) {
      FUN_005005c0(DAT_00666c24,3 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666c20 + 0xc;
      FUN_004a8b00(DAT_00666c24,DAT_00666c24,iVar3);
      DAT_00666c24 = DAT_00666c24 + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666c20) = *(undefined4 *)((int)local_60 + iVar3 + 0xc);
      iVar4 = DAT_00666c44;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0xc);
    local_38[0] = (undefined **)&DAT_005ca230;
    uVar2 = DAT_00666c44 - (int)DAT_00666c40 >> 2;
    local_38[1] = (undefined **)&DAT_005ca220;
    local_38[2] = (undefined **)&DAT_005ca204;
    local_38[3] = (undefined **)&DAT_005ca208;
    local_38[4] = (undefined **)&DAT_005ca23c;
    local_20[0] = &PTR_DAT_005ca21c;
    local_20[1] = (undefined **)&DAT_005ca238;
    local_20[2] = (undefined **)&DAT_005ca228;
    local_20[3] = (undefined **)&DAT_005ca22c;
    local_20[4] = &PTR_DAT_005ca214;
    local_20[5] = &PTR_DAT_005ca218;
    local_20[6] = &PTR_DAT_005ca224;
    local_64 = 0;
    if (uVar2 < 2) {
      FUN_005005c0(DAT_00666c44,1 - uVar2,&local_64);
    }
    else {
      puVar1 = DAT_00666c40 + 1;
      FUN_004a8b00(DAT_00666c44,DAT_00666c44,puVar1);
      DAT_00666c44 = DAT_00666c44 + (iVar4 - (int)puVar1 >> 2) * -4;
    }
    local_64 = 0;
    *DAT_00666c40 = &DAT_005d5a24;
    iVar3 = DAT_00666c50;
    uVar2 = DAT_00666c50 - DAT_00666c4c >> 2;
    if (uVar2 < 6) {
      FUN_005005c0(DAT_00666c50,5 - uVar2,&local_64);
    }
    else {
      iVar4 = DAT_00666c4c + 0x14;
      FUN_0049f3d0(DAT_00666c50,DAT_00666c50,iVar4,0,0);
      DAT_00666c50 = DAT_00666c50 + (iVar3 - iVar4 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666c4c) = *(undefined4 *)((int)local_38 + iVar3);
      iVar4 = DAT_00666c5c;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x14);
    local_64 = 0;
    uVar2 = DAT_00666c5c - DAT_00666c58 >> 2;
    if (uVar2 < 8) {
      FUN_005005c0(DAT_00666c5c,7 - uVar2,&local_64);
    }
    else {
      iVar3 = DAT_00666c58 + 0x1c;
      FUN_0049f3d0(DAT_00666c5c,DAT_00666c5c,iVar3,0,0);
      DAT_00666c5c = DAT_00666c5c + (iVar4 - iVar3 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666c58) = *(undefined4 *)((int)local_20 + iVar3);
      iVar4 = DAT_00666c7c;
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x1c);
    local_20[0] = (undefined **)&DAT_005c67e4;
    local_20[1] = (undefined **)&DAT_005ca230;
    uVar2 = DAT_00666c7c - (int)DAT_00666c78 >> 2;
    local_20[2] = (undefined **)&DAT_005ca22c;
    local_20[3] = (undefined **)&DAT_005ca228;
    local_20[4] = (undefined **)&DAT_005ca204;
    local_20[5] = (undefined **)&DAT_005ca208;
    local_20[6] = (undefined **)&DAT_005ca23c;
    local_20[7] = (undefined **)&DAT_005ca220;
    local_38[0] = &PTR_DAT_005ca214;
    local_38[1] = (undefined **)&DAT_005ca238;
    local_38[2] = &PTR_DAT_005ca21c;
    local_38[3] = (undefined **)&DAT_005ca1fc;
    local_38[4] = &PTR_DAT_005ca218;
    local_38[5] = &PTR_DAT_005ca224;
    local_64 = 0;
    if (uVar2 < 2) {
      FUN_005005c0(DAT_00666c7c,1 - uVar2,&local_64);
    }
    else {
      puVar1 = DAT_00666c78 + 1;
      FUN_0049f3d0(DAT_00666c7c,DAT_00666c7c,puVar1,0,0);
      DAT_00666c7c = DAT_00666c7c + (iVar4 - (int)puVar1 >> 2) * -4;
    }
    local_64 = 0;
    *DAT_00666c78 = &DAT_005d5a24;
    iVar3 = DAT_00666c88;
    uVar2 = DAT_00666c88 - DAT_00666c84 >> 2;
    if (uVar2 < 9) {
      FUN_005005c0(DAT_00666c88,8 - uVar2,&local_64);
    }
    else {
      iVar4 = DAT_00666c84 + 0x20;
      FUN_0049f3d0(DAT_00666c88,DAT_00666c88,iVar4,0,0);
      DAT_00666c88 = DAT_00666c88 + (iVar3 - iVar4 >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(iVar3 + DAT_00666c84) = *(undefined4 *)((int)local_20 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x20);
    local_64 = 0;
    uVar2 = DAT_00666c94 - DAT_00666c90 >> 2;
    if (uVar2 < 7) {
      FUN_005005c0(DAT_00666c94,6 - uVar2,&local_64);
    }
    else {
      DAT_00666c94 = DAT_00666c94 + (DAT_00666c94 - (DAT_00666c90 + 0x18) >> 2) * -4;
    }
    iVar3 = 0;
    do {
      *(undefined4 *)(DAT_00666c90 + iVar3) = *(undefined4 *)((int)local_38 + iVar3);
      iVar3 = iVar3 + 4;
    } while (iVar3 < 0x18);
  }
  return;
}

