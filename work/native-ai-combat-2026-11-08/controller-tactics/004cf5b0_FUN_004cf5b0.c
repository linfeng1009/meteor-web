/* Original Meteor.exe static export @ 004cf5b0; original sample not executed. */
/* XREF 005aa7b0 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004cf5b0(int *param_1,int param_2)

{
  float *pfVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iStack_c;
  
  if (param_1[4] != 0) {
    switch(param_1[0x37]) {
    case 0:
      iVar3 = (**(code **)(*param_1 + 0x80))(param_2);
      if (iVar3 != 0) {
        param_1[0x39] = 1;
        FUN_00549a90(0,0);
      }
      break;
    case 1:
    case 0xb:
      (**(code **)(*param_1 + 0x68))();
      fVar2 = _DAT_005aa93c;
      if (param_2 != 0) {
        fVar2 = _DAT_005aa940;
      }
      param_1[0xe6] = (int)fVar2;
      (**(code **)(*param_1 + 300))(0);
      param_1[0x39] = 1;
      FUN_00549a90(0,0);
      if (param_1[0xd3] == 0) {
        (**(code **)(*param_1 + 0xc))(7,&stack0x00000000,4);
      }
      return 0;
    case 2:
      iVar3 = *param_1;
      uVar5 = 0;
      uVar4 = (**(code **)(iVar3 + 0x84))(0,0,0xbf800000);
      (**(code **)(iVar3 + 0x74))(uVar4);
      fVar2 = (float)param_1[0xe9] + _DAT_005a83f4;
      pfVar1 = (float *)(param_1 + 0xe4);
      *pfVar1 = (float)param_1[0xe7];
      param_1[0xe5] = param_1[0xe8];
      param_1[0xe6] = (int)fVar2;
      FUN_0047ec40(uVar4,uVar5,param_1[0xe7],param_1[0xe8]);
      fVar2 = _DAT_005aa93c;
      if (iStack_c != 0) {
        fVar2 = _DAT_005aa940;
      }
      *pfVar1 = fVar2 * *pfVar1;
      param_1[0xe5] = (int)(fVar2 * (float)param_1[0xe5]);
      param_1[0xe6] = (int)(fVar2 * (float)param_1[0xe6]);
      (**(code **)(*param_1 + 300))(0);
      param_1[0x39] = 1;
      FUN_00549a90(0,0);
      return 0;
    }
  }
  return 0xffffffff;
}

