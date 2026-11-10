/* Original Meteor.exe static export @ 0054b500; original sample not executed. */
/* XREF 004b7823 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0054b500(int param_1,float param_2,undefined4 param_3)

{
  bool bVar1;
  
  bVar1 = _DAT_005a83e4 <= param_2;
  *(undefined1 *)(param_1 + 0xf8) = 1;
  if (bVar1) {
    if (_DAT_005a83f4 < param_2) {
      param_2 = 1.0;
    }
  }
  else {
    param_2 = 0.0;
  }
  *(undefined4 *)(param_1 + 0xf4) = param_3;
  *(float *)(param_1 + 0xf0) = param_2;
  FUN_00554650(param_2);
  return;
}

