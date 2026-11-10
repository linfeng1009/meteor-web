/* Original Meteor.exe static export @ 0040a2a0; original sample not executed. */
/* XREF 00408ef0 UNCONDITIONAL_JUMP */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0040a2a0(uint *param_1,uint *param_2)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float *pfVar8;
  int iVar9;
  int *piVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  float10 fVar14;
  int local_1a8;
  float *local_1a0;
  int local_19c;
  float local_18c;
  float local_188;
  float local_184;
  float local_180;
  float local_17c;
  float local_178;
  float local_174;
  float local_170;
  float local_16c;
  float local_168 [27];
  undefined1 local_fc [24];
  undefined1 local_e4 [12];
  undefined1 local_d8 [12];
  undefined1 local_cc [12];
  float local_c0 [24];
  float local_60 [24];
  
  FUN_00406ed0(*param_1 | 0x2000000,local_cc,local_60,0);
  local_18c = 0.0;
  pfVar11 = local_60;
  iVar12 = 8;
  do {
    fVar14 = (float10)FUN_00431fd0(local_cc,pfVar11);
    if ((float10)local_18c < fVar14) {
      local_18c = (float)fVar14;
    }
    pfVar11 = pfVar11 + 3;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  local_18c = SQRT(local_18c);
  FUN_00406ed0(*param_2 | 0x2000000,local_d8,local_c0,0);
  local_188 = 0.0;
  pfVar11 = local_c0;
  iVar12 = 8;
  do {
    fVar14 = (float10)FUN_00431fd0(local_d8,pfVar11);
    if ((float10)local_188 < fVar14) {
      local_188 = (float)fVar14;
    }
    pfVar11 = pfVar11 + 3;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  local_188 = SQRT(local_188);
  fVar14 = (float10)FUN_00431fd0(local_cc,local_d8);
  if (fVar14 <= (float10)(local_188 + local_18c) * (float10)(local_188 + local_18c)) {
    if (local_18c <= local_188) {
      local_1a0 = local_60;
      pfVar11 = local_c0;
    }
    else {
      local_1a0 = local_c0;
      pfVar11 = local_60;
    }
    iVar12 = 0;
    do {
      piVar10 = (int *)((int)&DAT_005c4358 + iVar12);
      iVar9 = 4;
      pfVar8 = local_168 + 0x19;
      do {
        iVar13 = *piVar10;
        piVar10 = piVar10 + 1;
        iVar9 = iVar9 + -1;
        pfVar8[-1] = pfVar11[iVar13 * 3];
        *pfVar8 = pfVar11[iVar13 * 3 + 1];
        pfVar8[1] = pfVar11[iVar13 * 3 + 2];
        pfVar8 = pfVar8 + 3;
      } while (iVar9 != 0);
      FUN_00430f30((float *)((int)local_168 + iVar12),local_e4,local_168 + 0x18,local_fc);
      iVar9 = iVar12 + 0x10;
      *(float *)((int)local_168 + iVar12 + 0xc) =
           -(local_168[0x18] * *(float *)((int)local_168 + iVar12) +
            local_168[0x19] * *(float *)((int)local_168 + iVar12 + 4) +
            local_168[0x1a] * *(float *)((int)local_168 + iVar12 + 8));
      iVar12 = iVar9;
    } while (iVar9 < 0x60);
    local_19c = 0;
    do {
      local_174 = local_1a0[1];
      local_170 = local_1a0[2];
      iVar12 = 0;
      local_1a8 = 0;
      iVar9 = 0;
      do {
        fVar1 = *(float *)((int)local_168 + iVar12);
        if (*(float *)((int)local_168 + iVar12) <= _DAT_005a83e4) {
          fVar1 = -fVar1;
        }
        if ((_DAT_005a8408 < fVar1) &&
           (fVar1 = -((*(float *)((int)local_168 + iVar12 + 4) * local_1a0[1] +
                       local_1a0[2] * *(float *)((int)local_168 + iVar12 + 8) +
                       *local_1a0 * *(float *)((int)local_168 + iVar12) +
                      *(float *)((int)local_168 + iVar12 + 0xc)) /
                     *(float *)((int)local_168 + iVar12)), _DAT_005a83e4 < fVar1)) {
          local_178 = fVar1 + *local_1a0;
          iVar13 = 0;
          do {
            if (iVar13 == 0) {
              iVar2 = *(int *)((int)&DAT_005c4358 + iVar12);
              iVar3 = *(int *)((int)&DAT_005c4364 + iVar12);
            }
            else {
              iVar2 = (&DAT_005c4358)[iVar13 + iVar9];
              iVar3 = *(int *)((iVar13 + iVar9) * 4 + 0x5c4354);
            }
            FUN_00430f30(&local_184,pfVar11 + iVar3 * 3,pfVar11 + iVar2 * 3,&local_178);
          } while ((_DAT_005a83e4 <=
                    local_184 * *(float *)((int)local_168 + iVar12) +
                    local_180 * *(float *)((int)local_168 + iVar12 + 4) +
                    local_17c * *(float *)((int)local_168 + iVar12 + 8)) &&
                  (iVar13 = iVar13 + 1, iVar13 < 4));
          if (iVar13 == 4) {
            local_1a8 = local_1a8 + 1;
          }
        }
        iVar12 = iVar12 + 0x10;
        iVar9 = iVar9 + 4;
      } while (iVar12 < 0x60);
      if ((local_1a8 / 2) * 2 != local_1a8) {
        return 1;
      }
      local_19c = local_19c + 1;
    } while (local_19c < 8);
    iVar12 = 0;
    do {
      pfVar8 = (float *)((int)local_168 + iVar12);
      piVar10 = &DAT_005c43bc;
      do {
        iVar9 = piVar10[-1];
        fVar1 = local_1a0[iVar9 * 3];
        fVar4 = local_1a0[iVar9 * 3 + 1];
        fVar5 = local_1a0[iVar9 * 3 + 2];
        iVar9 = *piVar10;
        local_16c = local_1a0[iVar9 * 3] - fVar1;
        fVar6 = local_16c * *pfVar8 +
                (local_1a0[iVar9 * 3 + 2] - fVar5) * *(float *)((int)local_168 + iVar12 + 8) +
                (local_1a0[iVar9 * 3 + 1] - fVar4) * *(float *)((int)local_168 + iVar12 + 4);
        fVar7 = fVar6;
        if (fVar6 <= _DAT_005a83e4) {
          fVar7 = -fVar6;
        }
        if (((_DAT_005a8408 < fVar7) &&
            (fVar6 = -((fVar1 * *pfVar8 +
                       fVar4 * *(float *)((int)local_168 + iVar12 + 4) +
                       fVar5 * *(float *)((int)local_168 + iVar12 + 8) +
                       *(float *)((int)local_168 + iVar12 + 0xc)) / fVar6), _DAT_005a83e4 <= fVar6))
           && (fVar6 < _DAT_005a83f4 != (fVar6 == _DAT_005a83f4))) {
          local_178 = local_16c * fVar6 + fVar1;
          local_174 = (local_1a0[iVar9 * 3 + 1] - fVar4) * fVar6 + fVar4;
          local_170 = (local_1a0[iVar9 * 3 + 2] - fVar5) * fVar6 + fVar5;
          FUN_00430f30(&local_184,pfVar11 + *(int *)((int)&DAT_005c4364 + iVar12) * 3,
                       pfVar11 + *(int *)((int)&DAT_005c4358 + iVar12) * 3,&local_178);
          fVar14 = (float10)FUN_00529c80(&local_184,pfVar8);
          if ((float10)_DAT_005a83e4 <= fVar14) {
            FUN_00430f30(&local_184,pfVar11 + *(int *)((int)&DAT_005c4358 + iVar12) * 3,
                         pfVar11 + *(int *)((int)&DAT_005c435c + iVar12) * 3,&local_178);
            fVar14 = (float10)FUN_00529c80(&local_184,pfVar8);
            if ((float10)_DAT_005a83e4 <= fVar14) {
              FUN_00430f30(&local_184,pfVar11 + *(int *)((int)&DAT_005c435c + iVar12) * 3,
                           pfVar11 + *(int *)((int)&DAT_005c4360 + iVar12) * 3,&local_178);
              fVar14 = (float10)FUN_00529c80(&local_184,pfVar8);
              if ((float10)_DAT_005a83e4 <= fVar14) {
                FUN_00430f30(&local_184,pfVar11 + *(int *)((int)&DAT_005c4360 + iVar12) * 3,
                             pfVar11 + *(int *)((int)&DAT_005c4364 + iVar12) * 3,&local_178);
                fVar14 = (float10)FUN_00529c80(&local_184,pfVar8);
                if ((float10)_DAT_005a83e4 <= fVar14) {
                  return 1;
                }
              }
            }
          }
        }
        piVar10 = piVar10 + 2;
      } while ((int)piVar10 < 0x5c441c);
      iVar12 = iVar12 + 0x10;
    } while (iVar12 < 0x60);
    if (local_18c <= local_188) {
      local_1a0 = local_c0;
      pfVar11 = local_60;
    }
    else {
      local_1a0 = local_60;
      pfVar11 = local_c0;
    }
    iVar12 = 0;
    do {
      piVar10 = (int *)((int)&DAT_005c4358 + iVar12);
      iVar9 = 4;
      pfVar8 = local_168 + 0x19;
      do {
        iVar13 = *piVar10;
        piVar10 = piVar10 + 1;
        iVar9 = iVar9 + -1;
        pfVar8[-1] = pfVar11[iVar13 * 3];
        *pfVar8 = pfVar11[iVar13 * 3 + 1];
        pfVar8[1] = pfVar11[iVar13 * 3 + 2];
        pfVar8 = pfVar8 + 3;
      } while (iVar9 != 0);
      FUN_00430f30((float *)((int)local_168 + iVar12),local_e4,local_168 + 0x18,local_fc);
      iVar9 = iVar12 + 0x10;
      *(float *)((int)local_168 + iVar12 + 0xc) =
           -(local_168[0x18] * *(float *)((int)local_168 + iVar12) +
            local_168[0x19] * *(float *)((int)local_168 + iVar12 + 4) +
            local_168[0x1a] * *(float *)((int)local_168 + iVar12 + 8));
      iVar12 = iVar9;
    } while (iVar9 < 0x60);
    iVar12 = 0;
    do {
      pfVar8 = (float *)((int)local_168 + iVar12);
      piVar10 = &DAT_005c43bc;
      do {
        iVar9 = piVar10[-1];
        local_178 = local_1a0[iVar9 * 3];
        local_174 = local_1a0[iVar9 * 3 + 1];
        local_170 = local_1a0[iVar9 * 3 + 2];
        iVar9 = *piVar10;
        local_16c = local_1a0[iVar9 * 3] - local_178;
        fVar1 = local_16c * *pfVar8 +
                (local_1a0[iVar9 * 3 + 2] - local_170) * *(float *)((int)local_168 + iVar12 + 8) +
                (local_1a0[iVar9 * 3 + 1] - local_174) * *(float *)((int)local_168 + iVar12 + 4);
        fVar4 = fVar1;
        if (fVar1 <= _DAT_005a83e4) {
          fVar4 = -fVar1;
        }
        if (((_DAT_005a8408 < fVar4) &&
            (fVar1 = -((local_178 * *pfVar8 +
                       local_174 * *(float *)((int)local_168 + iVar12 + 4) +
                       local_170 * *(float *)((int)local_168 + iVar12 + 8) +
                       *(float *)((int)local_168 + iVar12 + 0xc)) / fVar1), _DAT_005a83e4 <= fVar1))
           && (fVar1 < _DAT_005a83f4)) {
          local_178 = local_16c * fVar1 + local_178;
          local_174 = (local_1a0[iVar9 * 3 + 1] - local_174) * fVar1 + local_174;
          local_170 = (local_1a0[iVar9 * 3 + 2] - local_170) * fVar1 + local_170;
          FUN_00430f30(&local_184,pfVar11 + *(int *)((int)&DAT_005c4364 + iVar12) * 3,
                       pfVar11 + *(int *)((int)&DAT_005c4358 + iVar12) * 3,&local_178);
          fVar14 = (float10)FUN_00529c80(&local_184,pfVar8);
          if ((float10)_DAT_005a83e4 <= fVar14) {
            FUN_00430f30(&local_184,pfVar11 + *(int *)((int)&DAT_005c4358 + iVar12) * 3,
                         pfVar11 + *(int *)((int)&DAT_005c435c + iVar12) * 3,&local_178);
            fVar14 = (float10)FUN_00529c80(&local_184,pfVar8);
            if ((float10)_DAT_005a83e4 <= fVar14) {
              FUN_00430f30(&local_184,pfVar11 + *(int *)((int)&DAT_005c435c + iVar12) * 3,
                           pfVar11 + *(int *)((int)&DAT_005c4360 + iVar12) * 3,&local_178);
              fVar14 = (float10)FUN_00529c80(&local_184,pfVar8);
              if ((float10)_DAT_005a83e4 <= fVar14) {
                FUN_00430f30(&local_184,pfVar11 + *(int *)((int)&DAT_005c4360 + iVar12) * 3,
                             pfVar11 + *(int *)((int)&DAT_005c4364 + iVar12) * 3,&local_178);
                fVar14 = (float10)FUN_00529c80(&local_184,pfVar8);
                if ((float10)_DAT_005a83e4 <= fVar14) {
                  return 1;
                }
              }
            }
          }
        }
        piVar10 = piVar10 + 2;
      } while ((int)piVar10 < 0x5c441c);
      iVar12 = iVar12 + 0x10;
    } while (iVar12 < 0x60);
  }
  return 0;
}

