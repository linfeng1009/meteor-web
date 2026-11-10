/* Original Meteor.exe static export @ 004caadb; original sample not executed. */
/* XREF 005bba4c DATA */

void Catch_004caadb(void)

{
  undefined4 *puVar1;
  uint uVar2;
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x14) != 0) {
    uVar2 = *(int *)(unaff_EBP + -0x14) * 0xc;
    if (uVar2 < 0x81) {
      FUN_00402330();
      puVar1 = *(undefined4 **)(unaff_EBP + -0x18);
      *puVar1 = *(undefined4 *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = puVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(*(undefined4 *)(unaff_EBP + -0x18));
    }
  }
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

