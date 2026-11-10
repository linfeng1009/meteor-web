/* Original Meteor.exe static export @ 004e2b30; original sample not executed. */
/* XREF 005aaf64 DATA */

bool __thiscall FUN_004e2b30(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x78);
  iVar3 = iVar1;
  iVar2 = *(int *)(iVar1 + 4);
  while (iVar2 != 0) {
    if (*(uint *)(iVar2 + 0x10) < param_2) {
      iVar2 = *(int *)(iVar2 + 0xc);
    }
    else {
      iVar3 = iVar2;
      iVar2 = *(int *)(iVar2 + 8);
    }
  }
  if ((iVar3 != iVar1) && (*(uint *)(iVar3 + 0x10) <= param_2)) {
    return iVar3 != *(int *)(param_1 + 0x78);
  }
  return iVar1 != *(int *)(param_1 + 0x78);
}

