/* Original Meteor.exe static export @ 00481fe0; original sample not executed. */
/* XREF 0047e08a UNCONDITIONAL_CALL */
/* XREF 005a9020 DATA */

undefined4 __fastcall FUN_00481fe0(int param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  LONG LVar4;
  HWND unaff_retaddr;
  
  iVar2 = Direct3DCreate8(0xdc);
  *(int *)(param_1 + 0x36c50) = iVar2;
  if (iVar2 == 0) {
    uVar3 = FUN_00483330(0x82000001,1);
    return uVar3;
  }
  iVar2 = FUN_00482150();
  if (-1 < iVar2) {
    *(HWND *)(param_1 + 0x36c4c) = unaff_retaddr;
    *(HWND *)(param_1 + 0x36c48) = unaff_retaddr;
    LVar4 = GetWindowLongA(unaff_retaddr,-0x10);
    *(LONG *)(param_1 + 0x36d50) = LVar4;
    GetWindowRect(*(HWND *)(param_1 + 0x36c48),(LPRECT)(param_1 + 0x36d54));
    GetClientRect(*(HWND *)(param_1 + 0x36c48),(LPRECT)(param_1 + 0x36d64));
    iVar2 = FUN_00482e30();
    if (-1 < iVar2) {
      FUN_004820c0();
      FUN_00482ab0();
      *(undefined4 *)(param_1 + 0x367a4) = 1;
      return 0;
    }
  }
  piVar1 = *(int **)(param_1 + 0x36c50);
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *(undefined4 *)(param_1 + 0x36c50) = 0;
  }
  uVar3 = FUN_00483330(iVar2,1);
  return uVar3;
}

