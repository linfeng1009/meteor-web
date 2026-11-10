/* Original Meteor.exe static export @ 004b1d60; original sample not executed. */
/* XREF 005a9bfc DATA */

void __fastcall FUN_004b1d60(int *param_1)

{
  uint uVar1;
  int iVar2;
  int iStack_10;
  int iStack_c;
  undefined1 auStack_8 [8];
  
  FUN_0054ec50();
  switch(param_1[0x78]) {
  case 3:
    iVar2 = (**(code **)(*param_1 + 0x100))();
    if (iVar2 != 0) {
      (**(code **)(*param_1 + 0x10c))();
      (**(code **)(*param_1 + 0x8c))();
      return;
    }
    (**(code **)(*param_1 + 0xd0))();
    (**(code **)(*param_1 + 0xd4))();
    FUN_00487830();
    FUN_00563780();
    iVar2 = FUN_00487830();
    *(undefined4 *)(iVar2 + 0x2444) = 1;
    iVar2 = FUN_005499a0(0);
    if (iVar2 != 0) {
      (**(code **)(*param_1 + 0x7c))();
      (**(code **)(*param_1 + 0xa8))();
    }
    iVar2 = FUN_005499a0(auStack_8);
    if (iVar2 != 0) {
      (**(code **)(*param_1 + 0xb4))(0x3e4ccccd);
    }
    iVar2 = FUN_005499a0(0);
    if (iVar2 != 0) {
      uVar1 = (**(code **)(*param_1 + 0x84))();
      if (uVar1 != 0) {
        if ((uVar1 & 2) != 0) {
          param_1[0xf1] = param_1[0xf1] + 1;
        }
        if ((uVar1 & 4) != 0) {
          param_1[0xf0] = param_1[0xf0] + 1;
        }
        iStack_10 = param_1[0xf0];
        iStack_c = param_1[0xf1];
        param_1[0xf2] = param_1[0xf2] + 1;
        (**(code **)(*param_1 + 0x40))(0x22,&iStack_10,8,1);
        iVar2 = (**(code **)(*param_1 + 0x9c))();
        if (iVar2 == 0) {
          param_1[0x78] = 4;
          (**(code **)(*param_1 + 0x40))(0x1b,0,0,1);
        }
        else {
          param_1[0x78] = 5;
          (**(code **)(*param_1 + 0x40))(0x28);
        }
        if (param_1[0xe8] == 0) {
          (**(code **)(*param_1 + 0xc0))();
        }
      }
      (**(code **)(*param_1 + 0x50))();
      iVar2 = FUN_005499a0(0);
      if (iVar2 != 0) {
        (**(code **)(*param_1 + 0x54))();
        return;
      }
    }
    break;
  case 4:
    iVar2 = (**(code **)(*param_1 + 0x90))();
    if (iVar2 == 1) {
      (**(code **)(*param_1 + 0x8c))();
      param_1[0x78] = 3;
      return;
    }
    iVar2 = FUN_005499a0(0);
    if (iVar2 != 0) {
      (**(code **)(*param_1 + 0x50))();
      return;
    }
    break;
  case 5:
    iVar2 = (**(code **)(*param_1 + 0x98))();
    if (iVar2 == 1) {
      (**(code **)(*param_1 + 0x94))();
      param_1[0x78] = 6;
      return;
    }
    iVar2 = FUN_005499a0(0);
    if (iVar2 != 0) {
      (**(code **)(*param_1 + 0x50))();
      return;
    }
    break;
  case 6:
    iVar2 = (**(code **)(*param_1 + 0xb8))();
    if (iVar2 != 0) {
      FUN_00549a90(0,0);
      iStack_c = param_1[0xe0];
      if (iStack_c == 0) {
        FUN_00549b00();
        iVar2 = __ftol();
        iStack_10 = param_1[0x87];
      }
      else {
        FUN_00549b00();
        iVar2 = __ftol();
        iStack_10 = param_1[0xe1];
      }
      iStack_10 = iStack_10 - iVar2;
      (**(code **)(*param_1 + 0x40))(0x3a,&iStack_10,8,1);
      param_1[0x78] = 3;
    }
  }
  return;
}

