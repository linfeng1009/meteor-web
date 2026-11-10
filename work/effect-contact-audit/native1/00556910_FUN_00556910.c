/* Original Meteor.exe static export @ 00556910; original sample not executed. */
/* XREF 00556f4a UNCONDITIONAL_CALL */
/* XREF 00556f5c UNCONDITIONAL_CALL */
/* XREF 0055cb5f UNCONDITIONAL_CALL */
/* XREF 00584c13 UNCONDITIONAL_CALL */

int __thiscall FUN_00556910(int param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  
  iVar4 = 0;
  pbVar5 = *(byte **)(param_1 + 0x350);
  pbVar2 = param_2;
  pbVar6 = pbVar5;
  if (0 < *(int *)(param_1 + 0x1c)) {
LAB_00556929:
    do {
      bVar1 = *pbVar2;
      bVar7 = bVar1 < *pbVar5;
      if (bVar1 == *pbVar5) {
        if (bVar1 != 0) {
          bVar1 = pbVar2[1];
          bVar7 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_0055694d;
          pbVar5 = pbVar5 + 2;
          pbVar2 = pbVar2 + 2;
          if (bVar1 != 0) goto LAB_00556929;
        }
        iVar3 = 0;
      }
      else {
LAB_0055694d:
        iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
      }
      if (iVar3 == 0) {
        return iVar4;
      }
      iVar4 = iVar4 + 1;
      pbVar5 = pbVar6 + 0x334;
      pbVar2 = param_2;
      pbVar6 = pbVar5;
    } while (iVar4 < *(int *)(param_1 + 0x1c));
  }
  iVar4 = 7;
  bVar7 = true;
  pbVar5 = param_2;
  pbVar2 = (byte *)s_weapon_005c9794;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar7 = *pbVar5 == *pbVar2;
    pbVar5 = pbVar5 + 1;
    pbVar2 = pbVar2 + 1;
  } while (bVar7);
  if (bVar7) {
    return 0x1000;
  }
  iVar4 = 7;
  bVar7 = true;
  pbVar5 = (byte *)s_effect_005d12b0;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    bVar7 = *param_2 == *pbVar5;
    param_2 = param_2 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar7);
  return (!bVar7 - 1 & 0x1002) - 1;
}

