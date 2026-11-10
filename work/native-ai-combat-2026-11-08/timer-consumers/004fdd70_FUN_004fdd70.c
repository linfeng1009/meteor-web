/* Original Meteor.exe read-only export. Sample not executed. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004fdd70(int param_1)

{
  char cVar1;
  int iVar2;
  DWORD DVar3;
  float10 fVar4;
  
  cVar1 = FUN_004fcbd0();
  if (cVar1 == '\0') {
    return 0;
  }
  FUN_004fcc00();
  if (*(int *)(param_1 + 0x74) != 0) {
    iVar2 = _rand();
    if (iVar2 % 100 < (int)*(short *)(*(int *)(param_1 + 0x10) + 6)) {
      FUN_004fd630(&LAB_00504560);
      return 1;
    }
    FUN_004fd530(*(undefined4 *)(param_1 + 0x74));
    if (0x3c < *(int *)(param_1 + 0x11c)) {
      fVar4 = (float10)FUN_0047ecf0();
      if (fVar4 < (float10)_DAT_005ab870) {
        iVar2 = _rand();
        if (iVar2 % 5 == 0) {
          FUN_00501010();
          return 1;
        }
      }
    }
  }
  iVar2 = _rand();
  if ((iVar2 % 5 == 0) && (-1 < *(int *)(param_1 + 0x5c))) {
    FUN_00501240();
    DVar3 = timeGetTime();
    *(DWORD *)(param_1 + 0x120) = DVar3;
    *(undefined4 *)(param_1 + 0x80) = 0x3f19999a;
    return 1;
  }
  iVar2 = _rand();
  if (iVar2 % 100 < (int)*(short *)(*(int *)(param_1 + 0x10) + 4)) {
    cVar1 = FUN_004fcf70();
    if (cVar1 == '\0') {
      FUN_00500c60(1);
      return 1;
    }
  }
  FUN_00500c60(0);
  if ((*(int *)(param_1 + 0x74) == 0) && (*(int *)(param_1 + 0x78) == 0)) {
    iVar2 = _rand();
    if (iVar2 % 100 < *(short *)(*(int *)(param_1 + 0x10) + 6) * 2) {
      FUN_004fd630(&LAB_005049d0);
    }
  }
  return 1;
}

