/* Original Meteor.exe static export @ 005818f0; original sample not executed. */
/* XREF 0056f29d UNCONDITIONAL_CALL */
/* XREF 0056f214 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_005818f0(int param_1,float *param_2,undefined4 *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined1 local_80 [64];
  undefined1 local_40 [64];
  
  FUN_00477200();
  iVar7 = *(int *)(*(int *)(param_1 + 0x1ec) + 0x10);
  fVar3 = *(float *)(iVar7 + 0x24);
  fVar4 = *(float *)(iVar7 + 0x28);
  fVar5 = *(float *)(iVar7 + 0x2c);
  FUN_00477db0(_DAT_005a83f4 / fVar3,_DAT_005a83f4 / fVar4,_DAT_005a83f4 / fVar5);
  fVar1 = *(float *)(param_1 + 0x1f8);
  fVar2 = *(float *)(param_1 + 500);
  *param_2 = fVar3 * *(float *)(param_1 + 0x1f0);
  param_2[1] = fVar4 * fVar2;
  param_2[2] = fVar5 * fVar1;
  puVar6 = (undefined4 *)FUN_00476f00(local_40,local_80,param_1 + 0x208);
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *param_3 = *puVar6;
    puVar6 = puVar6 + 1;
    param_3 = param_3 + 1;
  }
  return;
}

