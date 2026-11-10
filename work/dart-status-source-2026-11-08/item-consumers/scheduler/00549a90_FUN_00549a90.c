/* Original Meteor.exe static read-only source export; not executed. */

void __fastcall FUN_00549a90(int param_1)

{
  int iVar1;
  int iVar2;
  float10 extraout_ST0;
  undefined8 uVar3;
  LARGE_INTEGER local_10;
  LARGE_INTEGER local_8;
  
  QueryPerformanceCounter(&local_8);
  QueryPerformanceFrequency(&local_10);
  *(DWORD *)(param_1 + 0x38) = local_10.s.LowPart;
  *(LONG *)(param_1 + 0x3c) = local_10.s.HighPart;
  uVar3 = __ftol();
  *(undefined4 *)(param_1 + 0x40) = 0;
  iVar2 = local_8.s.LowPart - (uint)uVar3;
  iVar1 = (local_8.s.HighPart - (int)((ulonglong)uVar3 >> 0x20)) -
          (uint)(local_8.s.LowPart < (uint)uVar3);
  *(int *)(param_1 + 0x20) = iVar2;
  *(int *)(param_1 + 0x24) = iVar1;
  *(int *)(param_1 + 0x30) = iVar2;
  *(int *)(param_1 + 0x34) = iVar1;
  *(double *)(param_1 + 0x10) = (double)(extraout_ST0 / (float10)*(double *)(param_1 + 8));
  return;
}

