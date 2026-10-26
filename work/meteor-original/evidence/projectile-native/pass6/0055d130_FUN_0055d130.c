/* Original Meteor.exe static export @ 0055d130; original sample not executed. */
/* XREF 0055d124 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_0055d130(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int extraout_ECX;
  int iVar4;
  undefined4 *puVar5;
  
  if ((((*(int *)(param_1 + 0x620) != 0) && (*(int *)(param_1 + 0x5e0) != -1)) &&
      (iVar1 = *(int *)(param_1 + 0x644), iVar1 != 0)) &&
     ((-1 < (int)param_2 && (param_2 < (uint)(*(int *)(iVar1 + 0xc) - *(int *)(iVar1 + 8) >> 3)))))
  {
    iVar1 = *(int *)(param_1 + 0x638);
    if ((*(int *)(iVar1 + 0x48) <= *(int *)(param_1 + 0xfc)) &&
       (*(int *)(param_1 + 0xfc) <= *(int *)(iVar1 + 0x4c))) {
      iVar2 = *(int *)(iVar1 + 0x6c);
      iVar4 = 0;
      if (0 < iVar2) {
        puVar5 = *(undefined4 **)(iVar1 + 0x70);
        do {
          iVar3 = FUN_0055c550(*puVar5);
          if (iVar3 == 0) {
            return 3;
          }
          if (*(uint *)(iVar3 + 0x68) == param_2) {
            *(undefined4 *)(extraout_ECX + 0x620) = 0;
            *(undefined4 *)(extraout_ECX + 0x624) =
                 *(undefined4 *)(*(int *)(iVar1 + 0x70) + iVar4 * 4);
            *(undefined4 *)(extraout_ECX + 0x640) = 2;
            return 2;
          }
          iVar4 = iVar4 + 1;
          puVar5 = puVar5 + 1;
        } while (iVar4 < iVar2);
      }
    }
  }
  return 3;
}

