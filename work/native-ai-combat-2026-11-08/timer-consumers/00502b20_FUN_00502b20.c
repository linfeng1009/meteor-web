/* Original Meteor.exe read-only export. Sample not executed. */

void __fastcall FUN_00502b20(undefined4 *param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  LONG LVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = ExceptionList;
  puStack_8 = &LAB_005a3fd8;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005aa658;
  iVar8 = param_1[7];
  iVar6 = param_1[6];
  local_4 = 0;
  for (; iVar6 != iVar8; iVar6 = iVar6 + 8) {
    FUN_004e8500();
  }
  piVar2 = (int *)param_1[6];
  iVar8 = param_1[8] - (int)piVar2 >> 3;
  if (iVar8 != 0) {
    uVar1 = iVar8 * 8;
    if (0x80 < uVar1) {
      FUN_005089fd(piVar2);
      ExceptionList = local_c;
      return;
    }
    LVar4 = InterlockedExchange(&DAT_005d59e8,1);
    uVar3 = DAT_005c4248;
    if (LVar4 != 0) {
      uVar7 = 0;
      if (DAT_005c4248 != 0) {
        uVar5 = DAT_005d59ec >> 1;
        do {
          if (((uVar5 <= uVar7) && (DAT_005d59e8 == 0)) &&
             (LVar4 = InterlockedExchange(&DAT_005d59e8,1), LVar4 == 0)) {
            DAT_005c4248 = 1000;
            DAT_005d59ec = uVar7;
            goto LAB_00502ca8;
          }
          uVar7 = uVar7 + 1;
        } while (uVar7 < uVar3);
      }
      DAT_005c4248 = 0x1e;
      iVar8 = 6;
      while( true ) {
        iVar6 = iVar8;
        if (0x1b < iVar8) {
          iVar6 = 0x1b;
        }
        LVar4 = InterlockedExchange(&DAT_005d59e8,1);
        if (LVar4 == 0) break;
        if (iVar6 < 0x15) {
          Sleep(0);
          iVar8 = iVar8 + 1;
        }
        else {
          Sleep(1 << ((char)iVar6 - 0x14U & 0x1f));
          iVar8 = iVar8 + 1;
        }
      }
    }
LAB_00502ca8:
    *piVar2 = *(int *)(&DAT_005d59a4 + (uVar1 + 7 >> 3) * 4);
    *(int **)(&DAT_005d59a4 + (uVar1 + 7 >> 3) * 4) = piVar2;
    DAT_005d59e8 = 0;
  }
  ExceptionList = local_c;
  return;
}

