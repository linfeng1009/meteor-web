/* Original Meteor.exe static export @ 00564fc0; original sample not executed. */
/* XREF 0056c914 UNCONDITIONAL_CALL */
/* XREF 0056ca09 UNCONDITIONAL_CALL */
/* XREF 0056c2c7 UNCONDITIONAL_CALL */
/* XREF 0056bca1 UNCONDITIONAL_CALL */

int __thiscall FUN_00564fc0(int param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  bool bVar7;
  
  iVar4 = 0;
  iVar6 = *(int *)(param_1 + 0x4b4);
  if (0 < *(int *)(param_1 + 0x4b0)) {
    do {
      if (*(int *)(iVar6 + 0x28) != 0) {
        pbVar2 = (byte *)(*(int *)(iVar6 + 0x28) + 8);
        pbVar5 = param_2;
        do {
          bVar1 = *pbVar2;
          bVar7 = bVar1 < *pbVar5;
          if (bVar1 != *pbVar5) {
LAB_00565008:
            iVar3 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
            goto LAB_0056500d;
          }
          if (bVar1 == 0) break;
          bVar1 = pbVar2[1];
          bVar7 = bVar1 < pbVar5[1];
          if (bVar1 != pbVar5[1]) goto LAB_00565008;
          pbVar2 = pbVar2 + 2;
          pbVar5 = pbVar5 + 2;
        } while (bVar1 != 0);
        iVar3 = 0;
LAB_0056500d:
        if (iVar3 == 0) {
          return iVar6;
        }
      }
      iVar4 = iVar4 + 1;
      iVar6 = iVar6 + 0xac;
    } while (iVar4 < *(int *)(param_1 + 0x4b0));
  }
  return 0;
}

