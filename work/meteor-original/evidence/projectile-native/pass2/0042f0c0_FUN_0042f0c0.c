/* Original Meteor.exe static export @ 0042f0c0; original sample not executed. */
/* XREF 0042d17f UNCONDITIONAL_CALL */
/* XREF 0042d287 UNCONDITIONAL_CALL */
/* XREF 0042d2bc UNCONDITIONAL_CALL */
/* XREF 0042d2f3 UNCONDITIONAL_CALL */
/* XREF 0042d33f UNCONDITIONAL_CALL */
/* XREF 0042d376 UNCONDITIONAL_CALL */
/* XREF 0042d8d1 UNCONDITIONAL_CALL */
/* XREF 0042d93f UNCONDITIONAL_CALL */
/* XREF 0042d95a UNCONDITIONAL_CALL */
/* XREF 0042d9f4 UNCONDITIONAL_CALL */
/* XREF 0042da35 UNCONDITIONAL_CALL */
/* XREF 0042dad9 UNCONDITIONAL_CALL */
/* XREF 0042dafd UNCONDITIONAL_CALL */
/* XREF 0042db11 UNCONDITIONAL_CALL */
/* XREF 0042db74 UNCONDITIONAL_CALL */
/* XREF 0042d7c9 UNCONDITIONAL_CALL */
/* XREF 0042d7ef UNCONDITIONAL_CALL */
/* XREF 0042e5a1 UNCONDITIONAL_CALL */
/* XREF 0042e5ba UNCONDITIONAL_CALL */
/* XREF 0042e5ea UNCONDITIONAL_CALL */
/* XREF 0042e671 UNCONDITIONAL_CALL */
/* XREF 0042e6f0 UNCONDITIONAL_CALL */
/* XREF 0042e910 UNCONDITIONAL_CALL */
/* XREF 0042e965 UNCONDITIONAL_CALL */
/* XREF 0042e994 UNCONDITIONAL_CALL */
/* XREF 0042ea1f UNCONDITIONAL_CALL */
/* XREF 0042ea95 UNCONDITIONAL_CALL */
/* XREF 0042eafb UNCONDITIONAL_CALL */
/* XREF 0042ebc6 UNCONDITIONAL_CALL */
/* XREF 0042ec39 UNCONDITIONAL_CALL */
/* XREF 0042ecab UNCONDITIONAL_CALL */
/* XREF 0042ed58 UNCONDITIONAL_CALL */
/* XREF 0042f0a4 UNCONDITIONAL_CALL */
/* XREF 0042d3ad UNCONDITIONAL_CALL */
/* XREF 0042d1f9 UNCONDITIONAL_CALL */
/* XREF 0042d229 UNCONDITIONAL_CALL */
/* XREF 0042d862 UNCONDITIONAL_CALL */
/* XREF 0042d87d UNCONDITIONAL_CALL */
/* XREF 0042dd0e UNCONDITIONAL_CALL */
/* XREF 0042dd30 UNCONDITIONAL_CALL */
/* XREF 0042ddbd UNCONDITIONAL_CALL */
/* XREF 0042ddd6 UNCONDITIONAL_CALL */
/* XREF 0042df1d UNCONDITIONAL_CALL */
/* XREF 0042dfea UNCONDITIONAL_CALL */
/* XREF 0042e09a UNCONDITIONAL_CALL */
/* XREF 0042e0cf UNCONDITIONAL_CALL */
/* XREF 0042e117 UNCONDITIONAL_CALL */
/* XREF 0042e14c UNCONDITIONAL_CALL */
/* XREF 0042e1f6 UNCONDITIONAL_CALL */
/* XREF 0042e254 UNCONDITIONAL_CALL */
/* XREF 0042e2fe UNCONDITIONAL_CALL */
/* XREF 0042e336 UNCONDITIONAL_CALL */
/* XREF 0042e3b6 UNCONDITIONAL_CALL */
/* XREF 0042e3e6 UNCONDITIONAL_CALL */
/* XREF 0042e43f UNCONDITIONAL_CALL */
/* XREF 0042e466 UNCONDITIONAL_CALL */
/* XREF 0042e4ce UNCONDITIONAL_CALL */

void FUN_0042f0c0(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  char *pcVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  char *pcVar16;
  int iVar17;
  int iVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  int local_e4;
  int *local_e0;
  int local_dc;
  int *local_d8;
  int local_d0;
  int local_c8;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  undefined4 local_a4;
  char local_a0 [80];
  char local_50 [80];
  
  if (((DAT_005d5a0c == 0) || (param_1 == 0)) || (*(int *)(param_1 + 0x9c) == 0)) {
    return;
  }
  FUN_0040e660();
  iVar13 = *(int *)(param_1 + 0x44);
  if (((iVar13 == 2) || (iVar13 == 3)) || (iVar13 == 10)) {
    if (*(int *)(param_1 + 0x84) == 0) {
      uVar8 = *(undefined4 *)(param_1 + 0x48);
      goto LAB_0042f151;
    }
    uVar8 = *(undefined4 *)(param_1 + 0x80);
    uVar7 = *(undefined4 *)(param_1 + 0x58);
    uVar11 = *(undefined4 *)(param_1 + 0x54);
    uVar20 = *(undefined4 *)(param_1 + 0x50);
    uVar19 = *(undefined4 *)(param_1 + 0x4c);
  }
  else if (iVar13 == 7) {
    uVar8 = *(undefined4 *)(param_1 + 0x80);
LAB_0042f151:
    uVar7 = *(undefined4 *)(param_1 + 0x58);
    uVar11 = *(undefined4 *)(param_1 + 0x54);
    uVar20 = *(undefined4 *)(param_1 + 0x50);
    uVar19 = *(undefined4 *)(param_1 + 0x4c);
  }
  else {
    uVar8 = *(undefined4 *)(param_1 + 0x48);
    uVar7 = *(undefined4 *)(param_1 + 0x58);
    uVar11 = *(undefined4 *)(param_1 + 0x54);
    uVar20 = *(undefined4 *)(param_1 + 0x50);
    uVar19 = *(undefined4 *)(param_1 + 0x4c);
  }
  FUN_0041f900(uVar19,uVar20,uVar11,uVar7,uVar8);
  uVar7 = FUN_0041f6b0(0x5a,0x5a,0x5a);
  uVar8 = FUN_0041f6b0(0xff,0xff,0xff);
  if (((*(int *)(param_1 + 100) != 0) && (*(int *)(param_1 + 0x98) != 0)) ||
     ((*(int *)(param_1 + 0x84) != 0 ||
      ((*(int *)(param_1 + 0x44) != 10 && ((*(uint *)(param_1 + 0x5c) & 0xff000000) == 0)))))) {
    uVar9 = *(uint *)(param_1 + 0x5c) & 0xffffff;
    if (uVar9 == 0) {
      FUN_0041f9c0(*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x50));
      FUN_0041f9e0(*(int *)(param_1 + 0x54) + -1 + *(int *)(param_1 + 0x4c),
                   *(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x60));
      FUN_0041f9e0(*(int *)(param_1 + 0x54) + -1 + *(int *)(param_1 + 0x4c),
                   *(int *)(param_1 + 0x50) + -1 + *(int *)(param_1 + 0x58),
                   *(undefined4 *)(param_1 + 0x60));
      FUN_0041f9e0(*(undefined4 *)(param_1 + 0x4c),
                   *(int *)(param_1 + 0x50) + -1 + *(int *)(param_1 + 0x58),
                   *(undefined4 *)(param_1 + 0x60));
      uVar8 = *(undefined4 *)(param_1 + 0x60);
    }
    else {
      if (uVar9 != 1) {
        if (uVar9 == 2) {
          iVar13 = *(int *)(param_1 + 0x44);
          if ((((iVar13 == 2) || (iVar13 == 3)) || (iVar13 == 10)) &&
             (*(int *)(param_1 + 0x84) != 0)) {
            uVar7 = FUN_0041f6b0(0x5a,0x5a,0x5a);
            uVar8 = FUN_0041f6b0(0xff,0xff,0xff);
          }
          FUN_0041f9c0(*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x50));
          FUN_0041f9e0(*(int *)(param_1 + 0x54) + -1 + *(int *)(param_1 + 0x4c),
                       *(undefined4 *)(param_1 + 0x50),uVar8);
          FUN_0041f9e0(*(int *)(param_1 + 0x54) + -1 + *(int *)(param_1 + 0x4c),
                       *(int *)(param_1 + 0x50) + -1 + *(int *)(param_1 + 0x58),uVar7);
          FUN_0041f9e0(*(undefined4 *)(param_1 + 0x4c),
                       *(int *)(param_1 + 0x50) + -1 + *(int *)(param_1 + 0x58),uVar7);
          FUN_0041f9e0(*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x50),uVar8);
          FUN_0041f9c0(*(int *)(param_1 + 0x4c) + 1,*(int *)(param_1 + 0x50) + 1);
          FUN_0041f9e0(*(int *)(param_1 + 0x54) + -2 + *(int *)(param_1 + 0x4c),
                       *(int *)(param_1 + 0x50) + 1,uVar7);
          FUN_0041f9e0(*(int *)(param_1 + 0x54) + -2 + *(int *)(param_1 + 0x4c),
                       *(int *)(param_1 + 0x50) + -2 + *(int *)(param_1 + 0x58),uVar8);
          FUN_0041f9e0(*(int *)(param_1 + 0x4c) + 1,
                       *(int *)(param_1 + 0x50) + -2 + *(int *)(param_1 + 0x58),uVar8);
          FUN_0041f9e0(*(int *)(param_1 + 0x4c) + 1,*(int *)(param_1 + 0x50) + 1,uVar7);
        }
        goto LAB_0042f401;
      }
      iVar13 = *(int *)(param_1 + 0x44);
      if ((((iVar13 == 2) || (iVar13 == 3)) || (iVar13 == 10)) && (*(int *)(param_1 + 0x84) != 0)) {
        uVar8 = FUN_0041f6b0(0x5a,0x5a,0x5a);
        uVar7 = FUN_0041f6b0(0xff,0xff,0xff);
      }
      FUN_0041f9c0(*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x50));
      FUN_0041f9e0(*(int *)(param_1 + 0x54) + -1 + *(int *)(param_1 + 0x4c),
                   *(undefined4 *)(param_1 + 0x50),uVar8);
      FUN_0041f9e0(*(int *)(param_1 + 0x54) + -1 + *(int *)(param_1 + 0x4c),
                   *(int *)(param_1 + 0x50) + -1 + *(int *)(param_1 + 0x58),uVar7);
      FUN_0041f9e0(*(undefined4 *)(param_1 + 0x4c),
                   *(int *)(param_1 + 0x50) + -1 + *(int *)(param_1 + 0x58),uVar7);
    }
    FUN_0041f9e0(*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x50),uVar8);
  }
LAB_0042f401:
  iVar10 = FUN_0041f6b0(0x82,0x82,0x82);
  iVar13 = iVar10;
  if (*(int *)(param_1 + 0x98) != 0) {
    iVar13 = *(int *)(param_1 + 0x70);
  }
  FUN_004304e0(param_1 + 4,*(int *)(param_1 + 0x68) + *(int *)(param_1 + 0x4c),
               *(int *)(param_1 + 0x6c) + *(int *)(param_1 + 0x50),iVar13);
  if (*(int *)(param_1 + 0x98) == 0) {
    iVar13 = *(int *)(param_1 + 0x8c);
    if (iVar13 != 0) {
      iVar14 = *(int *)(param_1 + 0x94) + *(int *)(param_1 + 0x50);
      iVar15 = *(int *)(param_1 + 0x90) + *(int *)(param_1 + 0x4c);
      goto LAB_0042f49a;
    }
  }
  else {
    iVar13 = *(int *)(param_1 + 0x88);
    if (iVar13 != 0) {
      iVar14 = *(int *)(param_1 + 0x94) + *(int *)(param_1 + 0x50);
      iVar15 = *(int *)(param_1 + 0x90) + *(int *)(param_1 + 0x4c);
LAB_0042f49a:
      FUN_004209c0(iVar15,iVar14,iVar13);
    }
  }
  uVar8 = FUN_0041f6b0(0x5a,0x5a,0x5a);
  uVar7 = FUN_0041f6b0(0xff,0xff,0xff);
  switch(*(undefined4 *)(param_1 + 0x44)) {
  case 4:
    piVar2 = *(int **)(param_1 + 0xc0);
    if (*(int *)(param_1 + 0x84) != 0) {
      FUN_0041f900(*piVar2 + *(int *)(param_1 + 0x4c),piVar2[1] + *(int *)(param_1 + 0x50),piVar2[2]
                   ,piVar2[3],*(undefined4 *)(param_1 + 0x80));
    }
    iVar13 = piVar2[4];
    if (iVar13 == 0) {
      FUN_0041f9c0(*piVar2 + *(int *)(param_1 + 0x4c),*(int *)(param_1 + 0x50) + piVar2[1]);
      FUN_0041f9e0(*piVar2 + piVar2[2] + -1 + *(int *)(param_1 + 0x4c),
                   *(int *)(param_1 + 0x50) + piVar2[1],uVar8);
      FUN_0041f9e0(*piVar2 + piVar2[2] + -1 + *(int *)(param_1 + 0x4c),
                   piVar2[3] + *(int *)(param_1 + 0x50) + -1 + piVar2[1],uVar8);
      FUN_0041f9e0(*piVar2 + *(int *)(param_1 + 0x4c),
                   piVar2[3] + *(int *)(param_1 + 0x50) + -1 + piVar2[1],uVar8);
      FUN_0041f9e0(*piVar2 + *(int *)(param_1 + 0x4c),*(int *)(param_1 + 0x50) + piVar2[1],uVar8);
    }
    else if (iVar13 == 2) {
      FUN_0041f9c0(*piVar2 + *(int *)(param_1 + 0x4c),*(int *)(param_1 + 0x50) + piVar2[1]);
      FUN_0041f9e0(*piVar2 + piVar2[2] + -1 + *(int *)(param_1 + 0x4c),
                   *(int *)(param_1 + 0x50) + piVar2[1],uVar8);
      FUN_0041f9e0(*piVar2 + piVar2[2] + -1 + *(int *)(param_1 + 0x4c),
                   piVar2[3] + *(int *)(param_1 + 0x50) + -1 + piVar2[1],uVar8);
      FUN_0041f9e0(*piVar2 + *(int *)(param_1 + 0x4c),
                   piVar2[3] + *(int *)(param_1 + 0x50) + -1 + piVar2[1],uVar8);
      FUN_0041f9e0(*piVar2 + *(int *)(param_1 + 0x4c),*(int *)(param_1 + 0x50) + piVar2[1],uVar8);
      if (*(int *)(param_1 + 0x84) != 0) {
        FUN_0041f9e0(*piVar2 + piVar2[2] + -1 + *(int *)(param_1 + 0x4c),
                     piVar2[3] + *(int *)(param_1 + 0x50) + -1 + piVar2[1],uVar8);
        FUN_0041f9c0(*piVar2 + *(int *)(param_1 + 0x4c),
                     piVar2[3] + *(int *)(param_1 + 0x50) + -1 + piVar2[1]);
        FUN_0041f9e0(*piVar2 + piVar2[2] + -1 + *(int *)(param_1 + 0x4c),
                     *(int *)(param_1 + 0x50) + piVar2[1],uVar8);
      }
    }
    else if (iVar13 == 1) {
      if (*(int *)(param_1 + 0x84) != 0) {
        uVar7 = FUN_0041f6b0(0x5a,0x5a,0x5a);
        uVar8 = FUN_0041f6b0(0xff,0xff,0xff);
      }
      FUN_0041f9c0(*piVar2 + *(int *)(param_1 + 0x4c),*(int *)(param_1 + 0x50) + piVar2[1]);
      FUN_0041f9e0(*piVar2 + piVar2[2] + -1 + *(int *)(param_1 + 0x4c),
                   *(int *)(param_1 + 0x50) + piVar2[1],uVar7);
      FUN_0041f9e0(*piVar2 + piVar2[2] + -1 + *(int *)(param_1 + 0x4c),
                   piVar2[3] + *(int *)(param_1 + 0x50) + -1 + piVar2[1],uVar8);
      FUN_0041f9e0(*piVar2 + *(int *)(param_1 + 0x4c),
                   piVar2[3] + *(int *)(param_1 + 0x50) + -1 + piVar2[1],uVar8);
      FUN_0041f9e0(*piVar2 + *(int *)(param_1 + 0x4c),*(int *)(param_1 + 0x50) + piVar2[1],uVar7);
    }
    break;
  case 5:
    piVar2 = *(int **)(param_1 + 0xc0);
    iVar15 = piVar2[1] + *(int *)(param_1 + 0x50);
    iVar14 = *piVar2 + *(int *)(param_1 + 0x4c);
    FUN_0041f900(iVar14,iVar15,piVar2[2],piVar2[3],*(undefined4 *)(param_1 + 0x80));
    FUN_00508ae6(local_a0,(int)piVar2 + piVar2[5] + 0x20);
    iVar13 = DAT_005c71ec + DAT_005c71e4;
    uVar9 = 0xffffffff;
    pcVar16 = local_a0;
    do {
      if (uVar9 == 0) break;
      uVar9 = uVar9 - 1;
      cVar1 = *pcVar16;
      pcVar16 = pcVar16 + 1;
    } while (cVar1 != '\0');
    if (piVar2[2] <= (int)((~uVar9 - 1) * iVar13 + 3)) {
      do {
        uVar9 = 0xffffffff;
        pcVar16 = local_a0;
        do {
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          cVar1 = *pcVar16;
          pcVar16 = pcVar16 + 1;
        } while (cVar1 != '\0');
        local_a0[~uVar9 - 2] = '\0';
        uVar9 = 0xffffffff;
        pcVar16 = local_a0;
        do {
          if (uVar9 == 0) break;
          uVar9 = uVar9 - 1;
          cVar1 = *pcVar16;
          pcVar16 = pcVar16 + 1;
        } while (cVar1 != '\0');
      } while (piVar2[2] <= (int)((~uVar9 - 1) * iVar13 + 3));
    }
    if (piVar2[7] == 0) {
      iVar17 = piVar2[0x1c];
      FUN_0041f900(iVar17 * iVar13 + 1 + iVar14,iVar15 + 2,piVar2[0x1d] * iVar13,piVar2[3] + -4,
                   piVar2[0x1e]);
      if (*(int *)(param_1 + 0x98) != 0) {
        iVar10 = *(int *)(param_1 + 0x70);
      }
      FUN_004304e0(local_a0,iVar14 + 3,DAT_005c71e8 + iVar15,iVar10);
      iVar10 = 0;
      do {
        pcVar16 = local_a0 + iVar10;
        local_50[iVar10] = *pcVar16;
        iVar10 = iVar10 + 1;
      } while (*pcVar16 != '\0');
      local_50[piVar2[0x1d]] = '\0';
      iVar10 = -1 - *(int *)(param_1 + 0x70);
      pcVar16 = local_50;
      iVar13 = iVar17 * iVar13 + 3 + iVar14;
LAB_0042fd11:
      FUN_004304e0(pcVar16,iVar13,DAT_005c71e8 + iVar15,iVar10);
    }
    else {
      if (*(int *)(param_1 + 0x98) == 0) {
        iVar13 = iVar14 + 3;
        pcVar16 = local_a0;
        goto LAB_0042fd11;
      }
      FUN_004304e0(local_a0,iVar14 + 3,DAT_005c71e8 + iVar15,*(undefined4 *)(param_1 + 0x70));
    }
    if ((piVar2[7] != 1) && (iVar13 = piVar2[4], piVar2[5] <= iVar13)) {
      uVar9 = 0xffffffff;
      pcVar16 = local_a0;
      do {
        if (uVar9 == 0) break;
        uVar9 = uVar9 - 1;
        cVar1 = *pcVar16;
        pcVar16 = pcVar16 + 1;
      } while (cVar1 != '\0');
      if (iVar13 <= (int)((~uVar9 - 1) + piVar2[5])) {
        iVar13 = (iVar13 - piVar2[5]) * (DAT_005c71ec + DAT_005c71e4) + 1 + iVar14;
        uVar11 = FUN_0041f6b0(0,200,0);
        FUN_0041f9c0(iVar13,iVar15 + 2);
        FUN_0041f9e0(iVar13,DAT_005c71e8 + 3 + iVar15,uVar11);
        FUN_0041f9c0(iVar13 + 1,iVar15 + 2);
        FUN_0041f9e0(iVar13 + 1,DAT_005c71e8 + 3 + iVar15,uVar11);
      }
    }
    FUN_0041f9c0(piVar2[2] + -1 + iVar14,iVar15);
    FUN_0041f9e0(iVar14,iVar15,uVar8);
    FUN_0041f9e0(iVar14,piVar2[3] + -1 + iVar15,uVar8);
    FUN_0041f9e0(piVar2[2] + -1 + iVar14,piVar2[3] + -1 + iVar15,uVar7);
    FUN_0041f9e0(piVar2[2] + -1 + iVar14,iVar15,uVar7);
    break;
  case 7:
    piVar2 = *(int **)(param_1 + 0xc0);
    iVar10 = *(int *)(param_1 + 0x50);
    local_e4 = *(int *)(param_1 + 0x4c);
    iVar14 = piVar2[6];
    iVar15 = piVar2[5];
    FUN_0041f900(local_e4,iVar10,iVar15,iVar14,*(undefined4 *)(param_1 + 0x48));
    iVar13 = iVar15 + -1 + local_e4;
    FUN_0041f9c0(iVar13,iVar10);
    FUN_0041f9e0(local_e4,iVar10,uVar7);
    FUN_0041f9e0(local_e4,iVar14 + -1 + iVar10,uVar7);
    FUN_0041f9e0(iVar13,iVar14 + -1 + iVar10,uVar8);
    FUN_0041f9e0(iVar13,iVar10,uVar8);
    if (*piVar2 == 1) {
      iVar10 = (piVar2[1] - piVar2[6]) + *(int *)(param_1 + 0x50);
    }
    else {
      local_e4 = (piVar2[1] - piVar2[5]) + *(int *)(param_1 + 0x4c);
    }
    FUN_0041f900(local_e4,iVar10,iVar15,iVar14,*(undefined4 *)(param_1 + 0x48));
    iVar13 = iVar15 + -1 + local_e4;
    FUN_0041f9c0(iVar13,iVar10);
    FUN_0041f9e0(local_e4,iVar10,uVar7);
    iVar14 = iVar14 + -1 + iVar10;
    FUN_0041f9e0(local_e4,iVar14,uVar7);
    FUN_0041f9e0(iVar13,iVar14,uVar8);
    FUN_0041f9e0(iVar13,iVar10,uVar8);
    local_a4 = *(int *)(param_1 + 0x50);
    local_a8 = *(int *)(param_1 + 0x4c);
    if (*piVar2 == 1) {
      local_b8 = piVar2[5] / 2 + local_a8;
      local_b4 = ((int)(piVar2[5] + (piVar2[5] >> 0x1f & 3U)) >> 2) + local_a4;
      local_b0 = ((int)(piVar2[5] + (piVar2[5] >> 0x1f & 3U)) >> 2) + local_a8;
      local_ac = (piVar2[5] * 2) / 3 + local_a4;
      local_a8 = (piVar2[5] * 2) / 3 + 2 + local_a8;
      local_a4 = (piVar2[5] * 2) / 3 + local_a4;
      FUN_00420380(&local_b8,3,uVar8,1,uVar8,1);
      iVar13 = *(int *)(param_1 + 0x50);
      local_b4 = (iVar13 - ((int)(piVar2[5] + (piVar2[5] >> 0x1f & 3U)) >> 2)) + piVar2[1];
      local_ac = (iVar13 - (piVar2[5] * 2) / 3) + piVar2[1];
      local_a4 = (iVar13 - (piVar2[5] * 2) / 3) + piVar2[1];
    }
    else {
      local_b8 = ((int)(piVar2[6] + (piVar2[6] >> 0x1f & 3U)) >> 2) + local_a8;
      local_b4 = piVar2[6] / 2 + local_a4;
      local_b0 = (piVar2[6] * 2) / 3 + local_a8;
      local_ac = ((int)(piVar2[6] + (piVar2[6] >> 0x1f & 3U)) >> 2) + local_a4;
      local_a8 = (piVar2[6] * 2) / 3 + local_a8;
      local_a4 = (piVar2[6] * 2) / 3 + 2 + local_a4;
      FUN_00420380(&local_b8,3,uVar8,1,uVar8,1);
      iVar13 = *(int *)(param_1 + 0x4c);
      local_b8 = (iVar13 - ((int)(piVar2[6] + (piVar2[6] >> 0x1f & 3U)) >> 2)) + piVar2[1];
      local_b0 = (iVar13 - (piVar2[6] * 2) / 3) + piVar2[1];
      local_a8 = (iVar13 - (piVar2[6] * 2) / 3) + piVar2[1];
    }
    FUN_00420380(&local_b8,3,uVar8,1,uVar8,1);
    if (*piVar2 == 1) {
      local_e4 = *(int *)(param_1 + 0x4c);
      iVar13 = __ftol();
      iVar13 = iVar13 + *(int *)(param_1 + 0x50) + piVar2[6];
      local_e0 = (int *)piVar2[5];
      local_dc = __ftol();
    }
    else {
      iVar10 = __ftol();
      iVar13 = *(int *)(param_1 + 0x50);
      local_e4 = iVar10 + piVar2[5] + *(int *)(param_1 + 0x4c);
      local_e0 = (int *)__ftol();
      local_dc = piVar2[6];
    }
    FUN_0041f900(local_e4,iVar13,local_e0,local_dc,*(undefined4 *)(param_1 + 0x48));
    iVar10 = (int)local_e0 + -1 + local_e4;
    FUN_0041f9c0(iVar10,iVar13);
    FUN_0041f9e0(local_e4,iVar13,uVar7);
    iVar14 = local_dc + -1 + iVar13;
    FUN_0041f9e0(local_e4,iVar14,uVar7);
    FUN_0041f9e0(iVar10,iVar14,uVar8);
    FUN_0041f9e0(iVar10,iVar13,uVar8);
    break;
  case 8:
    iVar13 = *(int *)(param_1 + 0xc0);
    iVar17 = *(int *)(iVar13 + 0x40) + *(int *)(param_1 + 0x4c);
    iVar15 = *(int *)(iVar13 + 0x44) + *(int *)(param_1 + 0x50);
    FUN_0041f900(iVar17,iVar15,*(undefined4 *)(iVar13 + 0x50),*(undefined4 *)(iVar13 + 0x54),
                 *(undefined4 *)(param_1 + 0x80));
    local_d0 = DAT_005c71e8 + iVar15;
    iVar10 = *(int *)(iVar13 + 0x60);
    iVar14 = *(int *)(iVar13 + 0x5c);
    if ((iVar14 <= iVar10) && (iVar10 < *(int *)(iVar13 + 0x4c) + iVar14)) {
      FUN_0041f900(iVar17,(iVar10 - iVar14) * (DAT_005c71e8 + 2) + 1 + iVar15,
                   *(undefined4 *)(iVar13 + 0x50),DAT_005c71e8 + 2,*(undefined4 *)(iVar13 + 0x6c));
    }
    iVar10 = *(int *)(iVar13 + 0x70);
    iVar14 = 0;
    local_e0 = (int *)iVar10;
    if (0 < *(int *)(iVar13 + 0x5c)) {
      do {
        local_e0 = (int *)0;
        if (iVar10 == 0) break;
        iVar10 = *(int *)(iVar10 + 0x40);
        iVar14 = iVar14 + 1;
        local_e0 = (int *)iVar10;
      } while (iVar14 < *(int *)(iVar13 + 0x5c));
    }
    local_c8 = 0;
    if (0 < *(int *)(iVar13 + 0x4c)) {
      do {
        if (local_e0 == (int *)0x0) break;
        pcVar16 = local_a0;
        pcVar12 = (char *)(*(int *)(iVar13 + 0x58) + (int)local_e0);
        do {
          cVar1 = *pcVar12;
          pcVar12 = pcVar12 + 1;
          *pcVar16 = cVar1;
          pcVar16 = pcVar16 + 1;
        } while (cVar1 != '\0');
        local_a0[*(int *)(iVar13 + 0x48)] = '\0';
        if (local_c8 == *(int *)(iVar13 + 0x60) - *(int *)(iVar13 + 0x5c)) {
          iVar10 = -1 - *(int *)(param_1 + 0x70);
        }
        else {
          iVar10 = *(int *)(param_1 + 0x70);
        }
        FUN_004304e0(local_a0,iVar17 + 3,local_d0,iVar10);
        local_d0 = local_d0 + 2 + DAT_005c71e8;
        local_e0 = *(int **)((int)local_e0 + 0x40);
        local_c8 = local_c8 + 1;
      } while (local_c8 < *(int *)(iVar13 + 0x4c));
    }
    FUN_0041f9c0(iVar17 + -1 + *(int *)(iVar13 + 0x50),iVar15);
    FUN_0041f9e0(iVar17,iVar15,uVar8);
    FUN_0041f9e0(iVar17,*(int *)(iVar13 + 0x54) + -1 + iVar15,uVar8);
    FUN_0041f9e0(iVar17 + -1 + *(int *)(iVar13 + 0x50),*(int *)(iVar13 + 0x54) + -1 + iVar15,uVar7);
    FUN_0041f9e0(iVar17 + -1 + *(int *)(iVar13 + 0x50),iVar15,uVar7);
    break;
  case 10:
    if (*(int *)(param_1 + 0x84) != 0) {
      piVar2 = *(int **)(param_1 + 0xc0);
      iVar13 = *piVar2;
      iVar14 = piVar2[1];
      iVar15 = piVar2[2];
      iVar17 = piVar2[3];
      iVar3 = piVar2[4];
      FUN_0041f900(iVar13,iVar14,iVar15,iVar17,*(undefined4 *)(param_1 + 0x48));
      uVar9 = *(uint *)(param_1 + 0x5c) & 0xffffff;
      if (uVar9 == 0) {
        FUN_0041f9c0(iVar13,iVar14);
        FUN_0041f9e0(iVar15 + -1 + iVar13,iVar14,*(undefined4 *)(param_1 + 0x60));
        iVar17 = iVar17 + -1 + iVar14;
        FUN_0041f9e0(iVar15 + -1 + iVar13,iVar17,*(undefined4 *)(param_1 + 0x60));
        FUN_0041f9e0(iVar13,iVar17,*(undefined4 *)(param_1 + 0x60));
        FUN_0041f9e0(iVar13,iVar14,*(undefined4 *)(param_1 + 0x60));
      }
      else if (uVar9 == 1) {
        FUN_0041f9c0(iVar13,iVar14);
        FUN_0041f9e0(iVar15 + -1 + iVar13,iVar14,uVar7);
        iVar17 = iVar17 + -1 + iVar14;
        FUN_0041f9e0(iVar15 + -1 + iVar13,iVar17,uVar8);
        FUN_0041f9e0(iVar13,iVar17,uVar8);
        FUN_0041f9e0(iVar13,iVar14,uVar7);
      }
      else if (uVar9 == 2) {
        FUN_0041f9c0(iVar13,iVar14);
        FUN_0041f9e0(iVar15 + -1 + iVar13,iVar14,uVar7);
        FUN_0041f9e0(iVar15 + -1 + iVar13,iVar17 + -1 + iVar14,uVar8);
        FUN_0041f9e0(iVar13,iVar17 + -1 + iVar14,uVar8);
        FUN_0041f9e0(iVar13,iVar14,uVar7);
        FUN_0041f9c0(iVar13 + 1,iVar14 + 1);
        FUN_0041f9e0(iVar15 + -2 + iVar13,iVar14 + 1,uVar8);
        iVar17 = iVar17 + -2 + iVar14;
        FUN_0041f9e0(iVar15 + -2 + iVar13,iVar17,uVar7);
        FUN_0041f9e0(iVar13 + 1,iVar17,uVar7);
        FUN_0041f9e0(iVar13 + 1,iVar14 + 1,uVar8);
      }
      local_d8 = piVar2 + 7;
      local_c8 = 0;
      iVar13 = iVar13 + DAT_005c71e4 * 4;
      iVar14 = iVar14 + 5 + DAT_005c71e8;
      piVar6 = piVar2;
      if (0 < iVar3) {
        do {
          local_e0 = piVar6 + 9;
          if (*local_d8 == 3) {
            FUN_0041f9c0(*piVar2 + 7,iVar14 - DAT_005c71e8 / 2);
            FUN_0041f9e0(*piVar2 + -7 + iVar15,iVar14 - DAT_005c71e8 / 2,uVar8);
            FUN_0041f9c0(*piVar2 + 7,(iVar14 - DAT_005c71e8 / 2) + 1);
            FUN_0041f9e0(*piVar2 + -7 + iVar15,(iVar14 - DAT_005c71e8 / 2) + 1,uVar7);
          }
          else {
            if (local_c8 == piVar2[5]) {
              FUN_0041f900(*piVar2 + 2,iVar14 - DAT_005c71e8,iVar15 + -4,DAT_005c71e8 + 6,piVar2[6])
              ;
              FUN_004304e0(local_e0,iVar13,iVar14,-1 - *(int *)(param_1 + 0x70));
            }
            else {
              iVar17 = iVar10;
              if (piVar6[0xe] != 0) {
                iVar17 = *(int *)(param_1 + 0x70);
              }
              FUN_004304e0(local_e0,iVar13,iVar14,iVar17);
            }
            if ((*local_d8 == 2) && (piVar6[0xf] != 0)) {
              iVar17 = *piVar2 + 2 + DAT_005c71e4;
              local_bc = *(int *)(param_1 + 0x70);
              iVar18 = iVar14 - DAT_005c71e4 / 2;
              if (local_c8 == piVar2[5]) {
                local_bc = -1 - local_bc;
              }
              FUN_0041f9c0(iVar17,iVar18);
              FUN_0041f9e0(iVar17 + 2,iVar18 + 3,local_bc);
              FUN_0041f9e0(iVar17 + 7,iVar18 + -3,local_bc);
            }
          }
          local_d8 = local_d8 + 9;
          local_c8 = local_c8 + 1;
          iVar14 = iVar14 + 6 + DAT_005c71e8;
          piVar6 = local_e0;
        } while (local_c8 < iVar3);
      }
    }
  }
  if (*(int *)(param_1 + 0x78) != 0) {
    uVar8 = FUN_0041f6b0(0,0,0);
    for (puVar4 = *(undefined4 **)(param_1 + 0x78); puVar4 != (undefined4 *)0x0;
        puVar4 = (undefined4 *)puVar4[2]) {
      switch(*puVar4) {
      case 1:
        FUN_0041f9c0(*(int *)puVar4[1] + *(int *)(param_1 + 0x4c),
                     ((int *)puVar4[1])[1] + *(int *)(param_1 + 0x50));
        break;
      case 2:
        FUN_0041f9e0(*(int *)puVar4[1] + *(int *)(param_1 + 0x4c),
                     ((int *)puVar4[1])[1] + *(int *)(param_1 + 0x50),uVar8);
        break;
      case 3:
        FUN_004304e0(*(undefined4 *)puVar4[1],DAT_007e270c,DAT_007e2708,uVar8);
        break;
      case 4:
        puVar5 = (undefined1 *)puVar4[1];
        uVar8 = FUN_0041f6b0(CONCAT31((int3)((uint)puVar5 >> 8),*puVar5),puVar5[4],puVar5[8]);
      }
    }
  }
  FUN_0040e680();
  return;
}

