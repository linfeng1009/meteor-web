/* Original Meteor.exe static export @ 00553de0; original sample not executed. */
/* XREF 0054b234 UNCONDITIONAL_CALL */
/* XREF 0054f776 UNCONDITIONAL_CALL */
/* XREF 0054ac97 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_00553de0(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  DWORD *pDVar6;
  DWORD *pDVar7;
  DWORD local_24 [6];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a4e38;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  FUN_005542f0(300);
  if ((*(byte *)(param_2 + 5) & 0x40) != 0) {
    FUN_00553ae0();
  }
  if ((*(byte *)(param_2 + 5) & 8) != 0) {
    FUN_005539c0();
  }
  if ((*(byte *)(param_2 + 5) & 0x10) != 0) {
    FUN_005539e0(*(undefined4 *)(param_1 + 0x14));
  }
  if ((*(byte *)(param_2 + 5) & 1) == 0) {
    FUN_00554630((undefined2 *)(param_1 + 8));
    *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 8);
    *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + 1;
    iVar5 = FUN_00553870();
    *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + iVar5;
  }
  else {
    FUN_00554630((undefined2 *)(param_1 + 10));
    *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 10);
    *(undefined2 *)(param_2 + 8) = 0;
    FUN_00554c90();
    local_4 = 0;
    local_24[3] = timeGetTime();
    local_24[1] = *param_3;
    local_24[2] = param_3[1];
    FUN_00554cd0(param_2);
    pDVar7 = *(DWORD **)(param_1 + 0x3c);
    if (pDVar7 == (DWORD *)(*(int *)(param_1 + 0x44) + -0x18)) {
      FUN_0054c510(local_24);
    }
    else {
      if (pDVar7 != (DWORD *)0x0) {
        pDVar6 = local_24;
        for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
          *pDVar7 = *pDVar6;
          pDVar6 = pDVar6 + 1;
          pDVar7 = pDVar7 + 1;
        }
      }
      *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 0x18;
    }
    *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + 1;
    iVar5 = FUN_00553870();
    local_4 = 0xffffffff;
    *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + iVar5;
    FUN_004e8500();
  }
  if (_DAT_005a83e4 < *(float *)(param_1 + 0x20)) {
    iVar5 = _rand();
    iVar2 = __ftol();
    if (iVar5 % 1000 < iVar2) {
      ExceptionList = local_c;
      return 0;
    }
  }
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_1 + 0xe);
  if (*(char *)(param_1 + 0x1c) != '\0') {
    *(byte *)(param_2 + 5) = *(byte *)(param_2 + 5) | 2;
  }
  uVar3 = FUN_00553870(param_3);
  uVar4 = FUN_00553880(uVar3);
  iVar5 = FUN_005547a0(uVar4,uVar3,param_3);
  if ((iVar5 == 0) && (iVar2 = *(int *)(param_1 + 0x2c), *(int *)(param_1 + 0x3c) != iVar2)) {
    iVar1 = (iVar2 - *(int *)(param_1 + 0x30)) / 0x18;
    if ((iVar1 < 0) || (0x14 < iVar1)) {
      if (iVar1 < 1) {
        iVar2 = -1 - (-iVar1 - 1U) / 0x15;
      }
      else {
        iVar2 = iVar1 / 0x15;
      }
      iVar2 = *(int *)(*(int *)(param_1 + 0x38) + iVar2 * 4) + (iVar1 + iVar2 * -0x15) * 0x18;
    }
    *(int *)(iVar2 + 0xc) = *(int *)(iVar2 + 0xc) + -1000;
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  ExceptionList = local_c;
  return iVar5;
}

