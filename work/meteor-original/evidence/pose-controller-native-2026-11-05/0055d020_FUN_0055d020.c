/* Original Meteor.exe static export @ 0055d020; original sample not executed. */
/* XREF 004dbfdf UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_0055d020(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0x644);
  if (((iVar5 != 0) && (-1 < (int)param_2)) &&
     (param_2 < (uint)(*(int *)(iVar5 + 0xc) - *(int *)(iVar5 + 8) >> 3))) {
    *(uint *)(param_1 + 0x5fc) = param_3;
    uVar1 = param_3 & 4;
    if (*(int *)(param_1 + 0x5f0) == 0) {
      param_3 = param_3 | 1;
    }
    if ((param_3 & 1) != 0) {
      FUN_0055d260(*(undefined4 *)(*(int *)(iVar5 + 8) + param_2 * 8),0,uVar1,0xc0a00000,1);
      *(undefined4 *)(param_1 + 0x5f0) = 1;
      *(undefined4 *)(param_1 + 0x620) = 1;
      return 1;
    }
    if ((param_3 & 2) == 0) {
      uVar3 = FUN_0055d130(param_2);
      return uVar3;
    }
    iVar5 = *(int *)(param_1 + 0x638);
    puVar4 = *(undefined4 **)(iVar5 + 0x70);
    uVar1 = *(uint *)(iVar5 + 0x6c);
    if ((uVar1 <= (uint)(*(int *)(iVar5 + 0x74) - (int)puVar4 >> 2)) && (iVar5 = 0, 0 < (int)uVar1))
    {
      do {
        iVar2 = FUN_0055c550(*puVar4);
        if (iVar2 == 0) {
          return 3;
        }
        if (*(uint *)(iVar2 + 0x68) == param_2) {
          *(undefined4 *)(param_1 + 0x620) = 0;
          *(undefined4 *)(param_1 + 0x624) =
               *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x638) + 0x70) + iVar5 * 4);
          *(undefined4 *)(param_1 + 0x640) = 2;
          return 2;
        }
        iVar5 = iVar5 + 1;
        puVar4 = puVar4 + 1;
      } while (iVar5 < (int)uVar1);
    }
  }
  return 3;
}

