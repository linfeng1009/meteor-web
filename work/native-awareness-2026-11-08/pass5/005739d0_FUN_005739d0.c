/* Original Meteor.exe static export @ 005739d0; original sample not executed. */
/* XREF 00573fcc UNCONDITIONAL_CALL */
/* XREF 00573d1a UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_005739d0(int param_1)

{
  float *pfVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  undefined1 local_c [8];
  float local_4;
  
  if (*(int *)(param_1 + 0x2c) != 0) {
    pfVar1 = (float *)(param_1 + 0x84);
    iVar6 = 8;
    pfVar5 = pfVar1;
    do {
      pfVar4 = (float *)FUN_00476e80(local_c,pfVar5 + 0x28,param_1 + 0x184);
      *pfVar5 = *pfVar4;
      iVar6 = iVar6 + -1;
      pfVar5[1] = pfVar4[1];
      pfVar5[2] = pfVar4[2];
      pfVar5 = pfVar5 + 3;
    } while (iVar6 != 0);
    local_4 = *(float *)(param_1 + 0x8c) + *(float *)(param_1 + 0xd4);
    fVar2 = (*(float *)(param_1 + 0x88) + *(float *)(param_1 + 0xd0)) * _DAT_005a83e8;
    *(float *)(param_1 + 0x78) = (*pfVar1 + *(float *)(param_1 + 0xcc)) * _DAT_005a83e8;
    fVar3 = local_4 * _DAT_005a83e8;
    *(float *)(param_1 + 0x7c) = fVar2;
    *(float *)(param_1 + 0x80) = fVar3;
    local_30 = *(float *)(param_1 + 0x90) - *pfVar1;
    local_2c = *(float *)(param_1 + 0x94) - *(float *)(param_1 + 0x88);
    local_28 = *(float *)(param_1 + 0x98) - *(float *)(param_1 + 0x8c);
    FUN_0047ec40();
    local_24 = *(float *)(param_1 + 0xb4) - *pfVar1;
    local_20 = *(float *)(param_1 + 0xb8) - *(float *)(param_1 + 0x88);
    local_1c = *(float *)(param_1 + 0xbc) - *(float *)(param_1 + 0x8c);
    FUN_0047ec40();
    local_18 = *(float *)(param_1 + 0xa8) - *pfVar1;
    local_14 = *(float *)(param_1 + 0xac) - *(float *)(param_1 + 0x88);
    local_10 = *(float *)(param_1 + 0xb0) - *(float *)(param_1 + 0x8c);
    FUN_0047ec40();
    FUN_00477b90(0,&local_30);
    FUN_00477b90(1,&local_24);
    FUN_00477b90(2,&local_18);
    FUN_00477b90(3,(float *)(param_1 + 0x78));
  }
  return;
}

