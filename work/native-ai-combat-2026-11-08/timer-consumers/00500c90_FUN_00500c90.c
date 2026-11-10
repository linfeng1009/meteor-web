/* Original Meteor.exe read-only export. Sample not executed. */

void __thiscall FUN_00500c90(int *param_1,int param_2,int param_3)

{
  char *pcVar1;
  char cVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  char *pcVar8;
  bool bVar9;
  int iStack_24;
  char *pcStack_20;
  int iStack_1c;
  undefined4 uStack_18;
  int iStack_14;
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a3fa0;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  piVar3 = (int *)(**(code **)(*param_1 + 0x44))();
  if ((piVar3 != (int *)0x0) && (-1 < param_2)) {
    iVar4 = FUN_004c38d0();
    if (iVar4 < 1) {
      cVar2 = FUN_00501070();
      if (cVar2 != '\0') {
        iVar4 = _rand();
        uStack_18 = 0;
        iStack_14 = 0;
        pvStack_10 = (void *)0x0;
        pcVar1 = (&PTR_DAT_005ca240)[iVar4 % 0x11];
        uVar6 = 0xffffffff;
        uStack_4 = 0;
        pcVar8 = pcVar1;
        do {
          if (uVar6 == 0) break;
          uVar6 = uVar6 - 1;
          cVar2 = *pcVar8;
          pcVar8 = pcVar8 + 1;
        } while (cVar2 != '\0');
        FUN_004608a0(pcVar1 + (~uVar6 - 1) + (1 - (int)pcVar1));
        iStack_14 = FUN_004da870(pcVar1,pcVar1 + (~uVar6 - 1),uStack_18);
        FUN_00402a70();
        uStack_4 = 1;
        (**(code **)(*piVar3 + 0x1b0))(&uStack_18);
        puStack_8 = (undefined1 *)0xffffffff;
        if ((iStack_1c != 0) && (iStack_14 - iStack_1c != 0)) {
          FUN_00402e90(iStack_1c,iStack_14 - iStack_1c);
        }
        (**(code **)(*piVar3 + 0xa0))();
        ExceptionList = pvStack_10;
        return;
      }
      uVar6 = _rand();
      uVar6 = uVar6 & 0x80000001;
      bVar9 = uVar6 == 0;
      if ((int)uVar6 < 0) {
        bVar9 = (uVar6 - 1 | 0xfffffffe) == 0xffffffff;
      }
      if (bVar9) {
        param_3 = param_1[0x12a];
        iVar5 = param_1[0x129];
        piVar7 = &DAT_00666a10 + param_2 * 0xe + param_3 * 3;
        iVar4 = (&DAT_00666a14)[param_2 * 0xe + param_3 * 3] - *piVar7 >> 2;
        if (iVar4 <= iVar5) {
          iVar5 = iVar4 + -1;
        }
      }
      else {
        piVar7 = &DAT_00666a10 + param_3 * 3 + param_2 * 0xe;
        iVar4 = (int)((&DAT_00666a14)[param_3 * 3 + param_2 * 0xe] -
                     (&DAT_00666a10)[param_3 * 3 + param_2 * 0xe]) >> 2;
        if (param_3 == 3) {
          iVar5 = (**(code **)(*piVar3 + 0x170))();
          if (iVar5 == 0) {
            iVar4 = iVar4 + -1;
          }
        }
        iVar5 = _rand();
        iVar5 = iVar5 % iVar4;
      }
      param_1[0x129] = iVar5;
      param_1[0x12a] = param_3;
      pcVar1 = *(char **)(*piVar7 + iVar5 * 4);
      iStack_24 = 0;
      pcStack_20 = (char *)0x0;
      iStack_1c = 0;
      uVar6 = 0xffffffff;
      pcVar8 = pcVar1;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar2 = *pcVar8;
        pcVar8 = pcVar8 + 1;
      } while (cVar2 != '\0');
      uVar6 = ~uVar6;
      uStack_4 = 2;
      if (uVar6 == 0xffffffff) {
        FUN_004030f0();
      }
      else if (uVar6 == 0) {
        iStack_24 = 0;
        pcStack_20 = (char *)0x0;
        iStack_1c = 0;
      }
      else {
        iStack_24 = FUN_00402bf0(uVar6);
        iStack_1c = uVar6 + iStack_24;
        pcStack_20 = (char *)iStack_24;
      }
      iVar4 = iStack_24;
      FUN_005092c0(iStack_24,pcVar1,uVar6 - 1);
      pcStack_20 = pcVar1 + (iVar4 - (int)pcVar1) + (uVar6 - 1);
      FUN_00402a70();
      uStack_4 = 3;
      (**(code **)(*piVar3 + 0x1b0))(&iStack_24);
      uVar6 = (int)pcStack_20 - (int)piVar3;
      puStack_8 = (undefined1 *)0xffffffff;
      if ((piVar3 != (int *)0x0) && (uVar6 != 0)) {
        if (uVar6 < 0x81) {
          FUN_00402330();
          *piVar3 = *(int *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
          *(int **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = piVar3;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(piVar3);
        }
      }
      (**(code **)(*piVar3 + 0xa0))();
    }
  }
  ExceptionList = pvStack_c;
  return;
}

