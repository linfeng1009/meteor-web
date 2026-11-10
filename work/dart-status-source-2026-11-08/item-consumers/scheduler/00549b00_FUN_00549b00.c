/* Original Meteor.exe static read-only source export; not executed. */

float10 __fastcall FUN_00549b00(int param_1)

{
  LARGE_INTEGER local_8;
  
  QueryPerformanceCounter(&local_8);
  if (*(int *)(param_1 + 0x40) != 0) {
    return (float10)CONCAT44((*(int *)(param_1 + 0x34) - *(int *)(param_1 + 0x24)) -
                             (uint)(*(uint *)(param_1 + 0x30) < *(uint *)(param_1 + 0x20)),
                             *(uint *)(param_1 + 0x30) - *(uint *)(param_1 + 0x20)) /
           (float10)*(longlong *)(param_1 + 0x38);
  }
  return (float10)CONCAT44((local_8.s.HighPart - *(int *)(param_1 + 0x24)) -
                           (uint)(local_8.s.LowPart < *(uint *)(param_1 + 0x20)),
                           local_8.s.LowPart - *(uint *)(param_1 + 0x20)) /
         (float10)*(longlong *)(param_1 + 0x38);
}

