/* Original Meteor.exe static read-only source export; not executed. */

int __fastcall FUN_005498c0(int param_1)

{
  longlong lVar1;
  LARGE_INTEGER local_10;
  LARGE_INTEGER local_8;
  
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0x403e0000;
  *(undefined4 *)(param_1 + 0x18) = 0x9999999a;
  *(undefined4 *)(param_1 + 0x1c) = 0x3fc99999;
  *(undefined4 *)(param_1 + 0x44) = 1;
  QueryPerformanceFrequency(&local_10);
  QueryPerformanceCounter(&local_8);
  *(DWORD *)(param_1 + 0x20) = local_8.s.LowPart;
  *(LONG *)(param_1 + 0x24) = local_8.s.HighPart;
  *(DWORD *)(param_1 + 0x30) = local_8.s.LowPart;
  *(LONG *)(param_1 + 0x34) = local_8.s.HighPart;
  *(DWORD *)(param_1 + 0x38) = local_10.s.LowPart;
  *(LONG *)(param_1 + 0x3c) = local_10.s.HighPart;
  *(double *)(param_1 + 0x10) =
       (double)CONCAT44(local_10.s.HighPart,local_10.s.LowPart) / *(double *)(param_1 + 8);
  lVar1 = __ftol();
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(longlong *)(param_1 + 0x28) = lVar1 + CONCAT44(local_8.s.HighPart,local_8.s.LowPart);
  return param_1;
}

