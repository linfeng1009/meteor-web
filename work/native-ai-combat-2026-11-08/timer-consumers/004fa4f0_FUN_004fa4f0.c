/* Original Meteor.exe read-only export. Sample not executed. */

void __fastcall FUN_004fa4f0(undefined4 *param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  *param_1 = &PTR_LAB_005ab82c;
  piVar1 = (int *)param_1[3];
  uVar3 = param_1[5] - (int)piVar1;
  if ((piVar1 != (int *)0x0) && (uVar3 != 0)) {
    if (0x80 < uVar3) {
      FUN_005089fd(piVar1);
      return;
    }
    iVar4 = FUN_00443110(&DAT_005d59e8,1);
    uVar2 = DAT_005c4248;
    if (iVar4 != 0) {
      uVar7 = 0;
      if (DAT_005c4248 != 0) {
        uVar6 = DAT_005d59ec >> 1;
        do {
          if (((uVar6 <= uVar7) && (DAT_005d59e8 == 0)) &&
             (iVar4 = FUN_00443110(&DAT_005d59e8,1), iVar4 == 0)) {
            DAT_005c4248 = 1000;
            DAT_005d59ec = uVar7;
            goto LAB_004fa61c;
          }
          uVar7 = uVar7 + 1;
        } while (uVar7 < uVar2);
      }
      DAT_005c4248 = 0x1e;
      iVar4 = 6;
      while( true ) {
        iVar8 = iVar4;
        if (0x1b < iVar4) {
          iVar8 = 0x1b;
        }
        iVar5 = FUN_00443110(&DAT_005d59e8,1);
        if (iVar5 == 0) break;
        FUN_00443130(iVar8);
        iVar4 = iVar4 + 1;
      }
    }
LAB_004fa61c:
    *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
    *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
    DAT_005d59e8 = 0;
  }
  return;
}

