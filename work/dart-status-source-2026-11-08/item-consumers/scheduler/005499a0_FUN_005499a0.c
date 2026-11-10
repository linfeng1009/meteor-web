/* Original Meteor.exe static read-only source export; not executed. */

int __thiscall FUN_005499a0(LARGE_INTEGER *param_1,LARGE_INTEGER *param_2)

{
  LARGE_INTEGER LVar1;
  LONG LVar2;
  int iVar3;
  longlong lVar4;
  
  if (param_1[8].s.LowPart != 0) {
    if (param_2 != (LARGE_INTEGER *)0x0) {
      (param_2->s).LowPart = 0;
      (param_2->s).HighPart = 0;
    }
    return 0;
  }
  QueryPerformanceCounter(param_1);
  if (param_2 != (LARGE_INTEGER *)0x0) {
    LVar1.QuadPart =
         (double)CONCAT44(((param_1->s).HighPart - *(int *)((int)param_1 + 0x24)) -
                          (uint)((param_1->s).LowPart < param_1[4].s.LowPart),
                          (param_1->s).LowPart - param_1[4].s.LowPart) /
         (double)(longlong)param_1[7];
    param_2->QuadPart = (LONGLONG)LVar1;
    if (param_1[3].QuadPart <= LVar1.QuadPart) {
      LVar1 = param_1[3];
    }
    param_2->QuadPart = (LONGLONG)LVar1;
    LVar2 = (param_1->s).HighPart;
    param_1[4].s.LowPart = (param_1->s).LowPart;
    *(LONG *)((int)param_1 + 0x24) = LVar2;
    param_1[6].s.LowPart = (param_1->s).LowPart;
    *(LONG *)((int)param_1 + 0x34) = LVar2;
  }
  LVar1.s = *(_struct_19 *)(param_1 + 5);
  iVar3 = 0;
  if ((*(int *)((int)param_1 + 0x2c) <= (param_1->s).HighPart) &&
     ((*(int *)((int)param_1 + 0x2c) < (param_1->s).HighPart ||
      (param_1[5].s.LowPart <= (param_1->s).LowPart)))) {
    lVar4 = __ftol();
    param_1[5] = (LARGE_INTEGER)(lVar4 + LVar1.s);
    iVar3 = 1;
    if (*(int *)((int)param_1 + 0x44) != 0) {
      while( true ) {
        if (((param_1->s).HighPart < *(int *)((int)param_1 + 0x2c)) ||
           (((param_1->s).HighPart <= *(int *)((int)param_1 + 0x2c) &&
            ((param_1->s).LowPart < param_1[5].s.LowPart)))) break;
        param_1[5] = (LARGE_INTEGER)(lVar4 + *(_struct_19 *)(param_1 + 5));
        iVar3 = iVar3 + 1;
      }
    }
  }
  return iVar3;
}

