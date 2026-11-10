/* Original Meteor.exe static export @ 004086c0; original sample not executed. */
/* XREF 004a53ea UNCONDITIONAL_CALL */
/* XREF 004a552a UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_004086c0(undefined4 param_1,float param_2,int param_3,float param_4,int param_5,int param_6)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 uVar9;
  float fVar10;
  int local_40;
  float local_3c;
  undefined4 local_38;
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
  uVar5 = DAT_007eac64;
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  iVar4 = *(int *)(iVar2 + 0x144);
  if ((iVar4 == 0) || (*(int *)(iVar4 + 4) == 0)) {
    param_3 = 0;
  }
  if (*(int *)(iVar2 + 0x148) == -1) {
    param_3 = 0;
  }
  uVar9 = *(undefined4 *)(&DAT_007f1840 + (*(int *)(iVar2 + 0xb8) + *(int *)(iVar2 + 0xb4) * 6) * 4)
  ;
  fVar10 = param_2;
  local_38 = uVar9;
  if (param_3 == 0) {
LAB_0040898d:
    FUN_00407f80(iVar2,uVar9,fVar10);
    if ((param_6 != 0) && (iVar4 = FUN_00408da0(iVar2), iVar4 != 0)) {
      if (param_3 == 0) {
        FUN_00407f80(iVar2,*(undefined4 *)(iVar2 + 0xb4),-param_4);
        FUN_00407f80(iVar2,local_38,-param_2);
        return 0xfffffffe;
      }
      FUN_00407f80(iVar2,*(undefined4 *)(iVar2 + 0xb4),(local_1c - local_3c) - param_4);
      FUN_00407f80(iVar2,local_38,-param_2);
      return 0xfffffffe;
    }
    if ((param_3 != 0) && (param_5 != 0)) {
      FUN_00408ad0(iVar2,local_24,local_c,
                   *(int *)(*(int *)(iVar2 + 0x144) + 0x10) + *(int *)(iVar2 + 0x148) * 0xc);
    }
    iVar4 = *(int *)(iVar2 + 0x164);
    *(float *)(iVar2 + 0x14c) = param_4;
    if ((iVar4 != 0) && (*(int *)(iVar2 + 0x160) == 0)) {
      iVar3 = 0;
      if (0 < *(int *)(iVar4 + 0xc)) {
        do {
          iVar4 = *(int *)(*(int *)(iVar4 + 0x14) + iVar3 * 4);
          if (iVar4 != 0) {
            puVar7 = (undefined4 *)(iVar2 + 8);
            puVar8 = (undefined4 *)(iVar4 + 8);
            for (iVar6 = 0xc; iVar6 != 0; iVar6 = iVar6 + -1) {
              *puVar8 = *puVar7;
              puVar7 = puVar7 + 1;
              puVar8 = puVar8 + 1;
            }
          }
          iVar4 = *(int *)(iVar2 + 0x164);
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(iVar4 + 0xc));
      }
    }
    return 0xfffffffd;
  }
  local_34 = *(int *)(iVar4 + 0xc);
  local_2c = *(int *)(*(int *)(iVar4 + 4) + 0x9c);
  uVar1 = *(undefined4 *)(local_2c + 0x1c);
  iVar4 = *(int *)(local_2c + 0x40);
  local_40 = 3;
  if (param_2 < _DAT_005a83e4) {
    local_40 = 4;
  }
  local_30 = iVar4;
  FUN_00407f80(iVar2,uVar9,param_2);
  FUN_00407c10(param_1,local_24,local_18,local_c);
  iVar3 = FUN_00408b70(uVar1,iVar4,iVar2,local_24,local_18,
                       *(undefined4 *)(*(int *)(iVar2 + 0x144) + 0x28),local_40,uVar5);
  if (iVar3 != 0) {
    iVar4 = FUN_004100b0(uVar1,iVar4 + 0xc + *(int *)(iVar2 + 0x148) * DAT_005c4314 * 4,local_24,
                         *(undefined4 *)(local_34 + *(int *)(iVar2 + 0x148) * 4),&local_3c,uVar5);
    if (iVar4 != 0) {
LAB_004088fd:
      uVar9 = *(undefined4 *)(iVar2 + 0xb4);
      fVar10 = (local_3c - local_1c) + param_4;
      goto LAB_0040898d;
    }
    local_40 = 0;
    iVar4 = *(int *)(*(int *)(*(int *)(iVar2 + 0x144) + 0x14) + *(int *)(iVar2 + 0x148) * 4);
    iVar3 = *(int *)(*(int *)(iVar2 + 0x144) + 0x1c);
    local_28 = *(int *)(iVar3 + iVar4 * 4);
    iVar4 = iVar3 + iVar4 * 4 + 4;
    if (0 < local_28) {
      do {
        iVar3 = *(int *)(iVar4 + local_40 * 4);
        iVar3 = FUN_004100b0(uVar1,local_30 + 0xc + iVar3 * DAT_005c4314 * 4,local_24,
                             *(undefined4 *)(local_34 + iVar3 * 4),&local_3c,uVar5);
        if (iVar3 != 0) {
          *(undefined4 *)(iVar2 + 0x148) = *(undefined4 *)(iVar4 + local_40 * 4);
          goto LAB_004088fd;
        }
        local_40 = local_40 + 1;
      } while (local_40 < local_28);
    }
    iVar4 = 0;
    if (0 < *(int *)(local_2c + 0x34)) {
      do {
        iVar3 = FUN_004100b0(uVar1,local_30 + 0xc + DAT_005c4314 * iVar4 * 4,local_24,
                             *(undefined4 *)(local_34 + iVar4 * 4),&local_3c,uVar5);
        if (iVar3 != 0) {
          *(int *)(iVar2 + 0x148) = iVar4;
          goto LAB_004088fd;
        }
        iVar4 = iVar4 + 1;
      } while (iVar4 < *(int *)(local_2c + 0x34));
    }
  }
  FUN_00407f80(iVar2,local_38,-param_2);
  FUN_00407c10(param_1,local_24,local_18,0);
  uVar5 = FUN_004080a0(*(undefined4 *)(iVar2 + 0x144),*(undefined4 *)(iVar2 + 0x148),local_24,
                       local_18,0);
  return uVar5;
}

