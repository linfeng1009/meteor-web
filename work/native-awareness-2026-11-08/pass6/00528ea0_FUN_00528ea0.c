/* Original Meteor.exe static export @ 00528ea0; original sample not executed. */
/* XREF 00506138 UNCONDITIONAL_CALL */
/* XREF 00506178 UNCONDITIONAL_CALL */
/* XREF 005062b0 UNCONDITIONAL_CALL */
/* XREF 005062c3 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00528ea0(int param_1,int param_2,float param_3)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  
  uVar3 = FUN_00525980();
  FUN_00525610(uVar3);
  cVar2 = FUN_00528e40(param_1);
  if (cVar2 == '\0') {
    FUN_005255b0(0xa001);
    FUN_00525620(uVar3);
    return;
  }
  iVar1 = param_2 + -0x1001;
  switch(param_2) {
  case 0x1001:
  case 0x1002:
    if ((param_3 < _DAT_005a83e4) || (param_3 < _DAT_005a84a8 == (param_3 == _DAT_005a84a8))) {
LAB_005290ce:
      FUN_005255b0(0xa003);
      FUN_00525620(uVar3);
      return;
    }
    *(float *)(param_1 + iVar1 * 0x1c) = param_3;
    *(undefined1 *)(param_1 + -0x1c004 + param_2 * 0x1c) = 1;
    uVar4 = *(uint *)(param_1 + 0xe30) | 0x100;
    break;
  case 0x1003:
    if ((param_3 < _DAT_005a83e4) || (param_3 < _DAT_005a8b80 == (param_3 == _DAT_005a8b80)))
    goto LAB_005290ce;
    *(float *)(param_1 + 0x38) = param_3;
    *(undefined1 *)(param_1 + -0x1c004 + param_2 * 0x1c) = 1;
    uVar4 = *(uint *)(param_1 + 0xe30) | 2;
    break;
  default:
    FUN_005255b0(0xa002);
    FUN_00525620(uVar3);
    return;
  case 0x100a:
  case 0x1020:
  case 0x1021:
  case 0x1023:
    if (param_3 < _DAT_005a83e4) goto LAB_005290ce;
    *(float *)(param_1 + iVar1 * 0x1c) = param_3;
    *(undefined1 *)(param_1 + -0x1c004 + param_2 * 0x1c) = 1;
    if (param_2 == 0x100a) {
      *(uint *)(param_1 + 0xe30) = *(uint *)(param_1 + 0xe30) | 1;
      FUN_005260b0(uVar3,1,param_1);
      FUN_00525620(uVar3);
      return;
    }
    if (param_2 == 0x1023) {
      *(uint *)(param_1 + 0xe30) = *(uint *)(param_1 + 0xe30) | 0x40;
      FUN_005260b0(uVar3,1,param_1);
      FUN_00525620(uVar3);
      return;
    }
    if (param_2 == 0x1020) {
      *(uint *)(param_1 + 0xe30) = *(uint *)(param_1 + 0xe30) | 0x20;
      FUN_005260b0(uVar3,1,param_1);
      FUN_00525620(uVar3);
      return;
    }
    goto LAB_005290b7;
  case 0x100d:
  case 0x100e:
  case 0x1022:
    if ((param_3 < _DAT_005a83e4) || (param_3 < _DAT_005a83f4 == (param_3 == _DAT_005a83f4)))
    goto LAB_005290ce;
    *(float *)(param_1 + iVar1 * 0x1c) = param_3;
    *(undefined1 *)(param_1 + -0x1c004 + param_2 * 0x1c) = 1;
    uVar4 = *(uint *)(param_1 + 0xe30) | 0x200;
  }
  *(uint *)(param_1 + 0xe30) = uVar4;
LAB_005290b7:
  FUN_005260b0(uVar3,1,param_1);
  FUN_00525620(uVar3);
  return;
}

