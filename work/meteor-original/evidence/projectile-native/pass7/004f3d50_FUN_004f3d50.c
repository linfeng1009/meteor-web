/* Original Meteor.exe static export @ 004f3d50; original sample not executed. */
/* XREF 005ab54c DATA */
/* XREF 005ab98c DATA */
/* XREF 005ab30c DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_004f3d50(int *param_1)

{
  float fVar1;
  int iVar2;
  int *piVar3;
  float unaff_ESI;
  undefined4 *puVar4;
  float *pfVar5;
  undefined1 *puVar6;
  float *pfStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_18;
  float fStack_14;
  undefined4 *puStack_c;
  float *pfStack_8;
  
  fStack_44 = 7.277014e-39;
  iVar2 = (**(code **)(*param_1 + 0x48))();
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  fStack_44 = 0.0;
  pfStack_4c = &fStack_3c;
  fStack_48 = 0.0;
  (**(code **)(*(int *)(iVar2 + 0x65c) + 4))();
  iVar2 = (**(code **)(*param_1 + 0x168))(&fStack_24);
  puVar4 = puStack_c;
  if (iVar2 == 0) {
    return 0;
  }
  *puStack_c = pfStack_4c;
  puStack_c[1] = fStack_48;
  fVar1 = fStack_44 + _DAT_005a8dbc;
  puStack_c[2] = fVar1;
  fStack_18 = fStack_24 * _DAT_005a9bac;
  fStack_14 = fStack_20 * _DAT_005a9bac;
  fStack_34 = (float)pfStack_4c + fStack_28 * _DAT_005a9bac;
  fStack_30 = fStack_48 + fStack_18;
  *pfStack_8 = fStack_34;
  fStack_2c = fVar1 + fStack_14;
  pfStack_8[1] = fStack_30;
  pfStack_8[2] = fStack_2c;
  puVar6 = &stack0xffffffc0;
  pfVar5 = &fStack_28;
  puStack_c = (undefined4 *)fVar1;
  FUN_00487830(puVar4,pfVar5,puVar6);
  iVar2 = FUN_00564920(puVar4,pfVar5,puVar6);
  if (iVar2 != 0) {
    *pfStack_8 = unaff_ESI;
    pfStack_8[1] = fStack_3c;
    pfStack_8[2] = fStack_38;
    fStack_48 = fStack_3c;
    fStack_44 = fStack_38;
    piVar3 = (int *)FUN_00487830();
    (**(code **)(*piVar3 + 0x200))(param_1[0x95],s_GunHit_005c9a5c,&pfStack_4c,0,0);
  }
  return 1;
}

