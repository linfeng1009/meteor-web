/* Original Meteor.exe static export @ 004d0540; original sample not executed. */
/* XREF 005aa768 DATA */

/* WARNING: Removing unreachable block (ram,0x004d09ef) */
/* WARNING: Removing unreachable block (ram,0x004d0a07) */
/* WARNING: Removing unreachable block (ram,0x004d073d) */
/* WARNING: Removing unreachable block (ram,0x004d06ed) */
/* WARNING: Removing unreachable block (ram,0x004d0741) */
/* WARNING: Removing unreachable block (ram,0x004d0745) */
/* WARNING: Removing unreachable block (ram,0x004d076d) */
/* WARNING: Removing unreachable block (ram,0x004d0762) */
/* WARNING: Removing unreachable block (ram,0x004d076f) */
/* WARNING: Removing unreachable block (ram,0x004d078f) */
/* WARNING: Removing unreachable block (ram,0x004d0797) */
/* WARNING: Removing unreachable block (ram,0x004d07ef) */
/* WARNING: Removing unreachable block (ram,0x004d0806) */
/* WARNING: Removing unreachable block (ram,0x004d0838) */
/* WARNING: Removing unreachable block (ram,0x004d0822) */
/* WARNING: Removing unreachable block (ram,0x004d083a) */
/* WARNING: Removing unreachable block (ram,0x004d0865) */
/* WARNING: Removing unreachable block (ram,0x004d0852) */
/* WARNING: Removing unreachable block (ram,0x004d0856) */
/* WARNING: Removing unreachable block (ram,0x004d085c) */
/* WARNING: Removing unreachable block (ram,0x004d0874) */
/* WARNING: Removing unreachable block (ram,0x004d08a6) */
/* WARNING: Removing unreachable block (ram,0x004d0939) */
/* WARNING: Removing unreachable block (ram,0x004d0969) */
/* WARNING: Removing unreachable block (ram,0x004d09fc) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004d0540(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  float *pfVar5;
  undefined4 uStack_c4;
  int iStack_c0;
  undefined4 *puStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float local_a4 [3];
  float fStack_98;
  float fStack_94;
  float fStack_90;
  int *local_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  float afStack_80 [4];
  float fStack_70;
  float fStack_6c;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  float fStack_54;
  undefined1 auStack_48 [28];
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float fStack_24;
  void *pvStack_18;
  uint uStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a1aad;
  pvStack_c = ExceptionList;
  if (param_1[4] == 0) {
    piVar4 = (int *)0x0;
  }
  else {
    piVar4 = (int *)(param_1[4] + -0x65c);
  }
  ExceptionList = &pvStack_c;
  local_8c = param_1;
  iVar2 = (**(code **)(*param_1 + 0xc))(0x19,local_a4);
  if (0 < iVar2) {
    (**(code **)(*piVar4 + 0x6c))(auStack_48,2);
    afStack_80[3] = -fStack_b8;
    pfVar5 = afStack_80;
    for (iVar2 = 0xc; iVar2 != 0; iVar2 = iVar2 + -1) {
      *pfVar5 = 0.0;
      pfVar5 = pfVar5 + 1;
    }
    fStack_70 = -fStack_b4;
    fStack_6c = -fStack_b0;
    fStack_54 = fStack_24 + _DAT_005a8e7c;
    uStack_60 = 0x3f800000;
    afStack_80[0] = 1.0;
    uStack_5c = uStack_2c;
    uStack_58 = uStack_28;
    uStack_c4 = 0;
    iStack_c0 = 0;
    puStack_bc = (undefined4 *)0x0;
    pvStack_18 = (void *)0x2;
    if ((uStack_10 < 3) || (uStack_10 == 0x54)) {
      uStack_84 = 0;
      uStack_88 = 0;
      local_8c = (int *)0x0;
      fStack_ac = fStack_b8 * _DAT_005aa934;
      fStack_a8 = fStack_b4 * _DAT_005aa934;
      local_a4[0] = (fStack_b0 + _DAT_005aa944) * _DAT_005aa934;
      fStack_98 = fStack_ac;
      fStack_94 = fStack_a8;
      fStack_90 = local_a4[0];
      FUN_004d1ea0(0,&fStack_98);
      FUN_004d1ea0(0,&local_8c);
    }
    (**(code **)(*param_1 + 0xc))(0xc,&uStack_c4,0);
    if (iStack_c0 / 0xc != 0) {
      uVar3 = (iStack_c0 / 0xc) * 0xc;
      if (uVar3 < 0x81) {
        FUN_00402330();
        uRam00000000 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
        *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = 0;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(0);
      }
    }
    puVar1 = puStack_bc;
    iVar2 = (int)fStack_b4 - (int)puStack_bc >> 2;
    if (iVar2 != 0) {
      uVar3 = iVar2 * 4;
      if (uVar3 < 0x81) {
        FUN_00402330();
        *puVar1 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puVar1;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(puStack_bc);
      }
    }
  }
  ExceptionList = pvStack_18;
  return;
}

