/* Original Meteor.exe static export @ 0056f1d0; original sample not executed. */
/* XREF 0055db88 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_0056f1d0(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 local_4c [12];
  undefined1 local_40 [64];
  
  iVar4 = 0;
  if (0 < *(int *)(param_1 + 0x40)) {
    do {
      iVar3 = *(int *)(*(int *)(param_1 + 0x4c) + iVar4 * 4);
      iVar2 = *(int *)(iVar3 + 4);
      if (((iVar2 != 2) && (iVar2 != 10)) &&
         ((cVar1 = *(char *)(iVar3 + 0x24), cVar1 == 'a' || (cVar1 == 'A')))) {
        if (iVar2 == 9) {
          iVar3 = FUN_005877c0(param_2 + 0x1e8);
        }
        else {
          FUN_005818f0(local_4c,local_40);
          iVar3 = FUN_0055d950(local_4c,local_40,0);
        }
        if (iVar3 != 0) {
          return 1;
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(param_1 + 0x40));
  }
  return 0;
}

