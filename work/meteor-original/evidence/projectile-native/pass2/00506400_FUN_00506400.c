/* Original Meteor.exe static export @ 00506400; original sample not executed. */
/* XREF 0048aad6 UNCONDITIONAL_CALL */

void FUN_00506400(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  
  uVar1 = FUN_005063d0();
  if (DAT_00667584 < uVar1 - DAT_0066757c) {
    FUN_005063b0();
  }
  if (uVar1 - DAT_00667580 < 0xc9) {
    if (uVar1 < DAT_00667580) {
      DAT_00667580 = 0;
      DAT_0066757c = 0;
    }
  }
  else {
    iVar3 = (uint)(DAT_00667570 - DAT_0066756c >> 6) / 10 + 1;
    uVar4 = DAT_006675ec;
    DAT_00667580 = uVar1;
    if ((int)DAT_006675ec < (int)(DAT_006675ec + iVar3)) {
      do {
        uVar4 = uVar4 + 1;
        iVar2 = FUN_005060d0(uVar4);
        if (iVar2 == 0) {
          FUN_00506090(uVar4);
        }
      } while ((int)uVar4 < (int)(DAT_006675ec + iVar3));
    }
    DAT_006675ec = DAT_006675ec + iVar3;
    if ((uint)(DAT_00667570 - DAT_0066756c >> 6) <= DAT_006675ec) {
      DAT_006675ec = 0;
      return;
    }
  }
  return;
}

