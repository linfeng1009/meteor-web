/* Original Meteor.exe static export @ 00566020; original sample not executed. */
/* XREF 00566003 UNCONDITIONAL_CALL */

void __fastcall FUN_00566020(undefined4 *param_1)

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
  uint local_4;
  
  puStack_8 = &LAB_005a57b6;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_LAB_005ae1f4;
  local_4 = 1;
  FUN_005661d0();
  piVar1 = (int *)param_1[0x48];
  uVar3 = param_1[0x4a] - (int)piVar1;
  local_4 = local_4 & 0xffffff00;
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
              goto LAB_0056618b;
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
LAB_0056618b:
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  local_4 = 0xffffffff;
  FUN_0047b570();
  ExceptionList = local_c;
  return;
}

