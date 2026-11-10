/* Original Meteor.exe static export @ 0056e870; original sample not executed. */
/* XREF 0056ee3f UNCONDITIONAL_CALL */
/* XREF 00566495 UNCONDITIONAL_CALL */
/* XREF 00588a73 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0056e870(LPCRITICAL_SECTION param_1,ULONG_PTR param_2)

{
  HANDLE *ppvVar1;
  float fVar2;
  float fVar3;
  HANDLE pvVar4;
  int *piVar5;
  PRTL_CRITICAL_SECTION_DEBUG p_Var6;
  int iVar7;
  int iVar8;
  int iVar9;
  ULONG_PTR *pUVar10;
  ULONG_PTR *pUVar11;
  float10 fVar12;
  
  EnterCriticalSection(param_1);
  param_1[1].SpinCount = param_2;
  fVar12 = (float10)FUN_004748b0();
  param_1[2].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)(float)fVar12;
  iVar9 = 0;
  param_1[2].LockCount = (LONG)(float)(fVar12 + (float10)(float)param_1[2].LockCount);
  if (fVar12 < (float10)_DAT_005a83e4) {
    param_1[2].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)0x0;
  }
  if (param_1[0xc].RecursionCount == 0) {
    iVar7 = FUN_00583c10();
    if (iVar7 != 0) {
      iVar7 = FUN_00583c10();
      pUVar10 = (ULONG_PTR *)(iVar7 + 0x16c);
      pUVar11 = &param_1[3].SpinCount;
      for (iVar8 = 0x10; iVar8 != 0; iVar8 = iVar8 + -1) {
        *pUVar11 = *pUVar10;
        pUVar10 = pUVar10 + 1;
        pUVar11 = pUVar11 + 1;
      }
    }
    (**(code **)(*(int *)param_1[0xc].OwningThread + 0x40))(param_2);
  }
  param_1[8].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)0x501502f9;
  param_1[7].SpinCount = 0x501502f9;
  param_1[7].LockSemaphore = (HANDLE)0x501502f9;
  param_1[8].OwningThread = (HANDLE)0xd01502f9;
  param_1[8].RecursionCount = -0x2feafd07;
  param_1[8].LockCount = -0x2feafd07;
  pvVar4 = param_1[2].LockSemaphore;
  *(undefined1 *)&param_1[6].OwningThread = 0;
  if (0 < (int)pvVar4) {
    do {
      piVar5 = *(int **)(param_1[3].LockCount + iVar9 * 4);
      fVar12 = (float10)FUN_00583560();
      if ((((fVar12 <= (float10)(float)param_1[1].OwningThread) &&
           (iVar7 = (**(code **)(*piVar5 + 0x40))(param_2), iVar7 != 0)) &&
          (iVar7 = piVar5[1], iVar7 != 2)) &&
         (((iVar7 != 10 && (iVar7 != 4)) && (((char)piVar5[9] == 'a' || ((char)piVar5[9] == 'A')))))
         ) {
        pvVar4 = param_1[7].LockSemaphore;
        *(undefined1 *)&param_1[6].OwningThread = 1;
        if ((float)piVar5[0x92] < (float)pvVar4) {
          param_1[7].LockSemaphore = (HANDLE)piVar5[0x92];
        }
        if ((float)piVar5[0x93] < (float)param_1[7].SpinCount) {
          param_1[7].SpinCount = piVar5[0x93];
        }
        if ((float)piVar5[0x94] < (float)param_1[8].DebugInfo) {
          param_1[8].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)piVar5[0x94];
        }
        if ((float)param_1[8].LockCount < (float)piVar5[0x95]) {
          param_1[8].LockCount = piVar5[0x95];
        }
        if ((float)param_1[8].RecursionCount < (float)piVar5[0x96]) {
          param_1[8].RecursionCount = piVar5[0x96];
        }
        if ((float)param_1[8].OwningThread < (float)piVar5[0x97]) {
          param_1[8].OwningThread = (HANDLE)piVar5[0x97];
        }
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < (int)param_1[2].LockSemaphore);
  }
  ppvVar1 = &param_1[8].LockSemaphore;
  param_1[1].LockSemaphore = (HANDLE)param_1[1].SpinCount;
  fVar2 = ((float)param_1[7].SpinCount + (float)param_1[8].RecursionCount) * _DAT_005a83e8;
  *ppvVar1 = (HANDLE)(((float)param_1[7].LockSemaphore + (float)param_1[8].LockCount) *
                     _DAT_005a83e8);
  p_Var6 = (PRTL_CRITICAL_SECTION_DEBUG)
           (((float)param_1[8].DebugInfo + (float)param_1[8].OwningThread) * _DAT_005a83e8);
  param_1[8].SpinCount = (ULONG_PTR)fVar2;
  param_1[9].DebugInfo = p_Var6;
  fVar2 = (float)param_1[8].RecursionCount;
  fVar3 = (float)param_1[8].SpinCount;
  pvVar4 = param_1[8].OwningThread;
  param_1[9].LockCount = (LONG)((float)param_1[8].LockCount - (float)*ppvVar1);
  param_1[9].RecursionCount = (LONG)(fVar2 - fVar3);
  param_1[9].OwningThread = (HANDLE)((float)pvVar4 - (float)param_1[9].DebugInfo);
  FUN_00477200();
  FUN_00477b90(3,ppvVar1);
  LeaveCriticalSection(param_1);
  return;
}

