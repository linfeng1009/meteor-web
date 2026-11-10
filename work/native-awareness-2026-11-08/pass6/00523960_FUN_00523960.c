/* Original Meteor.exe static export @ 00523960; original sample not executed. */
/* XREF 0041732a UNCONDITIONAL_CALL */
/* XREF 0042259f UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

char FUN_00523960(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  char cVar27;
  char cVar28;
  
  iVar3 = *(int *)(param_1 + 0xa0);
  fVar4 = *(float *)(iVar3 + 0x18);
  fVar5 = *(float *)(iVar3 + 0x1c);
  fVar1 = *(float *)(iVar3 + 0x10);
  fVar2 = *(float *)(iVar3 + 0x14);
  fVar6 = *(float *)(iVar3 + 0x20);
  fVar7 = *(float *)(iVar3 + 0x24);
  fVar16 = fVar6 * param_2[8] + param_2[0xc];
  fVar21 = fVar7 * param_2[8] + param_2[0xc];
  fVar22 = fVar6 * param_2[9] + param_2[0xd];
  fVar23 = fVar7 * param_2[9] + param_2[0xd];
  fVar24 = fVar6 * param_2[10] + param_2[0xe];
  fVar25 = fVar7 * param_2[10] + param_2[0xe];
  fVar10 = fVar6 * param_2[0xb] + param_2[0xf];
  fVar14 = fVar7 * param_2[0xb] + param_2[0xf];
  fVar6 = fVar5 * param_2[7] + fVar2 * param_2[3];
  fVar12 = fVar5 * param_2[7] + fVar1 * param_2[3];
  fVar11 = fVar6 + fVar10;
  fVar13 = fVar10 + fVar12;
  fVar12 = fVar12 + fVar14;
  fVar6 = fVar6 + fVar14;
  fVar7 = fVar4 * param_2[7] + fVar2 * param_2[3];
  fVar9 = fVar4 * param_2[7] + fVar1 * param_2[3];
  fVar8 = fVar7 + fVar10;
  fVar10 = fVar10 + fVar9;
  fVar9 = fVar9 + fVar14;
  fVar7 = fVar7 + fVar14;
  fVar17 = fVar2 * *param_2 + fVar5 * param_2[4];
  fVar18 = fVar5 * param_2[4] + fVar1 * *param_2;
  fVar20 = fVar17 + fVar16;
  fVar19 = fVar16 + fVar18;
  fVar18 = fVar18 + fVar21;
  fVar17 = fVar17 + fVar21;
  fVar14 = fVar2 * *param_2 + fVar4 * param_2[4];
  fVar15 = fVar4 * param_2[4] + fVar1 * *param_2;
  fVar26 = fVar14 + fVar16;
  fVar16 = fVar16 + fVar15;
  fVar15 = fVar15 + fVar21;
  fVar14 = fVar14 + fVar21;
  cVar27 = fVar20 < fVar11;
  if (fVar19 < fVar13) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar18 < fVar12) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar17 < fVar6) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar26 < fVar8) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar16 < fVar10) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar15 < fVar9) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar14 < fVar7) {
    cVar27 = cVar27 + '\x01';
  }
  if (cVar27 == '\0') {
    return '\0';
  }
  cVar28 = cVar27 == '\b';
  cVar27 = -fVar11 < fVar20;
  if (-fVar13 < fVar19) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar12 < fVar18) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar6 < fVar17) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar8 < fVar26) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar10 < fVar16) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar9 < fVar15) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar7 < fVar14) {
    cVar27 = cVar27 + '\x01';
  }
  if (cVar27 == '\0') {
    return '\0';
  }
  if (cVar27 == '\b') {
    cVar28 = cVar28 + '\x01';
  }
  fVar14 = fVar5 * param_2[5] + fVar2 * param_2[1];
  fVar16 = fVar5 * param_2[5] + fVar1 * param_2[1];
  fVar15 = fVar14 + fVar22;
  fVar17 = fVar22 + fVar16;
  fVar16 = fVar16 + fVar23;
  fVar14 = fVar14 + fVar23;
  fVar18 = fVar4 * param_2[5] + fVar2 * param_2[1];
  fVar20 = fVar4 * param_2[5] + fVar1 * param_2[1];
  fVar19 = fVar18 + fVar22;
  fVar22 = fVar22 + fVar20;
  fVar20 = fVar20 + fVar23;
  fVar18 = fVar18 + fVar23;
  cVar27 = fVar15 < fVar11;
  if (fVar17 < fVar13) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar16 < fVar12) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar14 < fVar6) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar19 < fVar8) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar22 < fVar10) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar20 < fVar9) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar18 < fVar7) {
    cVar27 = cVar27 + '\x01';
  }
  if (cVar27 == '\0') {
    return '\0';
  }
  if (cVar27 == '\b') {
    cVar28 = cVar28 + '\x01';
  }
  cVar27 = -fVar11 < fVar15;
  if (-fVar13 < fVar17) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar12 < fVar16) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar6 < fVar14) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar8 < fVar19) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar10 < fVar22) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar9 < fVar20) {
    cVar27 = cVar27 + '\x01';
  }
  if (-fVar7 < fVar18) {
    cVar27 = cVar27 + '\x01';
  }
  if (cVar27 == '\0') {
    return '\0';
  }
  if (cVar27 == '\b') {
    cVar28 = cVar28 + '\x01';
  }
  fVar15 = fVar5 * param_2[6] + fVar2 * param_2[2];
  fVar5 = fVar5 * param_2[6] + fVar1 * param_2[2];
  fVar16 = fVar15 + fVar24;
  fVar14 = fVar24 + fVar5;
  fVar5 = fVar5 + fVar25;
  fVar15 = fVar15 + fVar25;
  fVar2 = fVar4 * param_2[6] + fVar2 * param_2[2];
  fVar1 = fVar4 * param_2[6] + fVar1 * param_2[2];
  fVar4 = fVar2 + fVar24;
  fVar24 = fVar24 + fVar1;
  fVar1 = fVar1 + fVar25;
  fVar2 = fVar2 + fVar25;
  cVar27 = _DAT_005a83e4 < fVar16;
  if (_DAT_005a83e4 < fVar14) {
    cVar27 = cVar27 + '\x01';
  }
  if (_DAT_005a83e4 < fVar5) {
    cVar27 = cVar27 + '\x01';
  }
  if (_DAT_005a83e4 < fVar15) {
    cVar27 = cVar27 + '\x01';
  }
  if (_DAT_005a83e4 < fVar4) {
    cVar27 = cVar27 + '\x01';
  }
  if (_DAT_005a83e4 < fVar24) {
    cVar27 = cVar27 + '\x01';
  }
  if (_DAT_005a83e4 < fVar1) {
    cVar27 = cVar27 + '\x01';
  }
  if (_DAT_005a83e4 < fVar2) {
    cVar27 = cVar27 + '\x01';
  }
  if (cVar27 == '\0') {
    return '\0';
  }
  if (cVar27 == '\b') {
    cVar28 = cVar28 + '\x01';
  }
  cVar27 = fVar16 < fVar11;
  if (fVar14 < fVar13) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar5 < fVar12) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar15 < fVar6) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar4 < fVar8) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar24 < fVar10) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar1 < fVar9) {
    cVar27 = cVar27 + '\x01';
  }
  if (fVar2 < fVar7) {
    cVar27 = cVar27 + '\x01';
  }
  if (cVar27 == '\0') {
    return '\0';
  }
  if (cVar27 == '\b') {
    cVar28 = cVar28 + '\x01';
  }
  return (cVar28 == '\x06') + '\x01';
}

