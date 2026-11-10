/* Original Meteor.exe static export @ 00557fa0; original sample not executed. */
/* XREF 005ae184 DATA */
/* XREF 0055c0f7 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00557fa0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  float *pfVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  float fStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float fStack_c4;
  int local_c0;
  int local_bc;
  undefined1 local_b8 [8];
  float local_b0;
  float fStack_a8;
  undefined1 local_a0 [4];
  float afStack_9c [23];
  undefined1 local_40 [64];
  
  *(undefined4 *)(param_1 + 0x1cc) = 0x501502f9;
  *(undefined4 *)(param_1 + 0x1c8) = 0x501502f9;
  *(undefined4 *)(param_1 + 0x1c4) = 0x501502f9;
  *(undefined4 *)(param_1 + 0x1d8) = 0xd01502f9;
  *(undefined4 *)(param_1 + 0x1d4) = 0xd01502f9;
  *(undefined4 *)(param_1 + 0x1d0) = 0xd01502f9;
  iVar8 = *(int *)(param_1 + 0x1c);
  if (0 < iVar8) {
    pfVar6 = (float *)(*(int *)(param_1 + 0x350) + 0x88);
    do {
      if (pfVar6[-0x17] != 0.0) {
        iVar5 = 8;
        pfVar4 = pfVar6;
        do {
          if (pfVar4[-1] < *(float *)(param_1 + 0x1c4)) {
            *(float *)(param_1 + 0x1c4) = pfVar4[-1];
          }
          if (*(float *)(param_1 + 0x1d0) < pfVar4[-1]) {
            *(float *)(param_1 + 0x1d0) = pfVar4[-1];
          }
          if (*pfVar4 < *(float *)(param_1 + 0x1c8)) {
            *(float *)(param_1 + 0x1c8) = *pfVar4;
          }
          if (*(float *)(param_1 + 0x1d4) < *pfVar4) {
            *(float *)(param_1 + 0x1d4) = *pfVar4;
          }
          if (pfVar4[1] < *(float *)(param_1 + 0x1cc)) {
            *(float *)(param_1 + 0x1cc) = pfVar4[1];
          }
          if (*(float *)(param_1 + 0x1d8) < pfVar4[1]) {
            *(float *)(param_1 + 0x1d8) = pfVar4[1];
          }
          pfVar4 = pfVar4 + 3;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
      pfVar6 = pfVar6 + 0xcd;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  pfVar6 = (float *)(param_1 + 0x294);
  *(float *)(param_1 + 0x1ac) = *(float *)(param_1 + 0x1d0) - *(float *)(param_1 + 0x1c4);
  *(float *)(param_1 + 0x1b0) = *(float *)(param_1 + 0x1d4) - *(float *)(param_1 + 0x1c8);
  *(float *)(param_1 + 0x1b4) = *(float *)(param_1 + 0x1d8) - *(float *)(param_1 + 0x1cc);
  local_b0 = *(float *)(param_1 + 0x1d8) + *(float *)(param_1 + 0x1cc);
  fVar1 = (*(float *)(param_1 + 0x1d4) + *(float *)(param_1 + 0x1c8)) * _DAT_005a83e8;
  *(float *)(param_1 + 0x1dc) =
       (*(float *)(param_1 + 0x1d0) + *(float *)(param_1 + 0x1c4)) * _DAT_005a83e8;
  fVar2 = local_b0 * _DAT_005a83e8;
  *(float *)(param_1 + 0x1e0) = fVar1;
  *(float *)(param_1 + 0x1e4) = fVar2;
  *(float *)(param_1 + 0x1b8) = *(float *)(param_1 + 0x1d0) - *(float *)(param_1 + 0x1dc);
  *(float *)(param_1 + 0x1bc) = *(float *)(param_1 + 0x1d4) - *(float *)(param_1 + 0x1e0);
  *(float *)(param_1 + 0x1c0) = *(float *)(param_1 + 0x1d8) - *(float *)(param_1 + 0x1e4);
  *(float *)(param_1 + 0x288) = *(float *)(param_1 + 0x1c4);
  *(undefined4 *)(param_1 + 0x28c) = *(undefined4 *)(param_1 + 0x1c8);
  *(undefined4 *)(param_1 + 0x290) = *(undefined4 *)(param_1 + 0x1cc);
  *pfVar6 = *(float *)(param_1 + 0x1d0);
  *(undefined4 *)(param_1 + 0x298) = *(undefined4 *)(param_1 + 0x1d4);
  *(undefined4 *)(param_1 + 0x29c) = *(undefined4 *)(param_1 + 0x1d8);
  local_c0 = 0;
  if (0 < *(int *)(param_1 + 0x20)) {
    local_bc = 0;
    do {
      iVar5 = *(int *)(param_1 + 0x354) + local_bc;
      iVar8 = *(int *)(iVar5 + 0xa8);
      if (iVar8 != 0) {
        puVar7 = (undefined4 *)(iVar5 + 0x3c);
        puVar9 = (undefined4 *)(iVar8 + 0x54);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar9 = *puVar7;
          puVar7 = puVar7 + 1;
          puVar9 = puVar9 + 1;
        }
        (**(code **)(**(int **)(local_bc + 0xa8 + *(int *)(param_1 + 0x354)) + 4))
                  (local_40,local_b8,local_a0);
        fStack_c4 = *(float *)(param_1 + 0x288);
        fStack_c8 = *pfVar6;
        fStack_d4 = *(float *)(param_1 + 0x28c);
        fStack_d0 = *(float *)(param_1 + 0x298);
        fStack_cc = *(float *)(param_1 + 0x290);
        fVar1 = *(float *)(param_1 + 0x29c);
        pfVar4 = afStack_9c;
        iVar8 = 8;
        do {
          if (pfVar4[-1] < fStack_c4) {
            fStack_c4 = pfVar4[-1];
          }
          if (fStack_c8 < pfVar4[-1]) {
            fStack_c8 = pfVar4[-1];
          }
          if (*pfVar4 < fStack_d4) {
            fStack_d4 = *pfVar4;
          }
          if (fStack_d0 < *pfVar4) {
            fStack_d0 = *pfVar4;
          }
          if (pfVar4[1] < fStack_cc) {
            fStack_cc = pfVar4[1];
          }
          if (fVar1 < pfVar4[1]) {
            fVar1 = pfVar4[1];
          }
          pfVar4 = pfVar4 + 3;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        *pfVar6 = fStack_c8;
        *(float *)(param_1 + 0x288) = fStack_c4;
        *(float *)(param_1 + 0x290) = fStack_cc;
        *(float *)(param_1 + 0x29c) = fVar1;
        *(float *)(param_1 + 0x28c) = fStack_d4;
        *(float *)(param_1 + 0x298) = fStack_d0;
      }
      local_c0 = local_c0 + 1;
      local_bc = local_bc + 0x2f0;
    } while (local_c0 < *(int *)(param_1 + 0x20));
  }
  pfVar4 = (float *)(param_1 + 0x2ac);
  *(float *)(param_1 + 0x2a0) = *pfVar6 - *(float *)(param_1 + 0x288);
  *(float *)(param_1 + 0x2a4) = *(float *)(param_1 + 0x298) - *(float *)(param_1 + 0x28c);
  *(float *)(param_1 + 0x2a8) = *(float *)(param_1 + 0x29c) - *(float *)(param_1 + 0x290);
  local_b0 = *(float *)(param_1 + 0x29c) + *(float *)(param_1 + 0x290);
  fVar1 = (*(float *)(param_1 + 0x298) + *(float *)(param_1 + 0x28c)) * _DAT_005a83e8;
  *pfVar4 = (*pfVar6 + *(float *)(param_1 + 0x288)) * _DAT_005a83e8;
  fVar2 = local_b0 * _DAT_005a83e8;
  *(float *)(param_1 + 0x2b0) = fVar1;
  *(float *)(param_1 + 0x2b4) = fVar2;
  *(float *)(param_1 + 0x2b8) = *pfVar6 - *pfVar4;
  *(float *)(param_1 + 700) = *(float *)(param_1 + 0x298) - *(float *)(param_1 + 0x2b0);
  *(float *)(param_1 + 0x2c0) = *(float *)(param_1 + 0x29c) - *(float *)(param_1 + 0x2b4);
  FUN_00477200();
  FUN_00477b90(3,pfVar4);
  fVar1 = *(float *)(param_1 + 0x1ac);
  fStack_a8 = *(float *)(param_1 + 0x1b0);
  local_b0 = *(float *)(param_1 + 0x1b4);
  FUN_00477200();
  FUN_00477b90(3,param_1 + 0x1dc);
  pfVar6 = (float *)(param_1 + 0x1c4);
  *(float *)(param_1 + 0x1e8) = *pfVar6;
  *(undefined4 *)(param_1 + 0x1ec) = *(undefined4 *)(param_1 + 0x1c8);
  *(undefined4 *)(param_1 + 0x1f0) = *(undefined4 *)(param_1 + 0x1cc);
  pfVar4 = (float *)(param_1 + 500);
  *pfVar4 = fVar1 + *pfVar6;
  *(undefined4 *)(param_1 + 0x1f8) = *(undefined4 *)(param_1 + 0x1c8);
  *(undefined4 *)(param_1 + 0x1fc) = *(undefined4 *)(param_1 + 0x1cc);
  *(float *)(param_1 + 0x200) = *pfVar4;
  *(undefined4 *)(param_1 + 0x204) = *(undefined4 *)(param_1 + 0x1f8);
  *(float *)(param_1 + 0x208) = local_b0 + *(float *)(param_1 + 0x1fc);
  *(float *)(param_1 + 0x20c) = *pfVar6;
  *(undefined4 *)(param_1 + 0x210) = *(undefined4 *)(param_1 + 0x1c8);
  *(float *)(param_1 + 0x214) = local_b0 + *(float *)(param_1 + 0x1cc);
  *(float *)(param_1 + 0x218) = *(float *)(param_1 + 0x1e8);
  *(float *)(param_1 + 0x21c) = fStack_a8 + *(float *)(param_1 + 0x1ec);
  *(undefined4 *)(param_1 + 0x220) = *(undefined4 *)(param_1 + 0x1f0);
  *(float *)(param_1 + 0x224) = *pfVar4;
  *(float *)(param_1 + 0x228) = fStack_a8 + *(float *)(param_1 + 0x1f8);
  *(undefined4 *)(param_1 + 0x22c) = *(undefined4 *)(param_1 + 0x1fc);
  *(float *)(param_1 + 0x230) = *(float *)(param_1 + 0x200);
  *(float *)(param_1 + 0x234) = fStack_a8 + *(float *)(param_1 + 0x204);
  *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(param_1 + 0x208);
  *(float *)(param_1 + 0x23c) = *(float *)(param_1 + 0x20c);
  *(float *)(param_1 + 0x240) = fStack_a8 + *(float *)(param_1 + 0x210);
  *(undefined4 *)(param_1 + 0x244) = *(undefined4 *)(param_1 + 0x214);
  return;
}

