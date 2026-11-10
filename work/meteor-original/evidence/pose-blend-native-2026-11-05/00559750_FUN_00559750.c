/* Original Meteor.exe static export @ 00559750; original sample not executed. */
/* XREF 0055d899 UNCONDITIONAL_CALL */
/* XREF 0055d8e4 UNCONDITIONAL_CALL */

undefined4 __fastcall FUN_00559750(int param_1)

{
  DWORD DVar1;
  int iVar2;
  
  DVar1 = timeGetTime();
  iVar2 = DVar1 - *(int *)(param_1 + 0x11c);
  *(int *)(param_1 + 0x120) = iVar2;
  if (*(int *)(param_1 + 0x124) <= iVar2) {
    *(int *)(param_1 + 0xfc) = *(int *)(param_1 + 0x114);
    *(float *)(param_1 + 0xf8) = (float)*(int *)(param_1 + 0x114);
    return 0;
  }
  *(float *)(param_1 + 0x118) = (float)iVar2 / (float)*(int *)(param_1 + 0x124);
  FUN_00558ae0();
  return 1;
}

