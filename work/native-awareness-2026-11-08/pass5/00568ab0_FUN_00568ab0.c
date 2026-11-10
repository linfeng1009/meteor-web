/* Original Meteor.exe static export @ 00568ab0; original sample not executed. */
/* XREF 005690ce UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00568ab0(int param_1,undefined4 param_2,undefined4 param_3)

{
  float fVar1;
  float fVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_6c;
  int local_68;
  undefined1 local_4c [64];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a594b;
  local_c = ExceptionList;
  iVar4 = *(int *)(param_1 + 0x120);
  ExceptionList = &local_c;
  *(undefined4 *)(iVar4 + 0x54) = 0x501502f9;
  iVar5 = 0;
  *(undefined4 *)(iVar4 + 0x50) = 0x501502f9;
  *(undefined4 *)(iVar4 + 0x4c) = 0x501502f9;
  iVar4 = *(int *)(param_1 + 0x120);
  local_6c = 0;
  *(undefined4 *)(iVar4 + 0x60) = 0xd01502f9;
  *(undefined4 *)(iVar4 + 0x5c) = 0xd01502f9;
  *(undefined4 *)(iVar4 + 0x58) = 0xd01502f9;
  if ((char)param_3 == '\0') {
    FUN_0050b600(param_2,s__s__d__s__d_005d12d0,local_4c,*(int *)(param_1 + 0x120) + 0x38,local_4c,
                 *(int *)(param_1 + 0x120) + 0x40);
    FUN_0050b600(param_2,s__s__d__s__d_005d12d0,local_4c,*(int *)(param_1 + 0x120) + 0xe4,local_4c,
                 *(int *)(param_1 + 0x120) + 0xec);
  }
  else {
    FUN_0050a118(*(int *)(param_1 + 0x120) + 0x38,4,1,param_2);
    FUN_0050a118(*(int *)(param_1 + 0x120) + 0x40,4,1,param_2);
    FUN_0050a118(*(int *)(param_1 + 0x120) + 0xe4,4,1,param_2);
    FUN_0050a118(*(int *)(param_1 + 0x120) + 0xec,4,1,param_2);
  }
  *(int *)(*(int *)(param_1 + 0x120) + 0xe8) = *(int *)(*(int *)(param_1 + 0x120) + 0xec) * 3;
  FUN_00568780(0);
  pvVar3 = operator_new(*(int *)(*(int *)(param_1 + 0x120) + 0xe4) * 0x24);
  *(void **)(*(int *)(param_1 + 0x120) + 0xd8) = pvVar3;
  if (*(int *)(*(int *)(param_1 + 0x120) + 0xd8) != 0) {
    iVar4 = *(int *)(*(int *)(param_1 + 0x120) + 0xec);
    pvVar3 = operator_new(iVar4 * 0x54);
    local_4 = 0;
    if (pvVar3 == (void *)0x0) {
      pvVar3 = (void *)0x0;
    }
    else if (-1 < iVar4 + -1) {
      iVar6 = (int)pvVar3 + 0x1c;
      do {
        FUN_00403840(iVar6,0xc,3,FUN_0048ee20);
        iVar6 = iVar6 + 0x54;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    iVar6 = 0;
    local_4 = 0xffffffff;
    *(void **)(*(int *)(param_1 + 0x120) + 0xd4) = pvVar3;
    iVar4 = *(int *)(param_1 + 0x120);
    if (*(int *)(iVar4 + 0xd8) != 0) {
      iVar7 = *(int *)(iVar4 + 0x3c);
      local_68 = 0;
      if (0 < *(int *)(iVar4 + 0x38)) {
        do {
          *(int *)(iVar7 + 0x20c) = local_6c;
          *(int *)(iVar7 + 0x210) = iVar5;
          *(int *)(iVar7 + 0x214) = iVar5 * 3;
          FUN_00567fd0(param_2,iVar7,param_3);
          iVar5 = iVar5 + *(int *)(iVar7 + 0x204);
          local_68 = local_68 + *(int *)(iVar7 + 0x204);
          local_6c = local_6c + *(int *)(iVar7 + 0x208);
          iVar6 = iVar6 + 1;
          iVar7 = iVar7 + 0x2b0;
        } while (iVar6 < *(int *)(*(int *)(param_1 + 0x120) + 0x38));
      }
      if (local_68 != *(int *)(*(int *)(param_1 + 0x120) + 0xec)) {
        FUN_0050ac20(s_Miss_faces_005d1728);
      }
      iVar4 = *(int *)(param_1 + 0x120);
      *(float *)(iVar4 + 100) = *(float *)(iVar4 + 0x58) - *(float *)(iVar4 + 0x4c);
      *(float *)(iVar4 + 0x68) = *(float *)(iVar4 + 0x5c) - *(float *)(iVar4 + 0x50);
      *(float *)(iVar4 + 0x6c) = *(float *)(iVar4 + 0x60) - *(float *)(iVar4 + 0x54);
      iVar4 = *(int *)(param_1 + 0x120);
      fVar1 = (*(float *)(iVar4 + 0x50) + *(float *)(iVar4 + 0x5c)) * _DAT_005a83e8;
      *(float *)(iVar4 + 0x70) =
           (*(float *)(iVar4 + 0x4c) + *(float *)(iVar4 + 0x58)) * _DAT_005a83e8;
      fVar2 = (*(float *)(iVar4 + 0x54) + *(float *)(iVar4 + 0x60)) * _DAT_005a83e8;
      *(float *)(iVar4 + 0x74) = fVar1;
      *(float *)(iVar4 + 0x78) = fVar2;
      iVar4 = *(int *)(param_1 + 0x120);
      *(float *)(iVar4 + 0x7c) = *(float *)(iVar4 + 0x58) - *(float *)(iVar4 + 0x70);
      *(float *)(iVar4 + 0x80) = *(float *)(iVar4 + 0x5c) - *(float *)(iVar4 + 0x74);
      *(float *)(iVar4 + 0x84) = *(float *)(iVar4 + 0x60) - *(float *)(iVar4 + 0x78);
      FUN_00477200();
      FUN_00477b90(3,*(int *)(param_1 + 0x120) + 0x70);
      iVar4 = *(int *)(param_1 + 0x120);
      *(undefined4 *)(param_1 + 0xf0) = *(undefined4 *)(iVar4 + 0x4c);
      *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)(iVar4 + 0x50);
      *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(iVar4 + 0x54);
      *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(iVar4 + 0x58);
      *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(iVar4 + 0x5c);
      *(undefined4 *)(param_1 + 0xec) = *(undefined4 *)(iVar4 + 0x60);
      *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(iVar4 + 0x70);
      *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(iVar4 + 0x74);
      *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(iVar4 + 0x78);
      *(float *)(param_1 + 0x114) = *(float *)(iVar4 + 100);
      *(undefined4 *)(param_1 + 0x118) = *(undefined4 *)(iVar4 + 0x68);
      *(undefined4 *)(param_1 + 0x11c) = *(undefined4 *)(iVar4 + 0x6c);
      fVar1 = *(float *)(param_1 + 0x118) * _DAT_005a83e8;
      fVar2 = *(float *)(param_1 + 0x11c) * _DAT_005a83e8;
      *(float *)(param_1 + 0x108) = *(float *)(param_1 + 0x114) * _DAT_005a83e8;
      *(float *)(param_1 + 0x10c) = fVar1;
      *(float *)(param_1 + 0x110) = fVar2;
      FUN_00477200();
      FUN_00477b90(3,(undefined4 *)(param_1 + 0xfc));
      iVar4 = *(int *)(param_1 + 0x120);
      *(float *)(iVar4 + 200) =
           SQRT(*(float *)(iVar4 + 100) * *(float *)(iVar4 + 100) +
                *(float *)(iVar4 + 0x68) * *(float *)(iVar4 + 0x68) +
                *(float *)(iVar4 + 0x6c) * *(float *)(iVar4 + 0x6c));
      *(undefined4 *)(*(int *)(param_1 + 0x120) + 0xcc) =
           *(undefined4 *)(*(int *)(param_1 + 0x120) + 100);
      iVar4 = *(int *)(param_1 + 0x120);
      if (*(float *)(iVar4 + 0xcc) < *(float *)(iVar4 + 0x68)) {
        *(undefined4 *)(iVar4 + 0xcc) = *(undefined4 *)(iVar4 + 0x68);
      }
      iVar4 = *(int *)(param_1 + 0x120);
      if (*(float *)(iVar4 + 0xcc) < *(float *)(iVar4 + 0x6c)) {
        *(undefined4 *)(iVar4 + 0xcc) = *(undefined4 *)(iVar4 + 0x6c);
      }
      ExceptionList = local_c;
      return 1;
    }
  }
  FUN_005679f0();
  ExceptionList = local_c;
  return 0;
}

