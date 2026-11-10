/* Original Meteor.exe static export @ 004c9040; original sample not executed. */
/* XREF 005aa678 DATA */

undefined4 __thiscall FUN_004c9040(int param_1,undefined4 *param_2)

{
  float fVar1;
  undefined4 *puVar2;
  float10 fVar3;
  
  if (*(int *)(param_1 + 0x44) != *(int *)(param_1 + 0x3c)) {
    fVar1 = *(float *)(*(int *)(param_1 + 0x44) + 0xc);
    fVar3 = (float10)FUN_00549b00();
    if ((float10)fVar1 <= fVar3) {
      puVar2 = *(undefined4 **)(param_1 + 0x44);
      *param_2 = *puVar2;
      param_2[1] = puVar2[1];
      param_2[2] = puVar2[2];
      param_2[3] = puVar2[3];
      *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 0x10;
      return 1;
    }
  }
  return 0;
}

