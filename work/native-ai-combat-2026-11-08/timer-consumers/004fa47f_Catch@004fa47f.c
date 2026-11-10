/* Original Meteor.exe read-only export. Sample not executed. */

void Catch_004fa47f(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  int unaff_EBP;
  undefined4 *puVar4;
  
  puVar2 = *(undefined4 **)(unaff_EBP + -0x1c);
  puVar1 = *(undefined4 **)(unaff_EBP + -0x14);
  for (puVar4 = puVar1; puVar4 != puVar2; puVar4 = puVar4 + 7) {
    FUN_004c6910();
  }
  if (*(int *)(unaff_EBP + -0x18) != 0) {
    uVar3 = *(int *)(unaff_EBP + -0x18) * 0x1c;
    if (uVar3 < 0x81) {
      FUN_00402330();
      *puVar1 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(puVar1);
    }
  }
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

