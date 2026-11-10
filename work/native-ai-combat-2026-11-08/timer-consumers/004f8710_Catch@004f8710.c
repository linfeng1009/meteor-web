/* Original Meteor.exe read-only export. Sample not executed. */

void Catch_004f8710(void)

{
  undefined4 *puVar1;
  uint uVar2;
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x18) != 0) {
    uVar2 = *(int *)(unaff_EBP + -0x18) * 4;
    if (uVar2 < 0x81) {
      FUN_00402330();
      puVar1 = *(undefined4 **)(unaff_EBP + -0x14);
      *puVar1 = *(undefined4 *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = puVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(*(undefined4 *)(unaff_EBP + -0x14));
    }
  }
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

