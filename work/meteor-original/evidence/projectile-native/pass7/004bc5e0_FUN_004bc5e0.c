/* Original Meteor.exe static export @ 004bc5e0; original sample not executed. */
/* XREF 005aa0c4 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004bc5e0(int *param_1,float *param_2,float *param_3)

{
  undefined4 uVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  uVar1 = FUN_00410ce0(&fStack_30,&fStack_24,0);
  FUN_00407c10(uVar1);
  *param_2 = fStack_30;
  param_2[1] = fStack_2c;
  param_2[2] = fStack_28;
  fStack_48 = fStack_24;
  fStack_44 = fStack_20;
  fStack_40 = fStack_1c;
  fStack_14 = fStack_20 * _DAT_005a9bac;
  fStack_10 = fStack_1c * _DAT_005a9bac;
  fStack_3c = fStack_30 + fStack_24 * _DAT_005a9bac;
  fStack_38 = fStack_2c + fStack_14;
  *param_3 = fStack_3c;
  fStack_34 = fStack_28 + fStack_10;
  param_3[1] = fStack_38;
  param_3[2] = fStack_34;
  pfVar4 = &fStack_c;
  pfVar3 = &fStack_48;
  FUN_00487830(param_2,pfVar3,pfVar4);
  iVar2 = FUN_00564920(param_2,pfVar3,pfVar4);
  if (iVar2 != 0) {
    *param_3 = fStack_c;
    param_3[1] = fStack_8;
    param_3[2] = fStack_4;
    (**(code **)(*param_1 + 0x140))(s_GunHit_005c9a5c,fStack_c,fStack_8,fStack_4,0);
  }
  return 1;
}

