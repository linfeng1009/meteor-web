/* Original Meteor.exe static export @ 004cada0; original sample not executed. */
/* XREF 004cad83 UNCONDITIONAL_CALL */

void __fastcall FUN_004cada0(undefined4 *param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a1994;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005aa6a8;
  local_4 = 2;
  if (param_1[0x3a] != 0) {
    FUN_00507850(param_1[0x3a]);
  }
  FUN_004d0f60();
  piVar1 = (int *)param_1[0xbd];
  uVar3 = param_1[0xbf] - (int)piVar1;
  local_4._0_1_ = 1;
  if ((piVar1 != (int *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
      FUN_00402330();
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  piVar1 = (int *)param_1[0xba];
  uVar3 = param_1[0xbc] - (int)piVar1;
  local_4 = (uint)local_4._1_3_ << 8;
  if ((piVar1 != (int *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
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
              goto LAB_004caf79;
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
LAB_004caf79:
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  local_4 = 0xffffffff;
  FUN_00502e00();
  ExceptionList = local_c;
  return;
}

