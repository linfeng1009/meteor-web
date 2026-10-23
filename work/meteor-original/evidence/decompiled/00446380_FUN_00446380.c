/* Meteor.exe original x86 @ 00446380 */
/* Caller: 00435bbd */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00446380(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  int *piVar7;
  undefined4 *puVar8;
  void *pvVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  undefined4 *puVar13;
  int *piVar14;
  char *pcVar15;
  char *pcVar16;
  char *pcVar17;
  int ***pppiVar18;
  int **appiStack_120 [4];
  int **ppiStack_110;
  int **ppiStack_10c;
  int **ppiStack_108;
  char *local_104;
  int local_100;
  int **local_fc;
  int **local_f8;
  int *local_e0;
  int *local_dc;
  int *local_d8;
  void *local_d4;
  int *local_d0;
  int *local_cc;
  int *local_c8;
  int *local_c4;
  undefined4 *local_c0;
  int local_bc;
  int *local_b8;
  undefined4 local_b4;
  undefined4 *local_b0;
  int local_ac;
  undefined4 *local_a8;
  undefined4 *local_a4;
  undefined4 *local_a0;
  int local_9c;
  undefined4 *local_98;
  undefined4 *local_94;
  undefined4 *local_90;
  undefined4 *local_8c;
  undefined4 *local_88;
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 *local_78;
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
  puStack_8 = &LAB_0059bdcc;
  pvStack_c = ExceptionList;
  local_f8 = (int **)0x4463aa;
  ExceptionList = &pvStack_c;
  local_6c = operator_new(0x6c);
  local_4 = 0;
  local_88 = local_6c;
  if (local_6c == (undefined4 *)0x0) {
    local_6c = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *local_6c = &PTR_FUN_005a8580;
  }
  local_4 = 0xffffffff;
  local_6c[1] = s_Con_Forward_005c7354;
  local_f8 = (int **)0x4463f2;
  puVar5 = operator_new(0xc);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    *puVar5 = &PTR_FUN_005a8528;
  }
  local_f8 = (int **)0x446414;
  FUN_00463cb0();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x446444;
  FUN_00462e50();
  local_f8 = (int **)0x44644d;
  FUN_00463050();
  local_f8 = (int **)0x446454;
  local_74 = operator_new(0x6c);
  local_4 = 1;
  local_88 = local_74;
  if (local_74 == (undefined4 *)0x0) {
    local_74 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *local_74 = &PTR_FUN_005a8580;
  }
  local_4 = 0xffffffff;
  local_74[1] = s_Con_Forward_005c7354;
  local_f8 = (int **)0x446499;
  puVar5 = operator_new(0xc);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    *puVar5 = &PTR_FUN_005a8528;
  }
  local_f8 = (int **)0x4464bb;
  FUN_00463cb0();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x4464eb;
  FUN_00462e50();
  local_f8 = (int **)0x4464f4;
  FUN_00463050();
  DAT_005dbb74 = 0;
  local_f8 = (int **)0x446501;
  local_70 = operator_new(0x6c);
  local_4 = 2;
  local_88 = local_70;
  if (local_70 == (undefined4 *)0x0) {
    local_70 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *local_70 = &PTR_FUN_005a8580;
  }
  local_4 = 0xffffffff;
  local_70[1] = &DAT_005c73d8;
  local_f8 = (int **)0x446549;
  puVar5 = operator_new(0xc);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    *puVar5 = &PTR_FUN_005a8528;
  }
  local_f8 = (int **)0x44656b;
  FUN_00463cb0();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44659b;
  FUN_00462e50();
  local_f8 = (int **)0x4465a2;
  local_78 = operator_new(0xc);
  if (local_78 == (undefined4 *)0x0) {
    local_78 = (undefined4 *)0x0;
  }
  else {
    local_78[1] = 0;
    *local_78 = &PTR_FUN_005a84d0;
    local_78[2] = 0;
  }
  local_f8 = (int **)0x4465c9;
  FUN_0046a510();
  local_f8 = (int **)0x4465d0;
  puVar5 = operator_new(0x6c);
  local_4 = 3;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    local_88 = puVar5;
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8868;
  }
  local_4 = 0xffffffff;
  local_f8 = (int **)0x44660b;
  local_88 = puVar5;
  local_b0 = operator_new(0x78);
  local_4 = 4;
  if (local_b0 != (void *)0x0) {
    FUN_00467160();
  }
  DAT_005dbb74 = 0;
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = 0;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x446669;
  FUN_00462e50();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  local_100 = 7;
  DAT_005ddd68 = 0x430f0000;
  DAT_005ddd6c = 82.0;
  _DAT_005ddd70 = 0x43f00000;
  _DAT_005ddd74 = 0x438c0000;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[2] = (int **)0x4466ae;
  FUN_00467840();
  local_f8 = (int **)0x4466b5;
  local_b0 = operator_new(0x50);
  local_4 = 5;
  if (local_b0 == (void *)0x0) {
    local_b0 = (undefined4 *)0x0;
  }
  else {
    local_b0 = (undefined4 *)FUN_00465610();
  }
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x0;
  ppiStack_110 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x446705;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 91.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44674b;
  FUN_00466a10();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 91.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446791;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dd270;
  ppiStack_108 = (int **)0x4467ae;
  FUN_00466340();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 1;
  local_104 = (char *)&DAT_005ddc30;
  ppiStack_108 = (int **)0x4467cb;
  FUN_00466340();
  local_f8 = (int **)0x4467d2;
  local_e0 = operator_new(0x50);
  local_4 = 6;
  if (local_e0 == (int *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x0;
  ppiStack_110 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x446822;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 131.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446868;
  FUN_00466a10();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 131.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x4468ae;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dd8bc;
  ppiStack_108 = (int **)0x4468cb;
  FUN_00466340();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 1;
  local_104 = (char *)&DAT_005dd23c;
  ppiStack_108 = (int **)0x4468e8;
  FUN_00466340();
  local_f8 = (int **)0x4468ef;
  local_d8 = operator_new(0x50);
  local_4 = 7;
  if (local_d8 == (int *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00465610();
  }
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x0;
  ppiStack_110 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44693f;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 171.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446985;
  FUN_00466a10();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 171.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x4469cb;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005e00b0;
  ppiStack_108 = (int **)0x4469e8;
  FUN_00466340();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 1;
  local_104 = (char *)&DAT_005de4d0;
  ppiStack_108 = (int **)0x446a05;
  FUN_00466340();
  local_f8 = (int **)0x446a0c;
  local_d4 = operator_new(0x50);
  local_4 = 8;
  if (local_d4 == (void *)0x0) {
    local_d4 = (void *)0x0;
  }
  else {
    local_d4 = (void *)FUN_00465610();
  }
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x0;
  ppiStack_110 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x446a5c;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 211.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446aa2;
  FUN_00466a10();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 211.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446ae8;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dd680;
  ppiStack_108 = (int **)0x446b05;
  FUN_00466340();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 1;
  local_104 = (char *)&DAT_005ddb94;
  ppiStack_108 = (int **)0x446b22;
  FUN_00466340();
  local_f8 = (int **)0x446b29;
  local_cc = operator_new(0x50);
  local_4 = 9;
  if (local_cc == (int *)0x0) {
    local_cc = (int *)0x0;
  }
  else {
    local_cc = (int *)FUN_00465610();
  }
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x0;
  ppiStack_110 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x446b79;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 251.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446bbf;
  FUN_00466a10();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 251.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446c05;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dd340;
  ppiStack_108 = (int **)0x446c22;
  FUN_00466340();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 1;
  local_104 = (char *)&DAT_005dd924;
  ppiStack_108 = (int **)0x446c3f;
  FUN_00466340();
  local_f8 = (int **)0x446c46;
  local_d0 = operator_new(0x50);
  local_4 = 10;
  if (local_d0 == (int *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_00465610();
  }
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x0;
  ppiStack_110 = (int **)0x2;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x446c96;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 291.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446cdc;
  FUN_00466a10();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x1;
  _DAT_005ddd70 = 0x42f00000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x438e8000;
  DAT_005ddd6c = 291.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446d22;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dd98c;
  ppiStack_108 = (int **)0x446d3f;
  FUN_00466340();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 1;
  local_104 = (char *)&DAT_005dd548;
  ppiStack_108 = (int **)0x446d5c;
  FUN_00466340();
  local_f8 = (int **)0x446d63;
  local_c8 = operator_new(0x50);
  local_4 = 0xb;
  if (local_c8 != (int *)0x0) {
    FUN_00465610();
  }
  local_4 = 0xffffffff;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x0;
  ppiStack_110 = (int **)0x1;
  appiStack_120[3] = (int **)0x446daf;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x43780000;
  _DAT_005ddd74 = 0x41e00000;
  DAT_005ddd68 = 0x41d80000;
  DAT_005ddd6c = 331.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x446df5;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dd4ac;
  ppiStack_108 = (int **)0x446e12;
  FUN_00466340();
  local_f8 = (int **)0x446e1e;
  FUN_00467950();
  local_f8 = (int **)0x446e2a;
  FUN_00467950();
  local_f8 = (int **)0x446e36;
  FUN_00467950();
  local_f8 = (int **)0x446e42;
  FUN_00467950();
  local_f8 = (int **)0x446e4e;
  FUN_00467950();
  local_f8 = (int **)0x446e5a;
  FUN_00467950();
  local_f8 = (int **)0x446e62;
  FUN_00467950();
  local_f8 = (int **)0x446e69;
  puVar5 = operator_new(0x6c);
  local_4 = 0xc;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    local_b0 = puVar5;
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8868;
  }
  local_4 = 0xffffffff;
  local_f8 = (int **)0x446ea7;
  local_b0 = puVar5;
  local_e0 = operator_new(0x78);
  local_4 = 0xd;
  if (local_e0 == (int *)0x0) {
    uVar6 = 0;
  }
  else {
    uVar6 = FUN_00467160();
  }
  DAT_005dbb74 = 1;
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = 1;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x446f04;
  FUN_00462e50();
  local_f8 = (int **)0x0;
  local_fc = (int **)s_MU00500_BMP_005c7524;
  local_100 = 10;
  DAT_005ddd68 = 0x43d38000;
  DAT_005ddd6c = 77.0;
  _DAT_005ddd70 = 0x43480000;
  _DAT_005ddd74 = 0x438f0000;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[2] = (int **)0x446f4f;
  FUN_00467840();
  *(undefined4 *)(local_84 + 0x278) = uVar6;
  local_f8 = (int **)0x446f60;
  local_e0 = operator_new(0x50);
  local_4 = 0xe;
  if (local_e0 == (int *)0x0) {
    local_bc = 0;
  }
  else {
    local_bc = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 111.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x446fda;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 111.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447024;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de22c;
  ppiStack_108 = (int **)0x447041;
  FUN_00466340();
  local_f8 = (int **)0x447048;
  local_e0 = operator_new(0x50);
  local_4 = 0xf;
  if (local_e0 == (int *)0x0) {
    local_7c = 0;
  }
  else {
    local_7c = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 135.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x4470c5;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 135.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447112;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de2c8;
  ppiStack_108 = (int **)0x44712f;
  FUN_00466340();
  local_f8 = (int **)0x447136;
  local_e0 = operator_new(0x50);
  local_4 = 0x10;
  if (local_e0 == (int *)0x0) {
    local_80 = 0;
  }
  else {
    local_80 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 159.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x4471b3;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 159.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447200;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de2fc;
  ppiStack_108 = (int **)0x44721d;
  FUN_00466340();
  local_f8 = (int **)0x447224;
  local_e0 = operator_new(0x50);
  local_4 = 0x11;
  if (local_e0 == (int *)0x0) {
    local_a8 = (undefined4 *)0x0;
  }
  else {
    local_a8 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 183.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44729e;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 183.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x4472e8;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de260;
  ppiStack_108 = (int **)0x447305;
  FUN_00466340();
  local_f8 = (int **)0x44730c;
  local_e0 = operator_new(0x50);
  local_4 = 0x12;
  if (local_e0 == (int *)0x0) {
    local_a0 = (undefined4 *)0x0;
  }
  else {
    local_a0 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 207.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447386;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 207.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x4473d0;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de294;
  ppiStack_108 = (int **)0x4473ed;
  FUN_00466340();
  local_f8 = (int **)0x4473f4;
  local_e0 = operator_new(0x50);
  local_4 = 0x13;
  if (local_e0 == (int *)0x0) {
    local_98 = (undefined4 *)0x0;
  }
  else {
    local_98 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 231.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44746e;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 231.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x4474b8;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de398;
  ppiStack_108 = (int **)0x4474d5;
  FUN_00466340();
  local_f8 = (int **)0x4474dc;
  local_e0 = operator_new(0x50);
  local_4 = 0x14;
  if (local_e0 == (int *)0x0) {
    local_a4 = (undefined4 *)0x0;
  }
  else {
    local_a4 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 255.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447556;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 255.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x4475a0;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de3cc;
  ppiStack_108 = (int **)0x4475bd;
  FUN_00466340();
  local_f8 = (int **)0x4475c4;
  local_e0 = operator_new(0x50);
  local_4 = 0x15;
  if (local_e0 == (int *)0x0) {
    local_8c = (undefined4 *)0x0;
  }
  else {
    local_8c = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 279.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447641;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 279.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44768e;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de330;
  ppiStack_108 = (int **)0x4476ab;
  FUN_00466340();
  local_f8 = (int **)0x4476b2;
  local_e0 = operator_new(0x50);
  local_4 = 0x16;
  if (local_e0 == (int *)0x0) {
    local_90 = (undefined4 *)0x0;
  }
  else {
    local_90 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 303.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44772c;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 303.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447779;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005de364;
  ppiStack_108 = (int **)0x447796;
  FUN_00466340();
  local_f8 = (int **)0x44779d;
  local_e0 = operator_new(0x50);
  local_4 = 0x17;
  if (local_e0 == (int *)0x0) {
    local_94 = (undefined4 *)0x0;
  }
  else {
    local_94 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 327.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447817;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 327.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447861;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005db99c;
  ppiStack_108 = (int **)0x44787e;
  FUN_00466340();
  local_f8 = (int **)0x447885;
  local_e0 = operator_new(0x50);
  local_4 = 0x18;
  if (local_e0 == (int *)0x0) {
    local_ac = 0;
  }
  else {
    local_ac = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 351.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x4478ff;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 351.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447949;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005db900;
  ppiStack_108 = (int **)0x447966;
  FUN_00466340();
  local_f8 = (int **)0x44796d;
  local_e0 = operator_new(0x50);
  local_4 = 0x19;
  if (local_e0 == (int *)0x0) {
    local_9c = 0;
  }
  else {
    local_9c = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 375.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x4479e7;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 375.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447a31;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005db934;
  ppiStack_108 = (int **)0x447a4e;
  FUN_00466340();
  local_f8 = (int **)0x447a55;
  local_e0 = operator_new(0x50);
  local_4 = 0x1a;
  if (local_e0 == (int *)0x0) {
    local_b4 = 0;
  }
  else {
    local_b4 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 399.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447acf;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 399.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447b19;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005dba6c;
  ppiStack_108 = (int **)0x447b36;
  FUN_00466340();
  local_f8 = (int **)0x447b3d;
  local_e0 = operator_new(0x50);
  local_4 = 0x1b;
  if (local_e0 == (int *)0x0) {
    local_c0 = (undefined4 *)0x0;
  }
  else {
    local_c0 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 423.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447bb7;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 423.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447c01;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005dbad4;
  ppiStack_108 = (int **)0x447c1e;
  FUN_00466340();
  local_f8 = (int **)0x447c25;
  local_e0 = operator_new(0x50);
  local_4 = 0x1c;
  if (local_e0 == (int *)0x0) {
    local_b8 = (int *)0x0;
  }
  else {
    local_b8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 447.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447c9f;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 447.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447ce9;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005dba04;
  ppiStack_108 = (int **)0x447d06;
  FUN_00466340();
  local_f8 = (int **)0x447d0d;
  local_e0 = operator_new(0x50);
  local_4 = 0x1d;
  if (local_e0 == (int *)0x0) {
    local_c4 = (int *)0x0;
  }
  else {
    local_c4 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 471.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447d87;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 471.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447dd1;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dba38;
  ppiStack_108 = (int **)0x447dee;
  FUN_00466340();
  local_f8 = (int **)0x447df5;
  local_e0 = operator_new(0x50);
  local_4 = 0x1e;
  if (local_e0 == (int *)0x0) {
    local_c8 = (int *)0x0;
  }
  else {
    local_c8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 495.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447e6f;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 495.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447eb9;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dbc1c;
  ppiStack_108 = (int **)0x447ed6;
  FUN_00466340();
  local_f8 = (int **)0x447edd;
  local_e0 = operator_new(0x50);
  local_4 = 0x1f;
  if (local_e0 == (int *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 519.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x447f57;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 519.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x447fa1;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dbc50;
  ppiStack_108 = (int **)0x447fbe;
  FUN_00466340();
  local_f8 = (int **)0x447fc5;
  local_e0 = operator_new(0x50);
  local_4 = 0x20;
  if (local_e0 == (int *)0x0) {
    local_cc = (int *)0x0;
  }
  else {
    local_cc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 543.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44803f;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 543.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x448089;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dbbe8;
  ppiStack_108 = (int **)0x4480a6;
  FUN_00466340();
  local_f8 = (int **)0x4480ad;
  local_e0 = operator_new(0x50);
  local_4 = 0x21;
  if (local_e0 == (int *)0x0) {
    local_d4 = (void *)0x0;
  }
  else {
    local_d4 = (void *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x432c0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43d88000;
  DAT_005ddd6c = 567.0;
  ppiStack_10c = (int **)0x1;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x448127;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 567.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x448171;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = (char *)&DAT_005dbaa0;
  ppiStack_108 = (int **)0x44818e;
  FUN_00466340();
  local_f8 = (int **)0x448195;
  piVar7 = operator_new(0x34);
  local_e0 = piVar7;
  if (piVar7 == (int *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    *piVar7 = (int)&PTR_LAB_005a8810;
    piVar7[1] = 0;
    piVar14 = piVar7 + 9;
    piVar7[3] = 0;
    piVar7[4] = 0;
    piVar7[5] = 0;
    piVar7[6] = 0;
    piVar7[7] = 0x3f800000;
    local_4._0_1_ = 0x23;
    local_4._1_3_ = 0;
    *piVar14 = 0;
    piVar7[10] = 0;
    piVar7[0xb] = 0;
    local_f8 = (int **)0x4481e9;
    local_d8 = piVar14;
    iVar10 = FUN_00402bf0();
    *piVar14 = iVar10;
    piVar7[10] = iVar10;
    piVar7[0xb] = iVar10 + 8;
    local_4 = CONCAT31(local_4._1_3_,0x26);
    FUN_00402a70();
    *piVar7 = (int)&PTR_FUN_005a8700;
    local_d8 = piVar7;
  }
  local_f8 = (int **)0x0;
  _DAT_005ddd70 = 0x430e0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43e00000;
  DAT_005ddd6c = 87.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 5;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  ppiStack_110 = (int **)0x448267;
  FUN_004636d0();
  local_f8 = (int **)0x448275;
  FUN_00463b30();
  _DAT_005ddd70 = 0x41000000;
  _DAT_005ddd74 = 0x436d0000;
  DAT_005ddd68 = 0x44174000;
  DAT_005ddd6c = 111.0;
  local_f8 = (int **)0x4482a4;
  puVar5 = operator_new(0x74);
  local_4 = 0x27;
  local_dc = puVar5;
  if (puVar5 != (undefined4 *)0x0) {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0;
    puVar5[8] = 0x3f800000;
    FUN_00402330();
    local_4._0_1_ = 0x29;
    if (DAT_005d59ac == (undefined4 *)0x0) {
      local_e0 = (int *)0x14;
      local_f8 = (int **)0x10;
      local_fc = (int **)0x44830d;
      puVar8 = (undefined4 *)FUN_004036c0();
      if (local_e0 != (int *)0x1) {
        puVar13 = puVar8 + 4;
        iVar10 = 1;
        puVar4 = puVar13;
        DAT_005d59ac = puVar13;
        if (local_e0 != (int *)0x2) {
          do {
            puVar13 = puVar4 + 4;
            *puVar4 = puVar13;
            iVar10 = iVar10 + 1;
            puVar4 = puVar13;
          } while ((int)local_e0 + -1 != iVar10);
        }
        *puVar13 = 0;
      }
    }
    else {
      puVar8 = DAT_005d59ac;
      DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
    }
    DAT_005d59e8 = 0;
    puVar5[0xb] = puVar8;
    *puVar8 = puVar8;
    *(undefined4 *)(puVar5[0xb] + 4) = puVar5[0xb];
    local_4 = CONCAT31(local_4._1_3_,0x2a);
    local_f8 = (int **)0x448379;
    FUN_00469e30();
    *puVar5 = &PTR_FUN_005a87b8;
  }
  local_4 = 0xffffffff;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0xa;
  ppiStack_110 = (int **)0x4483ac;
  FUN_004698c0();
  local_f8 = (int **)0x4483b3;
  puVar5 = operator_new(0x6c);
  local_4 = 0x2b;
  local_dc = puVar5;
  if (puVar5 != (undefined4 *)0x0) {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8758;
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448417;
  FUN_00462e50();
  local_f8 = (int **)0x448423;
  FUN_00467950();
  local_f8 = (int **)0x44842f;
  FUN_00467950();
  local_f8 = (int **)0x44843b;
  FUN_00467950();
  local_f8 = (int **)0x448447;
  FUN_00467950();
  local_f8 = (int **)0x448453;
  FUN_00467950();
  local_f8 = (int **)0x44845f;
  FUN_00467950();
  local_f8 = (int **)0x44846b;
  FUN_00467950();
  local_f8 = (int **)0x448477;
  FUN_00467950();
  local_f8 = (int **)0x448483;
  FUN_00467950();
  local_f8 = (int **)0x44848f;
  FUN_00467950();
  local_f8 = (int **)0x44849b;
  FUN_00467950();
  local_f8 = (int **)0x4484a7;
  FUN_00467950();
  local_f8 = (int **)0x4484b3;
  FUN_00467950();
  local_f8 = (int **)0x4484bf;
  FUN_00467950();
  local_f8 = (int **)0x4484cb;
  FUN_00467950();
  local_f8 = (int **)0x4484d7;
  FUN_00467950();
  local_f8 = (int **)0x4484e3;
  FUN_00467950();
  local_f8 = (int **)0x4484ef;
  FUN_00467950();
  local_f8 = (int **)0x4484fb;
  FUN_00467950();
  local_f8 = (int **)0x448507;
  FUN_00467950();
  local_f8 = (int **)0x448510;
  FUN_00465f10();
  local_f8 = (int **)local_d8;
  local_fc = (int **)0x44851e;
  FUN_00467c50();
  local_f8 = (int **)0x448526;
  FUN_00469330();
  local_f8 = (int **)0x448532;
  FUN_00469760();
  local_f8 = (int **)0x44853e;
  FUN_00469760();
  local_f8 = (int **)0x44854a;
  FUN_00469760();
  local_f8 = (int **)0x448556;
  FUN_00469760();
  local_f8 = (int **)0x448562;
  FUN_00469760();
  local_f8 = (int **)0x44856e;
  FUN_00469760();
  local_f8 = (int **)0x44857a;
  FUN_00469760();
  local_f8 = (int **)0x448586;
  FUN_00469760();
  local_f8 = (int **)0x448592;
  FUN_00469760();
  local_f8 = (int **)0x44859e;
  FUN_00469760();
  local_f8 = (int **)0x4485aa;
  FUN_00469760();
  local_f8 = (int **)0x4485b6;
  FUN_00469760();
  local_f8 = (int **)0x4485c2;
  FUN_00469760();
  local_f8 = (int **)0x4485ce;
  FUN_00469760();
  local_f8 = (int **)0x4485da;
  FUN_00469760();
  local_f8 = (int **)0x4485e6;
  FUN_00469760();
  local_f8 = (int **)0x4485f2;
  FUN_00469760();
  local_f8 = (int **)0x4485fe;
  FUN_00469760();
  local_f8 = (int **)0x44860a;
  FUN_00469760();
  local_f8 = (int **)0x448612;
  FUN_00469760();
  puVar5 = local_b0;
  local_f8 = (int **)0x44861e;
  FUN_00462bf0();
  puVar5[1] = s_map_name_005c7530;
  local_f8 = (int **)0x44862e;
  FUN_00463050();
  local_f8 = (int **)0x448635;
  local_dc = operator_new(0x7c);
  local_4 = 0x2c;
  if (local_dc != (void *)0x0) {
    FUN_00463fb0();
  }
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  local_100 = 0;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41900000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 96.0;
  local_4 = 0xffffffff;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[2] = (int **)0x4486a9;
  FUN_004642f0();
  local_f8 = (int **)0x4486b0;
  local_dc = operator_new(0x6c);
  local_4 = 0x2d;
  if (local_dc == (void *)0x0) {
    local_9c = 0;
  }
  else {
    local_9c = FUN_00462d50();
  }
  local_4 = 0xffffffff;
  *(char **)(local_9c + 4) = s_game_name_005c7518;
  local_f8 = (int **)0x4486f2;
  FUN_00463050();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448722;
  FUN_00462e50();
  local_f8 = (int **)0x448733;
  FUN_00464240();
  local_f8 = (int **)0x44873a;
  local_dc = operator_new(0x7c);
  local_4 = 0x2e;
  if (local_dc != (void *)0x0) {
    FUN_00463fb0();
  }
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  local_100 = 0;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41900000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 136.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_120[2] = (int **)0x4487ac;
  FUN_004642f0();
  local_f8 = (int **)0x4487b3;
  local_dc = operator_new(0x6c);
  local_4 = 0x2f;
  if (local_dc == (void *)0x0) {
    local_ac = 0;
  }
  else {
    local_ac = FUN_00462d50();
  }
  local_4 = 0xffffffff;
  *(char **)(local_ac + 4) = s_password_005c4218;
  local_f8 = (int **)0x4487f5;
  FUN_00463050();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448823;
  FUN_00462e50();
  local_f8 = (int **)0x44882a;
  puVar5 = operator_new(0x24);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    *puVar5 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 93.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x448898;
  FUN_0046a670();
  local_f8 = (int **)0x44889f;
  puVar5 = operator_new(0x6c);
  local_4 = 0x30;
  local_dc = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    local_94 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8980;
    local_94 = puVar5;
  }
  local_4 = 0xffffffff;
  local_94[1] = s_hideitem_005c7500;
  local_f8 = (int **)0x4488e7;
  FUN_00463050();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448915;
  FUN_00462e50();
  local_f8 = (int **)0x44891c;
  puVar5 = operator_new(0x24);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    *puVar5 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 133.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x44898a;
  FUN_0046a670();
  local_f8 = (int **)0x448991;
  puVar5 = operator_new(0x6c);
  local_4 = 0x31;
  local_dc = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    local_90 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8980;
    local_90 = puVar5;
  }
  local_4 = 0xffffffff;
  local_90[1] = s_friendfire_005c74f4;
  local_f8 = (int **)0x4489d9;
  FUN_00463050();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448a07;
  FUN_00462e50();
  local_f8 = (int **)0x448a0e;
  puVar5 = operator_new(0x24);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    *puVar5 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 173.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x448a7c;
  FUN_0046a670();
  local_f8 = (int **)0x448a83;
  puVar5 = operator_new(0x6c);
  local_4 = 0x32;
  local_dc = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    local_8c = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8980;
    local_8c = puVar5;
  }
  local_4 = 0xffffffff;
  local_8c[1] = s_autoswitch_005c74e8;
  local_f8 = (int **)0x448acb;
  FUN_00463050();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448af9;
  FUN_00462e50();
  local_f8 = (int **)0x448b00;
  puVar5 = operator_new(0x24);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    *puVar5 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 213.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x448b6e;
  FUN_0046a670();
  local_f8 = (int **)0x448b75;
  puVar5 = operator_new(0x6c);
  local_4 = 0x33;
  local_dc = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    local_a4 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8980;
    local_a4 = puVar5;
  }
  local_4 = 0xffffffff;
  local_a4[1] = s_healthitem_005c74dc;
  local_f8 = (int **)0x448bbd;
  FUN_00463050();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448beb;
  FUN_00462e50();
  local_f8 = (int **)0x448bf2;
  puVar5 = operator_new(0x24);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    *puVar5 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 253.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x448c60;
  FUN_0046a670();
  local_f8 = (int **)0x448c67;
  puVar5 = operator_new(0x6c);
  local_4 = 0x34;
  local_dc = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    local_98 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8980;
    local_98 = puVar5;
  }
  local_4 = 0xffffffff;
  local_98[1] = s_updateitem_005c74d0;
  local_f8 = (int **)0x448caf;
  FUN_00463050();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448cdd;
  FUN_00462e50();
  local_f8 = (int **)0x448ce4;
  puVar5 = operator_new(0x24);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    puVar5[3] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0x3f800000;
    *puVar5 = &PTR_FUN_005a89e0;
  }
  _DAT_005ddd70 = 0x41c00000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x43bb0000;
  DAT_005ddd6c = 293.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x448d52;
  FUN_0046a670();
  local_f8 = (int **)0x448d59;
  puVar5 = operator_new(0x6c);
  local_4 = 0x35;
  local_dc = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    local_a0 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8980;
    local_a0 = puVar5;
  }
  local_4 = 0xffffffff;
  local_a0[1] = s_specialitem_005c74c4;
  local_f8 = (int **)0x448da0;
  FUN_00463050();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x448dce;
  FUN_00462e50();
  local_f8 = (int **)0x448dd5;
  local_dc = operator_new(0x78);
  local_4 = 0x36;
  if (local_dc == (void *)0x0) {
    local_c4 = (int *)0x0;
  }
  else {
    local_c4 = (int *)FUN_00467160();
  }
  local_f8 = (int **)0x0;
  local_fc = (int **)s_mu01500_bmp_005c74b8;
  local_100 = 5;
  local_4 = 0xffffffff;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 194.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[2] = (int **)0x448e4a;
  FUN_00467840();
  local_f8 = (int **)0x448e51;
  local_dc = operator_new(0x50);
  local_4 = 0x37;
  if (local_dc == (void *)0x0) {
    local_d4 = (void *)0x0;
  }
  else {
    local_d4 = (void *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 194.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x448ec7;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x448ee2;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005dda90;
  ppiStack_108 = (int **)0x448efe;
  FUN_00466340();
  local_f8 = (int **)0x448f05;
  local_dc = operator_new(0x50);
  local_4 = 0x38;
  if (local_dc == (void *)0x0) {
    local_cc = (int *)0x0;
  }
  else {
    local_cc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 218.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x448f7b;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x448f96;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005ddac4;
  ppiStack_108 = (int **)0x448fb2;
  FUN_00466340();
  local_f8 = (int **)0x448fb9;
  local_dc = operator_new(0x50);
  local_4 = 0x39;
  if (local_dc == (void *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 242.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44902f;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44904a;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005dda28;
  ppiStack_108 = (int **)0x449066;
  FUN_00466340();
  local_f8 = (int **)0x44906d;
  local_dc = operator_new(0x50);
  local_4 = 0x3a;
  if (local_dc == (void *)0x0) {
    local_c8 = (int *)0x0;
  }
  else {
    local_c8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 266.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x4490e3;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x4490fe;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005dda5c;
  ppiStack_108 = (int **)0x44911a;
  FUN_00466340();
  local_f8 = (int **)0x449121;
  local_dc = operator_new(0x50);
  local_4 = 0x3b;
  if (local_dc == (void *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 290.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x0;
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44919b;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x4491b6;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005ddaf8;
  ppiStack_108 = (int **)0x4491d2;
  FUN_00466340();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 196.0;
  local_f8 = (int **)0x449201;
  puVar5 = operator_new(0x74);
  local_4 = 0x3c;
  local_dc = puVar5;
  if (puVar5 != (undefined4 *)0x0) {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0;
    puVar5[8] = 0x3f800000;
    FUN_00402330();
    local_4._0_1_ = 0x3e;
    if (DAT_005d59ac == (undefined4 *)0x0) {
      local_e0 = (int *)0x14;
      local_f8 = (int **)0x10;
      local_fc = (int **)0x449269;
      puVar8 = (undefined4 *)FUN_004036c0();
      if (local_e0 != (int *)0x1) {
        puVar13 = puVar8 + 4;
        iVar10 = 1;
        puVar4 = puVar13;
        DAT_005d59ac = puVar13;
        if (local_e0 != (int *)0x2) {
          do {
            puVar13 = puVar4 + 4;
            *puVar4 = puVar13;
            iVar10 = iVar10 + 1;
            puVar4 = puVar13;
          } while ((int)local_e0 + -1 != iVar10);
        }
        *puVar13 = 0;
      }
    }
    else {
      puVar8 = DAT_005d59ac;
      DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
    }
    DAT_005d59e8 = 0;
    puVar5[0xb] = puVar8;
    *puVar8 = puVar8;
    *(undefined4 *)(puVar5[0xb] + 4) = puVar5[0xb];
    local_4 = CONCAT31(local_4._1_3_,0x3f);
    local_f8 = (int **)0x4492cd;
    FUN_00469e30();
    *puVar5 = &PTR_FUN_005a87b8;
  }
  local_4 = 0xffffffff;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x5;
  ppiStack_110 = (int **)0x4492fe;
  FUN_004698c0();
  local_f8 = (int **)0x449305;
  piVar7 = operator_new(0x6c);
  local_4 = 0x40;
  local_dc = piVar7;
  if (piVar7 == (int *)0x0) {
    local_b8 = (int *)0x0;
  }
  else {
    FUN_00462d50();
    *piVar7 = (int)&PTR_FUN_005a8758;
    local_b8 = piVar7;
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44936d;
  FUN_00462e50();
  piVar7 = local_c4;
  local_f8 = (int **)0x44937d;
  FUN_00467950();
  local_f8 = (int **)0x449389;
  FUN_00467950();
  local_f8 = (int **)0x449395;
  FUN_00467950();
  local_f8 = (int **)0x4493a1;
  FUN_00467950();
  local_f8 = (int **)0x4493ad;
  FUN_00467950();
  local_f8 = (int **)0x4493b5;
  FUN_00469330();
  local_f8 = (int **)0x4493c1;
  FUN_00469760();
  local_f8 = (int **)0x4493cd;
  FUN_00469760();
  local_f8 = (int **)0x4493d9;
  FUN_00469760();
  local_f8 = (int **)0x4493e5;
  FUN_00469760();
  local_f8 = (int **)0x4493ed;
  FUN_00469760();
  if (piVar7[0xf] != 0) {
    local_f8 = &local_cc;
    local_fc = &local_d0;
    local_104 = (char *)0x44940d;
    local_100 = piVar7[0xf];
    FUN_00429e60();
    ppiStack_110 = (int **)piVar7[0xf];
    local_104 = (undefined *)0x1;
    ppiStack_108 = (int **)local_cc;
    ppiStack_10c = (int **)local_d0;
    appiStack_120[3] = (int **)0x449422;
    FUN_00429d40();
    piVar14 = *(int **)piVar7[2];
    if (piVar14 != (int *)piVar7[2]) {
      do {
        local_c0 = (undefined4 *)piVar14[2];
        local_d4 = *(void **)(*(int *)((int)local_c0 + 0x20) + 8);
        if (local_d4 != (void *)*(int *)((int)local_c0 + 0x20)) {
          do {
            iVar10 = *(int *)((int)local_d4 + 0x14);
            if ((*(int *)(iVar10 + 0x44) == 0) && (*(int *)(iVar10 + 0x1c) != 0)) {
              local_f8 = &local_e0;
              local_fc = &local_d8;
              local_104 = (char *)0x44946f;
              local_100 = *(int *)(iVar10 + 0x1c);
              FUN_00429e60();
              ppiStack_110 = *(int ***)(iVar10 + 0x1c);
              local_104 = (undefined *)0x2;
              ppiStack_108 = (int **)local_e0;
              ppiStack_10c = (int **)local_d8;
              appiStack_120[3] = (int **)0x449484;
              FUN_00429d40();
              appiStack_120[3] = &local_c8;
              appiStack_120[2] = &local_e0;
              appiStack_120[0] = *(int ***)(iVar10 + 0x20);
              appiStack_120[1] = &local_d8;
              FUN_00429e60();
              FUN_00429d40(*(undefined4 *)(iVar10 + 0x20),local_d8,local_e0,3);
            }
            FUN_0043c6c0();
          } while (local_d4 != (void *)*(int *)((int)local_c0 + 0x20));
        }
        piVar14 = (int *)*piVar14;
      } while (piVar14 != (int *)piVar7[2]);
    }
    iVar10 = piVar7[0xe];
    if (iVar10 != 0) {
      local_f8 = &local_e0;
      local_100 = *(int *)(iVar10 + 0x54);
      local_fc = &local_d8;
      local_104 = (char *)0x4494fd;
      FUN_00429e60();
      ppiStack_110 = *(int ***)(iVar10 + 0x54);
      local_104 = (undefined *)0x2;
      ppiStack_108 = (int **)local_e0;
      ppiStack_10c = (int **)local_d8;
      appiStack_120[3] = (int **)0x449512;
      FUN_00429d40();
    }
  }
  local_f8 = (int **)0x44951c;
  puVar5 = operator_new(0x58);
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[1] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0;
    puVar5[8] = 0;
    puVar5[9] = 0x3f800000;
    puVar5[10] = 0;
    puVar5[0xb] = 0;
    puVar5[0xc] = 0;
    puVar5[0xd] = 0;
    puVar5[0xe] = 0x3f800000;
    *puVar5 = &PTR_FUN_005a8928;
  }
  local_f8 = (int **)0x449560;
  puVar5 = operator_new(0x70);
  local_4 = 0x41;
  local_dc = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    puVar5 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a88c8;
    puVar5[0x1b] = 0;
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x4495ca;
  local_a8 = puVar5;
  FUN_00462e50();
  local_f8 = (int **)0x0;
  _DAT_005db098 = 0x41c00000;
  _DAT_005db094 = 0x41c00000;
  DAT_005db090 = 0x432e0000;
  DAT_005db08c = 0x435e0000;
  puVar8 = &DAT_005db08c;
  pppiVar18 = appiStack_120 + 5;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar8;
    puVar8 = puVar8 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 172.0;
  puVar8 = &DAT_005ddd68;
  pppiVar18 = appiStack_120;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar8;
    puVar8 = puVar8 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_f8 = (int **)0x449656;
  FUN_0046adf0();
  local_f8 = (int **)0x449662;
  FUN_0046b240();
  puVar5[1] = s_rules_005c74a4;
  local_f8 = (int **)0x449675;
  FUN_00462bf0();
  local_f8 = (int **)0x44967e;
  FUN_00463050();
  local_f8 = (int **)0x449685;
  local_dc = operator_new(0x78);
  local_4 = 0x42;
  if (local_dc == (void *)0x0) {
    local_bc = 0;
  }
  else {
    local_bc = FUN_00467160();
  }
  local_f8 = (int **)0x0;
  local_fc = (int **)s_mu01500_bmp_005c74b8;
  local_100 = 5;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 234.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_120[2] = (int **)0x449707;
  FUN_00467840();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 236.0;
  local_f8 = (int **)0x449736;
  puVar5 = operator_new(0x74);
  local_4 = 0x43;
  local_dc = puVar5;
  if (puVar5 != (undefined4 *)0x0) {
    *puVar5 = &PTR_LAB_005a8810;
    puVar5[1] = 0;
    puVar5[4] = 0;
    puVar5[5] = 0;
    puVar5[6] = 0;
    puVar5[7] = 0;
    puVar5[8] = 0x3f800000;
    FUN_00402330();
    local_4._0_1_ = 0x45;
    if (DAT_005d59ac == (undefined4 *)0x0) {
      local_e0 = (int *)0x14;
      local_f8 = (int **)0x10;
      local_fc = (int **)0x4497a0;
      puVar8 = (undefined4 *)FUN_004036c0();
      if (local_e0 != (int *)0x1) {
        puVar13 = puVar8 + 4;
        iVar10 = 1;
        puVar4 = puVar13;
        DAT_005d59ac = puVar13;
        if (local_e0 != (int *)0x2) {
          do {
            puVar13 = puVar4 + 4;
            *puVar4 = puVar13;
            iVar10 = iVar10 + 1;
            puVar4 = puVar13;
          } while ((int)local_e0 + -1 != iVar10);
        }
        *puVar13 = 0;
      }
    }
    else {
      puVar8 = DAT_005d59ac;
      DAT_005d59ac = (undefined4 *)*DAT_005d59ac;
    }
    DAT_005d59e8 = 0;
    puVar5[0xb] = puVar8;
    *puVar8 = puVar8;
    *(undefined4 *)(puVar5[0xb] + 4) = puVar5[0xb];
    local_4 = CONCAT31(local_4._1_3_,0x46);
    local_f8 = (int **)0x44980c;
    FUN_00469e30();
    *puVar5 = &PTR_FUN_005a87b8;
  }
  local_4 = 0xffffffff;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x5;
  ppiStack_110 = (int **)0x44983a;
  FUN_004698c0();
  local_f8 = (int **)0x449841;
  puVar5 = operator_new(0x6c);
  local_4 = 0x47;
  local_dc = puVar5;
  if (puVar5 == (undefined4 *)0x0) {
    local_c0 = (undefined4 *)0x0;
  }
  else {
    FUN_00462d50();
    *puVar5 = &PTR_FUN_005a8758;
    local_c0 = puVar5;
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x4498a5;
  FUN_00462e50();
  local_f8 = (int **)0x4498af;
  FUN_00469330();
  if (*(code **)(local_84 + 0x28) == (code *)0x0) {
    local_f8 = (int **)0x4499ef;
    local_dc = operator_new(0x50);
    local_4 = 0x49;
    if (local_dc == (void *)0x0) {
      local_e0 = (int *)0x0;
    }
    else {
      local_e0 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 234.0;
    ppiStack_10c = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 6;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_110 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_120[3] = (int **)0x449a67;
    FUN_00466720();
    local_f8 = (int **)0x0;
    local_fc = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 4;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_120[3] = (int **)0x449a85;
    FUN_00466a10();
    local_f8 = (int **)0xff;
    local_fc = (int **)0xff;
    local_100 = 0;
    local_104 = &DAT_005c74a0;
    ppiStack_108 = (int **)0x449aa2;
    FUN_00466340();
    local_f8 = (int **)0x449aa9;
    local_dc = operator_new(0x50);
    local_4 = 0x4a;
    if (local_dc == (void *)0x0) {
      local_d8 = (int *)0x0;
    }
    else {
      local_d8 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 258.0;
    ppiStack_10c = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 6;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_110 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_120[3] = (int **)0x449b21;
    FUN_00466720();
    local_f8 = (int **)0x0;
    local_fc = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 4;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_120[3] = (int **)0x449b3f;
    FUN_00466a10();
    local_f8 = (int **)0xff;
    local_fc = (int **)0xff;
    local_100 = 0;
    local_104 = &DAT_005c749c;
    ppiStack_108 = (int **)0x449b5c;
    FUN_00466340();
    local_f8 = (int **)0x449b63;
    local_dc = operator_new(0x50);
    local_4 = 0x4b;
    if (local_dc == (void *)0x0) {
      local_d4 = (void *)0x0;
    }
    else {
      local_d4 = (void *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 282.0;
    ppiStack_10c = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 6;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_110 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_120[3] = (int **)0x449bdb;
    FUN_00466720();
    local_f8 = (int **)0x0;
    local_fc = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 4;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_120[3] = (int **)0x449bf9;
    FUN_00466a10();
    local_f8 = (int **)0xff;
    local_fc = (int **)0xff;
    local_100 = 0;
    local_104 = &DAT_005c7498;
    ppiStack_108 = (int **)0x449c16;
    FUN_00466340();
    local_f8 = (int **)0x449c1d;
    local_dc = operator_new(0x50);
    local_4 = 0x4c;
    if (local_dc == (void *)0x0) {
      local_cc = (int *)0x0;
    }
    else {
      local_cc = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 306.0;
    ppiStack_10c = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 6;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_110 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_120[3] = (int **)0x449c95;
    FUN_00466720();
    local_f8 = (int **)0x0;
    local_fc = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 4;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_120[3] = (int **)0x449cb3;
    FUN_00466a10();
    local_f8 = (int **)0xff;
    local_fc = (int **)0xff;
    local_100 = 0;
    local_104 = &DAT_005c7494;
    ppiStack_108 = (int **)0x449cd0;
    FUN_00466340();
    local_f8 = (int **)0x449cd7;
    local_dc = operator_new(0x50);
    local_4 = 0x4d;
    if (local_dc == (void *)0x0) {
      local_d0 = (int *)0x0;
    }
    else {
      local_d0 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 330.0;
    ppiStack_10c = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 6;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_110 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_120[3] = (int **)0x449d4f;
    FUN_00466720();
    local_f8 = (int **)0x0;
    local_fc = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 4;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_120[3] = (int **)0x449d6d;
    FUN_00466a10();
    local_f8 = (int **)0xff;
    local_fc = (int **)0xff;
    local_100 = 0;
    local_104 = &DAT_005c7490;
    ppiStack_108 = (int **)0x449d8a;
    FUN_00466340();
    local_f8 = (int **)0x449d91;
    local_dc = operator_new(0x50);
    local_4 = 0x4e;
    if (local_dc == (void *)0x0) {
      local_c8 = (int *)0x0;
    }
    else {
      local_c8 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 354.0;
    ppiStack_10c = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 6;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_110 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_120[3] = (int **)0x449e09;
    FUN_00466720();
    local_f8 = (int **)0x0;
    local_fc = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 4;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_120[3] = (int **)0x449e27;
    FUN_00466a10();
    local_f8 = (int **)0xff;
    local_fc = (int **)0xff;
    local_100 = 0;
    local_104 = &DAT_005c748c;
    ppiStack_108 = (int **)0x449e44;
    FUN_00466340();
    local_f8 = (int **)0x449e4b;
    local_dc = operator_new(0x50);
    local_4 = 0x4f;
    if (local_dc == (void *)0x0) {
      local_c4 = (int *)0x0;
    }
    else {
      local_c4 = (int *)FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 378.0;
    ppiStack_10c = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 6;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_110 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_120[3] = (int **)0x449ec3;
    FUN_00466720();
    local_f8 = (int **)0x0;
    local_fc = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 4;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_120[3] = (int **)0x449ee1;
    FUN_00466a10();
    local_f8 = (int **)0xff;
    local_fc = (int **)0xff;
    local_100 = 0;
    local_104 = &DAT_005c7488;
    ppiStack_108 = (int **)0x449efe;
    FUN_00466340();
    local_f8 = (int **)0x449f05;
    local_dc = operator_new(0x50);
    local_4 = 0x50;
    if (local_dc != (undefined4 *)0x0) {
      FUN_00465610();
    }
    _DAT_005ddd70 = 0x42e60000;
    _DAT_005ddd74 = 0x41c00000;
    DAT_005ddd68 = 0x42d20000;
    DAT_005ddd6c = 402.0;
    ppiStack_10c = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 6;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    ppiStack_110 = (int **)0x1;
    local_4 = 0xffffffff;
    appiStack_120[3] = (int **)0x449f79;
    FUN_00466720();
    local_f8 = (int **)0x0;
    local_fc = (int **)0x0;
    puVar5 = &DAT_005ddd68;
    pppiVar18 = appiStack_120 + 4;
    for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
      *pppiVar18 = (int **)*puVar5;
      puVar5 = puVar5 + 1;
      pppiVar18 = pppiVar18 + 1;
    }
    appiStack_120[3] = (int **)0x449f97;
    FUN_00466a10();
    local_f8 = (int **)0xff;
    local_fc = (int **)0xff;
    local_100 = 0;
    local_104 = &DAT_005c7484;
    ppiStack_108 = (int **)0x449fb4;
    FUN_00466340();
    local_f8 = (int **)0x449fc4;
    FUN_00467950();
    local_f8 = (int **)0x449fd0;
    FUN_00467950();
    local_f8 = (int **)0x449fdc;
    FUN_00467950();
    local_f8 = (int **)0x449fe8;
    FUN_00467950();
    local_f8 = (int **)0x449ff4;
    FUN_00467950();
    local_f8 = (int **)0x44a000;
    FUN_00467950();
    local_f8 = (int **)0x44a00c;
    FUN_00467950();
    local_f8 = (int **)0x44a014;
    FUN_00467950();
    local_f8 = (int **)0x44a020;
    FUN_00469760();
    local_f8 = (int **)0x44a02c;
    FUN_00469760();
    local_f8 = (int **)0x44a038;
    FUN_00469760();
    local_f8 = (int **)0x44a044;
    FUN_00469760();
    local_f8 = (int **)0x44a050;
    FUN_00469760();
    local_f8 = (int **)0x44a05c;
    FUN_00469760();
    local_f8 = (int **)0x44a064;
    FUN_00469760();
    local_f8 = (int **)0x44a06c;
    FUN_00469760();
  }
  else {
    iVar10 = (**(code **)(local_84 + 0x28))();
    local_d8 = (int *)0x1;
    local_d4 = (void *)(iVar10 / 2);
    if (0 < (int)local_d4) {
      local_e0 = (int *)0xea;
      do {
        local_f8 = (int **)0x4498e9;
        local_dc = operator_new(0x50);
        local_4 = 0x48;
        if (local_dc != (undefined4 *)0x0) {
          FUN_00465610();
        }
        DAT_005ddd6c = (float)(int)local_e0;
        _DAT_005ddd70 = 0x42e60000;
        _DAT_005ddd74 = 0x41c00000;
        DAT_005ddd68 = 0x42d20000;
        puVar5 = &DAT_005ddd68;
        pppiVar18 = appiStack_120 + 6;
        for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
          *pppiVar18 = (int **)*puVar5;
          puVar5 = puVar5 + 1;
          pppiVar18 = pppiVar18 + 1;
        }
        ppiStack_10c = (int **)0x0;
        ppiStack_110 = (int **)0x1;
        local_4 = 0xffffffff;
        appiStack_120[3] = (int **)0x44995d;
        FUN_00466720();
        local_f8 = (int **)0x0;
        local_fc = (int **)0x0;
        puVar5 = &DAT_005ddd68;
        pppiVar18 = appiStack_120 + 4;
        for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
          *pppiVar18 = (int **)*puVar5;
          puVar5 = puVar5 + 1;
          pppiVar18 = pppiVar18 + 1;
        }
        appiStack_120[3] = (int **)0x44997b;
        FUN_00466a10();
        piVar7 = local_d8;
        local_f8 = (int **)auStack_34;
        local_fc = (int **)((int)local_d8 * 2);
        local_100 = 0x449992;
        FUN_0050aaa9();
        local_104 = auStack_34;
        local_f8 = (int **)0xff;
        local_fc = (int **)0xff;
        local_100 = 0;
        ppiStack_108 = (int **)0x4499b5;
        FUN_00466340();
        local_f8 = (int **)0x4499bf;
        FUN_00467950();
        local_f8 = (int **)0x4499c7;
        FUN_00469760();
        local_d8 = (int *)((int)piVar7 + 1);
        local_e0 = local_e0 + 6;
      } while ((int)local_d8 <= (int)local_d4);
    }
  }
  if (*(int *)(local_bc + 0x3c) != 0) {
    local_f8 = &local_d0;
    local_fc = &local_c8;
    local_104 = (char *)0x44a090;
    local_100 = *(int *)(local_bc + 0x3c);
    FUN_00429e60();
    iVar10 = local_bc;
    local_104 = (undefined *)0x1;
    ppiStack_110 = *(int ***)(local_bc + 0x3c);
    ppiStack_108 = (int **)local_d0;
    ppiStack_10c = (int **)local_c8;
    appiStack_120[3] = (int **)0x44a0a9;
    FUN_00429d40();
    piVar7 = *(int **)(iVar10 + 8);
    local_cc = (int *)*piVar7;
    if (local_cc != piVar7) {
      do {
        iVar2 = local_cc[2];
        iVar3 = *(int *)(iVar2 + 0x20);
        local_d4 = *(void **)(iVar3 + 8);
        if (local_d4 != (void *)iVar3) {
          do {
            iVar3 = *(int *)((int)local_d4 + 0x14);
            if ((*(int *)(iVar3 + 0x44) == 0) && (*(int *)(iVar3 + 0x1c) != 0)) {
              local_f8 = &local_e0;
              local_fc = &local_d8;
              local_104 = (char *)0x44a0f6;
              local_100 = *(int *)(iVar3 + 0x1c);
              FUN_00429e60();
              ppiStack_110 = *(int ***)(iVar3 + 0x1c);
              local_104 = (undefined *)0x2;
              ppiStack_108 = (int **)local_e0;
              ppiStack_10c = (int **)local_d8;
              appiStack_120[3] = (int **)0x44a10b;
              FUN_00429d40();
              appiStack_120[3] = &local_c4;
              appiStack_120[2] = &local_e0;
              appiStack_120[0] = *(int ***)(iVar3 + 0x20);
              appiStack_120[1] = &local_d8;
              FUN_00429e60();
              FUN_00429d40(*(undefined4 *)(iVar3 + 0x20),local_d8,local_e0,3);
            }
            FUN_0043c6c0();
          } while (local_d4 != (void *)*(int *)(iVar2 + 0x20));
        }
        local_f8 = &local_b8;
        local_fc = (int **)0x44a15f;
        FUN_004a8420();
      } while (local_cc != *(int **)(iVar10 + 8));
    }
    if (*(int *)(local_bc + 0x38) != 0) {
      local_f8 = (int **)0x44a180;
      FUN_00443790();
    }
  }
  local_f8 = (int **)0x44a187;
  pvVar9 = operator_new(0x58);
  if (pvVar9 != (void *)0x0) {
    FUN_00443e60();
  }
  local_f8 = (int **)0x44a1a2;
  local_dc = operator_new(0x70);
  local_4 = 0x51;
  if (local_dc == (void *)0x0) {
    local_b8 = (int *)0x0;
  }
  else {
    local_b8 = (int *)FUN_00443d00();
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44a20c;
  FUN_00462e50();
  local_f8 = (int **)0x0;
  _DAT_005db098 = 0x41c00000;
  _DAT_005db094 = 0x41c00000;
  DAT_005db090 = 0x43560000;
  DAT_005db08c = 0x435e0000;
  puVar5 = &DAT_005db08c;
  pppiVar18 = appiStack_120 + 5;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 212.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_f8 = (int **)0x44a298;
  FUN_0046adf0();
  if (*(code **)(local_84 + 0x28) != (code *)0x0) {
    uVar11 = (**(code **)(local_84 + 0x28))();
    uVar12 = uVar11 & 0x80000001;
    if ((int)uVar12 < 0) {
      uVar12 = (uVar12 - 1 | 0xfffffffe) + 1;
    }
    local_f8 = (int **)auStack_20;
    local_fc = (int **)(uVar11 - uVar12);
    local_100 = 0x44a2cd;
    FUN_0050aaa9();
  }
  local_f8 = (int **)0x44a2df;
  FUN_0046b240();
  local_f8 = (int **)0x44a2eb;
  FUN_00443160();
  local_f8 = (int **)0x44a2f4;
  FUN_00463050();
  local_f8 = (int **)0x44a300;
  FUN_00462bf0();
  local_f8 = (int **)0x44a307;
  local_dc = operator_new(0x78);
  local_4 = 0x52;
  if (local_dc != (void *)0x0) {
    FUN_00467160();
  }
  local_f8 = (int **)0x0;
  local_fc = (int **)s_mu01500_bmp_005c74b8;
  local_100 = 5;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 274.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_120[2] = (int **)0x44a380;
  FUN_00467840();
  local_f8 = (int **)0x44a387;
  local_dc = operator_new(0x50);
  local_4 = 0x53;
  if (local_dc == (void *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 274.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44a409;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44a427;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c7474;
  ppiStack_108 = (int **)0x44a444;
  FUN_00466340();
  local_f8 = (int **)0x44a44b;
  local_dc = operator_new(0x50);
  local_4 = 0x54;
  if (local_dc == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 298.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44a4c3;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44a4e1;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c7470;
  ppiStack_108 = (int **)0x44a4fe;
  FUN_00466340();
  local_f8 = (int **)0x44a505;
  local_dc = operator_new(0x50);
  local_4 = 0x55;
  if (local_dc == (void *)0x0) {
    local_d4 = (void *)0x0;
  }
  else {
    local_d4 = (void *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 322.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44a57d;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44a59b;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c746c;
  ppiStack_108 = (int **)0x44a5b8;
  FUN_00466340();
  local_f8 = (int **)0x44a5bf;
  local_dc = operator_new(0x50);
  local_4 = 0x56;
  if (local_dc == (void *)0x0) {
    local_cc = (int *)0x0;
  }
  else {
    local_cc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 346.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44a637;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44a655;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c7468;
  ppiStack_108 = (int **)0x44a672;
  FUN_00466340();
  local_f8 = (int **)0x44a679;
  local_dc = operator_new(0x50);
  local_4 = 0x57;
  if (local_dc == (void *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 370.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44a6f1;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44a70f;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c7464;
  ppiStack_108 = (int **)0x44a72c;
  FUN_00466340();
  local_f8 = (int **)0x44a733;
  local_dc = operator_new(0x50);
  local_4 = 0x58;
  if (local_dc == (void *)0x0) {
    local_c8 = (int *)0x0;
  }
  else {
    local_c8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 394.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44a7ab;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44a7c9;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c7460;
  ppiStack_108 = (int **)0x44a7e6;
  FUN_00466340();
  local_f8 = (int **)0x44a7ed;
  local_dc = operator_new(0x50);
  local_4 = 0x59;
  if (local_dc == (void *)0x0) {
    local_c0 = (undefined4 *)0x0;
  }
  else {
    local_c0 = (undefined4 *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 418.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44a865;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44a883;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c745c;
  ppiStack_108 = (int **)0x44a8a0;
  FUN_00466340();
  local_f8 = (int **)0x44a8a7;
  local_dc = operator_new(0x50);
  local_4 = 0x5a;
  if (local_dc == (void *)0x0) {
    local_b4 = 0;
  }
  else {
    local_b4 = FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 442.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44a91f;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44a93d;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c7458;
  ppiStack_108 = (int **)0x44a95a;
  FUN_00466340();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 276.0;
  local_f8 = (int **)0x44a989;
  local_dc = operator_new(0x74);
  local_4 = 0x5b;
  if (local_dc != (void *)0x0) {
    FUN_00443630();
  }
  local_4 = 0xffffffff;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x5;
  ppiStack_110 = (int **)0x44a9d3;
  FUN_004698c0();
  local_f8 = (int **)0x44a9da;
  local_dc = operator_new(0x6c);
  local_4 = 0x5c;
  if (local_dc == (void *)0x0) {
    local_c4 = (int *)0x0;
  }
  else {
    local_c4 = (int *)FUN_00443a20();
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44aa40;
  FUN_00462e50();
  local_f8 = (int **)0x44aa4c;
  FUN_00467950();
  local_f8 = (int **)0x44aa58;
  FUN_00467950();
  local_f8 = (int **)0x44aa64;
  FUN_00467950();
  local_f8 = (int **)0x44aa70;
  FUN_00467950();
  local_f8 = (int **)0x44aa7c;
  FUN_00467950();
  local_f8 = (int **)0x44aa88;
  FUN_00467950();
  local_f8 = (int **)0x44aa94;
  FUN_00467950();
  local_f8 = (int **)0x44aaa0;
  FUN_00467950();
  local_f8 = (int **)0x44aaa8;
  FUN_00469330();
  local_f8 = (int **)0x44aab4;
  FUN_00469760();
  local_f8 = (int **)0x44aac0;
  FUN_00469760();
  local_f8 = (int **)0x44aacc;
  FUN_00469760();
  local_f8 = (int **)0x44aad8;
  FUN_00469760();
  local_f8 = (int **)0x44aae4;
  FUN_00469760();
  local_f8 = (int **)0x44aaf0;
  FUN_00469760();
  local_f8 = (int **)0x44aaf8;
  FUN_00469760();
  local_f8 = (int **)0x44ab00;
  FUN_00469760();
  local_f8 = (int **)0x44ab09;
  FUN_004438d0();
  local_f8 = (int **)0x44ab10;
  pvVar9 = operator_new(0x58);
  uVar6 = 0;
  if (pvVar9 == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00443e60();
  }
  local_f8 = (int **)0x44ab31;
  local_dc = operator_new(0x70);
  local_4 = 0x5d;
  if (local_dc != (void *)0x0) {
    uVar6 = FUN_00443d00();
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44ab93;
  local_c0 = (undefined4 *)uVar6;
  FUN_00462e50();
  local_f8 = (int **)0x0;
  _DAT_005db098 = 0x41c00000;
  _DAT_005db094 = 0x41c00000;
  DAT_005db090 = 0x437e0000;
  DAT_005db08c = 0x435e0000;
  puVar5 = &DAT_005db08c;
  pppiVar18 = appiStack_120 + 5;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 250.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_f8 = (int **)0x44ac1f;
  FUN_0046adf0();
  local_f8 = (int **)0x44ac2b;
  FUN_0046b240();
  local_f8 = (int **)0x44ac37;
  FUN_00443160();
  local_f8 = (int **)0x44ac40;
  FUN_00463050();
  local_f8 = (int **)0x44ac4c;
  FUN_00462bf0();
  local_f8 = (int **)0x44ac53;
  local_dc = operator_new(0x78);
  local_4 = 0x5e;
  if (local_dc == (void *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00467160();
  }
  local_f8 = (int **)0x0;
  local_fc = (int **)s_mu01500_bmp_005c74b8;
  local_100 = 5;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 314.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_120[2] = (int **)0x44acd5;
  FUN_00467840();
  local_f8 = (int **)0x44acdc;
  local_dc = operator_new(0x50);
  local_4 = 0x5f;
  if (local_dc == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 314.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44ad50;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44ad6e;
  FUN_00466a10();
  pcVar15 = acStack_68;
  for (iVar10 = 0xc; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar15[0] = '\0';
    pcVar15[1] = '\0';
    pcVar15[2] = '\0';
    pcVar15[3] = '\0';
    pcVar15 = pcVar15 + 4;
  }
  pcVar15[0] = '\0';
  pcVar15[1] = '\0';
  iVar10 = 0;
  do {
    cVar1 = (&DAT_005c7474)[iVar10];
    acStack_68[iVar10] = cVar1;
    iVar10 = iVar10 + 1;
  } while (cVar1 != '\0');
  uVar11 = 0xffffffff;
  pcVar15 = &DAT_005dd854;
  do {
    pcVar17 = pcVar15;
    if (uVar11 == 0) break;
    uVar11 = uVar11 - 1;
    pcVar17 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar17;
  } while (cVar1 != '\0');
  uVar11 = ~uVar11;
  iVar10 = -1;
  local_f8 = (int **)0xff;
  pcVar15 = acStack_68;
  do {
    pcVar16 = pcVar15;
    if (iVar10 == 0) break;
    iVar10 = iVar10 + -1;
    pcVar16 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar16;
  } while (cVar1 != '\0');
  pcVar15 = pcVar17 + -uVar11;
  pcVar17 = pcVar16 + -1;
  for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar15;
    pcVar15 = pcVar15 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_fc = (int **)0xff;
  local_100 = 0;
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *pcVar17 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_104 = acStack_68;
  ppiStack_108 = (int **)0x44ade6;
  FUN_00466340();
  local_f8 = (int **)0x44aded;
  local_dc = operator_new(0x50);
  local_4 = 0x60;
  if (local_dc == (void *)0x0) {
    local_d4 = (void *)0x0;
  }
  else {
    local_d4 = (void *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 338.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44ae61;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44ae7f;
  FUN_00466a10();
  pcVar15 = acStack_68;
  for (iVar10 = 0xc; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar15[0] = '\0';
    pcVar15[1] = '\0';
    pcVar15[2] = '\0';
    pcVar15[3] = '\0';
    pcVar15 = pcVar15 + 4;
  }
  pcVar15[0] = '\0';
  pcVar15[1] = '\0';
  iVar10 = 0;
  do {
    cVar1 = (&DAT_005c7470)[iVar10];
    acStack_68[iVar10] = cVar1;
    iVar10 = iVar10 + 1;
  } while (cVar1 != '\0');
  uVar11 = 0xffffffff;
  pcVar15 = &DAT_005dd854;
  do {
    pcVar17 = pcVar15;
    if (uVar11 == 0) break;
    uVar11 = uVar11 - 1;
    pcVar17 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar17;
  } while (cVar1 != '\0');
  uVar11 = ~uVar11;
  iVar10 = -1;
  local_f8 = (int **)0xff;
  pcVar15 = acStack_68;
  do {
    pcVar16 = pcVar15;
    if (iVar10 == 0) break;
    iVar10 = iVar10 + -1;
    pcVar16 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar16;
  } while (cVar1 != '\0');
  pcVar15 = pcVar17 + -uVar11;
  pcVar17 = pcVar16 + -1;
  for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar15;
    pcVar15 = pcVar15 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_fc = (int **)0xff;
  local_100 = 0;
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *pcVar17 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_104 = acStack_68;
  ppiStack_108 = (int **)0x44aef7;
  FUN_00466340();
  local_f8 = (int **)0x44aefe;
  local_dc = operator_new(0x50);
  local_4 = 0x61;
  if (local_dc == (void *)0x0) {
    local_cc = (int *)0x0;
  }
  else {
    local_cc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 362.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44af72;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44af90;
  FUN_00466a10();
  pcVar15 = acStack_68;
  for (iVar10 = 0xc; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar15[0] = '\0';
    pcVar15[1] = '\0';
    pcVar15[2] = '\0';
    pcVar15[3] = '\0';
    pcVar15 = pcVar15 + 4;
  }
  pcVar15[0] = '\0';
  pcVar15[1] = '\0';
  iVar10 = 0;
  do {
    cVar1 = (&DAT_005c746c)[iVar10];
    acStack_68[iVar10] = cVar1;
    iVar10 = iVar10 + 1;
  } while (cVar1 != '\0');
  uVar11 = 0xffffffff;
  pcVar15 = &DAT_005dd854;
  do {
    pcVar17 = pcVar15;
    if (uVar11 == 0) break;
    uVar11 = uVar11 - 1;
    pcVar17 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar17;
  } while (cVar1 != '\0');
  uVar11 = ~uVar11;
  iVar10 = -1;
  local_f8 = (int **)0xff;
  pcVar15 = acStack_68;
  do {
    pcVar16 = pcVar15;
    if (iVar10 == 0) break;
    iVar10 = iVar10 + -1;
    pcVar16 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar16;
  } while (cVar1 != '\0');
  pcVar15 = pcVar17 + -uVar11;
  pcVar17 = pcVar16 + -1;
  for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar15;
    pcVar15 = pcVar15 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_fc = (int **)0xff;
  local_100 = 0;
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *pcVar17 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_104 = acStack_68;
  ppiStack_108 = (int **)0x44b008;
  FUN_00466340();
  local_f8 = (int **)0x44b00f;
  local_dc = operator_new(0x50);
  local_4 = 0x62;
  if (local_dc == (void *)0x0) {
    local_c8 = (int *)0x0;
  }
  else {
    local_c8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 386.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44b083;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44b0a1;
  FUN_00466a10();
  pcVar15 = acStack_68;
  for (iVar10 = 0xc; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar15[0] = '\0';
    pcVar15[1] = '\0';
    pcVar15[2] = '\0';
    pcVar15[3] = '\0';
    pcVar15 = pcVar15 + 4;
  }
  pcVar15[0] = '\0';
  pcVar15[1] = '\0';
  iVar10 = 0;
  do {
    cVar1 = (&DAT_005c7490)[iVar10];
    acStack_68[iVar10] = cVar1;
    iVar10 = iVar10 + 1;
  } while (cVar1 != '\0');
  uVar11 = 0xffffffff;
  pcVar15 = &DAT_005dd854;
  do {
    pcVar17 = pcVar15;
    if (uVar11 == 0) break;
    uVar11 = uVar11 - 1;
    pcVar17 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar17;
  } while (cVar1 != '\0');
  uVar11 = ~uVar11;
  iVar10 = -1;
  local_f8 = (int **)0xff;
  pcVar15 = acStack_68;
  do {
    pcVar16 = pcVar15;
    if (iVar10 == 0) break;
    iVar10 = iVar10 + -1;
    pcVar16 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar16;
  } while (cVar1 != '\0');
  pcVar15 = pcVar17 + -uVar11;
  pcVar17 = pcVar16 + -1;
  for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar15;
    pcVar15 = pcVar15 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_fc = (int **)0xff;
  local_100 = 0;
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *pcVar17 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_104 = acStack_68;
  ppiStack_108 = (int **)0x44b119;
  FUN_00466340();
  local_f8 = (int **)0x44b120;
  local_dc = operator_new(0x50);
  local_4 = 99;
  if (local_dc != (void *)0x0) {
    FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 410.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44b190;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44b1ae;
  FUN_00466a10();
  pcVar15 = acStack_68;
  for (iVar10 = 0xc; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar15[0] = '\0';
    pcVar15[1] = '\0';
    pcVar15[2] = '\0';
    pcVar15[3] = '\0';
    pcVar15 = pcVar15 + 4;
  }
  pcVar15[0] = '\0';
  pcVar15[1] = '\0';
  iVar10 = 0;
  do {
    cVar1 = (&DAT_005c7464)[iVar10];
    acStack_68[iVar10] = cVar1;
    iVar10 = iVar10 + 1;
  } while (cVar1 != '\0');
  uVar11 = 0xffffffff;
  pcVar15 = &DAT_005dd854;
  do {
    pcVar17 = pcVar15;
    if (uVar11 == 0) break;
    uVar11 = uVar11 - 1;
    pcVar17 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar17;
  } while (cVar1 != '\0');
  uVar11 = ~uVar11;
  iVar10 = -1;
  local_f8 = (int **)0xff;
  pcVar15 = acStack_68;
  do {
    pcVar16 = pcVar15;
    if (iVar10 == 0) break;
    iVar10 = iVar10 + -1;
    pcVar16 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar16;
  } while (cVar1 != '\0');
  pcVar15 = pcVar17 + -uVar11;
  pcVar17 = pcVar16 + -1;
  for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar15;
    pcVar15 = pcVar15 + 4;
    pcVar17 = pcVar17 + 4;
  }
  local_fc = (int **)0xff;
  local_100 = 0;
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *pcVar17 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_104 = acStack_68;
  ppiStack_108 = (int **)0x44b226;
  FUN_00466340();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 316.0;
  local_f8 = (int **)0x44b255;
  local_dc = operator_new(0x74);
  local_4 = 100;
  if (local_dc != (void *)0x0) {
    FUN_00443630();
  }
  local_4 = 0xffffffff;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x5;
  ppiStack_110 = (int **)0x44b29f;
  FUN_004698c0();
  local_f8 = (int **)0x44b2a6;
  local_dc = operator_new(0x6c);
  local_4 = 0x65;
  if (local_dc == (void *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_00443a20();
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44b30c;
  FUN_00462e50();
  local_f8 = (int **)0x44b31c;
  FUN_00467950();
  local_f8 = (int **)0x44b328;
  FUN_00467950();
  local_f8 = (int **)0x44b334;
  FUN_00467950();
  local_f8 = (int **)0x44b340;
  FUN_00467950();
  local_f8 = (int **)0x44b348;
  FUN_00467950();
  local_f8 = (int **)0x44b350;
  FUN_00469330();
  local_f8 = (int **)0x44b35c;
  FUN_00469760();
  local_f8 = (int **)0x44b368;
  FUN_00469760();
  local_f8 = (int **)0x44b374;
  FUN_00469760();
  local_f8 = (int **)0x44b37c;
  FUN_00469760();
  local_f8 = (int **)0x44b384;
  FUN_00469760();
  local_f8 = (int **)0x44b38d;
  FUN_004438d0();
  local_f8 = (int **)0x44b394;
  pvVar9 = operator_new(0x58);
  if (pvVar9 != (void *)0x0) {
    FUN_00443e60();
  }
  local_f8 = (int **)0x44b3af;
  local_dc = operator_new(0x70);
  local_4 = 0x66;
  if (local_dc == (void *)0x0) {
    local_b4 = 0;
  }
  else {
    local_b4 = FUN_00443d00();
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44b40f;
  FUN_00462e50();
  local_f8 = (int **)0x0;
  _DAT_005db098 = 0x41c00000;
  _DAT_005db094 = 0x41c00000;
  DAT_005db090 = 0x43930000;
  DAT_005db08c = 0x435e0000;
  puVar5 = &DAT_005db08c;
  pppiVar18 = appiStack_120 + 5;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 292.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_f8 = (int **)0x44b49b;
  FUN_0046adf0();
  pcVar15 = acStack_68;
  for (iVar10 = 0xc; iVar10 != 0; iVar10 = iVar10 + -1) {
    pcVar15[0] = '\0';
    pcVar15[1] = '\0';
    pcVar15[2] = '\0';
    pcVar15[3] = '\0';
    pcVar15 = pcVar15 + 4;
  }
  pcVar15[0] = '\0';
  pcVar15[1] = '\0';
  iVar10 = 0;
  do {
    cVar1 = (&DAT_005c746c)[iVar10];
    acStack_68[iVar10] = cVar1;
    iVar10 = iVar10 + 1;
  } while (cVar1 != '\0');
  uVar11 = 0xffffffff;
  pcVar15 = &DAT_005dd854;
  do {
    pcVar17 = pcVar15;
    if (uVar11 == 0) break;
    uVar11 = uVar11 - 1;
    pcVar17 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar17;
  } while (cVar1 != '\0');
  uVar11 = ~uVar11;
  iVar10 = -1;
  pcVar15 = acStack_68;
  do {
    pcVar16 = pcVar15;
    if (iVar10 == 0) break;
    iVar10 = iVar10 + -1;
    pcVar16 = pcVar15 + 1;
    cVar1 = *pcVar15;
    pcVar15 = pcVar16;
  } while (cVar1 != '\0');
  pcVar15 = pcVar17 + -uVar11;
  pcVar17 = pcVar16 + -1;
  for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *(undefined4 *)pcVar17 = *(undefined4 *)pcVar15;
    pcVar15 = pcVar15 + 4;
    pcVar17 = pcVar17 + 4;
  }
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *pcVar17 = *pcVar15;
    pcVar15 = pcVar15 + 1;
    pcVar17 = pcVar17 + 1;
  }
  local_f8 = (int **)0x44b505;
  FUN_0046b240();
  local_f8 = (int **)0x44b511;
  FUN_00443160();
  local_f8 = (int **)0x44b51a;
  FUN_00463050();
  local_f8 = (int **)0x44b526;
  FUN_00462bf0();
  local_f8 = (int **)0x44b52d;
  local_dc = operator_new(0x78);
  local_4 = 0x67;
  if (local_dc == (void *)0x0) {
    local_c8 = (int *)0x0;
  }
  else {
    local_c8 = (int *)FUN_00467160();
  }
  local_f8 = (int **)0x0;
  local_fc = (int **)s_mu01500_bmp_005c74b8;
  local_100 = 5;
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x42f00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 354.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 3;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  local_4 = 0xffffffff;
  appiStack_120[2] = (int **)0x44b5aa;
  FUN_00467840();
  local_f8 = (int **)0x44b5b1;
  local_dc = operator_new(0x50);
  local_4 = 0x68;
  if (local_dc == (void *)0x0) {
    local_e0 = (int *)0x0;
  }
  else {
    local_e0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 354.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44b629;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44b647;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c743c;
  ppiStack_108 = (int **)0x44b664;
  FUN_00466340();
  local_f8 = (int **)0x44b66b;
  local_dc = operator_new(0x50);
  local_4 = 0x69;
  if (local_dc == (void *)0x0) {
    local_d8 = (int *)0x0;
  }
  else {
    local_d8 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 378.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44b6e3;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44b701;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c7434;
  ppiStack_108 = (int **)0x44b71e;
  FUN_00466340();
  local_f8 = (int **)0x44b725;
  local_dc = operator_new(0x50);
  local_4 = 0x6a;
  if (local_dc == (void *)0x0) {
    local_d4 = (void *)0x0;
  }
  else {
    local_d4 = (void *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 402.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44b79d;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44b7bb;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c742c;
  ppiStack_108 = (int **)0x44b7d8;
  FUN_00466340();
  local_f8 = (int **)0x44b7df;
  local_dc = operator_new(0x50);
  local_4 = 0x6b;
  if (local_dc == (void *)0x0) {
    local_cc = (int *)0x0;
  }
  else {
    local_cc = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 426.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44b857;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44b875;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c7424;
  ppiStack_108 = (int **)0x44b892;
  FUN_00466340();
  local_f8 = (int **)0x44b899;
  local_dc = operator_new(0x50);
  local_4 = 0x6c;
  if (local_dc == (void *)0x0) {
    local_d0 = (int *)0x0;
  }
  else {
    local_d0 = (int *)FUN_00465610();
  }
  _DAT_005ddd70 = 0x42e60000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 450.0;
  ppiStack_10c = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_110 = (int **)0x1;
  local_4 = 0xffffffff;
  appiStack_120[3] = (int **)0x44b911;
  FUN_00466720();
  local_f8 = (int **)0x0;
  local_fc = (int **)0x0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 4;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  appiStack_120[3] = (int **)0x44b92f;
  FUN_00466a10();
  local_f8 = (int **)0xff;
  local_fc = (int **)0xff;
  local_100 = 0;
  local_104 = &DAT_005c741c;
  ppiStack_108 = (int **)0x44b94c;
  FUN_00466340();
  _DAT_005ddd70 = 0x41b00000;
  _DAT_005ddd74 = 0x42ec0000;
  DAT_005ddd68 = 0x43600000;
  DAT_005ddd6c = 356.0;
  local_f8 = (int **)0x44b97b;
  local_dc = operator_new(0x74);
  local_4 = 0x6d;
  if (local_dc != (void *)0x0) {
    FUN_00443630();
  }
  local_4 = 0xffffffff;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120 + 6;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  ppiStack_10c = (int **)0x5;
  ppiStack_110 = (int **)0x44b9c5;
  FUN_004698c0();
  local_f8 = (int **)0x44b9cc;
  local_dc = operator_new(0x6c);
  local_4 = 0x6e;
  if (local_dc == (void *)0x0) {
    local_c4 = (int *)0x0;
  }
  else {
    local_c4 = (int *)FUN_00443a20();
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44ba2c;
  FUN_00462e50();
  local_f8 = (int **)0x44ba38;
  FUN_00467950();
  local_f8 = (int **)0x44ba44;
  FUN_00467950();
  local_f8 = (int **)0x44ba50;
  FUN_00467950();
  local_f8 = (int **)0x44ba5c;
  FUN_00467950();
  local_f8 = (int **)0x44ba68;
  FUN_00467950();
  local_f8 = (int **)0x44ba70;
  FUN_00469330();
  local_f8 = (int **)0x44ba7c;
  FUN_00469760();
  local_f8 = (int **)0x44ba88;
  FUN_00469760();
  local_f8 = (int **)0x44ba94;
  FUN_00469760();
  local_f8 = (int **)0x44ba9c;
  FUN_00469760();
  local_f8 = (int **)0x44baa4;
  FUN_00469760();
  local_f8 = (int **)0x44baad;
  FUN_004438d0();
  local_f8 = (int **)0x44bab4;
  pvVar9 = operator_new(0x58);
  if (pvVar9 != (void *)0x0) {
    FUN_00443e60();
  }
  local_f8 = (int **)0x44bacf;
  local_dc = operator_new(0x70);
  local_4 = 0x6f;
  if (local_dc != (void *)0x0) {
    FUN_00443d00();
  }
  local_4 = 0xffffffff;
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44bb2b;
  FUN_00462e50();
  local_f8 = (int **)0x0;
  _DAT_005db098 = 0x41c00000;
  _DAT_005db094 = 0x41c00000;
  DAT_005db090 = 0x43a70000;
  DAT_005db08c = 0x435e0000;
  puVar5 = &DAT_005db08c;
  pppiVar18 = appiStack_120 + 5;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  _DAT_005ddd70 = 0x430d0000;
  _DAT_005ddd74 = 0x41c00000;
  DAT_005ddd68 = 0x42d20000;
  DAT_005ddd6c = 332.0;
  puVar5 = &DAT_005ddd68;
  pppiVar18 = appiStack_120;
  for (iVar10 = 5; iVar10 != 0; iVar10 = iVar10 + -1) {
    *pppiVar18 = (int **)*puVar5;
    puVar5 = puVar5 + 1;
    pppiVar18 = pppiVar18 + 1;
  }
  FUN_0046aba0();
  local_f8 = (int **)0x44bbb7;
  FUN_0046adf0();
  local_f8 = (int **)0x44bbc3;
  FUN_0046b240();
  local_f8 = (int **)0x44bbcf;
  FUN_00443160();
  local_f8 = (int **)0x44bbd8;
  FUN_00463050();
  local_f8 = (int **)0x44bbe4;
  FUN_00462bf0();
  local_104 = DAT_005dbb70;
  local_100 = DAT_005dbb74;
  local_fc = DAT_005dbb78;
  local_f8 = (int **)DAT_005dbb7c;
  ppiStack_108 = (int **)0x44bc21;
  FUN_00462e50();
  local_f8 = (int **)0x44bc34;
  FUN_00462bf0();
  local_f8 = (int **)0x44bc44;
  FUN_00462bf0();
  local_f8 = (int **)0x44bc57;
  FUN_00462bf0();
  local_f8 = (int **)0x44bc67;
  FUN_00462bf0();
  local_f8 = (int **)0x44bc77;
  FUN_00462bf0();
  local_f8 = (int **)0x44bc87;
  FUN_00462bf0();
  local_f8 = (int **)0x44bc97;
  FUN_00462bf0();
  local_f8 = (int **)0x44bca7;
  FUN_00462bf0();
  local_f8 = (int **)0x44bcb7;
  FUN_00462bf0();
  local_f8 = (int **)0x44bcc7;
  FUN_00462bf0();
  local_f8 = (int **)0x44bcd7;
  FUN_00462bf0();
  local_f8 = (int **)0x44bce7;
  FUN_00462bf0();
  local_f8 = (int **)0x44bcf7;
  FUN_00462bf0();
  local_f8 = (int **)0x44bd07;
  FUN_00462bf0();
  local_f8 = (int **)0x44bd17;
  FUN_00462bf0();
  local_f8 = (int **)0x44bd27;
  FUN_00462bf0();
  local_f8 = (int **)0x44bd37;
  FUN_00462bf0();
  local_f8 = (int **)0x44bd43;
  FUN_00462bf0();
  local_f8 = (int **)0x44bd50;
  (**(code **)(**(int **)(local_84 + 0x2ac) + 0x58))();
  local_f8 = *(int ***)(local_84 + 0x2ac);
  local_fc = (int **)0x44bd62;
  FUN_00461e50();
  local_f8 = *(int ***)(local_84 + 0x2a0);
  local_fc = (int **)0x44bd70;
  FUN_00570fc0();
  local_f8 = *(int ***)(local_84 + 0x29c);
  local_fc = (int **)0x44bd7e;
  FUN_00570fc0();
  ExceptionList = pvStack_10;
  return 1;
}

