/* Original Meteor.exe read-only export. Sample not executed. */

undefined4 FUN_004fa030(undefined4 param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  undefined4 *local_18;
  undefined4 *local_14;
  undefined4 *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a3a80;
  local_c = ExceptionList;
  local_18 = (undefined4 *)0x0;
  local_14 = (undefined4 *)0x0;
  local_10 = (undefined4 *)0x0;
  ExceptionList = &local_c;
  local_18 = (undefined4 *)FUN_00402bf0(8);
  local_10 = local_18 + 2;
  local_4 = 2;
  local_14 = local_18;
  FUN_00402a70();
  local_4 = 3;
  FUN_004f9690(param_1,0,&local_18);
  puVar2 = local_18;
  uVar3 = (int)local_10 - (int)local_18;
  if ((local_18 != (undefined4 *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
      iVar4 = FUN_00443110(&DAT_005d59e8,1);
      uVar1 = DAT_005c4248;
      if (iVar4 != 0) {
        uVar7 = 0;
        if (DAT_005c4248 != 0) {
          uVar6 = DAT_005d59ec >> 1;
          do {
            if (((uVar6 <= uVar7) && (DAT_005d59e8 == 0)) &&
               (iVar4 = FUN_00443110(&DAT_005d59e8,1), iVar4 == 0)) {
              DAT_005c4248 = 1000;
              DAT_005d59ec = uVar7;
              goto LAB_004fa1c4;
            }
            uVar7 = uVar7 + 1;
          } while (uVar7 < uVar1);
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
LAB_004fa1c4:
      *puVar2 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puVar2;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(local_18);
    }
  }
  ExceptionList = local_c;
  return 1;
}

