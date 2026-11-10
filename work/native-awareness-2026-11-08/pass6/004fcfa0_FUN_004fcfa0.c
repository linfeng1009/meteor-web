/* Original Meteor.exe static export @ 004fcfa0; original sample not executed. */
/* XREF 004fb783 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004fcfa0(int param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;
  float10 fVar4;
  undefined4 uVar5;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (*(int *)(param_1 + 0xc4) == -1) {
    return;
  }
  if ((*(int *)(DAT_0066629c + 0x500) - *(int *)(DAT_0066629c + 0x4fc)) / 0x24 <=
      *(int *)(param_1 + 0xc4)) {
    return;
  }
  local_24 = *(float *)(param_1 + 200) - *(float *)(param_1 + 0x18);
  iVar1 = param_1 + 200;
  local_20 = *(float *)(param_1 + 0xcc) - *(float *)(param_1 + 0x1c);
  local_1c = *(float *)(param_1 + 0xd0) - *(float *)(param_1 + 0x20);
  FUN_00501160(&local_c);
  fVar4 = (float10)FUN_0047ecf0();
  if (fVar4 * (float10)_DAT_005ab868 * fVar4 * (float10)_DAT_005ab868 <=
      (float10)local_24 * (float10)local_24 + (float10)local_20 * (float10)local_20) {
    if (_DAT_005a83f0 < *(float *)(param_1 + 0xb0)) {
      *(undefined4 *)(param_1 + 0xb0) = 0;
      local_24 = *(float *)(param_1 + 0x18);
      local_20 = *(float *)(param_1 + 0x1c);
      local_18 = *(float *)(param_1 + 0x24) * _DAT_005a8b08 + *(float *)(param_1 + 0x18);
      local_14 = *(float *)(param_1 + 0x28) * _DAT_005a8b08 + *(float *)(param_1 + 0x1c);
      local_4 = *(float *)(param_1 + 0x2c) * _DAT_005a8b08 + *(float *)(param_1 + 0x20);
      local_1c = *(float *)(param_1 + 0x20) + _DAT_005ab844 + _DAT_005ab844;
      local_10 = _DAT_005ab844 + _DAT_005ab844 + local_4;
      local_c = local_18;
      local_8 = local_14;
      cVar2 = FUN_004c1360(&local_24,&local_18,0,0);
      if ((cVar2 == '\0') && (iVar3 = _rand(), iVar3 % 3 != 0)) {
        FUN_004fd4c0(iVar1);
        *(undefined4 *)(param_1 + 0xbc) = 1;
        FUN_00500be0(1,0);
        FUN_00500c40(1);
        return;
      }
      local_1c = local_1c - _DAT_005ab844;
      local_10 = local_10 - _DAT_005ab844;
      cVar2 = FUN_004c1360(&local_24,&local_18,0,0);
      if ((cVar2 == '\0') && (iVar3 = _rand(), iVar3 % 3 != 0)) {
        FUN_004fd4c0(iVar1);
        *(undefined4 *)(param_1 + 0xbc) = 1;
        FUN_00500be0(1,0);
        FUN_00500c40(0);
        return;
      }
      FUN_004fd630(&LAB_00504700);
      return;
    }
    if (_DAT_005a9518 < *(float *)(param_1 + 0xb4)) {
      *(undefined4 *)(param_1 + 0xb0) = 0;
    }
    if (*(float *)(param_1 + 0xb0) == _DAT_005a83e4) {
      FUN_004fd4c0(iVar1);
      if (*(int *)(param_1 + 0xb8) == 1) {
        cVar2 = FUN_004fcf00(0x42200000);
        if ((cVar2 != '\0') && (cVar2 = FUN_004fced0(0x41200000), cVar2 != '\0')) {
          FUN_00500be0(1,0);
          FUN_00500c40(1);
          *(undefined4 *)(param_1 + 0xb8) = 0;
          goto LAB_004fd06a;
        }
        uVar5 = 0x40a00000;
      }
      else {
        uVar5 = 0x42340000;
      }
      cVar2 = FUN_004fced0(uVar5);
      if (cVar2 == '\0') {
        *(undefined4 *)(param_1 + 0xbc) = 0;
      }
      else {
        *(undefined4 *)(param_1 + 0xbc) = 1;
      }
    }
  }
  else if ((float)_DAT_005ab860 <= ABS(local_1c)) {
    FUN_004fdd10();
  }
  else {
    FUN_004fd2e0();
  }
LAB_004fd06a:
  if ((*(int *)(param_1 + 0xb8) == 1) && (cVar2 = FUN_00501070(), cVar2 != '\0')) {
    *(undefined4 *)(param_1 + 0xbc) = 1;
  }
  return;
}

