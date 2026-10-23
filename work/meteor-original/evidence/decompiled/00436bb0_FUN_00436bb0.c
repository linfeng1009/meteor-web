/* Meteor.exe original x86 @ 00436bb0 */
/* Caller: 00435b77 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00436bb0(void)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  int *piVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined4 *puVar12;
  int *piVar13;
  char *pcVar14;
  undefined4 **ppuVar15;
  char *pcVar16;
  char *pcVar17;
  int ***pppiVar18;
  int **appiStack_134 [4];
  int **ppiStack_124;
  int **ppiStack_120;
  int **ppiStack_11c;
  char *local_118;
  int local_114;
  int **local_110;
  int **local_10c;
  int *local_f4;
  int *local_f0;
  int *local_ec;
  int local_e8;
  int *local_e4;
  int *local_e0;
  int *local_dc;
  int *local_d8;
  undefined4 *local_d4;
  int *local_d0;
  int local_cc;
  undefined4 local_c8;
  undefined4 *local_c4;
  undefined4 *local_c0;
  undefined4 *local_bc;
  undefined4 *local_b8;
  undefined4 *local_b4;
  undefined4 *local_b0;
  undefined4 *local_ac;
  int local_a8;
  int local_a4;
  undefined4 *local_a0;
  undefined4 *local_9c;
  undefined4 local_98;
  int local_94;
  undefined4 local_90;
  undefined4 *local_8c [6];
  undefined4 *local_74;
  undefined4 *local_70;
  undefined4 *local_6c;
  char acStack_68 [52];
  undefined1 auStack_34 [20];
  undefined1 auStack_20 [16];
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059ac64;
  pvStack_c = ExceptionList;
  local_10c = (int **)0x436bda;
  ExceptionList = &pvStack_c;
  local_70 = operator_new(0x6c);
  local_4 = 0;
  local_9c = local_70;
  if (local_70 == (undefined4 *)0x0) {
    local_70 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *local_70 = &PTR_FUN_005a8580;
  }
  local_4 = 0xffffffff;
  local_70[1] = s_Con_Forward_005c7354;
  local_10c = (int **)0x436c20;
  puVar4 = operator_new(0xc);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    *puVar4 = &PTR_FUN_005a8528;
  }
  local_10c = (int **)0x436c42;
  FUN_00463cb0();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x436c72;
  FUN_00462e50();
  local_10c = (int **)0x436c7b;
  FUN_00463050();
  local_10c = (int **)0x436c82;
  local_6c = operator_new(0x6c);
  local_4 = 1;
  local_9c = local_6c;
  if (local_6c == (undefined4 *)0x0) {
    local_6c = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *local_6c = &PTR_FUN_005a8580;
  }
  local_4 = 0xffffffff;
  local_6c[1] = s_Con_Forward_005c7354;
  local_10c = (int **)0x436cc7;
  puVar4 = operator_new(0xc);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    *puVar4 = &PTR_FUN_005a8528;
  }
  local_10c = (int **)0x436ce9;
  FUN_00463cb0();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x436d19;
  FUN_00462e50();
  local_10c = (int **)0x436d22;
  FUN_00463050();
  uVar5 = DAT_005dbb74;
  DAT_005dbb74 = 0;
  local_10c = (int **)0x436d35;
  local_74 = operator_new(0x6c);
  local_4 = 2;
  local_9c = local_74;
  if (local_74 == (undefined4 *)0x0) {
    local_74 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *local_74 = &PTR_FUN_005a8580;
  }
  local_4 = 0xffffffff;
  local_74[1] = &DAT_005c73d8;
  local_10c = (int **)0x436d7e;
  puVar4 = operator_new(0xc);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    *puVar4 = &PTR_FUN_005a8528;
  }
  local_10c = (int **)0x436da0;
  FUN_00463cb0();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x436dd0;
  FUN_00462e50();
  local_10c = (int **)0x436ddd;
  DAT_005dbb74 = uVar5;
  local_8c[5] = operator_new(0xc);
  if (local_8c[5] == (undefined4 *)0x0) {
    local_8c[5] = (undefined4 *)0x0;
  }
  else {
    local_8c[5][1] = 0;
    *local_8c[5] = &PTR_FUN_005a84d0;
    local_8c[5][2] = 0;
  }
  local_10c = (int **)0x436e07;
  FUN_0046a510();
  local_10c = (int **)0x436e0e;
  puVar4 = operator_new(0x6c);
  local_4 = 3;
  if (puVar4 == (undefined4 *)0x0) {
    puVar4 = (undefined4 *)0x0;
  }
  else {
    local_9c = puVar4;
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8868;
  }
  local_4 = 0xffffffff;
  local_10c = (int **)0x436e4d;
  local_9c = puVar4;
  local_c4 = operator_new(0x78);
  local_4 = 4;
  if (local_c4 != (void *)0x0) {
    FUN_00467160();
  }
  DAT_005dbb74 = 0;
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = 0;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x436eab;
  FUN_00462e50();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  local_114 = 7;
  DAT_005ddd68 = 0;
  DAT_005ddd6c = 0.0;
  _DAT_005ddd70 = 0;
  _DAT_005ddd74 = 0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[2] = (int **)0x436ef0;
  FUN_00467840();
  local_10c = (int **)0x436ef7;
  local_c4 = operator_new(0x50);
  local_4 = 5;
  if (local_c4 == (void *)0x0) {
    local_c4 = (undefined4 *)0x0;
  }
  else {
    local_c4 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d00000;
  DAT_005ddd6c = 88.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x436f6f;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 91.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x436fb5;
  FUN_00466a10();
  local_10c = (int **)0x0;
  local_110 = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 91.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x436ffb;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dd270;
  ppiStack_11c = (int **)0x437018;
  FUN_00466340();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 1;
  local_118 = (char *)&DAT_005ddc30;
  ppiStack_11c = (int **)0x437035;
  FUN_00466340();
  local_10c = (int **)0x43703c;
  local_f4 = operator_new(0x50);
  local_4 = 6;
  if (local_f4 == (int *)0x0) {
    local_f4 = (int *)0x0;
  }
  else {
    local_f4 = (int *)FUN_00465610();
  }
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x0;
  ppiStack_124 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43708c;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 131.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x4370d2;
  FUN_00466a10();
  local_10c = (int **)0x0;
  local_110 = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 131.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437118;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dd8bc;
  ppiStack_11c = (int **)0x437135;
  FUN_00466340();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 1;
  local_118 = (char *)&DAT_005dd23c;
  ppiStack_11c = (int **)0x437152;
  FUN_00466340();
  local_10c = (int **)0x437159;
  local_ec = operator_new(0x50);
  local_4 = 7;
  if (local_ec == (int *)0x0) {
    local_e8 = 0;
  }
  else {
    local_e8 = FUN_00465610();
  }
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x0;
  ppiStack_124 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4371a9;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 171.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x4371ef;
  FUN_00466a10();
  local_10c = (int **)0x0;
  local_110 = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 171.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437235;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005e00b0;
  ppiStack_11c = (int **)0x437252;
  FUN_00466340();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 1;
  local_118 = (char *)&DAT_005de4d0;
  ppiStack_11c = (int **)0x43726f;
  FUN_00466340();
  local_10c = (int **)0x437276;
  local_ec = operator_new(0x50);
  local_4 = 8;
  if (local_ec == (int *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x0;
  ppiStack_124 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4372c6;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 211.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43730c;
  FUN_00466a10();
  local_10c = (int **)0x0;
  local_110 = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 211.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437352;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dd680;
  ppiStack_11c = (int **)0x43736f;
  FUN_00466340();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 1;
  local_118 = (char *)&DAT_005ddb94;
  ppiStack_11c = (int **)0x43738c;
  FUN_00466340();
  local_10c = (int **)0x437393;
  local_ec = operator_new(0x50);
  local_4 = 9;
  if (local_ec == (int *)0x0) {
    local_e4 = (int *)0x0;
  }
  else {
    local_e4 = (int *)FUN_00465610();
  }
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x0;
  ppiStack_124 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4373e3;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 251.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437429;
  FUN_00466a10();
  local_10c = (int **)0x0;
  local_110 = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 251.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43746f;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dd340;
  ppiStack_11c = (int **)0x43748c;
  FUN_00466340();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 1;
  local_118 = (char *)&DAT_005dd924;
  ppiStack_11c = (int **)0x4374a9;
  FUN_00466340();
  local_10c = (int **)0x4374b0;
  local_ec = operator_new(0x50);
  local_4 = 10;
  if (local_ec != (int *)0x0) {
    FUN_00465610();
  }
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x0;
  ppiStack_124 = (int **)0x2;
  appiStack_134[3] = (int **)0x4374fc;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 291.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437542;
  FUN_00466a10();
  local_10c = (int **)0x0;
  local_110 = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 291.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437588;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dd98c;
  ppiStack_11c = (int **)0x4375a5;
  FUN_00466340();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 1;
  local_118 = (char *)&DAT_005dd548;
  ppiStack_11c = (int **)0x4375c2;
  FUN_00466340();
  local_10c = (int **)0x4375c9;
  local_ec = operator_new(0x50);
  local_4 = 0xb;
  if (local_ec == (int *)0x0) {
    local_ec = (int *)0x0;
  }
  else {
    local_ec = (int *)FUN_00465610();
  }
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x0;
  ppiStack_124 = (int **)0x1;
  appiStack_134[3] = (int **)0x43761f;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 331.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437669;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dd4ac;
  ppiStack_11c = (int **)0x437686;
  FUN_00466340();
  local_10c = (int **)0x437692;
  FUN_00467950();
  local_10c = (int **)0x43769e;
  FUN_00467950();
  local_10c = (int **)0x4376aa;
  FUN_00467950();
  local_10c = (int **)0x4376b6;
  FUN_00467950();
  local_10c = (int **)0x4376c2;
  FUN_00467950();
  local_10c = (int **)0x4376ca;
  FUN_00467950();
  local_10c = (int **)0x4376d2;
  FUN_00467950();
  local_10c = (int **)0x4376d9;
  puVar4 = operator_new(0x6c);
  local_4 = 0xc;
  if (puVar4 == (undefined4 *)0x0) {
    puVar4 = (undefined4 *)0x0;
  }
  else {
    local_c4 = puVar4;
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8868;
  }
  local_4 = 0xffffffff;
  puVar4[1] = s_map_name_005c7530;
  local_10c = (int **)0x437720;
  local_c4 = puVar4;
  FUN_00463050();
  local_10c = (int **)0x437727;
  local_f4 = operator_new(0x78);
  local_4 = 0xd;
  if (local_f4 == (int *)0x0) {
    uVar5 = 0;
  }
  else {
    uVar5 = FUN_00467160();
  }
  DAT_005dbb74 = 1;
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = 1;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x437784;
  FUN_00462e50();
  local_10c = (int **)0x0;
  local_110 = (int **)s_MU00500_BMP_005c7524;
  local_114 = 10;
  DAT_005ddd68 = 0x43d38000;
  DAT_005ddd6c = 77.0;
  _DAT_005ddd70 = 0x43480000;
  _DAT_005ddd74 = 0x438f0000;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[2] = (int **)0x4377cf;
  FUN_00467840();
  *(undefined4 *)(local_94 + 0x274) = uVar5;
  local_10c = (int **)0x4377e0;
  local_f4 = operator_new(0x50);
  local_4 = 0xe;
  if (local_f4 == (int *)0x0) {
    local_cc = 0;
  }
  else {
    local_cc = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 111.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43785a;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 111.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x4378a4;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de22c;
  ppiStack_11c = (int **)0x4378c1;
  FUN_00466340();
  local_10c = (int **)0x4378c8;
  local_f4 = operator_new(0x50);
  local_4 = 0xf;
  if (local_f4 == (int *)0x0) {
    local_90 = 0;
  }
  else {
    local_90 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 135.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x437945;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 135.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437992;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de2c8;
  ppiStack_11c = (int **)0x4379af;
  FUN_00466340();
  local_10c = (int **)0x4379b6;
  local_f4 = operator_new(0x50);
  local_4 = 0x10;
  if (local_f4 == (int *)0x0) {
    local_98 = 0;
  }
  else {
    local_98 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 159.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x437a33;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 159.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437a80;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de2fc;
  ppiStack_11c = (int **)0x437a9d;
  FUN_00466340();
  local_10c = (int **)0x437aa4;
  local_f4 = operator_new(0x50);
  local_4 = 0x11;
  if (local_f4 == (int *)0x0) {
    local_c0 = (undefined4 *)0x0;
  }
  else {
    local_c0 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 183.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x437b1e;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 183.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437b68;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de260;
  ppiStack_11c = (int **)0x437b85;
  FUN_00466340();
  local_10c = (int **)0x437b8c;
  local_f4 = operator_new(0x50);
  local_4 = 0x12;
  if (local_f4 == (int *)0x0) {
    local_b4 = (undefined4 *)0x0;
  }
  else {
    local_b4 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 207.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x437c06;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 207.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437c50;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de294;
  ppiStack_11c = (int **)0x437c6d;
  FUN_00466340();
  local_10c = (int **)0x437c74;
  local_f4 = operator_new(0x50);
  local_4 = 0x13;
  if (local_f4 == (int *)0x0) {
    local_ac = (undefined4 *)0x0;
  }
  else {
    local_ac = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 231.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x437cee;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 231.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437d38;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de398;
  ppiStack_11c = (int **)0x437d55;
  FUN_00466340();
  local_10c = (int **)0x437d5c;
  local_f4 = operator_new(0x50);
  local_4 = 0x14;
  if (local_f4 == (int *)0x0) {
    local_a0 = (undefined4 *)0x0;
  }
  else {
    local_a0 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 255.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x437dd9;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 255.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437e26;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de3cc;
  ppiStack_11c = (int **)0x437e43;
  FUN_00466340();
  local_10c = (int **)0x437e4a;
  local_f4 = operator_new(0x50);
  local_4 = 0x15;
  if (local_f4 == (int *)0x0) {
    local_b8 = (undefined4 *)0x0;
  }
  else {
    local_b8 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 279.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x437ec4;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 279.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437f0e;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de330;
  ppiStack_11c = (int **)0x437f2b;
  FUN_00466340();
  local_10c = (int **)0x437f32;
  local_f4 = operator_new(0x50);
  local_4 = 0x16;
  if (local_f4 == (int *)0x0) {
    local_b0 = (undefined4 *)0x0;
  }
  else {
    local_b0 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 303.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x437fac;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 303.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x437ff6;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005de364;
  ppiStack_11c = (int **)0x438013;
  FUN_00466340();
  local_10c = (int **)0x43801a;
  local_f4 = operator_new(0x50);
  local_4 = 0x17;
  if (local_f4 == (int *)0x0) {
    local_bc = (undefined4 *)0x0;
  }
  else {
    local_bc = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 327.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x438094;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 327.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x4380de;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005db99c;
  ppiStack_11c = (int **)0x4380fb;
  FUN_00466340();
  local_10c = (int **)0x438102;
  local_f4 = operator_new(0x50);
  local_4 = 0x18;
  if (local_f4 == (int *)0x0) {
    local_a8 = 0;
  }
  else {
    local_a8 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 351.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43817c;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 351.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x4381c6;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005db900;
  ppiStack_11c = (int **)0x4381e3;
  FUN_00466340();
  local_10c = (int **)0x4381ea;
  local_f4 = operator_new(0x50);
  local_4 = 0x19;
  if (local_f4 == (int *)0x0) {
    local_a4 = 0;
  }
  else {
    local_a4 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 375.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x438264;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 375.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x4382b1;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005db934;
  ppiStack_11c = (int **)0x4382ce;
  FUN_00466340();
  local_10c = (int **)0x4382d5;
  local_f4 = operator_new(0x50);
  local_4 = 0x1a;
  if (local_f4 == (int *)0x0) {
    local_c8 = 0;
  }
  else {
    local_c8 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 399.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43834f;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 399.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x438399;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005dba6c;
  ppiStack_11c = (int **)0x4383b6;
  FUN_00466340();
  local_10c = (int **)0x4383bd;
  local_f4 = operator_new(0x50);
  local_4 = 0x1b;
  if (local_f4 == (int *)0x0) {
    local_d4 = (undefined4 *)0x0;
  }
  else {
    local_d4 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 423.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x438437;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 423.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x438481;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005dbad4;
  ppiStack_11c = (int **)0x43849e;
  FUN_00466340();
  local_10c = (int **)0x4384a5;
  local_f4 = operator_new(0x50);
  local_4 = 0x1c;
  if (local_f4 == (int *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 447.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43851f;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 447.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x438569;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005dba04;
  ppiStack_11c = (int **)0x438586;
  FUN_00466340();
  local_10c = (int **)0x43858d;
  local_f4 = operator_new(0x50);
  local_4 = 0x1d;
  if (local_f4 == (int *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 471.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x438607;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 471.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x438651;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dba38;
  ppiStack_11c = (int **)0x43866e;
  FUN_00466340();
  local_10c = (int **)0x438675;
  local_f4 = operator_new(0x50);
  local_4 = 0x1e;
  if (local_f4 == (int *)0x0) {
    local_dc = (int *)0x0;
  }
  else {
    local_dc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 495.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4386ef;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 495.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x438739;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dbc1c;
  ppiStack_11c = (int **)0x438756;
  FUN_00466340();
  local_10c = (int **)0x43875d;
  local_f4 = operator_new(0x50);
  local_4 = 0x1f;
  if (local_f4 == (int *)0x0) {
    local_e4 = (int *)0x0;
  }
  else {
    local_e4 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 519.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4387d7;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 519.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x438821;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dbc50;
  ppiStack_11c = (int **)0x43883e;
  FUN_00466340();
  local_10c = (int **)0x438845;
  local_f4 = operator_new(0x50);
  local_4 = 0x20;
  if (local_f4 == (int *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 543.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4388bf;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 543.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x438909;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dbbe8;
  ppiStack_11c = (int **)0x438926;
  FUN_00466340();
  local_10c = (int **)0x43892d;
  local_f4 = operator_new(0x50);
  local_4 = 0x21;
  if (local_f4 == (int *)0x0) {
    local_e8 = 0;
  }
  else {
    local_e8 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 567.0;
  ppiStack_120 = (int **)0x1;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4389a7;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 567.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x4389f1;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = (char *)&DAT_005dbaa0;
  ppiStack_11c = (int **)0x438a0e;
  FUN_00466340();
  local_10c = (int **)0x438a15;
  piVar6 = operator_new(0x34);
  local_f4 = piVar6;
  if (piVar6 == (int *)0x0) {
    local_ec = (int *)0x0;
  }
  else {
    *piVar6 = (int)&PTR_LAB_005a8810;
    piVar6[1] = 0;
    piVar13 = piVar6 + 9;
    piVar6[3] = 0;
    piVar6[4] = 0;
    piVar6[5] = 0;
    piVar6[6] = 0;
    piVar6[7] = 0x3f800000;
    local_4._0_1_ = 0x23;
    local_4._1_3_ = 0;
    *piVar13 = 0;
    piVar6[10] = 0;
    piVar6[0xb] = 0;
    local_10c = (int **)0x438a69;
    local_ec = piVar13;
    iVar8 = FUN_00402bf0();
    *piVar13 = iVar8;
    piVar6[10] = iVar8;
    piVar6[0xb] = iVar8 + 8;
    local_4 = CONCAT31(local_4._1_3_,0x26);
    FUN_00402a70();
    *piVar6 = (int)&PTR_FUN_005a8700;
    local_ec = piVar6;
  }
  local_10c = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 87.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 5;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  ppiStack_124 = (int **)0x438ae7;
  FUN_004636d0();
  local_10c = (int **)0x438af5;
  FUN_00463b30();
  _DAT_005ddd70 = 0x41000000;
  _DAT_005ddd74 = 0x436d0000;
  DAT_005ddd68 = 0x44174000;
  DAT_005ddd6c = 111.0;
  local_10c = (int **)0x438b24;
  puVar4 = operator_new(0x74);
  local_f0 = puVar4;
  if (puVar4 != (undefined4 *)0x0) {
    *puVar4 = &PTR_LAB_005a8810;
    puVar4[1] = 0;
    local_4._0_1_ = 0x28;
    local_4._1_3_ = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0;
    puVar4[8] = 0x3f800000;
    FUN_00402330();
    local_4._0_1_ = 0x29;
    if (DAT_005d59ac == (undefined4 *)0x0) {
      local_f4 = (int *)0x14;
      local_10c = (int **)0x10;
      local_110 = (int **)0x438b95;
      puVar7 = (undefined4 *)FUN_004036c0();
      if (local_f4 != (int *)0x1) {
        puVar12 = puVar7 + 4;
        iVar8 = 1;
        puVar3 = puVar12;
        DAT_005d59ac = puVar12;
        if (local_f4 != (int *)0x2) {
          do {
            puVar12 = puVar3 + 4;
            *puVar3 = puVar12;
            iVar8 = iVar8 + 1;
            puVar3 = puVar12;
          } while ((int)local_f4 + -1 != iVar8);
        }
        *puVar12 = 0;
      }
    }
    else {
      puVar7 = DAT_005d59ac;
      DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
    }
    DAT_005d59e8 = 0;
    puVar4[0xb] = puVar7;
    *puVar7 = puVar7;
    *(undefined4 *)(puVar4[0xb] + 4) = puVar4[0xb];
    local_4 = CONCAT31(local_4._1_3_,0x2a);
    local_10c = (int **)0x438c01;
    FUN_00469e30();
    *puVar4 = &PTR_FUN_005a87b8;
  }
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0xa;
  ppiStack_124 = (int **)0x438c34;
  FUN_004698c0();
  local_10c = (int **)0x438c3b;
  puVar4 = operator_new(0x6c);
  local_4 = 0x2b;
  local_f0 = puVar4;
  if (puVar4 != (undefined4 *)0x0) {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8758;
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x438c9d;
  FUN_00462e50();
  local_10c = (int **)0x438ca9;
  FUN_00467950();
  local_10c = (int **)0x438cb5;
  FUN_00467950();
  local_10c = (int **)0x438cc1;
  FUN_00467950();
  local_10c = (int **)0x438ccd;
  FUN_00467950();
  local_10c = (int **)0x438cd9;
  FUN_00467950();
  local_10c = (int **)0x438ce5;
  FUN_00467950();
  local_10c = (int **)0x438cf1;
  FUN_00467950();
  local_10c = (int **)0x438cfd;
  FUN_00467950();
  local_10c = (int **)0x438d09;
  FUN_00467950();
  local_10c = (int **)0x438d15;
  FUN_00467950();
  local_10c = (int **)0x438d21;
  FUN_00467950();
  local_10c = (int **)0x438d2d;
  FUN_00467950();
  local_10c = (int **)0x438d39;
  FUN_00467950();
  local_10c = (int **)0x438d45;
  FUN_00467950();
  local_10c = (int **)0x438d51;
  FUN_00467950();
  local_10c = (int **)0x438d5d;
  FUN_00467950();
  local_10c = (int **)0x438d69;
  FUN_00467950();
  local_10c = (int **)0x438d75;
  FUN_00467950();
  local_10c = (int **)0x438d81;
  FUN_00467950();
  local_10c = (int **)0x438d8d;
  FUN_00467950();
  local_10c = (int **)0x438d96;
  FUN_00465f10();
  local_10c = (int **)local_ec;
  local_110 = (int **)0x438da4;
  FUN_00467c50();
  local_10c = (int **)0x438dac;
  FUN_00469330();
  local_10c = (int **)0x438db8;
  FUN_00469760();
  local_10c = (int **)0x438dc4;
  FUN_00469760();
  local_10c = (int **)0x438dd0;
  FUN_00469760();
  local_10c = (int **)0x438ddc;
  FUN_00469760();
  local_10c = (int **)0x438de8;
  FUN_00469760();
  local_10c = (int **)0x438df4;
  FUN_00469760();
  local_10c = (int **)0x438e00;
  FUN_00469760();
  local_10c = (int **)0x438e0c;
  FUN_00469760();
  local_10c = (int **)0x438e18;
  FUN_00469760();
  local_10c = (int **)0x438e24;
  FUN_00469760();
  local_10c = (int **)0x438e30;
  FUN_00469760();
  local_10c = (int **)0x438e3c;
  FUN_00469760();
  local_10c = (int **)0x438e48;
  FUN_00469760();
  local_10c = (int **)0x438e54;
  FUN_00469760();
  local_10c = (int **)0x438e60;
  FUN_00469760();
  local_10c = (int **)0x438e6c;
  FUN_00469760();
  local_10c = (int **)0x438e78;
  FUN_00469760();
  local_10c = (int **)0x438e84;
  FUN_00469760();
  local_10c = (int **)0x438e90;
  FUN_00469760();
  local_10c = (int **)0x438e98;
  FUN_00469760();
  local_10c = (int **)0x438ea2;
  FUN_00462bf0();
  local_10c = (int **)0x438ea9;
  local_f0 = operator_new(0x7c);
  local_4 = 0x2c;
  if (local_f0 != (void *)0x0) {
    FUN_00463fb0();
  }
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  local_114 = 0;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41900000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 96.0;
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[2] = (int **)0x438f1d;
  FUN_004642f0();
  local_10c = (int **)0x438f24;
  local_f0 = operator_new(0x6c);
  local_4 = 0x2d;
  if (local_f0 == (void *)0x0) {
    local_a4 = 0;
  }
  else {
    local_a4 = FUN_00462d50();
  }
  local_4 = 0xffffffff;
  *(char **)(local_a4 + 4) = s_game_name_005c7518;
  local_10c = (int **)0x438f66;
  FUN_00463050();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x438f94;
  FUN_00462e50();
  local_10c = (int **)0x438fa6;
  FUN_00464240();
  local_10c = (int **)0x438fad;
  local_f0 = operator_new(0x7c);
  local_4 = 0x2e;
  if (local_f0 != (void *)0x0) {
    FUN_00463fb0();
  }
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  local_114 = 0;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41900000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 136.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_134[2] = (int **)0x43901f;
  FUN_004642f0();
  local_10c = (int **)0x439026;
  local_f0 = operator_new(0x6c);
  local_4 = 0x2f;
  if (local_f0 == (void *)0x0) {
    local_a8 = 0;
  }
  else {
    local_a8 = FUN_00462d50();
  }
  local_4 = 0xffffffff;
  *(char **)(local_a8 + 4) = s_password_005c4218;
  local_10c = (int **)0x439068;
  FUN_00463050();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x439098;
  FUN_00462e50();
  local_10c = (int **)0x43909f;
  puVar4 = operator_new(0x24);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0x3f800000;
    *puVar4 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 93.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x43910d;
  FUN_0046a670();
  local_10c = (int **)0x439114;
  puVar4 = operator_new(0x6c);
  local_4 = 0x30;
  local_f0 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    local_bc = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8980;
    local_bc = puVar4;
  }
  local_4 = 0xffffffff;
  local_bc[1] = s_hideitem_005c7500;
  local_10c = (int **)0x43915c;
  FUN_00463050();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43918c;
  FUN_00462e50();
  local_10c = (int **)0x439193;
  puVar4 = operator_new(0x24);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0x3f800000;
    *puVar4 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 133.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x439201;
  FUN_0046a670();
  local_10c = (int **)0x439208;
  puVar4 = operator_new(0x6c);
  local_4 = 0x31;
  local_f0 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    local_b0 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8980;
    local_b0 = puVar4;
  }
  local_4 = 0xffffffff;
  local_b0[1] = s_friendfire_005c74f4;
  local_10c = (int **)0x439250;
  FUN_00463050();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x439280;
  FUN_00462e50();
  local_10c = (int **)0x439287;
  puVar4 = operator_new(0x24);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0x3f800000;
    *puVar4 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 173.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x4392f5;
  FUN_0046a670();
  local_10c = (int **)0x4392fc;
  puVar4 = operator_new(0x6c);
  local_4 = 0x32;
  local_f0 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    local_b8 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8980;
    local_b8 = puVar4;
  }
  local_4 = 0xffffffff;
  local_b8[1] = s_autoswitch_005c74e8;
  local_10c = (int **)0x439344;
  FUN_00463050();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x439374;
  FUN_00462e50();
  local_10c = (int **)0x43937b;
  puVar4 = operator_new(0x24);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0x3f800000;
    *puVar4 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 213.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x4393e9;
  FUN_0046a670();
  local_10c = (int **)0x4393f0;
  puVar4 = operator_new(0x6c);
  local_4 = 0x33;
  local_f0 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    local_a0 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8980;
    local_a0 = puVar4;
  }
  local_4 = 0xffffffff;
  local_a0[1] = s_healthitem_005c74dc;
  local_10c = (int **)0x439438;
  FUN_00463050();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x439468;
  FUN_00462e50();
  local_10c = (int **)0x43946f;
  puVar4 = operator_new(0x24);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0x3f800000;
    *puVar4 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 253.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x4394dd;
  FUN_0046a670();
  local_10c = (int **)0x4394e4;
  puVar4 = operator_new(0x6c);
  local_4 = 0x34;
  local_f0 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    local_ac = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8980;
    local_ac = puVar4;
  }
  local_4 = 0xffffffff;
  local_ac[1] = s_updateitem_005c74d0;
  local_10c = (int **)0x43952c;
  FUN_00463050();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43955c;
  FUN_00462e50();
  local_10c = (int **)0x439563;
  puVar4 = operator_new(0x24);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0x3f800000;
    *puVar4 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 293.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x4395d1;
  FUN_0046a670();
  local_10c = (int **)0x4395d8;
  puVar4 = operator_new(0x6c);
  local_4 = 0x35;
  local_f0 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    local_b4 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8980;
    local_b4 = puVar4;
  }
  local_4 = 0xffffffff;
  local_b4[1] = s_specialitem_005c74c4;
  local_10c = (int **)0x43961f;
  FUN_00463050();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43964f;
  FUN_00462e50();
  local_10c = (int **)0x439656;
  local_f0 = operator_new(0x78);
  local_4 = 0x36;
  if (local_f0 == (void *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00467160();
  }
  local_10c = (int **)0x0;
  local_110 = (int **)s_mu01500_bmp_005c74b8;
  local_114 = 5;
  local_4 = 0xffffffff;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 194.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[2] = (int **)0x4396cb;
  FUN_00467840();
  local_10c = (int **)0x4396d2;
  local_f0 = operator_new(0x50);
  local_4 = 0x37;
  if (local_f0 == (void *)0x0) {
    local_e8 = 0;
  }
  else {
    local_e8 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 194.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x439748;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x439763;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005dda90;
  ppiStack_11c = (int **)0x43977f;
  FUN_00466340();
  local_10c = (int **)0x439786;
  local_f0 = operator_new(0x50);
  local_4 = 0x38;
  if (local_f0 == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 218.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4397fc;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x439817;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005ddac4;
  ppiStack_11c = (int **)0x439833;
  FUN_00466340();
  local_10c = (int **)0x43983a;
  local_f0 = operator_new(0x50);
  local_4 = 0x39;
  if (local_f0 == (void *)0x0) {
    local_e4 = (int *)0x0;
  }
  else {
    local_e4 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 242.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x4398b0;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x4398cb;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005dda28;
  ppiStack_11c = (int **)0x4398e7;
  FUN_00466340();
  local_10c = (int **)0x4398ee;
  local_f0 = operator_new(0x50);
  local_4 = 0x3a;
  if (local_f0 == (void *)0x0) {
    local_dc = (int *)0x0;
  }
  else {
    local_dc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 266.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x439964;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43997f;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005dda5c;
  ppiStack_11c = (int **)0x43999b;
  FUN_00466340();
  local_10c = (int **)0x4399a2;
  local_f0 = operator_new(0x50);
  local_4 = 0x3b;
  if (local_f0 == (void *)0x0) {
    local_ec = (int *)0x0;
  }
  else {
    local_ec = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 290.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x0;
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x439a1c;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x439a37;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005ddaf8;
  ppiStack_11c = (int **)0x439a53;
  FUN_00466340();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 196.0;
  local_10c = (int **)0x439a82;
  puVar4 = operator_new(0x74);
  local_f0 = puVar4;
  if (puVar4 != (undefined4 *)0x0) {
    *puVar4 = &PTR_LAB_005a8810;
    puVar4[1] = 0;
    local_4._0_1_ = 0x3d;
    local_4._1_3_ = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0;
    puVar4[8] = 0x3f800000;
    FUN_00402330();
    local_4._0_1_ = 0x3e;
    if (DAT_005d59ac == (undefined4 *)0x0) {
      local_f4 = (int *)0x14;
      local_10c = (int **)0x10;
      local_110 = (int **)0x439af2;
      puVar7 = (undefined4 *)FUN_004036c0();
      if (local_f4 != (int *)0x1) {
        puVar12 = puVar7 + 4;
        iVar8 = 1;
        puVar3 = puVar12;
        DAT_005d59ac = puVar12;
        if (local_f4 != (int *)0x2) {
          do {
            puVar12 = puVar3 + 4;
            *puVar3 = puVar12;
            iVar8 = iVar8 + 1;
            puVar3 = puVar12;
          } while ((int)local_f4 + -1 != iVar8);
        }
        *puVar12 = 0;
      }
    }
    else {
      puVar7 = DAT_005d59ac;
      DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
    }
    DAT_005d59e8 = 0;
    puVar4[0xb] = puVar7;
    *puVar7 = puVar7;
    *(undefined4 *)(puVar4[0xb] + 4) = puVar4[0xb];
    local_4 = CONCAT31(local_4._1_3_,0x3f);
    local_10c = (int **)0x439b56;
    FUN_00469e30();
    *puVar4 = &PTR_FUN_005a87b8;
  }
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x5;
  ppiStack_124 = (int **)0x439b87;
  FUN_004698c0();
  local_10c = (int **)0x439b8e;
  piVar6 = operator_new(0x6c);
  local_4 = 0x40;
  local_f0 = piVar6;
  if (piVar6 == (int *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    FUN_00462d50();
    *piVar6 = (int)&PTR_FUN_005a8758;
    local_d0 = piVar6;
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x439bf2;
  FUN_00462e50();
  piVar6 = local_d8;
  local_10c = (int **)0x439c02;
  FUN_00467950();
  local_10c = (int **)0x439c0e;
  FUN_00467950();
  local_10c = (int **)0x439c1a;
  FUN_00467950();
  local_10c = (int **)0x439c26;
  FUN_00467950();
  local_10c = (int **)0x439c32;
  FUN_00467950();
  local_10c = (int **)0x439c3a;
  FUN_00469330();
  local_10c = (int **)0x439c46;
  FUN_00469760();
  local_10c = (int **)0x439c52;
  FUN_00469760();
  local_10c = (int **)0x439c5e;
  FUN_00469760();
  local_10c = (int **)0x439c6a;
  FUN_00469760();
  local_10c = (int **)0x439c72;
  FUN_00469760();
  if (piVar6[0xf] != 0) {
    local_10c = &local_e0;
    local_110 = &local_e4;
    local_118 = (char *)0x439c92;
    local_114 = piVar6[0xf];
    FUN_00429e60();
    ppiStack_124 = (int **)piVar6[0xf];
    local_118 = (undefined *)0x1;
    ppiStack_11c = (int **)local_e0;
    ppiStack_120 = (int **)local_e4;
    appiStack_134[3] = (int **)0x439ca7;
    FUN_00429d40();
    piVar13 = *(int **)piVar6[2];
    if (piVar13 != (int *)piVar6[2]) {
      do {
        local_d4 = (undefined4 *)piVar13[2];
        local_e8 = *(int *)(*(int *)((int)local_d4 + 0x20) + 8);
        if (local_e8 != *(int *)((int)local_d4 + 0x20)) {
          do {
            iVar8 = *(int *)(local_e8 + 0x14);
            if ((*(int *)(iVar8 + 0x44) == 0) && (*(int *)(iVar8 + 0x1c) != 0)) {
              local_10c = &local_f4;
              local_110 = &local_ec;
              local_118 = (char *)0x439cf4;
              local_114 = *(int *)(iVar8 + 0x1c);
              FUN_00429e60();
              ppiStack_124 = *(int ***)(iVar8 + 0x1c);
              local_118 = (undefined *)0x2;
              ppiStack_11c = (int **)local_f4;
              ppiStack_120 = (int **)local_ec;
              appiStack_134[3] = (int **)0x439d09;
              FUN_00429d40();
              appiStack_134[3] = &local_dc;
              appiStack_134[2] = &local_f4;
              appiStack_134[0] = *(int ***)(iVar8 + 0x20);
              appiStack_134[1] = &local_ec;
              FUN_00429e60();
              FUN_00429d40(*(undefined4 *)(iVar8 + 0x20),local_ec,local_f4,3);
            }
            FUN_0043c6c0();
          } while (local_e8 != *(int *)((int)local_d4 + 0x20));
        }
        piVar13 = (int *)*piVar13;
      } while (piVar13 != (int *)piVar6[2]);
    }
    iVar8 = piVar6[0xe];
    if (iVar8 != 0) {
      local_10c = &local_f4;
      local_114 = *(int *)(iVar8 + 0x54);
      local_110 = &local_ec;
      local_118 = (char *)0x439d82;
      FUN_00429e60();
      ppiStack_124 = *(int ***)(iVar8 + 0x54);
      local_118 = (undefined *)0x2;
      ppiStack_11c = (int **)local_f4;
      ppiStack_120 = (int **)local_ec;
      appiStack_134[3] = (int **)0x439d97;
      FUN_00429d40();
    }
  }
  local_10c = (int **)0x439da1;
  puVar4 = operator_new(0x58);
  if (puVar4 != (undefined4 *)0x0) {
    puVar4[1] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0;
    puVar4[8] = 0;
    puVar4[9] = 0x3f800000;
    puVar4[10] = 0;
    puVar4[0xb] = 0;
    puVar4[0xc] = 0;
    puVar4[0xd] = 0;
    puVar4[0xe] = 0x3f800000;
    *puVar4 = &PTR_FUN_005a8928;
  }
  local_10c = (int **)0x439de5;
  puVar4 = operator_new(0x70);
  local_4 = 0x41;
  local_f0 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    puVar4 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a88c8;
    puVar4[0x1b] = 0;
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x439e51;
  local_c0 = puVar4;
  FUN_00462e50();
  local_10c = (int **)0x0;
  local_8c[4] = (undefined4 *)0x3f800000;
  local_8c[3] = (undefined4 *)0x41c00000;
  local_8c[2] = (undefined4 *)0x41c00000;
  local_8c[1] = (undefined4 *)0x432e0000;
  local_8c[0] = (undefined4 *)0x435e0000;
  ppuVar15 = local_8c;
  pppiVar18 = appiStack_134 + 5;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*ppuVar15;
    ppuVar15 = ppuVar15 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 172.0;
  puVar7 = &DAT_005ddd68;
  pppiVar18 = appiStack_134;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar7;
    puVar7 = puVar7 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  puVar4[1] = s_rules_005c74a4;
  local_10c = (int **)0x439ef5;
  FUN_0046adf0();
  local_10c = (int **)0x439f01;
  FUN_0046b240();
  local_10c = (int **)0x439f0d;
  FUN_00462bf0();
  local_10c = (int **)0x439f16;
  FUN_00463050();
  local_10c = (int **)0x439f1d;
  local_f0 = operator_new(0x78);
  local_4 = 0x42;
  if (local_f0 == (void *)0x0) {
    local_cc = 0;
  }
  else {
    local_cc = FUN_00467160();
  }
  iVar8 = local_cc;
  local_10c = (int **)0x0;
  local_110 = (int **)s_mu01500_bmp_005c74b8;
  local_114 = 5;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 234.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar9 = 5; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_134[2] = (int **)0x439fa4;
  FUN_00467840();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 236.0;
  local_10c = (int **)0x439fd3;
  puVar4 = operator_new(0x74);
  local_f0 = puVar4;
  if (puVar4 != (undefined4 *)0x0) {
    *puVar4 = &PTR_LAB_005a8810;
    puVar4[1] = 0;
    local_4._0_1_ = 0x44;
    local_4._1_3_ = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0;
    puVar4[8] = 0x3f800000;
    FUN_00402330();
    local_4._0_1_ = 0x45;
    if (DAT_005d59ac == (undefined4 *)0x0) {
      local_f4 = (int *)0x14;
      local_10c = (int **)0x10;
      local_110 = (int **)0x43a045;
      puVar7 = (undefined4 *)FUN_004036c0();
      if (local_f4 != (int *)0x1) {
        puVar12 = puVar7 + 4;
        iVar9 = 1;
        puVar3 = puVar12;
        DAT_005d59ac = puVar12;
        if (local_f4 != (int *)0x2) {
          do {
            puVar12 = puVar3 + 4;
            *puVar3 = puVar12;
            iVar9 = iVar9 + 1;
            puVar3 = puVar12;
          } while ((int)local_f4 + -1 != iVar9);
        }
        *puVar12 = 0;
      }
    }
    else {
      puVar7 = DAT_005d59ac;
      DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
    }
    DAT_005d59e8 = 0;
    puVar4[0xb] = puVar7;
    *puVar7 = puVar7;
    *(undefined4 *)(puVar4[0xb] + 4) = puVar4[0xb];
    local_4 = CONCAT31(local_4._1_3_,0x46);
    local_10c = (int **)0x43a0b1;
    FUN_00469e30();
    *puVar4 = &PTR_FUN_005a87b8;
  }
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar9 = 5; iVar9 != 0; iVar9 = iVar9 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x5;
  ppiStack_124 = (int **)0x43a0e3;
  FUN_004698c0();
  local_10c = (int **)0x43a0ea;
  puVar4 = operator_new(0x6c);
  local_4 = 0x47;
  local_f0 = puVar4;
  if (puVar4 == (undefined4 *)0x0) {
    local_d4 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar4 = &PTR_FUN_005a8758;
    local_d4 = puVar4;
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43a14e;
  FUN_00462e50();
  local_10c = (int **)0x43a156;
  FUN_00469330();
  if (*(code **)(local_94 + 0x28) == (code *)0x0) {
    local_10c = (int **)0x43a296;
    local_f0 = operator_new(0x50);
    local_4 = 0x49;
    if (local_f0 == (void *)0x0) {
      local_f4 = (int *)0x0;
    }
    else {
      local_f4 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 234.0;
    ppiStack_120 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 6;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_124 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_134[3] = (int **)0x43a30e;
    FUN_00466720();
    local_10c = (int **)0x0;
    local_110 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 4;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_134[3] = (int **)0x43a32c;
    FUN_00466a10();
    local_10c = (int **)0xff;
    local_110 = (int **)0xff;
    local_114 = 0;
    local_118 = &DAT_005c74a0;
    ppiStack_11c = (int **)0x43a349;
    FUN_00466340();
    local_10c = (int **)0x43a350;
    local_f0 = operator_new(0x50);
    local_4 = 0x4a;
    if (local_f0 == (void *)0x0) {
      local_ec = (int *)0x0;
    }
    else {
      local_ec = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 258.0;
    ppiStack_120 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 6;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_124 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_134[3] = (int **)0x43a3c8;
    FUN_00466720();
    local_10c = (int **)0x0;
    local_110 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 4;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_134[3] = (int **)0x43a3e6;
    FUN_00466a10();
    local_10c = (int **)0xff;
    local_110 = (int **)0xff;
    local_114 = 0;
    local_118 = &DAT_005c749c;
    ppiStack_11c = (int **)0x43a403;
    FUN_00466340();
    local_10c = (int **)0x43a40a;
    local_f0 = operator_new(0x50);
    local_4 = 0x4b;
    if (local_f0 == (void *)0x0) {
      local_e8 = 0;
    }
    else {
      local_e8 = FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 282.0;
    ppiStack_120 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 6;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_124 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_134[3] = (int **)0x43a482;
    FUN_00466720();
    local_10c = (int **)0x0;
    local_110 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 4;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_134[3] = (int **)0x43a4a0;
    FUN_00466a10();
    local_10c = (int **)0xff;
    local_110 = (int **)0xff;
    local_114 = 0;
    local_118 = &DAT_005c7498;
    ppiStack_11c = (int **)0x43a4bd;
    FUN_00466340();
    local_10c = (int **)0x43a4c4;
    local_f0 = operator_new(0x50);
    local_4 = 0x4c;
    if (local_f0 == (void *)0x0) {
      local_e0 = (int *)0x0;
    }
    else {
      local_e0 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 306.0;
    ppiStack_120 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 6;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_124 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_134[3] = (int **)0x43a53c;
    FUN_00466720();
    local_10c = (int **)0x0;
    local_110 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 4;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_134[3] = (int **)0x43a55a;
    FUN_00466a10();
    local_10c = (int **)0xff;
    local_110 = (int **)0xff;
    local_114 = 0;
    local_118 = &DAT_005c7494;
    ppiStack_11c = (int **)0x43a577;
    FUN_00466340();
    local_10c = (int **)0x43a57e;
    local_f0 = operator_new(0x50);
    local_4 = 0x4d;
    if (local_f0 == (void *)0x0) {
      local_e4 = (int *)0x0;
    }
    else {
      local_e4 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 330.0;
    ppiStack_120 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 6;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_124 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_134[3] = (int **)0x43a5f6;
    FUN_00466720();
    local_10c = (int **)0x0;
    local_110 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 4;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_134[3] = (int **)0x43a614;
    FUN_00466a10();
    local_10c = (int **)0xff;
    local_110 = (int **)0xff;
    local_114 = 0;
    local_118 = &DAT_005c7490;
    ppiStack_11c = (int **)0x43a631;
    FUN_00466340();
    local_10c = (int **)0x43a638;
    local_f0 = operator_new(0x50);
    local_4 = 0x4e;
    if (local_f0 == (void *)0x0) {
      local_dc = (int *)0x0;
    }
    else {
      local_dc = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 354.0;
    ppiStack_120 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 6;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_124 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_134[3] = (int **)0x43a6b0;
    FUN_00466720();
    local_10c = (int **)0x0;
    local_110 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 4;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_134[3] = (int **)0x43a6ce;
    FUN_00466a10();
    local_10c = (int **)0xff;
    local_110 = (int **)0xff;
    local_114 = 0;
    local_118 = &DAT_005c748c;
    ppiStack_11c = (int **)0x43a6eb;
    FUN_00466340();
    local_10c = (int **)0x43a6f2;
    local_f0 = operator_new(0x50);
    local_4 = 0x4f;
    if (local_f0 == (void *)0x0) {
      local_d8 = (int *)0x0;
    }
    else {
      local_d8 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 378.0;
    ppiStack_120 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 6;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_124 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_134[3] = (int **)0x43a76a;
    FUN_00466720();
    local_10c = (int **)0x0;
    local_110 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 4;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_134[3] = (int **)0x43a788;
    FUN_00466a10();
    local_10c = (int **)0xff;
    local_110 = (int **)0xff;
    local_114 = 0;
    local_118 = &DAT_005c7488;
    ppiStack_11c = (int **)0x43a7a5;
    FUN_00466340();
    local_10c = (int **)0x43a7ac;
    local_f0 = operator_new(0x50);
    local_4 = 0x50;
    if (local_f0 != (undefined4 *)0x0) {
      FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 402.0;
    ppiStack_120 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 6;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_124 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_134[3] = (int **)0x43a820;
    FUN_00466720();
    local_10c = (int **)0x0;
    local_110 = (int **)0x0;
    puVar4 = &DAT_005ddd68;
    pppiVar18 = appiStack_134 + 4;
    for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
      *pppiVar18 = (int **)*puVar4;
      puVar4 = puVar4 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_134[3] = (int **)0x43a83e;
    FUN_00466a10();
    local_10c = (int **)0xff;
    local_110 = (int **)0xff;
    local_114 = 0;
    local_118 = &DAT_005c7484;
    ppiStack_11c = (int **)0x43a85b;
    FUN_00466340();
    local_10c = (int **)0x43a86b;
    FUN_00467950();
    local_10c = (int **)0x43a877;
    FUN_00467950();
    local_10c = (int **)0x43a883;
    FUN_00467950();
    local_10c = (int **)0x43a88f;
    FUN_00467950();
    local_10c = (int **)0x43a89b;
    FUN_00467950();
    local_10c = (int **)0x43a8a7;
    FUN_00467950();
    local_10c = (int **)0x43a8b3;
    FUN_00467950();
    local_10c = (int **)0x43a8bb;
    FUN_00467950();
    local_10c = (int **)0x43a8c7;
    FUN_00469760();
    local_10c = (int **)0x43a8d3;
    FUN_00469760();
    local_10c = (int **)0x43a8df;
    FUN_00469760();
    local_10c = (int **)0x43a8eb;
    FUN_00469760();
    local_10c = (int **)0x43a8f7;
    FUN_00469760();
    local_10c = (int **)0x43a903;
    FUN_00469760();
    local_10c = (int **)0x43a90b;
    FUN_00469760();
    local_10c = (int **)0x43a913;
    FUN_00469760();
    iVar8 = local_cc;
  }
  else {
    local_e8 = (**(code **)(local_94 + 0x28))();
    local_ec = (int *)0x1;
    local_e8 = local_e8 / 2;
    if (0 < local_e8) {
      local_f4 = (int *)0xea;
      do {
        local_10c = (int **)0x43a190;
        local_f0 = operator_new(0x50);
        local_4 = 0x48;
        if (local_f0 != (undefined4 *)0x0) {
          FUN_00465610();
        }
        DAT_005ddd6c = (float)(int)local_f4;
        _DAT_005ddd70 = 0x42e60000;
        _DAT_005ddd74 = 0x41c00000;
        DAT_005ddd68 = 0x42d20000;
        puVar4 = &DAT_005ddd68;
        pppiVar18 = appiStack_134 + 6;
        for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
          *pppiVar18 = (int **)*puVar4;
          puVar4 = puVar4 + 1;
          pppiVar18 = pppiVar18 + 1;
        }
        ppiStack_120 = (int **)0x0;
        ppiStack_124 = (int **)0x1;
        local_4 = 0xffffffff;
        appiStack_134[3] = (int **)0x43a204;
        FUN_00466720();
        local_10c = (int **)0x0;
        local_110 = (int **)0x0;
        puVar4 = &DAT_005ddd68;
        pppiVar18 = appiStack_134 + 4;
        for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
          *pppiVar18 = (int **)*puVar4;
          puVar4 = puVar4 + 1;
          pppiVar18 = pppiVar18 + 1;
        }
        appiStack_134[3] = (int **)0x43a222;
        FUN_00466a10();
        piVar6 = local_ec;
        local_10c = (int **)auStack_34;
        local_110 = (int **)((int)local_ec * 2);
        local_114 = 0x43a239;
        FUN_0050aaa9();
        local_118 = auStack_34;
        local_10c = (int **)0xff;
        local_110 = (int **)0xff;
        local_114 = 0;
        ppiStack_11c = (int **)0x43a25c;
        FUN_00466340();
        local_10c = (int **)0x43a266;
        FUN_00467950();
        local_10c = (int **)0x43a26e;
        FUN_00469760();
        local_ec = (int *)((int)piVar6 + 1);
        local_f4 = local_f4 + 6;
        iVar8 = local_cc;
      } while ((int)local_ec <= local_e8);
    }
  }
  if (*(int *)(iVar8 + 0x3c) != 0) {
    local_10c = &local_e4;
    local_110 = &local_dc;
    local_118 = (char *)0x43a937;
    local_114 = *(int *)(iVar8 + 0x3c);
    FUN_00429e60();
    ppiStack_124 = *(int ***)(iVar8 + 0x3c);
    local_118 = (undefined *)0x1;
    ppiStack_11c = (int **)local_e4;
    ppiStack_120 = (int **)local_dc;
    appiStack_134[3] = (int **)0x43a94c;
    FUN_00429d40();
    local_e0 = (int *)**(int **)(iVar8 + 8);
    if (local_e0 != *(int **)(iVar8 + 8)) {
      do {
        iVar9 = local_e0[2];
        iVar2 = *(int *)(iVar9 + 0x20);
        local_e8 = *(int *)(iVar2 + 8);
        if (local_e8 != iVar2) {
          do {
            iVar2 = *(int *)(local_e8 + 0x14);
            if ((*(int *)(iVar2 + 0x44) == 0) && (*(int *)(iVar2 + 0x1c) != 0)) {
              local_10c = &local_f4;
              local_110 = &local_ec;
              local_118 = (char *)0x43a997;
              local_114 = *(int *)(iVar2 + 0x1c);
              FUN_00429e60();
              ppiStack_124 = *(int ***)(iVar2 + 0x1c);
              local_118 = (undefined *)0x2;
              ppiStack_11c = (int **)local_f4;
              ppiStack_120 = (int **)local_ec;
              appiStack_134[3] = (int **)0x43a9ac;
              FUN_00429d40();
              appiStack_134[3] = &local_d8;
              appiStack_134[2] = &local_f4;
              appiStack_134[0] = *(int ***)(iVar2 + 0x20);
              appiStack_134[1] = &local_ec;
              FUN_00429e60();
              FUN_00429d40(*(undefined4 *)(iVar2 + 0x20),local_ec,local_f4,3);
            }
            FUN_0043c6c0();
          } while (local_e8 != *(int *)(iVar9 + 0x20));
        }
        local_10c = &local_d0;
        local_110 = (int **)0x43aa00;
        FUN_004a8420();
      } while (local_e0 != *(int **)(iVar8 + 8));
    }
    if (*(int *)(iVar8 + 0x38) != 0) {
      local_10c = (int **)0x43aa1d;
      FUN_00443790();
    }
  }
  local_10c = (int **)0x43aa24;
  local_f0 = operator_new(0x58);
  local_4 = 0x51;
  if (local_f0 != (void *)0x0) {
    FUN_00443e60();
  }
  local_4 = 0xffffffff;
  local_10c = (int **)0x43aa59;
  local_f0 = operator_new(0x70);
  local_4 = 0x52;
  if (local_f0 == (void *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_00443d00();
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43aac3;
  FUN_00462e50();
  local_10c = (int **)0x0;
  local_8c[3] = (undefined4 *)0x41c00000;
  local_8c[2] = (undefined4 *)0x41c00000;
  local_8c[1] = (undefined4 *)0x43560000;
  local_8c[0] = (undefined4 *)0x435e0000;
  ppuVar15 = local_8c;
  pppiVar18 = appiStack_134 + 5;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*ppuVar15;
    ppuVar15 = ppuVar15 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 212.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_10c = (int **)0x43ab55;
  FUN_0046adf0();
  if (*(code **)(local_94 + 0x28) != (code *)0x0) {
    uVar10 = (**(code **)(local_94 + 0x28))();
    uVar11 = uVar10 & 0x80000001;
    if ((int)uVar11 < 0) {
      uVar11 = (uVar11 - 1 | 0xfffffffe) + 1;
    }
    local_10c = (int **)auStack_20;
    local_110 = (int **)(uVar10 - uVar11);
    local_114 = 0x43ab8a;
    FUN_0050aaa9();
  }
  local_10c = (int **)0x43ab9c;
  FUN_0046b240();
  local_10c = (int **)0x43aba8;
  FUN_00443160();
  local_10c = (int **)0x43abb1;
  FUN_00463050();
  local_10c = (int **)0x43abbd;
  FUN_00462bf0();
  local_10c = (int **)0x43abc4;
  local_f0 = operator_new(0x78);
  local_4 = 0x53;
  if (local_f0 != (void *)0x0) {
    FUN_00467160();
  }
  local_10c = (int **)0x0;
  local_110 = (int **)s_mu01500_bmp_005c74b8;
  local_114 = 5;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 274.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_134[2] = (int **)0x43ac3d;
  FUN_00467840();
  local_10c = (int **)0x43ac44;
  local_f0 = operator_new(0x50);
  local_4 = 0x54;
  if (local_f0 == (void *)0x0) {
    local_f4 = (int *)0x0;
  }
  else {
    local_f4 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 274.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43acbc;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43acda;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c7474;
  ppiStack_11c = (int **)0x43acf7;
  FUN_00466340();
  local_10c = (int **)0x43acfe;
  local_f0 = operator_new(0x50);
  local_4 = 0x55;
  if (local_f0 == (void *)0x0) {
    local_ec = (int *)0x0;
  }
  else {
    local_ec = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 298.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43ad76;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43ad94;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c7470;
  ppiStack_11c = (int **)0x43adb1;
  FUN_00466340();
  local_10c = (int **)0x43adb8;
  local_f0 = operator_new(0x50);
  local_4 = 0x56;
  if (local_f0 == (void *)0x0) {
    local_e8 = 0;
  }
  else {
    local_e8 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 322.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43ae30;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43ae4e;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c746c;
  ppiStack_11c = (int **)0x43ae6b;
  FUN_00466340();
  local_10c = (int **)0x43ae72;
  local_f0 = operator_new(0x50);
  local_4 = 0x57;
  if (local_f0 == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 346.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43aeea;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43af08;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c7468;
  ppiStack_11c = (int **)0x43af25;
  FUN_00466340();
  local_10c = (int **)0x43af2c;
  local_f0 = operator_new(0x50);
  local_4 = 0x58;
  if (local_f0 == (void *)0x0) {
    local_e4 = (int *)0x0;
  }
  else {
    local_e4 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 370.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43afa4;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43afc2;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c7464;
  ppiStack_11c = (int **)0x43afdf;
  FUN_00466340();
  local_10c = (int **)0x43afe6;
  local_f0 = operator_new(0x50);
  local_4 = 0x59;
  if (local_f0 == (void *)0x0) {
    local_dc = (int *)0x0;
  }
  else {
    local_dc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 394.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43b05e;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43b07c;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c7460;
  ppiStack_11c = (int **)0x43b099;
  FUN_00466340();
  local_10c = (int **)0x43b0a0;
  local_f0 = operator_new(0x50);
  local_4 = 0x5a;
  if (local_f0 == (void *)0x0) {
    local_d4 = (undefined4 *)0x0;
  }
  else {
    local_d4 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 418.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43b118;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43b136;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c745c;
  ppiStack_11c = (int **)0x43b153;
  FUN_00466340();
  local_10c = (int **)0x43b15a;
  local_f0 = operator_new(0x50);
  local_4 = 0x5b;
  if (local_f0 == (void *)0x0) {
    local_c8 = 0;
  }
  else {
    local_c8 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 442.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43b1d2;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43b1f0;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c7458;
  ppiStack_11c = (int **)0x43b20d;
  FUN_00466340();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 276.0;
  local_10c = (int **)0x43b23c;
  local_f0 = operator_new(0x74);
  local_4 = 0x5c;
  if (local_f0 != (void *)0x0) {
    FUN_00443630();
  }
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x5;
  ppiStack_124 = (int **)0x43b286;
  FUN_004698c0();
  local_10c = (int **)0x43b28d;
  local_f0 = operator_new(0x6c);
  local_4 = 0x5d;
  if (local_f0 == (void *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00443a20();
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43b2f3;
  FUN_00462e50();
  local_10c = (int **)0x43b2ff;
  FUN_00467950();
  local_10c = (int **)0x43b30b;
  FUN_00467950();
  local_10c = (int **)0x43b317;
  FUN_00467950();
  local_10c = (int **)0x43b323;
  FUN_00467950();
  local_10c = (int **)0x43b32f;
  FUN_00467950();
  local_10c = (int **)0x43b33b;
  FUN_00467950();
  local_10c = (int **)0x43b347;
  FUN_00467950();
  local_10c = (int **)0x43b353;
  FUN_00467950();
  local_10c = (int **)0x43b35b;
  FUN_00469330();
  local_10c = (int **)0x43b367;
  FUN_00469760();
  local_10c = (int **)0x43b373;
  FUN_00469760();
  local_10c = (int **)0x43b37f;
  FUN_00469760();
  local_10c = (int **)0x43b38b;
  FUN_00469760();
  local_10c = (int **)0x43b397;
  FUN_00469760();
  local_10c = (int **)0x43b3a3;
  FUN_00469760();
  local_10c = (int **)0x43b3ab;
  FUN_00469760();
  local_10c = (int **)0x43b3b3;
  FUN_00469760();
  local_10c = (int **)0x43b3bc;
  FUN_004438d0();
  local_10c = (int **)0x43b3c3;
  local_f0 = operator_new(0x58);
  uVar5 = 0;
  local_4 = 0x5e;
  if (local_f0 == (void *)0x0) {
    local_f4 = (int *)0x0;
  }
  else {
    local_f4 = (int *)FUN_00443e60();
  }
  local_4 = 0xffffffff;
  local_10c = (int **)0x43b3fe;
  local_f0 = operator_new(0x70);
  local_4 = 0x5f;
  if (local_f0 != (void *)0x0) {
    uVar5 = FUN_00443d00();
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43b460;
  local_d4 = (undefined4 *)uVar5;
  FUN_00462e50();
  local_10c = (int **)0x0;
  local_8c[3] = (undefined4 *)0x41c00000;
  local_8c[2] = (undefined4 *)0x41c00000;
  local_8c[1] = (undefined4 *)0x437e0000;
  local_8c[0] = (undefined4 *)0x435e0000;
  ppuVar15 = local_8c;
  pppiVar18 = appiStack_134 + 5;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*ppuVar15;
    ppuVar15 = ppuVar15 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 252.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_10c = (int **)0x43b4f2;
  FUN_0046adf0();
  local_10c = (int **)0x43b4fe;
  FUN_0046b240();
  local_10c = (int **)0x43b50a;
  FUN_00443160();
  local_10c = (int **)0x43b513;
  FUN_00463050();
  local_10c = (int **)0x43b51f;
  FUN_00462bf0();
  local_10c = (int **)0x43b526;
  local_f0 = operator_new(0x78);
  local_4 = 0x60;
  if (local_f0 == (void *)0x0) {
    local_ec = (int *)0x0;
  }
  else {
    local_ec = (int *)FUN_00467160();
  }
  local_10c = (int **)0x0;
  local_110 = (int **)s_mu01500_bmp_005c74b8;
  local_114 = 5;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 314.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_134[2] = (int **)0x43b5a8;
  FUN_00467840();
  local_10c = (int **)0x43b5af;
  local_f0 = operator_new(0x50);
  local_4 = 0x61;
  if (local_f0 == (void *)0x0) {
    local_f4 = (int *)0x0;
  }
  else {
    local_f4 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 314.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43b623;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43b641;
  FUN_00466a10();
  pcVar14 = acStack_68;
  for (iVar8 = 0xc; iVar8 != 0; iVar8 = iVar8 + -1) {
    pcVar14[0] = '\0';
    pcVar14[1] = '\0';
    pcVar14[2] = '\0';
    pcVar14[3] = '\0';
    pcVar14 = pcVar14 + 4;
  }
  pcVar14[0] = '\0';
  pcVar14[1] = '\0';
  iVar8 = 0;
  do {
    cVar1 = (&DAT_005c7474)[iVar8];
    acStack_68[iVar8] = cVar1;
    iVar8 = iVar8 + 1;
  } while (cVar1 != '\0');
  uVar10 = 0xffffffff;
  pcVar14 = &DAT_005dd854;
  do {
    pcVar17 = pcVar14;
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    pcVar17 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar17;
  } while (cVar1 != '\0');
  uVar10 = ~uVar10;
  iVar8 = -1;
  local_10c = (int **)0xff;
  pcVar14 = acStack_68;
  do {
    pcVar16 = pcVar14;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    pcVar16 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar16;
  } while (cVar1 != '\0');
  pcVar14 = pcVar17 + -uVar10;
  pcVar17 = pcVar16 + -1;
  for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar14;
    pcVar14 = pcVar14 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_110 = (int **)0xff;
  local_114 = 0;
  for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar17 = *pcVar14;
    pcVar14 = pcVar14 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_118 = acStack_68;
  ppiStack_11c = (int **)0x43b6b9;
  FUN_00466340();
  local_10c = (int **)0x43b6c0;
  local_f0 = operator_new(0x50);
  local_4 = 0x62;
  if (local_f0 == (void *)0x0) {
    local_e8 = 0;
  }
  else {
    local_e8 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 338.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43b734;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43b752;
  FUN_00466a10();
  pcVar14 = acStack_68;
  for (iVar8 = 0xc; iVar8 != 0; iVar8 = iVar8 + -1) {
    pcVar14[0] = '\0';
    pcVar14[1] = '\0';
    pcVar14[2] = '\0';
    pcVar14[3] = '\0';
    pcVar14 = pcVar14 + 4;
  }
  pcVar14[0] = '\0';
  pcVar14[1] = '\0';
  iVar8 = 0;
  do {
    cVar1 = (&DAT_005c7470)[iVar8];
    acStack_68[iVar8] = cVar1;
    iVar8 = iVar8 + 1;
  } while (cVar1 != '\0');
  uVar10 = 0xffffffff;
  pcVar14 = &DAT_005dd854;
  do {
    pcVar17 = pcVar14;
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    pcVar17 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar17;
  } while (cVar1 != '\0');
  uVar10 = ~uVar10;
  iVar8 = -1;
  local_10c = (int **)0xff;
  pcVar14 = acStack_68;
  do {
    pcVar16 = pcVar14;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    pcVar16 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar16;
  } while (cVar1 != '\0');
  pcVar14 = pcVar17 + -uVar10;
  pcVar17 = pcVar16 + -1;
  for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar14;
    pcVar14 = pcVar14 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_110 = (int **)0xff;
  local_114 = 0;
  for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar17 = *pcVar14;
    pcVar14 = pcVar14 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_118 = acStack_68;
  ppiStack_11c = (int **)0x43b7ca;
  FUN_00466340();
  local_10c = (int **)0x43b7d1;
  local_f0 = operator_new(0x50);
  local_4 = 99;
  if (local_f0 == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 362.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43b845;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43b863;
  FUN_00466a10();
  pcVar14 = acStack_68;
  for (iVar8 = 0xc; iVar8 != 0; iVar8 = iVar8 + -1) {
    pcVar14[0] = '\0';
    pcVar14[1] = '\0';
    pcVar14[2] = '\0';
    pcVar14[3] = '\0';
    pcVar14 = pcVar14 + 4;
  }
  pcVar14[0] = '\0';
  pcVar14[1] = '\0';
  iVar8 = 0;
  do {
    cVar1 = (&DAT_005c746c)[iVar8];
    acStack_68[iVar8] = cVar1;
    iVar8 = iVar8 + 1;
  } while (cVar1 != '\0');
  uVar10 = 0xffffffff;
  pcVar14 = &DAT_005dd854;
  do {
    pcVar17 = pcVar14;
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    pcVar17 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar17;
  } while (cVar1 != '\0');
  uVar10 = ~uVar10;
  iVar8 = -1;
  local_10c = (int **)0xff;
  pcVar14 = acStack_68;
  do {
    pcVar16 = pcVar14;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    pcVar16 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar16;
  } while (cVar1 != '\0');
  pcVar14 = pcVar17 + -uVar10;
  pcVar17 = pcVar16 + -1;
  for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar14;
    pcVar14 = pcVar14 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_110 = (int **)0xff;
  local_114 = 0;
  for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar17 = *pcVar14;
    pcVar14 = pcVar14 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_118 = acStack_68;
  ppiStack_11c = (int **)0x43b8db;
  FUN_00466340();
  local_10c = (int **)0x43b8e2;
  local_f0 = operator_new(0x50);
  local_4 = 100;
  if (local_f0 == (void *)0x0) {
    local_dc = (int *)0x0;
  }
  else {
    local_dc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 386.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43b956;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43b974;
  FUN_00466a10();
  pcVar14 = acStack_68;
  for (iVar8 = 0xc; iVar8 != 0; iVar8 = iVar8 + -1) {
    pcVar14[0] = '\0';
    pcVar14[1] = '\0';
    pcVar14[2] = '\0';
    pcVar14[3] = '\0';
    pcVar14 = pcVar14 + 4;
  }
  pcVar14[0] = '\0';
  pcVar14[1] = '\0';
  iVar8 = 0;
  do {
    cVar1 = (&DAT_005c7490)[iVar8];
    acStack_68[iVar8] = cVar1;
    iVar8 = iVar8 + 1;
  } while (cVar1 != '\0');
  uVar10 = 0xffffffff;
  pcVar14 = &DAT_005dd854;
  do {
    pcVar17 = pcVar14;
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    pcVar17 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar17;
  } while (cVar1 != '\0');
  uVar10 = ~uVar10;
  iVar8 = -1;
  local_10c = (int **)0xff;
  pcVar14 = acStack_68;
  do {
    pcVar16 = pcVar14;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    pcVar16 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar16;
  } while (cVar1 != '\0');
  pcVar14 = pcVar17 + -uVar10;
  pcVar17 = pcVar16 + -1;
  for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar14;
    pcVar14 = pcVar14 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_110 = (int **)0xff;
  local_114 = 0;
  for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar17 = *pcVar14;
    pcVar14 = pcVar14 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_118 = acStack_68;
  ppiStack_11c = (int **)0x43b9ec;
  FUN_00466340();
  local_10c = (int **)0x43b9f3;
  local_f0 = operator_new(0x50);
  local_4 = 0x65;
  if (local_f0 != (void *)0x0) {
    FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 410.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43ba63;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43ba81;
  FUN_00466a10();
  pcVar14 = acStack_68;
  for (iVar8 = 0xc; iVar8 != 0; iVar8 = iVar8 + -1) {
    pcVar14[0] = '\0';
    pcVar14[1] = '\0';
    pcVar14[2] = '\0';
    pcVar14[3] = '\0';
    pcVar14 = pcVar14 + 4;
  }
  pcVar14[0] = '\0';
  pcVar14[1] = '\0';
  iVar8 = 0;
  do {
    cVar1 = (&DAT_005c7464)[iVar8];
    acStack_68[iVar8] = cVar1;
    iVar8 = iVar8 + 1;
  } while (cVar1 != '\0');
  uVar10 = 0xffffffff;
  pcVar14 = &DAT_005dd854;
  do {
    pcVar17 = pcVar14;
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    pcVar17 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar17;
  } while (cVar1 != '\0');
  uVar10 = ~uVar10;
  iVar8 = -1;
  local_10c = (int **)0xff;
  pcVar14 = acStack_68;
  do {
    pcVar16 = pcVar14;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    pcVar16 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar16;
  } while (cVar1 != '\0');
  pcVar14 = pcVar17 + -uVar10;
  pcVar17 = pcVar16 + -1;
  for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar14;
    pcVar14 = pcVar14 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_110 = (int **)0xff;
  local_114 = 0;
  for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar17 = *pcVar14;
    pcVar14 = pcVar14 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_118 = acStack_68;
  ppiStack_11c = (int **)0x43baf9;
  FUN_00466340();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 316.0;
  local_10c = (int **)0x43bb28;
  local_f0 = operator_new(0x74);
  local_4 = 0x66;
  if (local_f0 != (void *)0x0) {
    FUN_00443630();
  }
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x5;
  ppiStack_124 = (int **)0x43bb72;
  FUN_004698c0();
  local_10c = (int **)0x43bb79;
  local_f0 = operator_new(0x6c);
  local_4 = 0x67;
  if (local_f0 == (void *)0x0) {
    local_e4 = (int *)0x0;
  }
  else {
    local_e4 = (int *)FUN_00443a20();
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43bbdf;
  FUN_00462e50();
  local_10c = (int **)0x43bbef;
  FUN_00467950();
  local_10c = (int **)0x43bbfb;
  FUN_00467950();
  local_10c = (int **)0x43bc07;
  FUN_00467950();
  local_10c = (int **)0x43bc13;
  FUN_00467950();
  local_10c = (int **)0x43bc1b;
  FUN_00467950();
  local_10c = (int **)0x43bc23;
  FUN_00469330();
  local_10c = (int **)0x43bc2f;
  FUN_00469760();
  local_10c = (int **)0x43bc3b;
  FUN_00469760();
  local_10c = (int **)0x43bc47;
  FUN_00469760();
  local_10c = (int **)0x43bc4f;
  FUN_00469760();
  local_10c = (int **)0x43bc57;
  FUN_00469760();
  local_10c = (int **)0x43bc60;
  FUN_004438d0();
  local_10c = (int **)0x43bc67;
  local_f0 = operator_new(0x58);
  local_4 = 0x68;
  if (local_f0 != (void *)0x0) {
    FUN_00443e60();
  }
  local_4 = 0xffffffff;
  local_10c = (int **)0x43bc9c;
  local_f0 = operator_new(0x70);
  local_4 = 0x69;
  if (local_f0 == (void *)0x0) {
    local_c8 = 0;
  }
  else {
    local_c8 = FUN_00443d00();
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43bcfc;
  FUN_00462e50();
  local_10c = (int **)0x0;
  local_8c[3] = (undefined4 *)0x41c00000;
  local_8c[2] = (undefined4 *)0x41c00000;
  local_8c[1] = (undefined4 *)0x43930000;
  local_8c[0] = (undefined4 *)0x435e0000;
  ppuVar15 = local_8c;
  pppiVar18 = appiStack_134 + 5;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*ppuVar15;
    ppuVar15 = ppuVar15 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 292.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_10c = (int **)0x43bd8e;
  FUN_0046adf0();
  pcVar14 = acStack_68;
  for (iVar8 = 0xc; iVar8 != 0; iVar8 = iVar8 + -1) {
    pcVar14[0] = '\0';
    pcVar14[1] = '\0';
    pcVar14[2] = '\0';
    pcVar14[3] = '\0';
    pcVar14 = pcVar14 + 4;
  }
  pcVar14[0] = '\0';
  pcVar14[1] = '\0';
  iVar8 = 0;
  do {
    cVar1 = (&DAT_005c746c)[iVar8];
    acStack_68[iVar8] = cVar1;
    iVar8 = iVar8 + 1;
  } while (cVar1 != '\0');
  uVar10 = 0xffffffff;
  pcVar14 = &DAT_005dd854;
  do {
    pcVar17 = pcVar14;
    if (uVar10 == 0) break;
    uVar10 = uVar10 - 1;
    pcVar17 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar17;
  } while (cVar1 != '\0');
  uVar10 = ~uVar10;
  iVar8 = -1;
  pcVar14 = acStack_68;
  do {
    pcVar16 = pcVar14;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    pcVar16 = pcVar14 + 1;
    cVar1 = *pcVar14;
    pcVar14 = pcVar16;
  } while (cVar1 != '\0');
  pcVar14 = pcVar17 + -uVar10;
  pcVar17 = pcVar16 + -1;
  for (uVar11 = uVar10 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar14;
    pcVar14 = pcVar14 + 4;
    pcVar17 = pcVar17 + 4;
  }
  for (uVar10 = uVar10 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
    *pcVar17 = *pcVar14;
    pcVar14 = pcVar14 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_10c = (int **)0x43bdf8;
  FUN_0046b240();
  local_10c = (int **)0x43be04;
  FUN_00443160();
  local_10c = (int **)0x43be0d;
  FUN_00463050();
  local_10c = (int **)0x43be19;
  FUN_00462bf0();
  local_10c = (int **)0x43be20;
  local_f0 = operator_new(0x78);
  local_4 = 0x6a;
  if (local_f0 == (void *)0x0) {
    local_dc = (int *)0x0;
  }
  else {
    local_dc = (int *)FUN_00467160();
  }
  local_10c = (int **)0x0;
  local_110 = (int **)s_mu01500_bmp_005c74b8;
  local_114 = 5;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 354.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 3;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_134[2] = (int **)0x43be9d;
  FUN_00467840();
  local_10c = (int **)0x43bea4;
  local_f0 = operator_new(0x50);
  local_4 = 0x6b;
  if (local_f0 == (void *)0x0) {
    local_f4 = (int *)0x0;
  }
  else {
    local_f4 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 354.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43bf1c;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43bf3a;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c743c;
  ppiStack_11c = (int **)0x43bf57;
  FUN_00466340();
  local_10c = (int **)0x43bf5e;
  local_f0 = operator_new(0x50);
  local_4 = 0x6c;
  if (local_f0 == (void *)0x0) {
    local_ec = (int *)0x0;
  }
  else {
    local_ec = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 378.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43bfd6;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43bff4;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c7434;
  ppiStack_11c = (int **)0x43c011;
  FUN_00466340();
  local_10c = (int **)0x43c018;
  local_f0 = operator_new(0x50);
  local_4 = 0x6d;
  if (local_f0 == (void *)0x0) {
    local_e8 = 0;
  }
  else {
    local_e8 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 402.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43c090;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43c0ae;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c742c;
  ppiStack_11c = (int **)0x43c0cb;
  FUN_00466340();
  local_10c = (int **)0x43c0d2;
  local_f0 = operator_new(0x50);
  local_4 = 0x6e;
  if (local_f0 == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 426.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43c14a;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43c168;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c7424;
  ppiStack_11c = (int **)0x43c185;
  FUN_00466340();
  local_10c = (int **)0x43c18c;
  local_f0 = operator_new(0x50);
  local_4 = 0x6f;
  if (local_f0 == (void *)0x0) {
    local_e4 = (int *)0x0;
  }
  else {
    local_e4 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 450.0;
  ppiStack_120 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_124 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_134[3] = (int **)0x43c204;
  FUN_00466720();
  local_10c = (int **)0x0;
  local_110 = (int **)0x0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 4;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_134[3] = (int **)0x43c222;
  FUN_00466a10();
  local_10c = (int **)0xff;
  local_110 = (int **)0xff;
  local_114 = 0;
  local_118 = &DAT_005c741c;
  ppiStack_11c = (int **)0x43c23f;
  FUN_00466340();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 356.0;
  local_10c = (int **)0x43c26e;
  local_f0 = operator_new(0x74);
  local_4 = 0x70;
  if (local_f0 != (void *)0x0) {
    FUN_00443630();
  }
  local_4 = 0xffffffff;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134 + 6;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_120 = (int **)0x5;
  ppiStack_124 = (int **)0x43c2b8;
  FUN_004698c0();
  local_10c = (int **)0x43c2bf;
  local_f0 = operator_new(0x6c);
  local_4 = 0x71;
  if (local_f0 == (void *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00443a20();
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43c31f;
  FUN_00462e50();
  local_10c = (int **)0x43c32b;
  FUN_00467950();
  local_10c = (int **)0x43c337;
  FUN_00467950();
  local_10c = (int **)0x43c343;
  FUN_00467950();
  local_10c = (int **)0x43c34f;
  FUN_00467950();
  local_10c = (int **)0x43c35b;
  FUN_00467950();
  local_10c = (int **)0x43c363;
  FUN_00469330();
  local_10c = (int **)0x43c36f;
  FUN_00469760();
  local_10c = (int **)0x43c37b;
  FUN_00469760();
  local_10c = (int **)0x43c387;
  FUN_00469760();
  local_10c = (int **)0x43c38f;
  FUN_00469760();
  local_10c = (int **)0x43c397;
  FUN_00469760();
  local_10c = (int **)0x43c3a0;
  FUN_004438d0();
  local_10c = (int **)0x43c3a7;
  local_f0 = operator_new(0x58);
  local_4 = 0x72;
  if (local_f0 != (void *)0x0) {
    FUN_00443e60();
  }
  local_4 = 0xffffffff;
  local_10c = (int **)0x43c3dc;
  local_f0 = operator_new(0x70);
  local_4 = 0x73;
  if (local_f0 != (void *)0x0) {
    FUN_00443d00();
  }
  local_4 = 0xffffffff;
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43c438;
  FUN_00462e50();
  local_10c = (int **)0x0;
  local_8c[3] = (undefined4 *)0x41c00000;
  local_8c[2] = (undefined4 *)0x41c00000;
  local_8c[1] = (undefined4 *)0x43a70000;
  local_8c[0] = (undefined4 *)0x435e0000;
  ppuVar15 = local_8c;
  pppiVar18 = appiStack_134 + 5;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*ppuVar15;
    ppuVar15 = ppuVar15 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 332.0;
  puVar4 = &DAT_005ddd68;
  pppiVar18 = appiStack_134;
  for (iVar8 = 5; iVar8 != 0; iVar8 = iVar8 + -1) {
    *pppiVar18 = (int **)*puVar4;
    puVar4 = puVar4 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_10c = (int **)0x43c4ca;
  FUN_0046adf0();
  local_10c = (int **)0x43c4d6;
  FUN_0046b240();
  local_10c = (int **)0x43c4e2;
  FUN_00443160();
  local_10c = (int **)0x43c4eb;
  FUN_00463050();
  local_10c = (int **)0x43c4f7;
  FUN_00462bf0();
  local_118 = DAT_005dbb70;
  local_114 = DAT_005dbb74;
  local_110 = DAT_005dbb78;
  local_10c = (int **)DAT_005dbb7c;
  ppiStack_11c = (int **)0x43c537;
  FUN_00462e50();
  local_10c = (int **)0x43c54a;
  FUN_00462bf0();
  local_10c = (int **)0x43c55d;
  FUN_00462bf0();
  local_10c = (int **)0x43c570;
  FUN_00462bf0();
  local_10c = (int **)0x43c580;
  FUN_00462bf0();
  local_10c = (int **)0x43c590;
  FUN_00462bf0();
  local_10c = (int **)0x43c5a0;
  FUN_00462bf0();
  local_10c = (int **)0x43c5b0;
  FUN_00462bf0();
  local_10c = (int **)0x43c5c0;
  FUN_00462bf0();
  local_10c = (int **)0x43c5d0;
  FUN_00462bf0();
  local_10c = (int **)0x43c5e0;
  FUN_00462bf0();
  local_10c = (int **)0x43c5f0;
  FUN_00462bf0();
  local_10c = (int **)0x43c600;
  FUN_00462bf0();
  local_10c = (int **)0x43c610;
  FUN_00462bf0();
  local_10c = (int **)0x43c620;
  FUN_00462bf0();
  local_10c = (int **)0x43c630;
  FUN_00462bf0();
  local_10c = (int **)0x43c640;
  FUN_00462bf0();
  local_10c = (int **)0x43c650;
  FUN_00462bf0();
  local_10c = (int **)0x43c65c;
  FUN_00462bf0();
  local_10c = (int **)0x43c669;
  (**(code **)(**(int **)(local_94 + 0x284) + 0x58))();
  local_10c = *(int ***)(local_94 + 0x284);
  local_110 = (int **)0x43c67b;
  FUN_00461e50();
  local_10c = *(int ***)(local_94 + 0x2a0);
  local_110 = (int **)0x43c689;
  FUN_00570fc0();
  local_10c = *(int ***)(local_94 + 0x280);
  local_110 = (int **)0x43c697;
  FUN_00570fc0();
  ExceptionList = pvStack_10;
  return 1;
}

