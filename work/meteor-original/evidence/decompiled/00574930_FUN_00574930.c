/* Meteor.exe original x86 @ 00574930; function boundary recovered from direct vtable/code reference */
/* Caller: 004e830d */

undefined4 __thiscall FUN_00574930(int *param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  iVar2 = FUN_00509f8f(param_2,&DAT_005ca380);
  if (iVar2 == 0) {
    return 0;
  }
  FUN_0058e080(iVar2);
  FUN_0058c440();
  FUN_00509e57(iVar2);
  iVar2 = FUN_0058e0b0();
  if (iVar2 == 0) {
    piVar3 = (int *)FUN_0058cc30();
    piVar1 = param_1 + 2;
    if (piVar3 != piVar1) {
      iVar2 = piVar3[1];
      iVar4 = *piVar3;
      iVar6 = *piVar1;
      uVar8 = iVar2 - iVar4 >> 3;
      if ((uint)(param_1[4] - iVar6 >> 3) < uVar8) {
        iVar2 = FUN_00576930(uVar8,iVar4,iVar2);
        iVar4 = param_1[4] - *piVar1 >> 3;
        if (iVar4 != 0) {
          FUN_00402e90(*piVar1,iVar4 * 8);
        }
        *piVar1 = iVar2;
        param_1[4] = iVar2 + uVar8 * 8;
      }
      else {
        uVar7 = param_1[3] - iVar6 >> 3;
        if (uVar7 < uVar8) {
          FUN_004c6050(iVar4,iVar4 + uVar7 * 8,iVar6,param_2,0);
          FUN_004c6f20(*piVar3 + (param_1[3] - *piVar1 >> 3) * 8,piVar3[1],param_1[3],param_2);
        }
        else {
          FUN_004c6050(iVar4,iVar2,iVar6,param_2,0);
        }
      }
      param_1[3] = *piVar1 + uVar8 * 8;
    }
    piVar5 = (int *)FUN_0058cc40();
    piVar3 = param_1 + 5;
    if (piVar5 != piVar3) {
      iVar2 = piVar5[1];
      iVar4 = *piVar5;
      iVar6 = *piVar3;
      uVar8 = (iVar2 - iVar4) / 0x14;
      if ((uint)((param_1[7] - iVar6) / 0x14) < uVar8) {
        iVar6 = FUN_00576b90(uVar8,iVar4,iVar2);
        iVar2 = param_1[6];
        for (iVar4 = *piVar3; iVar4 != iVar2; iVar4 = iVar4 + 0x14) {
          FUN_004e8820(0);
        }
        iVar2 = (param_1[7] - *piVar3) / 0x14;
        if (iVar2 != 0) {
          FUN_00402e90(*piVar3,iVar2 * 0x14);
        }
        *piVar3 = iVar6;
        param_1[7] = iVar6 + uVar8 * 0x14;
      }
      else {
        uVar7 = (param_1[6] - iVar6) / 0x14;
        if (uVar7 < uVar8) {
          FUN_00576f00(iVar4,iVar4 + uVar7 * 0x14,iVar6);
          FUN_005775a0(*piVar5 + ((param_1[6] - *piVar3) / 0x14) * 0x14,piVar5[1],param_1[6],uVar8);
        }
        else {
          iVar4 = FUN_00577220(iVar4,iVar2,iVar6,uVar8,0);
          iVar2 = param_1[6];
          for (; iVar4 != iVar2; iVar4 = iVar4 + 0x14) {
            FUN_004e8820(0);
          }
        }
      }
      param_1[6] = *piVar3 + uVar8 * 0x14;
    }
    *param_1 = param_1[3] - *piVar1 >> 3;
    param_1[1] = (param_1[6] - *piVar3) / 0x14;
    return 1;
  }
  FUN_0050ac20(s_Load__s_fail_005d18d8,param_2);
  return 0;
}

