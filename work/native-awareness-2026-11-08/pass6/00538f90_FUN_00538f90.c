/* Original Meteor.exe static export @ 00538f90; original sample not executed. */
/* XREF 0052e9bc UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00538f90(void)

{
  float fVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined4 unaff_EBX;
  int iVar11;
  undefined4 unaff_EDI;
  undefined4 *puVar12;
  float10 fVar13;
  uint uStack0000000c;
  int in_stack_0000001c;
  int in_stack_00000020;
  float in_stack_00000324;
  int *in_stack_00002314;
  uint in_stack_00002324;
  int *in_stack_00002328;
  int in_stack_0000232c;
  
  FUN_00509ce0();
  iVar3 = FUN_0052e890();
  if (iVar3 != 0) {
    _DAT_007dc72c = in_stack_00002328[5];
    DAT_007500a4 = *in_stack_00002328;
    _DAT_007500ac = in_stack_00002328[1];
    DAT_0072cf00 = in_stack_00002328[2];
    _DAT_007dc724 = (uint)*(byte *)(in_stack_00002328 + 3);
    DAT_007500b4 = 0;
    _DAT_007500a8 = DAT_0072cf00;
    _DAT_007500b0 = DAT_007500a4;
    DAT_007b9584 = _DAT_007500ac;
    in_stack_00000020 = iVar3;
    iVar4 = FUN_00530d80();
    in_stack_0000001c = in_stack_0000232c * 3;
    iVar5 = FUN_00530d80();
    if ((iVar4 != 0) && (iVar5 != 0)) {
      iVar5 = FUN_00530d80();
      puVar6 = (undefined1 *)FUN_00530d80();
      iVar7 = FUN_00530d80();
      if ((iVar5 == 0) || ((puVar6 == (undefined1 *)0x0 || (iVar7 == 0)))) {
        FUN_00530db0();
        FUN_00530db0();
        FUN_00530db0();
        FUN_00530db0();
        FUN_00530db0();
        return 0;
      }
      uStack0000000c = 0;
      DAT_007dc728 = DAT_0072cf00 * DAT_007b9584 * DAT_007500a4;
      if (DAT_007dc728 != 0) {
        iVar5 = iVar5 - (int)puVar6;
        iVar10 = iVar7 - (int)puVar6;
        iVar11 = 0;
        do {
          puVar6[iVar5] = *(undefined1 *)(iVar11 + *(int *)(iVar3 + 0x14));
          *puVar6 = *(undefined1 *)(iVar11 + 1 + *(int *)(iVar3 + 0x14));
          puVar6[iVar10] = *(undefined1 *)(iVar11 + 2 + *(int *)(iVar3 + 0x14));
          uStack0000000c = uStack0000000c + 1;
          puVar6 = puVar6 + 1;
          iVar11 = iVar11 + 3;
        } while (uStack0000000c < DAT_007dc728);
      }
      DAT_0072cf04 = in_stack_0000232c;
      if (in_stack_0000232c < 0x101) {
        puVar12 = &DAT_0072cf20;
        for (iVar3 = 0x8c61; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        puVar12 = &DAT_007b95a0;
        for (iVar3 = 0x8c61; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        puVar12 = &DAT_00796400;
        for (iVar3 = 0x8c61; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        puVar12 = &DAT_00773260;
        for (iVar3 = 0x8c61; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        puVar12 = &DAT_007500c0;
        for (iVar3 = 0x8c61; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar12 = 0;
          puVar12 = puVar12 + 1;
        }
        cVar2 = FUN_005383e0();
        if (cVar2 != '\0') {
          FUN_00538530();
          iVar3 = 0;
          DAT_0072cf08 = 1;
          iVar5 = DAT_0072cf04;
          if (1 < DAT_0072cf04) {
            do {
              iVar11 = DAT_0072cf08;
              iVar10 = DAT_0072cf08 * 0x1c;
              iVar5 = FUN_00538d30();
              if (iVar5 == 0) {
                iVar11 = iVar11 + -1;
                *(undefined4 *)(&stack0x00000324 + iVar3 * 4) = 0;
                DAT_0072cf08 = iVar11;
              }
              else {
                if (*(int *)(&stack0x0000073c + iVar3 * 0x1c) < 2) {
                  fVar13 = (float10)_DAT_005a83e4;
                }
                else {
                  fVar13 = (float10)FUN_00538a90();
                }
                iVar5 = *(int *)(&stack0x0000073c + iVar10);
                *(float *)(&stack0x00000324 + iVar3 * 4) = (float)fVar13;
                if (iVar5 < 2) {
                  *(float *)(&stack0x00000324 + iVar11 * 4) = _DAT_005a83e4;
                }
                else {
                  fVar13 = (float10)FUN_00538a90();
                  *(float *)(&stack0x00000324 + iVar11 * 4) = (float)fVar13;
                }
              }
              iVar5 = 1;
              iVar3 = 0;
              fVar1 = in_stack_00000324;
              if (0 < iVar11) {
                do {
                  if (fVar1 < *(float *)(&stack0x00000324 + iVar5 * 4)) {
                    fVar1 = *(float *)(&stack0x00000324 + iVar5 * 4);
                    iVar3 = iVar5;
                  }
                  iVar5 = iVar5 + 1;
                } while (iVar5 <= iVar11);
              }
              iVar11 = iVar11 + 1;
              iVar5 = iVar11;
            } while ((fVar1 < (float)_DAT_005a84b8 == (fVar1 == (float)_DAT_005a84b8)) &&
                    (iVar5 = DAT_0072cf04, DAT_0072cf08 = iVar11, iVar11 < DAT_0072cf04));
          }
          DAT_0072cf04 = iVar5;
          iVar3 = FUN_00530d80();
          if (iVar3 != 0) {
            iVar5 = 0;
            if (0 < DAT_0072cf04) {
              do {
                FUN_00538f00();
                iVar11 = FUN_00538740();
                if (iVar11 == 0) {
                  (&stack0x00000224)[iVar5] = 0;
                  (&stack0x00000024)[iVar5] = 0;
                  (&stack0x00000124)[iVar5] = 0;
                }
                else {
                  iVar10 = FUN_00538740();
                  (&stack0x00000124)[iVar5] = (char)(iVar10 / iVar11);
                  iVar10 = FUN_00538740();
                  (&stack0x00000024)[iVar5] = (char)(iVar10 / iVar11);
                  iVar10 = FUN_00538740();
                  (&stack0x00000224)[iVar5] = (char)(iVar10 / iVar11);
                }
                iVar5 = iVar5 + 1;
              } while (iVar5 < DAT_0072cf04);
            }
            DAT_0072cf08 = 0;
            if (0 < (int)DAT_007dc728) {
              do {
                *(undefined1 *)(DAT_0072cf08 + iVar4) =
                     *(undefined1 *)((uint)*(ushort *)(DAT_007500b4 + DAT_0072cf08 * 2) + iVar3);
                DAT_0072cf08 = DAT_0072cf08 + 1;
              } while (DAT_0072cf08 < (int)DAT_007dc728);
            }
            FUN_00530db0();
            FUN_00530db0();
            if (in_stack_00002324 != 0) {
              puVar6 = (undefined1 *)(iVar7 + 2);
              uVar8 = 0;
              do {
                uVar9 = uVar8 + 1;
                puVar6[-2] = (&stack0x0000021c)[uVar8];
                puVar6[-1] = *(undefined1 *)((int)&stack0x0000001c + uVar8);
                *puVar6 = (&stack0x0000011c)[uVar8];
                puVar6 = puVar6 + 3;
                uVar8 = uVar9;
              } while (uVar9 < in_stack_00002324);
            }
            FUN_00530db0();
            FUN_00530db0();
            FUN_00530db0();
            FUN_0052c1a0();
            iVar3 = FUN_00530dc0();
            if (iVar3 == 0) {
              return 0;
            }
            FUN_0052cb10();
            *(undefined1 *)(iVar3 + 0xc) = 1;
            iVar4 = *in_stack_00002314;
            *(int *)(iVar3 + 0x10) = iVar4;
            iVar4 = in_stack_00002314[1] * iVar4;
            *(int *)(iVar3 + 0x1c) = iVar4;
            *(int *)(iVar3 + 0x18) = iVar4;
            *(undefined4 *)(iVar3 + 0x20) = 0x1900;
            *(undefined4 *)(iVar3 + 0x14) = unaff_EDI;
            *(undefined4 *)(iVar3 + 0x24) = 0x1401;
            *(undefined4 *)(iVar3 + 0x2c) = unaff_EBX;
            *(int *)(iVar3 + 0x30) = iVar7;
            *(undefined4 *)(iVar3 + 0x34) = 0x404;
            return iVar3;
          }
        }
      }
      else {
        FUN_00530d00();
      }
      FUN_00530db0();
      FUN_00530db0();
      FUN_00530db0();
      FUN_00530db0();
      FUN_00530db0();
      FUN_00530db0();
      FUN_00530db0();
      return 0;
    }
    FUN_00530db0();
    FUN_00530db0();
  }
  return 0;
}

