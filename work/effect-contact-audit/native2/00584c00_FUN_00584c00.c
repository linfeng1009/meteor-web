/* Original Meteor.exe static export @ 00584c00; original sample not executed. */
/* XREF 0056e134 UNCONDITIONAL_CALL */
/* XREF 00584cd8 UNCONDITIONAL_CALL */

int __thiscall FUN_00584c00(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x274) != 0) {
    iVar1 = FUN_00556910(param_2);
    if (iVar1 != -1) {
      return iVar1;
    }
    iVar1 = FUN_005569b0(param_2);
    if (iVar1 != -1) {
      iVar2 = FUN_005565d0();
      return iVar2 + iVar1;
    }
  }
  return -1;
}

