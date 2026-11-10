/* Original Meteor.exe static export @ 00482e30; original sample not executed. */
/* XREF 0048205f UNCONDITIONAL_CALL */
/* XREF 00483274 UNCONDITIONAL_CALL */

int __fastcall FUN_00482e30(int *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  RECT *lpRect;
  undefined **lpString2;
  char *lpString2_00;
  int *piVar7;
  int iStack_38;
  int iStack_34;
  int *piStack_30;
  int *piStack_2c;
  
  iVar2 = param_1[0xd9e6];
  piVar1 = param_1 + iVar2 * 0x15ca + param_1[iVar2 * 0x15ca + 0x15ca] * 0x425 + 0x111;
  piVar7 = piVar1 + piVar1[0x421] * 5 + 0x39;
  piStack_2c = (int *)0x482e88;
  (**(code **)*param_1)();
  piVar5 = param_1 + 0xdb05;
  piVar6 = piVar5;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  param_1[0xdb0c] = piVar1[0x422];
  param_1[0xdb08] = 1;
  if (piVar1[0x422] == 0) {
    iVar4 = piVar1[0x424];
  }
  else {
    iVar4 = piVar1[0x423];
  }
  param_1[0xdb0a] = 1;
  param_1[0xdb0d] = param_1[0xdb8e];
  param_1[0xdb09] = iVar4;
  iVar4 = piVar7[4];
  param_1[0xdb0b] = param_1[0xdb12];
  param_1[0xdb0e] = iVar4;
  if (param_1[0xd9e7] == 0) {
    *piVar5 = *piVar7;
    param_1[0xdb06] = piVar7[1];
    param_1[0xdb07] = piVar7[2];
  }
  else {
    *piVar5 = param_1[0xdb5b] - param_1[0xdb59];
    param_1[0xdb06] = param_1[0xdb5c] - param_1[0xdb5a];
    param_1[0xdb07] = param_1[iVar2 * 0x15ca + 0x10f];
  }
  if ((piVar1[9] & 0x1000U) != 0) {
    piStack_2c = (int *)0x0;
    piStack_30 = (int *)0x8200000d;
    iStack_34 = 0x482f62;
    FUN_00483330();
  }
  piStack_2c = param_1 + 0xdb15;
  piStack_30 = param_1 + 0xdb05;
  iStack_34 = piVar7[3];
  iStack_38 = param_1[0xdb13];
  iVar2 = *piVar1;
  iVar4 = (**(code **)(*(int *)param_1[0xdb14] + 0x3c))();
  if (iVar4 < 0) goto LAB_004831c1;
  if (param_1[0xd9e7] != 0) {
    SetWindowPos((HWND)param_1[0xdb12],(HWND)0xfffffffe,param_1[0xdb55],param_1[0xdb56],
                 param_1[0xdb57] - param_1[0xdb55],param_1[0xdb58] - param_1[0xdb56],0x40);
  }
  piVar5 = param_1 + 0xdb16;
  (**(code **)(*(int *)param_1[0xdb15] + 0x1c))();
  param_1[0xdb53] = piVar7[3];
  iVar4 = *piVar1;
  if (iVar4 == 2) {
    lpString2 = &PTR_LAB_00464551_1_005c8288;
LAB_0048302b:
    lstrcpyA((LPSTR)(param_1 + 0xdb60),(LPCSTR)lpString2);
  }
  else {
    if (iVar4 == 1) {
      lpString2 = (undefined **)&DAT_005c828c;
      goto LAB_0048302b;
    }
    if (iVar4 == 3) {
      lpString2 = (undefined **)&DAT_005c830c;
      goto LAB_0048302b;
    }
  }
  uVar3 = piVar7[3];
  if (((uVar3 & 0x40) == 0) || ((uVar3 & 0x10) == 0)) {
    if ((uVar3 & 0x40) != 0) {
      if (*piVar1 == 1) {
        lpString2_00 = s__hw_vp__005c82d8;
      }
      else {
        lpString2_00 = s__simulated_hw_vp__005c82c4;
      }
      goto LAB_004830b2;
    }
    if ((char)uVar3 < '\0') {
      if (*piVar1 == 1) {
        lpString2_00 = s__mixed_vp__005c82b8;
      }
      else {
        lpString2_00 = s__simulated_mixed_vp__005c82a0;
      }
      goto LAB_004830b2;
    }
    if ((uVar3 & 0x20) != 0) {
      lpString2_00 = &DAT_005c8294;
      goto LAB_004830b2;
    }
  }
  else {
    if (*piVar1 == 1) {
      lpString2_00 = s__pure_hw_vp__005c82fc;
    }
    else {
      lpString2_00 = s__simulated_pure_hw_vp__005c82e4;
    }
LAB_004830b2:
    lstrcatA((LPSTR)(param_1 + 0xdb60),lpString2_00);
  }
  if (*piVar1 == 1) {
    lstrcatA((LPSTR)(param_1 + 0xdb60),&DAT_005c8290);
    lstrcatA((LPSTR)(param_1 + 0xdb60),(LPCSTR)(iVar2 + 0x200));
  }
  piVar7 = &iStack_38;
  (**(code **)(*(int *)param_1[0xdb15] + 0x40))((int *)param_1[0xdb15],0,0);
  (**(code **)(*piVar5 + 0x20))(piVar5,param_1 + 0xdb4b);
  (**(code **)(*piVar7 + 8))(piVar7);
  if ((param_1[0xdb93] != 0) && (param_1[0xd9e7] == 0)) {
    GetClassLongA((HWND)param_1[0xdb12],-0xc);
    (**(code **)(*(int *)param_1[0xdb15] + 0x30))((int *)param_1[0xdb15],1);
  }
  if (param_1[0xdb94] != 0) {
    if (param_1[0xd9e7] == 0) {
      GetWindowRect((HWND)param_1[0xdb12],(LPRECT)&stack0xffffffb0);
      lpRect = (RECT *)&stack0xffffffb0;
    }
    else {
      lpRect = (RECT *)0x0;
    }
    ClipCursor(lpRect);
  }
  iVar4 = (**(code **)(*param_1 + 8))();
  if ((-1 < iVar4) && (iVar4 = (**(code **)(*param_1 + 0xc))(), -1 < iVar4)) {
    param_1[0xd9e8] = 1;
    return 0;
  }
  (**(code **)(*param_1 + 0x10))();
  (**(code **)(*param_1 + 0x14))();
  if ((int *)param_1[0xdb15] != (int *)0x0) {
    (**(code **)(*(int *)param_1[0xdb15] + 8))();
    param_1[0xdb15] = 0;
  }
LAB_004831c1:
  if (*piVar1 == 1) {
    uVar3 = 0;
    param_1[0xd9e6] = 0;
    if (param_1[0x110] != 0) {
      piVar5 = param_1 + 0x111;
      do {
        if (*piVar5 == 2) {
          param_1[0x15ca] = uVar3;
          param_1[0xd9e7] = param_1[uVar3 * 0x425 + 0x533];
          break;
        }
        uVar3 = uVar3 + 1;
        piVar5 = piVar5 + 0x425;
      } while (uVar3 < (uint)param_1[0x110]);
    }
    if (param_1[param_1[0x15ca] * 0x425 + 0x111] == 2) {
      SetWindowPos((HWND)param_1[0xdb12],(HWND)0xfffffffe,param_1[0xdb55],param_1[0xdb56],
                   param_1[0xdb57] - param_1[0xdb55],param_1[0xdb58] - param_1[0xdb56],0x40);
      (**(code **)*param_1)();
      FUN_00483330();
      iVar4 = FUN_00482e30();
    }
  }
  return iVar4;
}

