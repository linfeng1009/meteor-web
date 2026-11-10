/* Original Meteor.exe static export @ 00573140; original sample not executed. */
/* XREF 00558aef UNCONDITIONAL_CALL */
/* XREF 00558b41 UNCONDITIONAL_CALL */
/* XREF 00573484 UNCONDITIONAL_CALL */

void __fastcall FUN_00573140(int param_1)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  float local_14c;
  float local_148;
  float local_144;
  float local_140;
  float local_13c;
  float local_138;
  float local_134;
  float local_130;
  float local_12c;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined1 local_100 [64];
  undefined1 local_c0 [64];
  undefined4 local_80 [16];
  undefined1 local_40 [64];
  
  iVar3 = *(int *)(param_1 + 0x20);
  if (*(int *)(iVar3 + 0x28) != 0) {
    if (*(int *)(iVar3 + 900) == param_1) {
      puVar1 = (undefined4 *)(iVar3 + 0x16c);
      puVar4 = (undefined4 *)(param_1 + 0x3c);
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
      puVar1 = (undefined4 *)FUN_00572db0(*(undefined4 *)(iVar3 + 0x110));
      FUN_00477200();
      FUN_004781d0(puVar1[4],puVar1[5],puVar1[6],0);
      local_140 = (float)*puVar1;
      local_144 = (float)puVar1[3];
      local_148 = (float)puVar1[2];
      local_14c = (float)puVar1[1];
      FUN_00478670(local_14c,local_148,local_144,local_140);
      pfVar2 = (float *)FUN_00572db0(*(undefined4 *)(*(int *)(param_1 + 0x20) + 0x114));
      FUN_00477200();
      FUN_004781d0(pfVar2[4],pfVar2[5],pfVar2[6],0);
      local_140 = *pfVar2;
      local_144 = pfVar2[3];
      local_148 = pfVar2[2];
      local_14c = pfVar2[1];
      FUN_00478670(local_14c,local_148,local_144,local_140);
      FUN_00477b10();
      puVar1 = (undefined4 *)FUN_00476f00(local_40,local_c0,local_100);
      iVar3 = *(int *)(param_1 + 0x20);
      puVar4 = local_80;
      for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
      local_124 = *(float *)(iVar3 + 0x108) * *(float *)(iVar3 + 0x38);
      FUN_004787f0(&local_14c);
      local_140 = local_140 * local_124;
      iVar3 = *(int *)(param_1 + 0x20);
      *(float *)(iVar3 + 0x310) = local_14c;
      *(float *)(iVar3 + 0x314) = local_148;
      *(float *)(iVar3 + 0x318) = local_144;
      *(float *)(iVar3 + 0x31c) = local_140;
      iVar3 = *(int *)(param_1 + 0x20);
      *(undefined4 *)(iVar3 + 0x30c) = 0;
      *(undefined4 *)(iVar3 + 0x308) = 0;
      *(undefined4 *)(iVar3 + 0x304) = 0;
      iVar3 = FUN_0055c4f0(*(undefined4 *)(*(int *)(param_1 + 0x20) + 0x110));
      iVar5 = FUN_0055c4f0(*(undefined4 *)(*(int *)(param_1 + 0x20) + 0x114));
      if ((((iVar3 != 0) && (iVar5 != 0)) && (*(short *)(iVar3 + 2) == *(short *)(iVar5 + 2))) &&
         (*(int *)(*(int *)(param_1 + 0x20) + 0x110) < *(int *)(*(int *)(param_1 + 0x20) + 0x114)))
      {
        FUN_00477d30(3,&local_130);
        local_13c = local_130 * local_124;
        local_138 = local_12c * local_124;
        local_134 = local_128 * local_124;
        local_130 = local_13c;
        local_12c = local_138;
        local_128 = local_134;
        FUN_00477d30(3,&local_120);
        pfVar2 = (float *)FUN_00476e80(&local_110,&local_130,*(int *)(param_1 + 0x20) + 0x16c);
        local_13c = *pfVar2 - local_120;
        iVar3 = *(int *)(param_1 + 0x20);
        local_138 = pfVar2[1] - local_11c;
        local_134 = pfVar2[2] - local_118;
        *(float *)(iVar3 + 0x304) = local_13c;
        *(float *)(iVar3 + 0x308) = local_138;
        *(float *)(iVar3 + 0x30c) = local_134;
        FUN_004781d0(local_130,local_12c,local_128,0);
      }
      FUN_00478670(local_14c,local_148,local_144,local_140);
      FUN_00477220();
    }
    else {
      if (*(int *)(param_1 + 0x24) == 2) {
        iVar3 = FUN_00556670(*(undefined4 *)(param_1 + 0x28));
        puVar1 = (undefined4 *)(iVar3 + 0x184);
      }
      else if (*(int *)(param_1 + 0x24) == 3) {
        FUN_005566a0(*(undefined4 *)(param_1 + 0x28));
        FUN_00573140();
        iVar3 = FUN_005566a0(*(undefined4 *)(param_1 + 0x28));
        puVar1 = (undefined4 *)(iVar3 + 0x3c);
      }
      else {
        puVar1 = (undefined4 *)(iVar3 + 0x16c);
      }
      puVar4 = (undefined4 *)(param_1 + 0x3c);
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
      iVar3 = *(int *)(param_1 + 0x20);
      puVar1 = (undefined4 *)FUN_00572db0(*(undefined4 *)(iVar3 + 0x110));
      pfVar2 = (float *)FUN_00572db0(*(undefined4 *)(iVar3 + 0x114));
      local_118 = (float)puVar1[6];
      local_134 = *(float *)(*(int *)(param_1 + 0x20) + 0x118);
      local_13c = (pfVar2[4] - (float)puVar1[4]) * local_134;
      local_138 = (pfVar2[5] - (float)puVar1[5]) * local_134;
      local_134 = (pfVar2[6] - local_118) * local_134;
      local_130 = local_13c + (float)puVar1[4];
      local_12c = (float)puVar1[5] + local_138;
      local_128 = local_118 + local_134;
      FUN_004781d0(local_130,local_12c,local_128,0);
      local_104 = *puVar1;
      local_108 = puVar1[3];
      local_10c = puVar1[2];
      local_110 = puVar1[1];
      local_140 = *pfVar2;
      local_144 = pfVar2[3];
      local_148 = pfVar2[2];
      local_14c = pfVar2[1];
      puVar1 = (undefined4 *)
               FUN_0047ee00(&local_120,&local_110,&local_14c,
                            *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x118));
      FUN_00478670(*puVar1,puVar1[1],puVar1[2],puVar1[3]);
    }
    if (*(int *)(param_1 + 0xa8) != 0) {
      puVar4 = (undefined4 *)FUN_0047b740();
      puVar1 = (undefined4 *)(param_1 + 0x3c);
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
      FUN_0047b750();
      FUN_005724f0();
    }
  }
  return;
}

