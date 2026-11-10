/* Original Meteor.exe static export @ 00408270; original sample not executed. */
/* XREF 004a53d2 UNCONDITIONAL_CALL */
/* XREF 004a54fa UNCONDITIONAL_CALL */
/* XREF 004f708c UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_00408270(undefined4 param_1,float param_2,int param_3,float param_4,int param_5,int param_6)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  float fVar9;
  int local_3c;
  float local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined1 local_24 [8];
  float local_1c;
  undefined1 local_18 [12];
  undefined1 local_c [12];
  
  if (DAT_005d5a00 == 0) {
    return 0xffffffff;
  }
  iVar2 = FUN_00410a70(param_1);
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  iVar3 = *(int *)(iVar2 + 0x144);
  if ((iVar3 == 0) || (*(int *)(iVar3 + 4) == 0)) {
    param_3 = 0;
  }
  if (*(int *)(iVar2 + 0x148) == -1) {
    param_3 = 0;
  }
  else if (param_3 != 0) {
    local_34 = *(int *)(iVar3 + 0xc);
    local_2c = *(int *)(*(int *)(iVar3 + 4) + 0x9c);
    local_3c = 1;
    uVar4 = *(undefined4 *)(local_2c + 0x1c);
    iVar3 = *(int *)(local_2c + 0x40);
    if (param_2 < _DAT_005a83e4) {
      local_3c = 2;
    }
    local_30 = iVar3;
    FUN_00407f80(iVar2,*(undefined4 *)(iVar2 + 0xb8),param_2);
    FUN_00407c10(param_1,local_24,local_18,local_c);
    uVar1 = DAT_007eac64;
    iVar6 = FUN_00408b70(uVar4,iVar3,iVar2,local_24,local_18,
                         *(undefined4 *)(*(int *)(iVar2 + 0x144) + 0x28),local_3c,DAT_007eac64);
    if (iVar6 == 0) {
      uVar4 = *(undefined4 *)(iVar2 + 0xb8);
LAB_0040853a:
      FUN_00407f80(iVar2,uVar4,-param_2);
      FUN_00407c10(param_1,local_24,local_18,0);
      uVar4 = FUN_004080a0(*(undefined4 *)(iVar2 + 0x144),*(undefined4 *)(iVar2 + 0x148),local_24,
                           local_18,0);
      return uVar4;
    }
    iVar3 = FUN_004100b0(uVar4,iVar3 + 0xc + *(int *)(iVar2 + 0x148) * DAT_005c4314 * 4,local_24,
                         *(undefined4 *)(local_34 + *(int *)(iVar2 + 0x148) * 4),&local_38,uVar1);
    if (iVar3 == 0) {
      local_3c = 0;
      iVar3 = *(int *)(*(int *)(*(int *)(iVar2 + 0x144) + 0x14) + *(int *)(iVar2 + 0x148) * 4);
      iVar6 = *(int *)(*(int *)(iVar2 + 0x144) + 0x1c);
      local_28 = *(int *)(iVar6 + iVar3 * 4);
      iVar3 = iVar6 + iVar3 * 4 + 4;
      if (0 < local_28) {
        do {
          iVar6 = *(int *)(iVar3 + local_3c * 4);
          iVar6 = FUN_004100b0(uVar4,local_30 + 0xc + iVar6 * DAT_005c4314 * 4,local_24,
                               *(undefined4 *)(local_34 + iVar6 * 4),&local_38,uVar1);
          if (iVar6 != 0) {
            *(undefined4 *)(iVar2 + 0x148) = *(undefined4 *)(iVar3 + local_3c * 4);
            goto LAB_00408506;
          }
          local_3c = local_3c + 1;
        } while (local_3c < local_28);
      }
      iVar3 = 0;
      if (0 < *(int *)(local_2c + 0x34)) {
        do {
          iVar6 = FUN_004100b0(uVar4,local_30 + 0xc + DAT_005c4314 * iVar3 * 4,local_24,
                               *(undefined4 *)(local_34 + iVar3 * 4),&local_38,uVar1);
          if (iVar6 != 0) {
            *(int *)(iVar2 + 0x148) = iVar3;
            goto LAB_00408506;
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(local_2c + 0x34));
      }
      uVar4 = *(undefined4 *)(iVar2 + 0xb8);
      goto LAB_0040853a;
    }
LAB_00408506:
    uVar4 = *(undefined4 *)(iVar2 + 0xb4);
    fVar9 = (local_38 - local_1c) + param_4;
    goto LAB_004082f6;
  }
  uVar4 = *(undefined4 *)(iVar2 + 0xb8);
  fVar9 = param_2;
LAB_004082f6:
  FUN_00407f80(iVar2,uVar4,fVar9);
  if (param_6 == 0) {
    if ((param_3 != 0) && (param_5 != 0)) {
      FUN_00408ad0(iVar2,local_24,local_c,
                   *(int *)(*(int *)(iVar2 + 0x144) + 0x10) + *(int *)(iVar2 + 0x148) * 0xc);
    }
    *(float *)(iVar2 + 0x14c) = param_4;
  }
  else {
    iVar3 = FUN_00408da0(iVar2);
    if (iVar3 != 0) {
      if (param_3 == 0) {
        FUN_00407f80(iVar2,*(undefined4 *)(iVar2 + 0xb4),-param_4);
        FUN_00407f80(iVar2,*(undefined4 *)(iVar2 + 0xb8),-param_2);
        return 0xfffffffe;
      }
      FUN_00407f80(iVar2,*(undefined4 *)(iVar2 + 0xb4),(local_1c - local_38) - param_4);
      FUN_00407f80(iVar2,*(undefined4 *)(iVar2 + 0xb8),-param_2);
      return 0xfffffffe;
    }
    if ((param_3 != 0) && (param_5 != 0)) {
      FUN_00408ad0(iVar2,local_24,local_c,
                   *(int *)(*(int *)(iVar2 + 0x144) + 0x10) + *(int *)(iVar2 + 0x148) * 0xc);
    }
    *(float *)(iVar2 + 0x14c) = param_4;
  }
  iVar3 = *(int *)(iVar2 + 0x164);
  if ((iVar3 != 0) && (*(int *)(iVar2 + 0x160) == 0)) {
    iVar6 = 0;
    if (0 < *(int *)(iVar3 + 0xc)) {
      do {
        iVar3 = *(int *)(*(int *)(iVar3 + 0x14) + iVar6 * 4);
        if (iVar3 != 0) {
          puVar7 = (undefined4 *)(iVar2 + 8);
          puVar8 = (undefined4 *)(iVar3 + 8);
          for (iVar5 = 0xc; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar8 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar8 = puVar8 + 1;
          }
        }
        iVar3 = *(int *)(iVar2 + 0x164);
        iVar6 = iVar6 + 1;
      } while (iVar6 < *(int *)(iVar3 + 0xc));
    }
  }
  return 0xfffffffd;
}

