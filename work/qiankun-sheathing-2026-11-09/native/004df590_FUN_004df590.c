/* Original Meteor.exe static export @ 004df590; original sample not executed. */
/* XREF 005aabb8 DATA */
/* XREF 005aac28 DATA */
/* XREF 005aac98 DATA */
/* XREF 005aad08 DATA */
/* XREF 005aad78 DATA */
/* XREF 005aade8 DATA */
/* XREF 005aaf38 DATA */
/* XREF 005aafb8 DATA */
/* XREF 005ab030 DATA */

int __thiscall FUN_004df590(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = FUN_004dd100(param_2);
  if (iVar2 == 0) {
    iVar2 = *(int *)(*(int *)(param_1 + 0x34) + 8);
    while (iVar2 != *(int *)(param_1 + 0x34)) {
      if (*(int *)(iVar2 + 0x10) == param_2) {
        return 1;
      }
      iVar3 = *(int *)(iVar2 + 0xc);
      if (iVar3 == 0) {
        iVar3 = *(int *)(iVar2 + 4);
        if (iVar2 == *(int *)(iVar3 + 0xc)) {
          do {
            iVar2 = iVar3;
            iVar3 = *(int *)(iVar2 + 4);
          } while (iVar2 == *(int *)(iVar3 + 0xc));
        }
        if (*(int *)(iVar2 + 0xc) != iVar3) {
          iVar2 = iVar3;
        }
      }
      else {
        for (iVar1 = *(int *)(iVar3 + 8); iVar2 = iVar3, iVar1 != 0; iVar1 = *(int *)(iVar1 + 8)) {
          iVar3 = iVar1;
        }
      }
    }
    iVar2 = 0;
  }
  return iVar2;
}

