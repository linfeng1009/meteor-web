/* Original Meteor.exe static export @ 004c08d0; original sample not executed. */
/* XREF 004c083f UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004c08d0(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  char cVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  float10 fVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  uint local_74;
  int local_70;
  undefined1 local_68 [8];
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  local_48 = DAT_005e0878;
  local_44 = DAT_005e087c;
  local_40 = DAT_005e0880;
  pfVar6 = (float *)FUN_00476090(2);
  local_30 = *pfVar6;
  local_2c = pfVar6[1];
  local_28 = pfVar6[2];
  FUN_00501d90(6);
  if ((DAT_0066627c & 1) == 0) {
    DAT_0066627c = DAT_0066627c | 1;
    _DAT_00666204 = 0x3f4ccccd;
    _DAT_00666208 = 0x3f666666;
    _DAT_0066620c = 0x3f800000;
    _DAT_00666210 = 0x3e99999a;
    _DAT_00666214 = 0x3f4ccccd;
    _DAT_00666218 = 0x3e4ccccd;
    _DAT_0066621c = 0x3e99999a;
    _DAT_00666220 = 0x3ecccccd;
    _DAT_00666224 = 0x3f800000;
    _DAT_00666228 = 0x3f800000;
    _DAT_0066622c = 0x3e4ccccd;
    _DAT_00666230 = 0x3e99999a;
    FUN_005089bc(&DAT_004c0dc0);
  }
  iVar7 = *(int *)(param_1 + 0x500) - *(int *)(param_1 + 0x4fc);
  iVar8 = iVar7 >> 0x1f;
  local_74 = 0;
  if (iVar7 / 0x24 + iVar8 != iVar8) {
    local_70 = 0;
    do {
      iVar8 = *(int *)(param_1 + 0x4fc) + local_70;
      local_60 = *(float *)(iVar8 + 4) - local_48;
      puVar1 = (undefined4 *)(iVar8 + 4);
      local_5c = *(float *)(iVar8 + 8) - local_44;
      local_58 = *(float *)(iVar8 + 0xc) - local_40;
      local_3c = local_60;
      local_38 = local_5c;
      local_34 = local_58;
      fVar10 = (float10)FUN_0047ecf0();
      if (fVar10 <= (float10)_DAT_005a9bac) {
        if (_DAT_005a83ec < (float)fVar10) {
          fVar4 = _DAT_005a83f4 / (float)fVar10;
          local_60 = local_60 * fVar4;
          local_5c = local_5c * fVar4;
          local_58 = fVar4 * local_58;
          local_54 = local_60;
          local_50 = local_5c;
          local_4c = local_58;
          if (local_60 * local_30 + local_2c * local_5c + local_28 * local_58 < _DAT_005a83e8)
          goto LAB_004c0cc7;
        }
        fVar5 = (float)(int)*(short *)(iVar8 + 0x14) * _DAT_005a83e8;
        FUN_00501e70();
        FUN_00501f00(*puVar1,*(undefined4 *)(iVar8 + 8),*(undefined4 *)(iVar8 + 0xc));
        FUN_00501cb0(&DAT_00666204 + *(char *)(iVar8 + 0x10) * 0xc);
        FUN_005019e0(6);
        fVar4 = -fVar5;
        FUN_00501c40(fVar4,fVar5);
        FUN_00501c40(fVar4,fVar4);
        FUN_00501c40(fVar5,fVar4);
        FUN_00501c40(fVar5,fVar5);
        FUN_00501a20();
        FUN_00501ec0();
        FUN_00508ae6(local_68,&DAT_005c9b80,local_74);
        iVar7 = *(char *)(iVar8 + 0x10) * 0xc;
        FUN_00501c90(*(float *)(&DAT_00666204 + iVar7) * _DAT_005a83e8,
                     *(float *)(&DAT_00666208 + iVar7) * _DAT_005a83e8,
                     *(float *)(&DAT_0066620c + iVar7) * _DAT_005a83e8);
        local_24 = *puVar1;
        local_20 = *(undefined4 *)(iVar8 + 8);
        local_1c = *(float *)(iVar8 + 0xc) + _DAT_005a8f74;
        FUN_00501780(local_68,&local_24,0x41200000,1);
        uVar9 = 0;
        if (*(int *)(iVar8 + 0x1c) - *(int *)(iVar8 + 0x18) >> 3 != 0) {
          do {
            cVar3 = *(char *)(*(int *)(iVar8 + 0x18) + 2 + uVar9 * 8);
            if (cVar3 == '\0') {
              uVar13 = 0x3f800000;
              uVar12 = 0x3f666666;
              uVar11 = 0x3f4ccccd;
LAB_004c0c31:
              FUN_00501c90(uVar11,uVar12,uVar13);
            }
            else {
              if (cVar3 == '\x01') {
                uVar13 = 0x3f800000;
                uVar12 = 0x3f800000;
                uVar11 = 0x3f000000;
                goto LAB_004c0c31;
              }
              if (cVar3 == '\x02') {
                uVar13 = 0;
                uVar12 = 0;
                uVar11 = 0x3f800000;
                goto LAB_004c0c31;
              }
            }
            uStack_18 = *puVar1;
            uStack_14 = *(undefined4 *)(iVar8 + 8);
            uStack_10 = *(undefined4 *)(iVar8 + 0xc);
            puVar2 = (undefined4 *)
                     (*(int *)(param_1 + 0x4fc) + 4 +
                     (uint)*(ushort *)(*(int *)(iVar8 + 0x18) + uVar9 * 8) * 0x24);
            uStack_c = *puVar2;
            uStack_8 = puVar2[1];
            uStack_4 = puVar2[2];
            FUN_005019e0(1);
            FUN_00501c20(&uStack_18);
            FUN_00501c20(&uStack_c);
            FUN_00501a20();
            uVar9 = uVar9 + 1;
          } while (uVar9 < (uint)(*(int *)(iVar8 + 0x1c) - *(int *)(iVar8 + 0x18) >> 3));
        }
      }
LAB_004c0cc7:
      local_70 = local_70 + 0x24;
      local_74 = local_74 + 1;
    } while (local_74 < (uint)((*(int *)(param_1 + 0x500) - *(int *)(param_1 + 0x4fc)) / 0x24));
  }
  if ((DAT_0066627e != '\0') && (DAT_00666281 != '\0')) {
    FUN_00501d10(1);
    FUN_00501c60(0x3f4ccccd,0x3f666666,0x3f800000,0x3f000000);
    FUN_005019e0(1);
    FUN_00501c20(&DAT_00666234);
    FUN_00501b40(DAT_00666234,DAT_00666238,DAT_0066623c - _DAT_005a8dbc);
    FUN_00501a20();
    FUN_00501e70();
    FUN_00501f00(DAT_00666234,DAT_00666238,DAT_0066623c);
    FUN_00502050(0x41200000);
    FUN_00501ec0();
    FUN_00501d90(1);
  }
  FUN_00501d10(6);
  return;
}

