/* Original Meteor.exe read-only export. Sample not executed. */

/* WARNING: Removing unreachable block (ram,0x004fdb53) */
/* WARNING: Removing unreachable block (ram,0x004fdb5b) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004fda00(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  *(undefined4 *)(param_1 + 0x7c) = 0;
  iVar3 = _rand();
  *(undefined1 **)(param_1 + 100) = &LAB_005038e0;
  *(float *)(param_1 + 0x80) = (float)(iVar3 % 1000) * _DAT_005ab86c;
  if (*(undefined1 **)(param_1 + 0x8c) != *(undefined1 **)(param_1 + 0x90)) {
    **(undefined1 **)(param_1 + 0x8c) = 0;
    *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0x8c);
  }
  if (*(undefined1 **)(param_1 + 0x98) != *(undefined1 **)(param_1 + 0x9c)) {
    **(undefined1 **)(param_1 + 0x98) = 0;
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x98);
  }
  *(undefined4 *)(param_1 + 0x84) = 0xffffffff;
  iVar3 = *(int *)(param_1 + 0x68);
  iVar1 = *(int *)(param_1 + 0x6c);
  iVar4 = FUN_004fece0(iVar1,iVar1,iVar3,iVar3,0);
  iVar2 = *(int *)(param_1 + 0x6c);
  for (; iVar4 != iVar2; iVar4 = iVar4 + 0x30) {
    FUN_004c82b0(0);
  }
  iVar3 = (int)((ulonglong)((longlong)(iVar1 - iVar3) * -0x2aaaaaab) >> 0x20);
  *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + ((iVar3 >> 3) - (iVar3 >> 0x1f)) * 0x30;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0xc4) = 0xffffffff;
  *(undefined4 *)(param_1 + 0xdc) = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined4 *)(param_1 + 0xe0) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  if (*(undefined1 **)(param_1 + 0xfc) != *(undefined1 **)(param_1 + 0x100)) {
    **(undefined1 **)(param_1 + 0xfc) = 0;
    *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0xfc);
  }
  *(undefined4 *)(param_1 + 0x114) = 0x3f800000;
  *(undefined4 *)(param_1 + 0xe4) = 0xffffffff;
  *(int *)(param_1 + 0x10c) =
       *(int *)(param_1 + 0x10c) + (*(int *)(param_1 + 0x10c) - *(int *)(param_1 + 0x108) >> 1) * -2
  ;
  *(undefined4 *)(param_1 + 0x120) = 0;
  FUN_004fcc00();
  FUN_004fdd10();
  FUN_004fd580();
  return;
}

