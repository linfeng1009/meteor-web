/* Original Meteor.exe static export @ 0056b4a0; original sample not executed. */
/* XREF 00563282 UNCONDITIONAL_CALL */
/* XREF 00564c42 UNCONDITIONAL_CALL */
/* XREF 00564ca0 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_0056b4a0(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 local_40 [64];
  
  FUN_00476f00(local_40,param_1 + 0x94,param_1 + 0x54);
  cVar1 = FUN_00570630(param_1 + 0x108,local_40,param_2,param_3);
  if ((cVar1 != '\0') && (iVar3 = 0, 0 < *(int *)(*(int *)(param_1 + 0x120) + 0x38))) {
    do {
      iVar2 = FUN_0057f180(param_2,param_3,param_1);
      if (iVar2 != 0) {
        return 1;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(*(int *)(param_1 + 0x120) + 0x38));
  }
  return 0;
}

