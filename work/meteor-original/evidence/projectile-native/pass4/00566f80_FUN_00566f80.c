/* Original Meteor.exe static export @ 00566f80; original sample not executed. */
/* XREF 005671f2 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00566f80(int param_1)

{
  void **ppvVar1;
  int *piVar2;
  int *piVar3;
  LONG LVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  float10 fVar12;
  int local_24;
  undefined4 *local_20;
  undefined4 *local_1c;
  undefined4 *local_18;
  int *local_14;
  int *local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a58a8;
  local_c = ExceptionList;
  if (*(float *)(param_1 + 0x20) < _DAT_005a83f4) {
    ExceptionList = &local_c;
    fVar12 = (float10)FUN_004748b0();
    *(float *)(param_1 + 0x20) = (float)(fVar12 + (float10)*(float *)(param_1 + 0x20));
    ExceptionList = local_c;
    return;
  }
  local_1c = (undefined4 *)0x0;
  piVar2 = (int *)0x0;
  piVar9 = (int *)0x0;
  local_18 = (undefined4 *)0x0;
  local_14 = (int *)0x0;
  local_10 = (int *)0x0;
  local_4 = 0;
  piVar6 = (int *)**(int **)(param_1 + 0x10);
  ExceptionList = &local_c;
  ppvVar1 = &local_c;
  if (piVar6 != *(int **)(param_1 + 0x10)) {
    do {
      local_24 = piVar6[2];
      if ((*(char *)(local_24 + 0x139) != '\0') && (*(int *)(local_24 + 0x140) == 1)) {
        if (piVar2 == piVar9) {
          FUN_0055e370(piVar2,&local_24);
          piVar2 = local_14;
          local_1c = local_18;
          piVar9 = local_10;
        }
        else {
          piVar3 = (int *)0x0;
          if (piVar2 != (int *)0x0) {
            *piVar2 = local_24;
            piVar3 = local_14;
            local_1c = local_18;
            piVar9 = local_10;
          }
          local_14 = piVar3 + 1;
          piVar2 = local_14;
        }
      }
      piVar6 = (int *)*piVar6;
      ppvVar1 = ExceptionList;
    } while (piVar6 != (int *)*(int *)(param_1 + 0x10));
  }
  ExceptionList = ppvVar1;
  uVar7 = 0;
  if ((int)piVar2 - (int)local_1c >> 2 != 0) {
    do {
      FUN_00566e50(local_1c[uVar7]);
      uVar7 = uVar7 + 1;
      local_1c = local_18;
      piVar9 = local_10;
    } while (uVar7 < (uint)((int)local_14 - (int)local_18 >> 2));
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  iVar10 = (int)piVar9 - (int)local_1c >> 2;
  local_4 = 0xffffffff;
  if (iVar10 != 0) {
    uVar7 = iVar10 * 4;
    if (0x80 < uVar7) {
      FUN_005089fd(local_1c);
      ExceptionList = local_c;
      return;
    }
    local_20 = (undefined4 *)(&DAT_005d59a4 + (uVar7 + 7 >> 3) * 4);
    LVar4 = InterlockedExchange(&DAT_005d59e8,1);
    uVar7 = DAT_005c4248;
    if (LVar4 != 0) {
      uVar8 = 0;
      if (DAT_005c4248 != 0) {
        uVar5 = DAT_005d59ec >> 1;
        do {
          if (((uVar5 <= uVar8) && (DAT_005d59e8 == 0)) &&
             (LVar4 = InterlockedExchange(&DAT_005d59e8,1), LVar4 == 0)) {
            DAT_005c4248 = 1000;
            DAT_005d59ec = uVar8;
            goto LAB_0056719d;
          }
          uVar8 = uVar8 + 1;
        } while (uVar8 < uVar7);
      }
      DAT_005c4248 = 0x1e;
      iVar10 = 6;
      while( true ) {
        iVar11 = iVar10;
        if (0x1b < iVar10) {
          iVar11 = 0x1b;
        }
        LVar4 = InterlockedExchange(&DAT_005d59e8,1);
        if (LVar4 == 0) break;
        FUN_00443130(iVar11);
        iVar10 = iVar10 + 1;
      }
    }
LAB_0056719d:
    *local_1c = *local_20;
    *local_20 = local_1c;
    DAT_005d59e8 = 0;
  }
  ExceptionList = local_c;
  return;
}

