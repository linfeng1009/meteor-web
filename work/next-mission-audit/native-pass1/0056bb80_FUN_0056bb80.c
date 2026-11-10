/* Original Meteor.exe static export @ 0056bb80; original sample not executed. */
/* XREF 00560a63 DATA */

undefined4 FUN_0056bb80(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  CHAR aCStack_40 [64];
  
  iVar3 = DAT_0072b6ac;
  if (*(int *)(param_1 + 4) < 2) {
    return 0;
  }
  iVar1 = **(int **)(param_1 + 8);
  iVar2 = (*(int **)(param_1 + 8))[1];
  DAT_0072b6ac = DAT_0072b6ac + 1;
  FUN_00508ae6(aCStack_40,s_GameCallBack__s__d_005d1788,*(undefined4 *)(iVar1 + 0xc),iVar3);
  OutputDebugStringA(aCStack_40);
  uVar4 = (*(code *)PTR_FUN_005d186c)(100,*(undefined4 *)(iVar1 + 0xc),*(undefined4 *)(iVar2 + 8));
  return uVar4;
}

