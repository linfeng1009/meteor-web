/* Original Meteor.exe static export @ 00575180; original sample not executed. */
/* XREF 00574ed8 UNCONDITIONAL_CALL */
/* XREF 0057b03f UNCONDITIONAL_CALL */

void __fastcall FUN_00575180(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  *(undefined1 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x24) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  iVar4 = *(int *)(param_1 + 0x34);
  iVar1 = *(int *)(param_1 + 0x38);
  iVar3 = FUN_00552510(iVar1,iVar1,iVar4);
  iVar2 = *(int *)(param_1 + 0x38);
  for (; iVar3 != iVar2; iVar3 = iVar3 + 0xc) {
    FUN_0047a7e0(0);
  }
  iVar4 = (int)((ulonglong)((longlong)(iVar1 - iVar4) * -0x2aaaaaab) >> 0x20);
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + ((iVar4 >> 1) - (iVar4 >> 0x1f)) * 0xc;
  iVar4 = *(int *)(param_1 + 0x28);
  iVar1 = *(int *)(param_1 + 0x2c);
  FUN_0049f3d0(iVar1,iVar1,iVar4,iVar2,0);
  *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + (iVar1 - iVar4 >> 2) * -4;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0x3df5c28f;
  *(undefined4 *)(param_1 + 0x68) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  iVar4 = *(int *)(param_1 + 0x70);
  iVar1 = *(int *)(param_1 + 0x74);
  FUN_0049f3d0(iVar1,iVar1,iVar4,iVar2,0);
  *(int *)(param_1 + 0x74) = *(int *)(param_1 + 0x74) + (iVar1 - iVar4 >> 2) * -4;
  iVar4 = *(int *)(param_1 + 0x7c);
  iVar1 = *(int *)(param_1 + 0x80);
  FUN_00576490(iVar1,iVar1,iVar4);
  iVar4 = (int)((ulonglong)((longlong)(iVar1 - iVar4) * -0x2aaaaaab) >> 0x20);
  *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + ((iVar4 >> 1) - (iVar4 >> 0x1f)) * 0xc;
  *(undefined4 *)(param_1 + 0x58) = 0;
  iVar4 = *(int *)(param_1 + 0x88);
  iVar1 = *(int *)(param_1 + 0x8c);
  FUN_00576490(iVar1,iVar1,iVar4);
  iVar4 = (int)((ulonglong)((longlong)(iVar1 - iVar4) * -0x2aaaaaab) >> 0x20);
  *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + ((iVar4 >> 1) - (iVar4 >> 0x1f)) * 0xc;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  iVar4 = *(int *)(param_1 + 0x94);
  iVar1 = *(int *)(param_1 + 0x98);
  iVar3 = FUN_005764e0(iVar1,iVar1,iVar4);
  iVar2 = *(int *)(param_1 + 0x98);
  for (; iVar3 != iVar2; iVar3 = iVar3 + 0x68) {
    FUN_00577860(0);
  }
  iVar4 = (int)((ulonglong)((longlong)(iVar1 - iVar4) * -0x4ec4ec4f) >> 0x20);
  *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x98) + ((iVar4 >> 5) - (iVar4 >> 0x1f)) * 0x68;
  *(undefined4 *)(param_1 + 0x60) = 0;
  iVar4 = *(int *)(param_1 + 0xa0);
  iVar1 = *(int *)(param_1 + 0xa4);
  FUN_005771e0(iVar1,iVar1,iVar4,iVar2,0);
  iVar4 = (int)((ulonglong)((longlong)(iVar1 - iVar4) * -0x2aaaaaab) >> 0x20);
  *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) + ((iVar4 >> 2) - (iVar4 >> 0x1f)) * 0x18;
  *(undefined4 *)(param_1 + 100) = 0;
  return;
}

