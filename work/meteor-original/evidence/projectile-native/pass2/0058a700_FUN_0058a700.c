/* Original Meteor.exe static export @ 0058a700; original sample not executed. */
/* XREF 0056e561 UNCONDITIONAL_CALL */

undefined4 FUN_0058a700(byte *param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  
  iVar3 = 0;
  pbVar5 = &DAT_005d2f8c;
  pbVar4 = param_1;
  pbVar6 = pbVar5;
LAB_0058a713:
  do {
    bVar1 = *pbVar5;
    bVar7 = bVar1 < *pbVar4;
    if (bVar1 == *pbVar4) {
      if (bVar1 != 0) {
        bVar1 = pbVar5[1];
        bVar7 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_0058a737;
        pbVar5 = pbVar5 + 2;
        pbVar4 = pbVar4 + 2;
        if (bVar1 != 0) goto LAB_0058a713;
      }
      iVar2 = 0;
    }
    else {
LAB_0058a737:
      iVar2 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
    }
    if (iVar2 == 0) {
      return (&DAT_005d2f88)[iVar3 * 5];
    }
    pbVar5 = pbVar6 + 0x14;
    iVar3 = iVar3 + 1;
    pbVar4 = param_1;
    pbVar6 = pbVar5;
    if (0x5d307b < (int)pbVar5) {
      return 0;
    }
  } while( true );
}

