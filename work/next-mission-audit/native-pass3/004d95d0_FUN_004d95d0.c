/* Original Meteor.exe static export @ 004d95d0; original sample not executed. */
/* XREF 004936b8 DATA */

/* WARNING: Removing unreachable block (ram,0x004d9629) */
/* WARNING: Removing unreachable block (ram,0x004d9633) */
/* WARNING: Removing unreachable block (ram,0x004d965c) */

undefined4 __thiscall FUN_004d95d0(undefined4 param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)FUN_00487830(param_1);
  if (param_2 == 1) {
    piVar1[0x88d] = piVar1[0x88d] + (piVar1[0x88d] - piVar1[0x88c] >> 4) * -0x10;
  }
  else {
    if (param_2 == 2) {
      (**(code **)(*piVar1 + 0x29c))(&stack0x00000008);
      return 1;
    }
    if (param_2 == 3) {
      (**(code **)(*piVar1 + 0x2a0))();
      return 1;
    }
  }
  return 1;
}

