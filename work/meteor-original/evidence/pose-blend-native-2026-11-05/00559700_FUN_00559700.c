/* Original Meteor.exe static export @ 00559700; original sample not executed. */
/* XREF 0055d8dd UNCONDITIONAL_CALL */

void __fastcall FUN_00559700(int param_1)

{
  DWORD DVar1;
  
  DVar1 = timeGetTime();
  *(DWORD *)(param_1 + 0x11c) = DVar1;
  *(undefined4 *)(param_1 + 0x120) = 0;
  return;
}

