/* Original Meteor.exe static export @ 004ce540; original sample not executed. */
/* XREF 005aa7e4 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004ce540(int *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  float fVar6;
  int *piVar7;
  float10 fVar8;
  undefined1 *puVar9;
  undefined4 uVar10;
  float fVar11;
  float fStack_68;
  float fStack_64;
  undefined4 uStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  undefined1 auStack_38 [8];
  undefined1 auStack_30 [4];
  float fStack_2c;
  float fStack_28;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  
  if (param_1[0xd3] != 0) {
    uStack_48 = 0;
    fStack_44 = 0.0;
    fStack_40 = 1.0;
    if (param_1[4] == 0) {
      piVar7 = (int *)0x0;
    }
    else {
      piVar7 = (int *)(param_1[4] + -0x65c);
    }
    puVar9 = auStack_30;
    uVar10 = 2;
    (**(code **)(*piVar7 + 0x6c))(puVar9,2);
    fVar3 = fStack_c;
    fVar2 = fStack_10;
    fVar1 = fStack_14;
    thunk_FUN_0040c6f0(param_1[0xd3],auStack_38,2);
    fVar6 = fStack_14 - fVar1;
    fVar11 = fStack_10 - fVar2;
    fStack_54 = fStack_c - fVar3;
    fStack_5c = fVar6;
    fStack_58 = fVar11;
    fVar8 = (float10)FUN_0047ecf0(puVar9,uVar10,fVar6,fVar11,fStack_54);
    if ((fVar8 < (float10)_DAT_005aa924) &&
       (uVar4 = __ftol(), (int)((uVar4 ^ (int)uVar4 >> 0x1f) - ((int)uVar4 >> 0x1f)) < 100)) {
      uVar10 = 0;
      iVar5 = FUN_0047ec40();
      fStack_64 = fVar11;
      uStack_60 = uVar10;
      if (iVar5 == 0) {
        uStack_60 = 0;
        fVar6 = fStack_2c;
        fStack_64 = -fStack_28;
      }
      fStack_40 = fVar2;
      fStack_3c = fVar3;
      fStack_44 = fVar1;
      fStack_68 = fVar6;
      (**(code **)(*piVar7 + 0x74))(&fStack_44,&fStack_68,auStack_50);
      return;
    }
    (**(code **)(*param_1 + 0xc))(6,0,0);
  }
  return;
}

