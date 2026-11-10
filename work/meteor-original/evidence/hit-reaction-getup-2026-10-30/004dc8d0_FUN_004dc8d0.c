/* Original Meteor.exe static export @ 004dc8d0; original sample not executed. */
/* XREF 005aaa60 DATA */

undefined4 __thiscall FUN_004dc8d0(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_0055c4e0();
  iVar2 = FUN_0055c550(uVar1);
  if ((iVar2 != 0) && (*(int *)(iVar2 + 0x18) - *(int *)(param_1 + 0xfc) < param_2)) {
    return 1;
  }
  return 0;
}

