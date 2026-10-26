/* Original Meteor.exe static export @ 0056db90; original sample not executed. */
/* XREF 00566cc7 UNCONDITIONAL_CALL */
/* XREF 0056628f UNCONDITIONAL_CALL */

LPCRITICAL_SECTION __fastcall FUN_0056db90(LPCRITICAL_SECTION param_1)

{
  void *pvVar1;
  HANDLE pvVar2;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_005a5af6;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  param_1[3].LockCount = 0;
  param_1[3].RecursionCount = 0;
  param_1[3].OwningThread = (HANDLE)0x0;
  local_4 = 0;
  pvVar1 = operator_new(0x928);
  local_4._0_1_ = 1;
  if (pvVar1 == (void *)0x0) {
    pvVar2 = (HANDLE)0x0;
  }
  else {
    pvVar2 = (HANDLE)FUN_005838f0(param_1,1);
  }
  local_4 = (uint)local_4._1_3_ << 8;
  param_1[0xc].OwningThread = pvVar2;
  param_1[0xc].RecursionCount = 0;
  param_1[3].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)0x0;
  param_1[2].SpinCount = 0;
  *(undefined1 *)&param_1[3].LockSemaphore = 0;
  *(undefined1 *)&param_1[2].OwningThread = 0;
  *(undefined1 *)((int)&param_1[2].OwningThread + 1) = 0;
  *(undefined1 *)((int)&param_1[3].LockSemaphore + 1) = 0;
  *(undefined1 *)((int)&param_1[2].OwningThread + 2) = 0;
  param_1[1].RecursionCount = 0;
  param_1[1].OwningThread = (HANDLE)0x0;
  param_1[1].LockCount = 0;
  param_1[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)0x0;
  param_1[2].RecursionCount = 0;
  param_1[2].LockCount = 0;
  param_1[2].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)0x0;
  param_1[2].LockSemaphore = (HANDLE)0x0;
  FUN_00477200();
  InitializeCriticalSection(param_1);
  ExceptionList = local_c;
  return param_1;
}

