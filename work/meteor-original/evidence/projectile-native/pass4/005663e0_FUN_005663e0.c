/* Original Meteor.exe static export @ 005663e0; original sample not executed. */
/* XREF 005ae208 DATA */

undefined4 __fastcall FUN_005663e0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  float10 fVar5;
  
  if ((*(int *)(param_1 + 300) != 0) && (*(char *)(param_1 + 0xd8) != '\0')) {
    FUN_0047b750();
    iVar1 = FUN_0056f310();
    puVar2 = (undefined4 *)FUN_0056e220();
    iVar3 = 0x10;
    if (iVar1 == 0) {
      puVar4 = (undefined4 *)(param_1 + 0x54);
    }
    else {
      puVar4 = (undefined4 *)(iVar1 + 0x16c);
    }
    for (; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar2 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar2 = puVar2 + 1;
    }
    fVar5 = (float10)FUN_004748b0();
    fVar5 = fVar5 + (float10)*(float *)(param_1 + 0x134);
    *(undefined4 *)(param_1 + 0x140) = 0;
    *(float *)(param_1 + 0x134) = (float)fVar5;
    if ((float10)*(float *)(*(int *)(param_1 + 300) + 0x1c) < fVar5) {
      if (*(char *)(param_1 + 0x138) == '\0') {
        *(undefined4 *)(param_1 + 0x140) = 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x134) = *(undefined4 *)(*(int *)(param_1 + 300) + 0x18);
      }
    }
    if (*(int *)(param_1 + 0x140) == 0) {
      FUN_0056e870(*(undefined4 *)(param_1 + 0x134));
      FUN_0056ec40();
    }
  }
  return 0;
}

