/* Original Meteor.exe static export @ 004f4010; original sample not executed. */
/* XREF 005aa0d8 DATA */
/* XREF 005ab560 DATA */
/* XREF 005ab9a0 DATA */
/* XREF 005ab320 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004f4010(int *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  
  uVar1 = *param_2;
  uVar2 = param_2[3];
  fVar3 = (float)param_2[1] * _DAT_005a8410;
  uVar8 = (uint)*(ushort *)((int)param_2 + 2);
  fVar4 = (float)param_2[2] * _DAT_005a8410;
  piVar5 = (int *)(**(code **)(*param_1 + 0x44))();
  iVar6 = (**(code **)(*piVar5 + 0x11c))(uVar1 & 0xffff,fVar3,fVar4);
  if (iVar6 != 0) {
    param_1[0xd8] = 1;
    param_1[0xd9] = uVar8;
    if ((0x59 < uVar8) && (uVar8 < 0x76)) {
      piVar5 = (int *)FUN_00487830();
      iVar6 = *piVar5;
      uVar7 = (**(code **)(*param_1 + 0x4c))((uVar8 - 0x3e) + uVar2 * 0x38,0,0);
      (**(code **)(iVar6 + 0x20c))(uVar7);
    }
  }
  return 0;
}

