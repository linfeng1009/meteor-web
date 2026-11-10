/* Original Meteor.exe static export @ 005753b0; original sample not executed. */
/* XREF 0057b6b1 UNCONDITIONAL_CALL */

void __thiscall FUN_005753b0(int param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 0x80);
  if (puVar1 != *(undefined4 **)(param_1 + 0x84)) {
    if (puVar1 != (undefined4 *)0x0) {
      *puVar1 = *param_2;
      puVar1[1] = param_2[1];
      puVar1[2] = param_2[2];
    }
    *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + 0xc;
    *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
    return;
  }
  FUN_00575ad0(puVar1,param_2);
  *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
  return;
}

