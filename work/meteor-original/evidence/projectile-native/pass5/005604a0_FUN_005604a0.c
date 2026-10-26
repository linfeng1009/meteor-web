/* Original Meteor.exe static export @ 005604a0; original sample not executed. */
/* XREF 00563cfc UNCONDITIONAL_CALL */

void __thiscall FUN_005604a0(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined1 local_c [12];
  
  *(undefined4 *)(param_1 + 0x2c) = param_2;
  puVar1 = (undefined4 *)FUN_0056afc0(local_c);
  *(undefined4 *)(param_1 + 0x48) = *puVar1;
  *(undefined4 *)(param_1 + 0x4c) = puVar1[1];
  *(undefined4 *)(param_1 + 0x50) = puVar1[2];
  puVar1 = (undefined4 *)FUN_0056b0b0(local_c);
  *(undefined4 *)(param_1 + 0x54) = *puVar1;
  *(undefined4 *)(param_1 + 0x58) = puVar1[1];
  *(undefined4 *)(param_1 + 0x5c) = puVar1[2];
  FUN_005603f0();
  return;
}

