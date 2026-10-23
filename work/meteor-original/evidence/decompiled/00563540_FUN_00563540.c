/* Decompiled from user's Meteor.exe; address: 00563540 */
/* String anchors: [%s%s.gmc, %s%s.gmb] */

int * __thiscall FUN_00563540(int param_1,int param_2,int param_3)

{
  byte bVar1;
  void *pvVar2;
  int *piVar3;
  byte *pbVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  byte *pbVar8;
  bool bVar9;
  int local_90;
  undefined1 local_8c [128];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a566e;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  pvVar2 = operator_new(0x1d0);
  local_4 = 0;
  if (pvVar2 == (void *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = (int *)FUN_005678a0();
  }
  iVar7 = *(int *)(param_1 + 0x4b4);
  local_4 = 0xffffffff;
  local_90 = 0;
  if (0 < param_3) {
    do {
      pbVar4 = (byte *)(*(int *)(iVar7 + 0x28) + 0x48);
      pbVar8 = (byte *)(param_2 + 0x48);
      do {
        bVar1 = *pbVar8;
        bVar9 = bVar1 < *pbVar4;
        if (bVar1 != *pbVar4) {
LAB_005635e4:
          iVar5 = (1 - (uint)bVar9) - (uint)(bVar9 != 0);
          goto LAB_005635e9;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar8[1];
        bVar9 = bVar1 < pbVar4[1];
        if (bVar1 != pbVar4[1]) goto LAB_005635e4;
        pbVar8 = pbVar8 + 2;
        pbVar4 = pbVar4 + 2;
      } while (bVar1 != 0);
      iVar5 = 0;
LAB_005635e9:
      if (iVar5 == 0) {
        if (*(int *)(iVar7 + 0x2c) != 0) {
          FUN_0056b230(piVar3);
          ExceptionList = local_c;
          return piVar3;
        }
        if (piVar3 != (int *)0x0) {
          (**(code **)(*piVar3 + 8))(1);
        }
        ExceptionList = local_c;
        return (int *)0x0;
      }
      local_90 = local_90 + 1;
      iVar7 = iVar7 + 0xac;
    } while (local_90 < param_3);
  }
  param_2 = param_2 + 0x48;
  FUN_00508ae6(local_8c,s__s_s_gmb_005c9360,*(undefined4 *)(param_1 + 0x1d0),param_2);
  iVar7 = FUN_00568f80(local_8c,1);
  if (iVar7 == 0) {
    FUN_00508ae6(local_8c,s__s_s_gmc_005c9354,*(undefined4 *)(param_1 + 0x1d0),param_2);
    iVar7 = FUN_00568f80(local_8c,1);
    if (iVar7 == 0) {
      if (piVar3 == (int *)0x0) {
        ExceptionList = local_c;
        return (int *)0x0;
      }
      (**(code **)(*piVar3 + 8))(1);
      ExceptionList = local_c;
      return (int *)0x0;
    }
  }
  FUN_00508ae6(local_8c,s__s_s_des_005c9348,*(undefined4 *)(param_1 + 0x1d0),param_2);
  FUN_00569e10(local_8c);
  FUN_00508ae6(local_8c,s__s_s_fmc_005d15b0,*(undefined4 *)(param_1 + 0x1d0),param_2);
  iVar7 = FUN_005696a0(local_8c);
  if (iVar7 != 0) {
    FUN_00508ae6(local_8c,s__s_s_pos_005d15a4,*(undefined4 *)(param_1 + 0x1d0),param_2);
    iVar7 = FUN_00569b30(local_8c);
    if (iVar7 != 0) {
      *(undefined1 *)(piVar3 + 0x49) = 1;
    }
  }
  uVar6 = (*(code *)PTR_FUN_005d186c)(1,param_2,0);
  FUN_005679b0(0,uVar6);
  uVar6 = (*(code *)PTR_FUN_005d186c)(2,param_2,0);
  FUN_005679b0(1,uVar6);
  ExceptionList = local_c;
  return piVar3;
}

