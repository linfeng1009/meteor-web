/* Original Meteor.exe static export @ 0056dc50; original sample not executed. */
/* XREF 00566260 UNCONDITIONAL_CALL */
/* XREF 005661e0 UNCONDITIONAL_CALL */

void __fastcall FUN_0056dc50(LPCRITICAL_SECTION param_1)

{
  uint uVar1;
  int *piVar2;
  uint uVar3;
  LONG LVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005a5b0b;
  pvStack_c = ExceptionList;
  local_4 = 0;
  ExceptionList = &pvStack_c;
  if (param_1[0xc].OwningThread != (int *)0x0) {
    ExceptionList = &pvStack_c;
    (**(code **)(*(int *)param_1[0xc].OwningThread + 0x24))(1);
    param_1[0xc].OwningThread = (HANDLE)0x0;
  }
  iVar8 = 0;
  if (0 < (int)param_1[2].LockSemaphore) {
    do {
      piVar2 = *(int **)(param_1[3].LockCount + iVar8 * 4);
      if (piVar2 != (int *)0x0) {
        (**(code **)(*piVar2 + 0x24))(1);
        *(undefined4 *)(param_1[3].LockCount + iVar8 * 4) = 0;
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < (int)param_1[2].LockSemaphore);
  }
  DeleteCriticalSection(param_1);
  piVar2 = (int *)param_1[3].LockCount;
  iVar8 = (int)param_1[3].OwningThread - (int)piVar2 >> 2;
  if (iVar8 != 0) {
    uVar1 = iVar8 * 4;
    if (0x80 < uVar1) {
      FUN_005089fd(piVar2);
      ExceptionList = pvStack_c;
      return;
    }
    LVar4 = InterlockedExchange(&DAT_005d59e8,1);
    uVar3 = DAT_005c4248;
    if (LVar4 != 0) {
      uVar6 = 0;
      if (DAT_005c4248 != 0) {
        uVar5 = DAT_005d59ec >> 1;
        do {
          if (((uVar5 <= uVar6) && (DAT_005d59e8 == 0)) &&
             (LVar4 = InterlockedExchange(&DAT_005d59e8,1), LVar4 == 0)) {
            DAT_005c4248 = 1000;
            DAT_005d59ec = uVar6;
            goto LAB_0056ddff;
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < uVar3);
      }
      DAT_005c4248 = 0x1e;
      iVar8 = 6;
      while( true ) {
        iVar7 = iVar8;
        if (0x1b < iVar8) {
          iVar7 = 0x1b;
        }
        LVar4 = InterlockedExchange(&DAT_005d59e8,1);
        if (LVar4 == 0) break;
        if (iVar7 < 0x15) {
          Sleep(0);
          iVar8 = iVar8 + 1;
        }
        else {
          Sleep(1 << ((char)iVar7 - 0x14U & 0x1f));
          iVar8 = iVar8 + 1;
        }
      }
    }
LAB_0056ddff:
    *piVar2 = *(int *)(&DAT_005d59a4 + (uVar1 + 7 >> 3) * 4);
    *(int **)(&DAT_005d59a4 + (uVar1 + 7 >> 3) * 4) = piVar2;
    DAT_005d59e8 = 0;
  }
  ExceptionList = pvStack_c;
  return;
}

