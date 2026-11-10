/* Original Meteor.exe static export @ 004cc130; original sample not executed. */
/* XREF 005aa6ac DATA */

/* WARNING (jumptable): Unable to track spacebase fully for stack */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004cc130(int *param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  float unaff_EBX;
  int iVar5;
  float unaff_ESI;
  int unaff_EDI;
  float10 fVar6;
  float fVar7;
  float fStack_48;
  float fStack_44;
  float local_40;
  undefined4 local_3c;
  undefined1 auStack_30 [12];
  undefined1 auStack_24 [12];
  undefined1 auStack_18 [20];
  
  if (param_1[4] == 0) {
    return;
  }
  if ((int *)param_1[0xd2] != (int *)0x0) {
    (**(code **)(*(int *)param_1[0xd2] + 0x58))(param_1);
  }
  local_40 = 0.0;
  local_3c = 0;
  FUN_005499a0(&local_40);
  if (param_1[4] == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = param_1[4] + -0x65c;
  }
  if (*(int *)(iVar5 + 0x848) != 0) {
    FUN_0055d910((float)(double)CONCAT44(local_3c,local_40));
  }
  piVar2 = (int *)FUN_00487830();
  iVar3 = (**(code **)(*piVar2 + 0x364))();
  if (iVar3 == 0) {
    (**(code **)(*param_1 + 0x1c4))();
    if (param_1[0xf1] == 0) {
      (**(code **)(*param_1 + 0x54))();
    }
    else {
      param_1[0xee] = 0;
      param_1[0xef] = 0;
      param_1[0xf0] = 0;
    }
  }
  if (param_1[0xde] == 0) {
    fVar7 = 0.0;
    (**(code **)(*param_1 + 0xbc))();
  }
  else {
    fVar7 = 1.4013e-45;
    (**(code **)(*param_1 + 0xbc))();
  }
  (**(code **)(*(int *)param_1[4] + 4))(auStack_30,auStack_18,auStack_24);
  fVar6 = (float10)FUN_00549b00();
  if ((float10)_DAT_005aa8b8 <= fVar6) {
    piVar2 = param_1 + 0xba;
    if ((undefined1 *)param_1[0xba] != (undefined1 *)param_1[0xbb]) {
      *(undefined1 *)param_1[0xba] = 0;
      param_1[0xbb] = *piVar2;
    }
    if (param_1[0x18] == 0) {
      if (param_1[0x19] == 1) {
        if (param_1[0xbb] + 1 == param_1[0xbc]) {
          unaff_ESI = 1.4013e-45;
          unaff_EDI = param_1[0xbb] - *piVar2;
          piVar2 = (int *)&stack0xffffffac;
          if (unaff_EDI != 0) {
            piVar2 = (int *)&stack0xffffffa8;
          }
          FUN_0049be40(*piVar2 + unaff_EDI);
        }
        FUN_00402bc0(param_1[0xbb] + 1);
        *(undefined1 *)param_1[0xbb] = 0x72;
      }
      else {
        if (param_1[0x19] != -1) goto LAB_004cc38c;
        if (param_1[0xbb] + 1 == param_1[0xbc]) {
          unaff_ESI = 1.4013e-45;
          unaff_EDI = param_1[0xbb] - *piVar2;
          piVar2 = (int *)&stack0xffffffac;
          if (unaff_EDI != 0) {
            piVar2 = (int *)&stack0xffffffa8;
          }
          FUN_0049be40(*piVar2 + unaff_EDI);
        }
        FUN_00402bc0(param_1[0xbb] + 1);
        *(undefined1 *)param_1[0xbb] = 0x6c;
      }
    }
    else {
      iVar3 = param_1[0xbb];
      if (param_1[0x18] == 1) {
        if (iVar3 + 1 == param_1[0xbc]) {
          unaff_EDI = 1;
          unaff_ESI = (float)(iVar3 - *piVar2);
          piVar2 = (int *)&stack0xffffffa8;
          if (unaff_ESI != 0.0) {
            piVar2 = (int *)&stack0xffffffac;
          }
          FUN_0049be40(*piVar2 + (int)unaff_ESI);
        }
        FUN_00402bc0(param_1[0xbb] + 1);
        *(undefined1 *)param_1[0xbb] = 0x66;
      }
      else {
        if (iVar3 + 1 == param_1[0xbc]) {
          unaff_ESI = 1.4013e-45;
          unaff_EDI = iVar3 - *piVar2;
          piVar2 = (int *)&stack0xffffffac;
          if (unaff_EDI != 0) {
            piVar2 = (int *)&stack0xffffffa8;
          }
          FUN_0049be40(*piVar2 + unaff_EDI);
        }
        FUN_00402bc0(param_1[0xbb] + 1);
        *(undefined1 *)param_1[0xbb] = 0x62;
      }
    }
    param_1[0xbb] = param_1[0xbb] + 1;
  }
LAB_004cc38c:
  fVar6 = (float10)FUN_00549b00();
  if (((float10)_DAT_005aa8b8 <= fVar6) &&
     ((undefined1 *)param_1[0xbd] != (undefined1 *)param_1[0xbe])) {
    *(undefined1 *)param_1[0xbd] = 0;
    param_1[0xbe] = param_1[0xbd];
  }
  switch(param_1[0x37]) {
  case 0:
    unaff_ESI = (float)param_1[0xe6];
    uVar4 = (**(code **)(*param_1 + 0xe8))(&stack0xfffffffc,unaff_EBX);
    if (((uVar4 & 0x30) != 0) && (bVar1 = fVar7 < _DAT_005a842c, param_1[0x39] = 0, bVar1)) {
      (**(code **)(*param_1 + 300))(1);
    }
    (**(code **)(*param_1 + 0x78))();
    break;
  case 1:
    uVar4 = (**(code **)(*param_1 + 0xe8))(&stack0xfffffffc,unaff_EBX);
    if ((uVar4 & 0x30) == 0) {
      (**(code **)(*param_1 + 300))(0);
    }
    (**(code **)(*param_1 + 0x13c))();
    break;
  case 2:
    iVar3 = (**(code **)(*param_1 + 0xe4))(&stack0xfffffffc,unaff_EBX);
    if (iVar3 == 0) {
      param_1[0x31] = 0;
      param_1[0x32] = 0;
      param_1[0x33] = 0;
      (**(code **)(*param_1 + 300))(0);
    }
    break;
  case 3:
    (**(code **)(*param_1 + 0xe0))(&stack0xfffffffc,unaff_EBX);
    break;
  case 4:
    (**(code **)(*param_1 + 0xd0))(&stack0xfffffffc,unaff_EBX);
    break;
  case 5:
    (**(code **)(*param_1 + 0xcc))(&stack0xfffffffc,unaff_EBX);
    break;
  case 6:
    (**(code **)(*param_1 + 0xd4))(&stack0xfffffffc,unaff_EBX);
    break;
  case 7:
    (**(code **)(*param_1 + 0xec))(&stack0xfffffffc,unaff_EBX);
    break;
  case 8:
    (**(code **)(*param_1 + 0xd8))(&stack0xfffffffc,unaff_EBX);
    break;
  case 10:
    (**(code **)(*param_1 + 0xdc))(&stack0xfffffffc,unaff_EBX);
    break;
  case 0xb:
    (**(code **)(*param_1 + 0xf0))(&stack0xfffffffc,unaff_EBX);
  }
  (**(code **)(*(int *)param_1[4] + 4))(&fStack_48,0,0);
  fVar6 = (float10)_DAT_005a8418 / (float10)(double)CONCAT44(unaff_EDI,fVar7);
  param_1[0x23] = (int)(float)(((float10)unaff_ESI - (float10)fStack_48) * fVar6);
  param_1[0x24] = (int)(float)(((float10)(float)&stack0xfffffffc - (float10)fStack_44) * fVar6);
  param_1[0x25] = (int)(float)(((float10)unaff_EBX - (float10)local_40) * fVar6);
  *(int *)(iVar5 + 0x82c) = param_1[0x23];
  *(int *)(iVar5 + 0x830) = param_1[0x24];
  *(int *)(iVar5 + 0x834) = param_1[0x25];
  return;
}

