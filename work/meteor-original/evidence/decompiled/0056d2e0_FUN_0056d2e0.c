/* Decompiled from user's Meteor.exe; address: 0056d2e0 */
/* String anchors: [teamb] */

void __fastcall FUN_0056d2e0(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined1 *puVar10;
  undefined4 *puVar11;
  int local_28;
  char local_20 [32];
  
  FUN_0056a0c0();
  *(undefined1 *)(*(int *)(param_1 + 0x120) + 0x1f) = 0;
  iVar6 = *(int *)(*(int *)(param_1 + 0x120) + 0x3c);
  *(undefined4 *)(param_1 + 0x1e0) = *(undefined4 *)(param_1 + 0xf0);
  *(undefined4 *)(param_1 + 0x1e4) = *(undefined4 *)(param_1 + 0xf4);
  *(undefined4 *)(param_1 + 0x1e8) = *(undefined4 *)(param_1 + 0xf8);
  *(undefined4 *)(param_1 + 0x1ec) = *(undefined4 *)(param_1 + 0xe4);
  *(undefined4 *)(param_1 + 0x1f0) = *(undefined4 *)(param_1 + 0xe8);
  *(undefined4 *)(param_1 + 500) = *(undefined4 *)(param_1 + 0xec);
  *(undefined4 *)(param_1 + 0x1f8) = *(undefined4 *)(param_1 + 0x114);
  *(undefined4 *)(param_1 + 0x1fc) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0x200) = *(undefined4 *)(param_1 + 0x11c);
  *(undefined4 *)(param_1 + 0x204) = *(undefined4 *)(param_1 + 0xfc);
  *(undefined4 *)(param_1 + 0x208) = *(undefined4 *)(param_1 + 0x100);
  *(undefined4 *)(param_1 + 0x20c) = *(undefined4 *)(param_1 + 0x104);
  local_28 = 0;
  if (0 < *(int *)(*(int *)(param_1 + 0x120) + 0x38)) {
    puVar7 = (undefined4 *)(iVar6 + 0x220);
    do {
      if (puVar7[-10] == 1) {
        *(undefined4 *)(param_1 + 0x1e0) = *puVar7;
        *(undefined4 *)(param_1 + 0x1e4) = puVar7[1];
        *(undefined4 *)(param_1 + 0x1e8) = puVar7[2];
        *(undefined4 *)(param_1 + 0x1ec) = puVar7[3];
        *(undefined4 *)(param_1 + 0x1f0) = puVar7[4];
        *(undefined4 *)(param_1 + 500) = puVar7[5];
        *(undefined4 *)(param_1 + 0x1f8) = puVar7[6];
        *(undefined4 *)(param_1 + 0x1fc) = puVar7[7];
        *(undefined4 *)(param_1 + 0x200) = puVar7[8];
        *(undefined4 *)(param_1 + 0x204) = puVar7[9];
        *(undefined4 *)(param_1 + 0x208) = puVar7[10];
        *(undefined4 *)(param_1 + 0x20c) = puVar7[0xb];
      }
      iVar4 = _strncmp((char *)(puVar7 + -0x86),&DAT_005d1880,2);
      if (iVar4 == 0) {
        *(undefined1 *)(puVar7 + -9) = 0;
      }
      local_28 = local_28 + 1;
      puVar7 = puVar7 + 0xac;
    } while (local_28 < *(int *)(*(int *)(param_1 + 0x120) + 0x38));
  }
  iVar4 = *(int *)(*(int *)(param_1 + 0x120) + 0x44);
  *(undefined4 *)(param_1 + 0x214) = 0;
  *(undefined4 *)(param_1 + 0x218) = 0;
  *(undefined4 *)(param_1 + 0x21c) = 0;
  iVar2 = *(int *)(param_1 + 0x228);
  iVar3 = *(int *)(param_1 + 0x22c);
  FUN_00506e90(iVar3);
  *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + (iVar3 - iVar2 >> 6) * -0x40;
  iVar2 = *(int *)(param_1 + 0x234);
  iVar3 = *(int *)(param_1 + 0x238);
  FUN_00506e90(iVar3,iVar3,iVar2,iVar6,0);
  *(int *)(param_1 + 0x238) = *(int *)(param_1 + 0x238) + (iVar3 - iVar2 >> 6) * -0x40;
  iVar2 = *(int *)(param_1 + 0x240);
  iVar3 = *(int *)(param_1 + 0x244);
  FUN_00506e90(iVar3,iVar3,iVar2,iVar6,0);
  *(int *)(param_1 + 0x244) = *(int *)(param_1 + 0x244) + (iVar3 - iVar2 >> 6) * -0x40;
  piVar8 = (int *)**(int **)(param_1 + 0x24c);
  if (piVar8 != *(int **)(param_1 + 0x24c)) {
    do {
      piVar8 = (int *)*piVar8;
      FUN_00402e90();
    } while (piVar8 != (int *)*(int *)(param_1 + 0x24c));
  }
  local_28 = 0;
  *(undefined4 *)*(undefined4 *)(param_1 + 0x24c) = *(undefined4 *)(param_1 + 0x24c);
  *(int *)(*(int *)(param_1 + 0x24c) + 4) = *(int *)(param_1 + 0x24c);
  if (*(int *)(*(int *)(param_1 + 0x120) + 0x40) < 1) {
    *(undefined1 *)(*(int *)(param_1 + 0x120) + 0x1f) = 1;
    return;
  }
  puVar7 = (undefined4 *)(iVar4 + 0x98);
  puVar10 = &stack0xffffffb8 + -iVar4;
  do {
    pcVar5 = (char *)(puVar7 + -0x1c);
    do {
      cVar1 = *pcVar5;
      pcVar5[(int)puVar10] = cVar1;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    FUN_00593634();
    iVar6 = _strncmp(local_20,&DAT_005d1560,4);
    if (iVar6 == 0) {
      *(int *)(param_1 + 0x214) = *(int *)(param_1 + 0x214) + 1;
      FUN_0056d6f0();
      puVar11 = *(undefined4 **)(param_1 + 0x22c);
      if (puVar11 == *(undefined4 **)(param_1 + 0x230)) {
        FUN_005027e0();
      }
      else {
        if (puVar11 != (undefined4 *)0x0) {
          puVar9 = puVar7;
          for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar11 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar11 = puVar11 + 1;
          }
        }
        *(int *)(param_1 + 0x22c) = *(int *)(param_1 + 0x22c) + 0x40;
      }
    }
    iVar6 = _strncmp(local_20,s_teama_005d1878,5);
    if (iVar6 == 0) {
      *(int *)(param_1 + 0x218) = *(int *)(param_1 + 0x218) + 1;
      FUN_0056d6f0();
      puVar11 = *(undefined4 **)(param_1 + 0x238);
      if (puVar11 == *(undefined4 **)(param_1 + 0x23c)) {
        FUN_005027e0();
      }
      else {
        if (puVar11 != (undefined4 *)0x0) {
          puVar9 = puVar7;
          for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar11 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar11 = puVar11 + 1;
          }
        }
        *(int *)(param_1 + 0x238) = *(int *)(param_1 + 0x238) + 0x40;
      }
    }
    iVar6 = _strncmp(local_20,s_teamb_005d1870,5);
    if (iVar6 == 0) {
      *(int *)(param_1 + 0x21c) = *(int *)(param_1 + 0x21c) + 1;
      FUN_0056d6f0();
      puVar11 = *(undefined4 **)(param_1 + 0x244);
      if (puVar11 == *(undefined4 **)(param_1 + 0x248)) {
        FUN_005027e0();
      }
      else {
        if (puVar11 != (undefined4 *)0x0) {
          puVar9 = puVar7;
          for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar11 = *puVar9;
            puVar9 = puVar9 + 1;
            puVar11 = puVar11 + 1;
          }
        }
        *(int *)(param_1 + 0x244) = *(int *)(param_1 + 0x244) + 0x40;
      }
    }
    local_28 = local_28 + 1;
    puVar10 = puVar10 + -0x2b0;
    puVar7 = puVar7 + 0xac;
  } while (local_28 < *(int *)(*(int *)(param_1 + 0x120) + 0x40));
  *(undefined1 *)(*(int *)(param_1 + 0x120) + 0x1f) = 1;
  return;
}

