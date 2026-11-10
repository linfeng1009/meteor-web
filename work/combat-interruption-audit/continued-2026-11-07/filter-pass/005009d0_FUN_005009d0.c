/* Original Meteor.exe static export @ 005009d0; original sample not executed. */
/* XREF 005009b3 UNCONDITIONAL_CALL */

void __fastcall FUN_005009d0(undefined4 *param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a3f74;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005ab8a8;
  param_1[4] = &PTR_LAB_005ab878;
  local_4 = 2;
  FUN_004f8900();
  piVar1 = (int *)param_1[0x109];
  uVar3 = param_1[0x10b] - (int)piVar1;
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
  piVar1 = (int *)param_1[0x106];
  uVar3 = param_1[0x108] - (int)piVar1;
  local_4 = (uint)local_4._1_3_ << 8;
  if ((piVar1 != (int *)0x0) && (uVar3 != 0)) {
    if (uVar3 < 0x81) {
      iVar4 = FUN_00443110(&DAT_005d59e8,1);
      uVar2 = DAT_005c4248;
      if (iVar4 != 0) {
        uVar8 = 0;
        if (DAT_005c4248 != 0) {
          uVar6 = DAT_005d59ec >> 1;
          do {
            if (((uVar6 <= uVar8) && (DAT_005d59e8 == 0)) &&
               (iVar4 = FUN_00443110(&DAT_005d59e8,1), iVar4 == 0)) {
              DAT_005c4248 = 1000;
              DAT_005d59ec = uVar8;
              goto LAB_00500b9e;
            }
            uVar8 = uVar8 + 1;
          } while (uVar8 < uVar2);
        }
        DAT_005c4248 = 0x1e;
        iVar4 = 6;
        while( true ) {
          iVar7 = iVar4;
          if (0x1b < iVar4) {
            iVar7 = 0x1b;
          }
          iVar5 = FUN_00443110(&DAT_005d59e8,1);
          if (iVar5 == 0) break;
          FUN_00443130(iVar7);
          iVar4 = iVar4 + 1;
        }
      }
LAB_00500b9e:
      *piVar1 = *(int *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = piVar1;
      DAT_005d59e8 = 0;
    }
    else {
      FUN_005089fd(piVar1);
    }
  }
  local_4 = 0xffffffff;
  FUN_004ecc00();
  ExceptionList = local_c;
  return;
}

