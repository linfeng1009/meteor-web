/* Original Meteor.exe static export @ 0055d560; original sample not executed. */
/* XREF 0055d942 UNCONDITIONAL_CALL */
/* XREF 0055d790 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_0055d560(int *param_1,float param_2)

{
  float fVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  
  param_1[0x192] = 0;
  switch(param_1[400]) {
  case 0:
    fVar3 = param_2 + (float)param_1[0x3e];
    iVar5 = param_1[0x18e];
    param_1[0x3e] = (int)fVar3;
    fVar1 = (float)param_1[0x181];
    param_1[0x181] = (int)((float)param_1[0x42] + fVar1);
    iVar4 = *(int *)(iVar5 + 0x44);
    if ((iVar4 < 1) || (param_1[0x177] <= iVar4)) {
      if ((_DAT_005ae1d4 <= (float)param_1[0x182]) &&
         ((float)param_1[0x182] <= (float)param_1[0x42] + fVar1)) {
        if (param_1[0x17d] != 0) {
          param_1[400] = 1;
          FUN_0055d560(0);
          return 1;
        }
        param_1[400] = 4;
        iVar5 = *param_1;
        param_1[0x3e] = (int)(fVar3 - param_2);
        uVar6 = __ftol();
        (**(code **)(iVar5 + 0x14))(uVar6);
        return 1;
      }
      if ((float)*(int *)(iVar5 + 0x20) < fVar3) {
        param_1[0x3e] = (int)(float)*(int *)(iVar5 + 0x1c);
      }
    }
    else if ((float)*(int *)(iVar5 + 0x18) < fVar3) {
      iVar2 = param_1[0x18b];
      FUN_00559720(*(undefined4 *)(iVar5 + 0x50));
      if ((*(int *)(iVar2 + iVar4 * 0xac + 0x1c) == -1) || (*(char *)((int)param_1 + 0x616) == '\0')
         ) {
        iVar5 = param_1[0x182];
        uVar6 = 0;
      }
      else {
        iVar5 = param_1[0x182];
        uVar6 = 3;
      }
      FUN_0055d260(*(undefined4 *)(param_1[0x18e] + 0x44),uVar6,1,iVar5,0);
      return 1;
    }
    (**(code **)(*param_1 + 0x10))(param_1[0x3e]);
    return 1;
  case 1:
    fVar1 = (float)param_1[0x3e];
    iVar4 = param_1[0x18e];
    param_1[0x3e] = (int)(param_2 + fVar1);
    iVar5 = *(int *)(iVar4 + 0x18);
    if ((float)iVar5 <= param_2 + fVar1) {
      iVar2 = *(int *)(iVar4 + 0x44);
      if ((0 < iVar2) && (iVar2 < param_1[0x177])) {
        iVar5 = param_1[0x18b];
        FUN_00559720(*(undefined4 *)(iVar4 + 0x50));
        if ((*(int *)(iVar5 + iVar2 * 0xac + 0x1c) != -1) &&
           (*(char *)((int)param_1 + 0x616) != '\0')) {
          FUN_0055d260(*(undefined4 *)(param_1[0x18e] + 0x44),1,1,0xc0a00000,0);
          return 1;
        }
        FUN_0055d260(*(undefined4 *)(param_1[0x18e] + 0x44),param_1[0x17f] & 8,1,0xc0a00000,0);
        return 1;
      }
      param_1[400] = 4;
      param_1[0x3e] = (int)(float)iVar5;
    }
    (**(code **)(*param_1 + 0x10))(param_1[0x3e]);
    return 1;
  case 2:
    fVar1 = (float)param_1[0x3e];
    param_1[0x3e] = (int)(param_2 + fVar1);
    if ((float)param_1[0x4c] < param_2 + fVar1) {
      param_1[0x3e] = (int)(float)param_1[0x4c];
    }
    iVar5 = __ftol();
    param_1[0x3f] = iVar5;
    iVar4 = FUN_0055c4f0(iVar5);
    if ((*(char *)(iVar4 + 4) == '\0') && (iVar5 < *(int *)(param_1[0x18e] + 0x18))) {
      (**(code **)(*param_1 + 0x10))(param_1[0x3e]);
      return 1;
    }
    param_1[0x192] = 1;
    FUN_0055d450(param_1[0x189]);
    param_1[0x189] = -1;
    return 1;
  case 3:
    break;
  case 4:
    param_1[0x17c] = 0;
    param_1[0x188] = 1;
    (**(code **)(*param_1 + 0x10))(param_1[0x3e]);
    return 1;
  default:
    return 1;
  }
  if (param_1[0x17b] == 0) {
    param_1[0x17b] = 1;
    FUN_00559700();
    FUN_00559750();
    return 1;
  }
  iVar5 = FUN_00559750();
  if (iVar5 != 0) {
    return 1;
  }
  param_1[400] = (uint)(param_1[0x179] == 0);
  (**(code **)(*param_1 + 0x14))(param_1[0x45]);
  FUN_0055d1e0(param_1[0x18e]);
  return 1;
}

