/* Original Meteor.exe static export @ 004a9bc0; original sample not executed. */
/* XREF 005a9454 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 * __thiscall FUN_004a9bc0(int param_1,uint *param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar4;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 *puVar5;
  float *pfVar6;
  undefined2 *puVar7;
  float10 fVar8;
  undefined1 local_36;
  undefined1 local_35;
  float local_34;
  undefined4 *local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  float local_18;
  float local_14;
  float local_10;
  void *local_c;
  undefined1 *puStack_8;
  uint local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059fcf0;
  local_c = ExceptionList;
  puVar5 = (undefined2 *)0x0;
  ExceptionList = &local_c;
  FUN_005005b0(&local_36);
  local_4 = 0;
  FUN_005005b0(&local_35);
  local_4 = CONCAT31(local_4._1_3_,1);
  if (*(int *)(param_1 + 8) != 0) {
    FUN_004b48c0(&local_34);
    if (local_34 != *(float *)(param_1 + 4)) {
      do {
        if (((param_3 != *(int *)((int)local_34 + 0x10)) && (*(int *)((int)local_34 + 0xdc) != 0))
           && (*(int *)((int)local_34 + 0x200) != 0)) {
          if (local_2c == local_28) {
            FUN_0049c640(local_2c,(int)local_34 + 0x10);
          }
          else {
            FUN_004a8e30();
            local_2c = local_2c + 4;
          }
          if (local_20 == local_1c) {
            FUN_004b51d0(local_20,(int)local_34 + 0x18);
          }
          else {
            FUN_004b5f10();
            local_20 = local_20 + 0x44;
          }
        }
        FUN_0043c6c0();
      } while (local_34 != *(float *)(param_1 + 4));
    }
  }
  uVar1 = (local_2c - (int)local_30 >> 2) * ((uint)(param_4 == 0) * 2 + 0xe);
  *param_2 = uVar1;
  puVar3 = local_30;
  if (uVar1 != 0) {
    puVar5 = operator_new(uVar1);
    uVar1 = 0;
    puVar3 = local_30;
    if (local_2c - (int)local_30 >> 2 != 0) {
      param_3 = 0;
      puVar7 = puVar5;
      do {
        *puVar7 = *(undefined2 *)(local_30 + uVar1);
        pfVar6 = (float *)(param_3 + local_24);
        if (param_4 == 0) {
          if (pfVar6[4] <= _DAT_005a83e4) {
            fVar8 = (float10)FUN_00509d10();
            fVar8 = -fVar8;
            uVar4 = extraout_var_02;
          }
          else {
            fVar8 = (float10)FUN_00509d10();
            uVar4 = extraout_var_01;
          }
          local_34 = (float)fVar8;
          FUN_004b3c70(pfVar6,local_34,pfVar6 + 0xc,pfVar6[0xf],
                       CONCAT22(uVar4,*(undefined2 *)(pfVar6 + 0x10)),puVar7 + 1);
          puVar7 = puVar7 + 8;
          pfVar6[6] = *pfVar6;
          pfVar6[7] = pfVar6[1];
          pfVar6[8] = pfVar6[2];
        }
        else {
          local_18 = *pfVar6 - pfVar6[6];
          local_14 = pfVar6[1] - pfVar6[7];
          local_10 = pfVar6[2] - pfVar6[8];
          if (pfVar6[4] <= _DAT_005a83e4) {
            fVar8 = (float10)FUN_00509d10();
            fVar8 = -fVar8;
            uVar4 = extraout_var_00;
          }
          else {
            fVar8 = (float10)FUN_00509d10();
            uVar4 = extraout_var;
          }
          local_34 = (float)fVar8;
          FUN_004b3e60(&local_18,local_34,pfVar6 + 0xc,pfVar6[0xf],
                       CONCAT22(uVar4,*(undefined2 *)(pfVar6 + 0x10)),puVar7 + 1);
          pfVar6[6] = *pfVar6;
          pfVar6[7] = pfVar6[1];
          pfVar6[8] = pfVar6[2];
          puVar7 = puVar7 + 7;
        }
        uVar1 = uVar1 + 1;
        param_3 = param_3 + 0x44;
        puVar3 = local_30;
      } while (uVar1 < (uint)(local_2c - (int)local_30 >> 2));
    }
  }
  local_4 = local_4 & 0xffffff00;
  iVar2 = local_28 - (int)puVar3 >> 2;
  if (iVar2 != 0) {
    uVar1 = iVar2 * 4;
    if (uVar1 < 0x81) {
      FUN_00402330();
      *puVar3 = *(undefined4 *)(&DAT_005d59a4 + (uVar1 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar1 + 7 >> 3) * 4) = puVar3;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(puVar3);
    }
  }
  iVar2 = (local_1c - local_24) / 0x44;
  local_4 = 0xffffffff;
  if (iVar2 != 0) {
    FUN_00402e90(local_24,iVar2 * 0x44);
  }
  ExceptionList = local_c;
  return puVar5;
}

