/* Original Meteor.exe static export @ 004d8cf0; original sample not executed. */
/* XREF 004936ae DATA */

int FUN_004d8cf0(int param_1,char *param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  undefined4 uVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  undefined **ppuVar9;
  char *pcVar10;
  bool bVar11;
  undefined1 auStack_2dc [464];
  undefined1 auStack_10c [256];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a23bc;
  pvStack_c = ExceptionList;
  if (param_1 == 0x1e) {
    ExceptionList = &pvStack_c;
    if (param_2 != (char *)0x0) {
      ExceptionList = &pvStack_c;
      uVar3 = FUN_0050915b(param_2);
      piVar2 = (int *)FUN_00487830();
      (**(code **)(*piVar2 + 0x31c))(uVar3,0x4d,param_3,0x40,1);
    }
  }
  else {
    ExceptionList = &pvStack_c;
    if (param_1 == 100) {
      iVar7 = 4;
      bVar11 = true;
      pcVar8 = param_2;
      ppuVar9 = &PTR_DAT_005c9d04;
      do {
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        bVar11 = *pcVar8 == *(char *)ppuVar9;
        pcVar8 = pcVar8 + 1;
        ppuVar9 = (undefined **)((int)ppuVar9 + 1);
      } while (bVar11);
      if (bVar11) {
        ExceptionList = &pvStack_c;
        piVar2 = (int *)FUN_00487830();
        (**(code **)(*piVar2 + 0x2a8))(1,param_3);
        ExceptionList = pvStack_c;
        return 1;
      }
      iVar7 = 4;
      bVar11 = true;
      pcVar8 = param_2;
      pcVar10 = &DAT_005c9d00;
      do {
        if (iVar7 == 0) break;
        iVar7 = iVar7 + -1;
        bVar11 = *pcVar8 == *pcVar10;
        pcVar8 = pcVar8 + 1;
        pcVar10 = pcVar10 + 1;
      } while (bVar11);
      ExceptionList = &pvStack_c;
      if (bVar11) {
        ExceptionList = &pvStack_c;
        piVar2 = (int *)FUN_00487830();
        iVar7 = (**(code **)(*piVar2 + 0x260))();
        ExceptionList = pvStack_c;
        return *(int *)(iVar7 + 0x24);
      }
    }
  }
  if (DAT_005e0328 == 0) {
    pvVar4 = operator_new(0x33c);
    uStack_4 = 0;
    if (pvVar4 == (void *)0x0) {
      DAT_005e0328 = 0;
    }
    else {
      DAT_005e0328 = FUN_0044d020();
    }
    uStack_4 = 0xffffffff;
  }
  FUN_0045a450(auStack_2dc);
  uStack_4 = 1;
  iVar7 = FUN_004d6570();
  iVar7 = *(int *)(iVar7 + 4);
  iVar5 = 0;
  if (param_2 != (char *)0x0) {
    iVar5 = FUN_004d6570();
    if (iVar7 != *(int *)(iVar5 + 8)) {
      do {
        FUN_00508ae6(auStack_10c,*(undefined4 *)(iVar7 + 0x10));
        iVar5 = FUN_0050a9d0(*(undefined4 *)(iVar7 + 0x10),param_2);
        if (iVar5 == 0) break;
        iVar7 = iVar7 + 0x48;
        iVar5 = FUN_004d6570();
      } while (iVar7 != *(int *)(iVar5 + 8));
    }
    iVar6 = FUN_004d6570();
    iVar5 = iVar7;
    if (iVar7 != *(int *)(iVar6 + 8)) goto LAB_004d8e83;
    uStack_4 = 2;
    FUN_00402bd0();
    goto LAB_004d9528;
  }
LAB_004d8e83:
  switch(param_1) {
  case 1:
    iVar7 = *(int *)(iVar5 + 0x2c);
    uStack_4 = 3;
    FUN_00402bd0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  case 2:
    iVar7 = *(int *)(iVar5 + 0x28);
    uStack_4 = 4;
    FUN_00402bd0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  case 3:
    piVar2 = *(int **)(iVar5 + 0x30);
    piVar1 = *(int **)(iVar5 + 0x34);
    if (piVar2 != piVar1) {
      do {
        if (*piVar2 == 0xd) break;
        piVar2 = piVar2 + 3;
      } while (piVar2 != piVar1);
      if ((piVar2 != piVar1) && (piVar2 != (int *)0x0)) {
        iVar7 = piVar2[1];
        uStack_4 = 0xc;
        FUN_004026e0();
        uStack_4 = 0xffffffff;
        FUN_004026e0();
        ExceptionList = pvStack_c;
        return iVar7;
      }
    }
    uStack_4 = 0xd;
    FUN_004026e0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    iVar7 = 5;
    break;
  case 4:
    piVar2 = *(int **)(iVar5 + 0x30);
    piVar1 = *(int **)(iVar5 + 0x34);
    if (piVar2 != piVar1) {
      do {
        if (*piVar2 == 0xb) break;
        piVar2 = piVar2 + 3;
      } while (piVar2 != piVar1);
      if ((piVar2 != piVar1) && (piVar2 != (int *)0x0)) {
        switch(piVar2[1]) {
        case 0:
          piVar2 = (int *)FUN_00487830();
          iVar7 = (**(code **)(*piVar2 + 0x260))();
          if (*(int *)(iVar7 + 0x44) == 0) {
            uStack_4 = 7;
            FUN_00402bd0();
            uStack_4 = 0xffffffff;
            FUN_004026e0();
            ExceptionList = pvStack_c;
            return 0;
          }
          break;
        case 1:
          piVar2 = (int *)FUN_00487830();
          iVar7 = (**(code **)(*piVar2 + 0x260))();
          if (*(int *)(iVar7 + 0x48) == 0) {
            uStack_4 = 8;
            FUN_00402bd0();
            uStack_4 = 0xffffffff;
            FUN_004026e0();
            ExceptionList = pvStack_c;
            return 0;
          }
          break;
        case 2:
          piVar2 = (int *)FUN_00487830();
          iVar7 = (**(code **)(*piVar2 + 0x260))();
          if (*(int *)(iVar7 + 0x4c) == 0) {
            uStack_4 = 9;
            FUN_00402bd0();
            uStack_4 = 0xffffffff;
            FUN_004026e0();
            ExceptionList = pvStack_c;
            return 0;
          }
          break;
        case 3:
          piVar2 = (int *)FUN_00487830();
          iVar7 = (**(code **)(*piVar2 + 0x260))();
          if (*(int *)(iVar7 + 0x40) == 0) {
            uStack_4 = 10;
            FUN_00402bd0();
            uStack_4 = 0xffffffff;
            FUN_004026e0();
            ExceptionList = pvStack_c;
            return 0;
          }
        }
        uStack_4 = 0x1a;
        goto LAB_004d951c;
      }
    }
    uStack_4 = 0xb;
    FUN_00402bd0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    iVar7 = 1;
    break;
  case 5:
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x260))();
    uVar3 = *(undefined4 *)(iVar7 + 0x24);
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x2d4))();
    if (iVar7 == 2) {
      piVar2 = (int *)FUN_00487830();
      iVar7 = (**(code **)(*piVar2 + 0x364))();
      if (iVar7 != 0) goto LAB_004d8f55;
      iVar7 = 0x40;
    }
    else {
LAB_004d8f55:
      iVar7 = 1 << ((byte)uVar3 & 0x1f);
    }
    uStack_4 = 5;
    FUN_00402bd0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  default:
    uStack_4 = 0x19;
    goto LAB_004d951c;
  case 10:
    FUN_00487830();
    iVar7 = FUN_0054bf60();
    uStack_4 = 0xe;
    FUN_004026e0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  case 0xb:
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x2d8))();
    uStack_4 = 0xf;
    FUN_004026e0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  case 0xc:
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x260))();
    iVar7 = *(int *)(iVar7 + 0x24);
    uStack_4 = 6;
    FUN_00402bd0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  case 0x14:
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x14c))(param_3);
    if (iVar7 != 0) {
      iVar7 = *(int *)(iVar7 + 0x1f0);
      uStack_4 = 0x10;
      FUN_004026e0();
      uStack_4 = 0xffffffff;
      FUN_004026e0();
      ExceptionList = pvStack_c;
      return iVar7;
    }
    uStack_4 = 0x11;
LAB_004d951c:
    FUN_004026e0();
LAB_004d9528:
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    iVar7 = -1;
    break;
  case 0x15:
    iVar7 = FUN_00487830();
    iVar7 = (**(code **)(*(int *)(iVar7 + 0x2488) + 0x4c))();
    uStack_4 = 0x12;
    FUN_004026e0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  case 0x16:
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x158))(param_3);
    uStack_4 = 0x13;
    FUN_004026e0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  case 0x17:
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x14c))(param_3);
    if ((iVar7 == 0) || (*(char *)(iVar7 + 0x210) != '\x02')) {
      uStack_4 = 0x15;
      FUN_004026e0();
      uStack_4 = 0xffffffff;
      FUN_004026e0();
      iVar7 = 0;
    }
    else {
      uStack_4 = 0x14;
      FUN_004026e0();
      uStack_4 = 0xffffffff;
      FUN_004026e0();
      iVar7 = 1;
    }
    break;
  case 0x18:
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x15c))();
    uStack_4 = 0x16;
    FUN_004026e0();
    uStack_4 = 0xffffffff;
    FUN_004026e0();
    break;
  case 0x19:
    piVar2 = (int *)FUN_00487830();
    iVar7 = (**(code **)(*piVar2 + 0x14c))(param_3);
    if ((iVar7 == 0) ||
       (iVar5 = *(int *)(iVar7 + 0xb8) - *(int *)(iVar7 + 0xb4), iVar7 = iVar5 >> 0x1f,
       iVar5 / 0x48 + iVar7 == iVar7)) {
      uStack_4 = 0x18;
      FUN_004026e0();
      uStack_4 = 0xffffffff;
      FUN_004026e0();
      iVar7 = 0;
    }
    else {
      uStack_4 = 0x17;
      FUN_00402bd0();
      uStack_4 = 0xffffffff;
      FUN_004026e0();
      iVar7 = 1;
    }
  }
  ExceptionList = pvStack_c;
  return iVar7;
}

