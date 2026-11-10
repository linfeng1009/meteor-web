/* Original Meteor.exe read-only export. Sample not executed. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004fb770(int param_1,float param_2)

{
  float fVar1;
  
  if (*(int *)(param_1 + 0xc4) != -1) {
    FUN_004fcfa0(param_2);
  }
  FUN_004fd3b0(param_2);
  FUN_00500be0(*(undefined4 *)(param_1 + 0xbc),*(undefined4 *)(param_1 + 0xc0));
  if (*(char *)(param_1 + 0x14) == '\0') {
    *(float *)(param_1 + 0xb4) = param_2 + *(float *)(param_1 + 0xb4);
  }
  else {
    *(undefined4 *)(param_1 + 0xb4) = 0;
    *(float *)(param_1 + 0xb0) = param_2 + *(float *)(param_1 + 0xb0);
  }
  param_2 = param_2 + *(float *)(param_1 + 0x7c);
  *(float *)(param_1 + 0x7c) = param_2;
  fVar1 = (float)(int)*(short *)(*(int *)(param_1 + 0x10) + 2) * _DAT_005a8410;
  if (fVar1 < _DAT_005a83ec) {
    fVar1 = _DAT_005a83ec;
  }
  if (*(undefined **)(param_1 + 100) == &DAT_00504be0) {
    fVar1 = _DAT_005a83f4;
  }
  if (*(float *)(param_1 + 0x80) / fVar1 <= param_2) {
    *(undefined4 *)(param_1 + 0x7c) = 0;
    if (*(char *)(*(int *)(param_1 + 0xc) + 0x498) != '\0') {
      FUN_004fda00();
      FUN_004c0580(*(undefined4 *)(param_1 + 8),(int)*(short *)(*(int *)(param_1 + 0xc) + 0x44a));
      *(undefined1 *)(*(int *)(param_1 + 0xc) + 0x498) = 0;
    }
    if (*(int *)(param_1 + 100) != 0) {
      if ((*(int *)(param_1 + 0x74) != 0) && (*(int *)(*(int *)(param_1 + 0x74) + 0x48) < 1)) {
        *(undefined4 *)(param_1 + 0x74) = 0;
      }
      if ((*(int *)(param_1 + 0x78) != 0) && (*(int *)(*(int *)(param_1 + 0x78) + 0x48) < 1)) {
        *(undefined4 *)(param_1 + 0x78) = 0;
      }
      FUN_004fe0c0();
      (**(code **)(param_1 + 100))();
      *(int *)(param_1 + 0x84) = *(int *)(param_1 + 0x84) + 1;
    }
    FUN_004fa210();
  }
  return;
}

