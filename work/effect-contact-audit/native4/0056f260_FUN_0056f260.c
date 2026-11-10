/* Original Meteor.exe static export @ 0056f260; original sample not executed. */
/* XREF 0055dd4b UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_0056f260(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined1 local_4c [12];
  undefined1 local_40 [64];
  
  iVar4 = 0;
  if (0 < *(int *)(param_1 + 0x40)) {
    do {
      iVar1 = *(int *)(*(int *)(param_1 + 0x4c) + iVar4 * 4);
      iVar2 = *(int *)(iVar1 + 4);
      if (((iVar2 != 2) && (iVar2 != 10)) &&
         ((cVar3 = *(char *)(iVar1 + 0x24), cVar3 == 'a' || (cVar3 == 'A')))) {
        FUN_005818f0(local_4c,local_40);
        cVar3 = FUN_00570630(local_4c,local_40,param_2,param_3);
        if (cVar3 != '\0') {
          return 1;
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(param_1 + 0x40));
  }
  return 0;
}

