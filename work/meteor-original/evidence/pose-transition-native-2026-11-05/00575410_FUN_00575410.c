/* Original Meteor.exe static export @ 00575410; original sample not executed. */
/* XREF 0057b702 UNCONDITIONAL_CALL */

void __thiscall FUN_00575410(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x8c);
  if (puVar1 != *(undefined4 **)(param_1 + 0x90)) {
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = *param_2;
      puVar1[1] = param_2[1];
      puVar1[2] = param_2[2];
    }
    *(int *)(param_1 + 0x8c) = *(int *)(param_1 + 0x8c) + 0xc;
    *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
    return;
  }
  FUN_00575ad0(puVar1,param_2);
  *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
  return;
}

