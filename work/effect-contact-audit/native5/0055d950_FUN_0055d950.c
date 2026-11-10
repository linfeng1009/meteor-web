/* Original Meteor.exe static export @ 0055d950; original sample not executed. */
/* XREF 0055db2e UNCONDITIONAL_CALL */
/* XREF 0055dbdf UNCONDITIONAL_CALL */
/* XREF 0056f227 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_0055d950(int param_1,undefined4 param_2,undefined4 param_3,char param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined1 local_4c [12];
  undefined1 local_40 [64];
  
  if (param_4 == '\0') {
    cVar1 = FUN_00570630(param_1 + 0x1b8,param_1 + 0x248,param_2,param_3);
    if (cVar1 != '\0') {
      return 1;
    }
  }
  else {
    iVar3 = 0;
    if (0 < *(int *)(param_1 + 800)) {
      iVar2 = 0;
      do {
        if (*(int *)(*(int *)(param_1 + 0x350) + 0x2c + iVar2) != 0) {
          FUN_00557f30(*(undefined4 *)(*(int *)(param_1 + 0x324) + iVar3 * 4),local_40,local_4c);
          cVar1 = FUN_00570630(param_2,param_3,local_4c,local_40);
          if (cVar1 != '\0') {
            return 1;
          }
        }
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + 0x334;
      } while (iVar3 < *(int *)(param_1 + 800));
    }
  }
  return 0;
}

