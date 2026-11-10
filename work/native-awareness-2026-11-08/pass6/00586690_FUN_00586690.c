/* Original Meteor.exe static export @ 00586690; original sample not executed. */
/* XREF 00585fe2 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00586690(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int *piVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  int iVar13;
  float *pfVar14;
  int iVar15;
  float *pfVar16;
  float10 fVar17;
  int local_10c;
  undefined1 auStack_18 [12];
  undefined1 auStack_c [12];
  
  iVar15 = *(int *)(param_1 + 0x28c);
  if ((iVar15 != 0) && (local_10c = 0, 0 < *(int *)(param_1 + 0x268))) {
    pfVar16 = (float *)(iVar15 + 0xc);
    do {
      if (*(int *)(param_1 + 0x274) != 0) {
        pfVar16[0x20] = (_DAT_005a83f4 - pfVar16[0x22] / pfVar16[0x24]) * pfVar16[0x21];
      }
      piVar6 = *(int **)(param_1 + 0x298);
      if (piVar6 == (int *)0x0) {
        fVar1 = pfVar16[0x20];
        fVar7 = *(float *)(*(int *)(param_1 + 8) + 0x30);
        pfVar16[-1] = fVar1 * pfVar16[8] * fVar7 + pfVar16[-1];
        *pfVar16 = fVar1 * pfVar16[9] * fVar7 + *pfVar16;
        pfVar16[1] = fVar1 * pfVar16[10] * fVar7 + pfVar16[1];
LAB_005868c4:
        pfVar16[0x22] = *(float *)(*(int *)(param_1 + 8) + 0x30) + pfVar16[0x22];
        pfVar16[0x23] = *(float *)(*(int *)(param_1 + 8) + 0x30) + pfVar16[0x23];
        if ((_DAT_005a83e4 < pfVar16[0x22]) && (pfVar16[0x24] <= pfVar16[0x22])) {
          if (*(int *)(param_1 + 0x270) != 0) {
            FUN_00585e30(local_10c);
            local_10c = local_10c + -1;
            goto LAB_00586d06;
          }
          FUN_00586d40(iVar15);
        }
        if (pfVar16[0x25] < pfVar16[0x23]) {
          fVar1 = *(float *)(param_1 + 0x340);
          fVar7 = pfVar16[10];
          fVar8 = pfVar16[10] - *(float *)(param_1 + 0x340);
          iVar13 = _rand();
          fVar11 = (float)iVar13 * _DAT_005a8f78;
          fVar9 = pfVar16[9] - *(float *)(param_1 + 0x33c);
          fVar2 = pfVar16[9];
          fVar3 = *(float *)(param_1 + 0x33c);
          iVar13 = _rand();
          pfVar14 = pfVar16 + 8;
          fVar12 = (float)iVar13 * _DAT_005a8f78;
          fVar10 = *pfVar14 - *(float *)(param_1 + 0x338);
          fVar4 = *pfVar14;
          fVar5 = *(float *)(param_1 + 0x338);
          iVar13 = _rand();
          *pfVar14 = ((fVar4 + fVar5) - fVar10) * (float)iVar13 * _DAT_005a8f78 + fVar10;
          pfVar16[9] = ((fVar2 + fVar3) - fVar9) * fVar12 + fVar9;
          pfVar16[10] = ((fVar1 + fVar7) - fVar8) * fVar11 + fVar8;
          FUN_0047ec40();
          fVar1 = *(float *)(param_1 + 0x300);
          fVar7 = *(float *)(param_1 + 0x304);
          iVar13 = _rand();
          pfVar16[0x23] = 0.0;
          fVar7 = (fVar1 - fVar7) * (float)iVar13 * _DAT_005a8f78 + fVar7;
          pfVar16[0x20] = fVar7;
          pfVar16[0x21] = fVar7;
        }
        if ((*(int *)(param_1 + 0x294) == 0) || (*(int *)(param_1 + 0x2a0) != 2)) {
          if (*(int *)(param_1 + 0x2a8) != 0) {
            pfVar14 = (float *)FUN_00476e80(auStack_c,pfVar16 + 2,*(int *)(param_1 + 0x2a8));
            pfVar16[5] = *pfVar14;
            pfVar16[6] = pfVar14[1];
            pfVar16[7] = pfVar14[2];
            fVar1 = pfVar16[5];
            fVar7 = pfVar16[-1];
            fVar2 = pfVar16[6];
            fVar3 = *pfVar16;
            fVar4 = pfVar16[7];
            fVar5 = pfVar16[1];
            FUN_0047ec40();
            fVar8 = *(float *)(*(int *)(param_1 + 8) + 0x30) * *(float *)(param_1 + 0x2e4);
            pfVar16[8] = (fVar1 - fVar7) * fVar8 + pfVar16[8];
            pfVar16[9] = (fVar2 - fVar3) * fVar8 + pfVar16[9];
            pfVar16[10] = (fVar4 - fVar5) * fVar8 + pfVar16[10];
            FUN_0047ec40();
          }
        }
        else {
          pfVar14 = (float *)FUN_00476e80(auStack_18,pfVar16 + 2,*(int *)(param_1 + 0x294) + 0x58);
          pfVar16[5] = *pfVar14;
          pfVar16[6] = pfVar14[1];
          pfVar16[7] = pfVar14[2];
          iVar13 = (**(code **)(**(int **)(param_1 + 0x294) + 0x60))(pfVar16 + -1);
          if (iVar13 == 0) {
            fVar1 = pfVar16[5];
            fVar7 = pfVar16[-1];
            fVar2 = pfVar16[6];
            fVar3 = *pfVar16;
            fVar4 = pfVar16[7];
            fVar5 = pfVar16[1];
            FUN_0047ec40();
            fVar8 = *(float *)(*(int *)(param_1 + 8) + 0x30) * *(float *)(param_1 + 0x2e4);
            pfVar16[8] = (fVar1 - fVar7) * fVar8 + pfVar16[8];
            pfVar16[9] = (fVar2 - fVar3) * fVar8 + pfVar16[9];
            pfVar16[10] = (fVar4 - fVar5) * fVar8 + pfVar16[10];
            FUN_0047ec40();
          }
          else {
            if (*(int *)(param_1 + 0x270) != 0) {
              FUN_00585e30(local_10c);
              local_10c = local_10c + -1;
              goto LAB_00586d06;
            }
            FUN_00586d40(iVar15);
          }
        }
        if (*(int *)(param_1 + 0x318) != 0) {
          fVar17 = (float10)FUN_004748b0();
          pfVar16[0x27] = (float)(fVar17 * (float10)pfVar16[0x26] + (float10)pfVar16[0x27]);
          FUN_00477200();
          FUN_004782e0(pfVar16[0x27],pfVar16[0xb],pfVar16[0xc],pfVar16[0xd],0);
          FUN_00477b90(3,pfVar16 + -1);
        }
      }
      else {
        iVar13 = piVar6[0x7b];
        fVar1 = (pfVar16[0x22] * pfVar16[0x20]) / *(float *)(iVar13 + 0x34);
        if (fVar1 < _DAT_005a83f4) {
          (**(code **)(*piVar6 + 0x40))
                    (fVar1 * *(float *)(iVar13 + 0x1c) + *(float *)(iVar13 + 0x14));
          iVar13 = *(int *)(param_1 + 0x298);
          fVar3 = *(float *)(*(int *)(param_1 + 8) + 0x30) * pfVar16[0x20];
          fVar4 = _DAT_005a83f4 - *(float *)(param_1 + 0x2e4);
          fVar1 = *(float *)(param_1 + 0x2e4);
          fVar7 = *(float *)(iVar13 + 0x40);
          fVar2 = *(float *)(iVar13 + 0x44);
          pfVar16[-1] = fVar1 * *(float *)(iVar13 + 0x3c) +
                        (fVar3 * pfVar16[8] + pfVar16[-1]) * fVar4;
          *pfVar16 = fVar1 * fVar7 + (fVar3 * pfVar16[9] + *pfVar16) * fVar4;
          pfVar16[1] = fVar1 * fVar2 + (fVar3 * pfVar16[10] + pfVar16[1]) * fVar4;
          goto LAB_005868c4;
        }
        if (*(int *)(param_1 + 0x270) == 0) {
          FUN_00586d40(iVar15);
          goto LAB_005868c4;
        }
        FUN_00585e30(local_10c);
        local_10c = local_10c + -1;
      }
LAB_00586d06:
      local_10c = local_10c + 1;
      iVar15 = iVar15 + 0xac;
      pfVar16 = pfVar16 + 0x2b;
    } while (local_10c < *(int *)(param_1 + 0x268));
  }
  return;
}

