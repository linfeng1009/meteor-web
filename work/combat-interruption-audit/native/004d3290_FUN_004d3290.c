/* Original Meteor.exe static export @ 004d3290; original sample not executed. */
/* XREF 004d2e79 UNCONDITIONAL_CALL */

void __thiscall FUN_004d3290(uint *param_1,undefined4 *param_2,undefined4 *param_3,int *param_4)

{
  undefined4 *puVar1;
  uint uVar2;
  uint *puVar3;
  undefined4 uVar4;
  LONG LVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 *puVar9;
  int *piVar10;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  int *local_20;
  uint local_1c;
  uint local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  uVar2 = (uint)param_3;
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a1c70;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_14 = &stack0xffffffc4;
  if (param_3 != (undefined4 *)0x0) {
    uVar7 = param_1[1];
    if ((uint)((int)(param_1[2] - uVar7) / 0xc) < param_3) {
      local_18 = (int)(uVar7 - *param_1) / 0xc;
      puVar3 = (uint *)&param_3;
      if (param_3 <= local_18) {
        puVar3 = &local_18;
      }
      local_18 = *puVar3 + local_18;
      if (local_18 == 0) {
        param_3 = (undefined4 *)0x0;
      }
      else {
        param_3 = (undefined4 *)FUN_00402bf0(local_18 * 0xc);
      }
      local_8 = 0;
      uVar4 = FUN_004f4800(*param_1,param_2,param_3,param_2);
      uVar4 = FUN_004d48b0(uVar4,uVar2,param_4,param_2);
      local_24 = FUN_004f4800(param_2,param_1[1],uVar4,param_2);
      for (uVar2 = *param_1; uVar2 != param_1[1]; uVar2 = uVar2 + 0xc) {
      }
      piVar10 = (int *)*param_1;
      iVar6 = (int)(param_1[2] - (int)piVar10) / 0xc;
      if (iVar6 != 0) {
        uVar2 = iVar6 * 0xc;
        param_4 = piVar10;
        if (uVar2 < 0x81) {
          local_20 = (int *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
          LVar5 = InterlockedExchange(&DAT_005d59e8,1);
          uVar2 = DAT_005c4248;
          if (LVar5 != 0) {
            uVar7 = 0;
            local_1c = DAT_005d59ec;
            if (DAT_005c4248 != 0) {
              do {
                if (((local_1c >> 1 <= uVar7) && (DAT_005d59e8 == 0)) &&
                   (LVar5 = InterlockedExchange(&DAT_005d59e8,1), LVar5 == 0)) {
                  DAT_005c4248 = 1000;
                  piVar10 = param_4;
                  DAT_005d59ec = uVar7;
                  goto LAB_004d35f7;
                }
                uVar7 = uVar7 + 1;
              } while (uVar7 < uVar2);
            }
            DAT_005c4248 = 0x1e;
            iVar6 = 0;
            while( true ) {
              iVar8 = iVar6 + 6;
              if (0x1b < iVar8) {
                iVar8 = 0x1b;
              }
              LVar5 = InterlockedExchange(&DAT_005d59e8,1);
              piVar10 = param_4;
              if (LVar5 == 0) break;
              if (iVar8 < 0x15) {
                Sleep(0);
                iVar6 = iVar6 + 1;
              }
              else {
                Sleep(1 << ((char)iVar8 - 0x14U & 0x1f));
                iVar6 = iVar6 + 1;
              }
            }
          }
LAB_004d35f7:
          *piVar10 = *local_20;
          *local_20 = (int)piVar10;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(piVar10);
        }
      }
      *param_1 = (uint)param_3;
      param_1[1] = local_24;
      param_1[2] = (int)param_3 + local_18 * 0xc;
      *unaff_FS_OFFSET = local_10;
      return;
    }
    puVar9 = (undefined4 *)param_1[1];
    local_30 = *param_4;
    local_2c = param_4[1];
    local_28 = param_4[2];
    uVar7 = (int)(uVar7 - (int)param_2) / 0xc;
    if (param_3 < uVar7) {
      iVar6 = (int)param_3 * 0xc;
      param_3 = puVar9 + (int)param_3 * -3;
      FUN_004f4800(param_3,puVar9,puVar9,param_2);
      param_1[1] = param_1[1] + iVar6;
      uVar7 = ((int)param_3 - (int)param_2) / 0xc;
      puVar1 = param_3;
      param_3 = (undefined4 *)uVar7;
      if (0 < (int)uVar7) {
        do {
          puVar9[-3] = puVar1[-3];
          puVar9[-2] = puVar1[-2];
          puVar9[-1] = puVar1[-1];
          param_3 = (undefined4 *)((int)param_3 - 1);
          puVar1 = puVar1 + -3;
          puVar9 = puVar9 + -3;
        } while (param_3 != (undefined4 *)0x0);
      }
      puVar9 = param_2 + uVar2 * 3;
      for (; param_2 != puVar9; param_2 = param_2 + 3) {
        *param_2 = local_30;
        param_2[1] = local_2c;
        param_2[2] = local_28;
      }
    }
    else {
      iVar6 = (int)param_3 - uVar7;
      param_3 = (undefined4 *)uVar7;
      FUN_004d48b0(puVar9,iVar6,&local_30,param_2);
      uVar2 = param_1[1] + iVar6 * 0xc;
      param_1[1] = uVar2;
      FUN_004f4800(param_2,puVar9,uVar2,param_2);
      param_1[1] = param_1[1] + (int)param_3 * 0xc;
      if (param_2 != puVar9) {
        do {
          puVar1 = param_2 + 3;
          *param_2 = local_30;
          param_2[1] = local_2c;
          param_2[2] = local_28;
          param_2 = puVar1;
        } while (puVar1 != puVar9);
        *unaff_FS_OFFSET = local_10;
        return;
      }
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

