/* Original Meteor.exe static export @ 00538530; original sample not executed. */
/* XREF 005391d5 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00538530(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  float *pfVar12;
  int iVar13;
  byte local_2a7;
  byte local_2a6;
  byte local_2a5;
  int local_2a4;
  int local_294 [33];
  int local_210 [33];
  int local_18c [33];
  int local_108 [33];
  float local_84 [33];
  
  uVar6 = 1;
  local_2a7 = 1;
  do {
    piVar11 = local_108;
    for (iVar5 = 0x21; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar11 = 0;
      piVar11 = piVar11 + 1;
    }
    piVar11 = local_294;
    for (iVar5 = 0x21; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar11 = 0;
      piVar11 = piVar11 + 1;
    }
    piVar11 = local_210;
    for (iVar5 = 0x21; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar11 = 0;
      piVar11 = piVar11 + 1;
    }
    piVar11 = local_18c;
    for (iVar5 = 0x21; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar11 = 0;
      piVar11 = piVar11 + 1;
    }
    pfVar12 = local_84;
    for (iVar5 = 0x21; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar12 = 0.0;
      pfVar12 = pfVar12 + 1;
    }
    local_2a5 = 1;
    do {
      iVar10 = 0;
      uVar7 = 1;
      iVar9 = 0;
      iVar13 = 0;
      local_2a4 = 0;
      local_2a6 = 1;
      iVar5 = 0;
      fVar2 = _DAT_005a83e4;
      do {
        uVar7 = uVar7 + ((uint)local_2a5 + uVar6 * 0x21) * 0x21;
        iVar4 = (uVar7 & 0xffff) * 4;
        iVar8 = (uVar7 - 0x441 & 0xffff) * 4;
        iVar10 = iVar10 + *(int *)(iVar4 + param_1);
        iVar13 = iVar13 + *(int *)(iVar4 + param_2);
        iVar9 = iVar9 + *(int *)(iVar4 + param_3);
        local_2a4 = local_2a4 + *(int *)(iVar4 + param_4);
        fVar2 = fVar2 + *(float *)(iVar4 + param_5);
        *(int *)((int)local_108 + iVar5 + 4) = *(int *)((int)local_108 + iVar5 + 4) + iVar10;
        *(int *)((int)local_294 + iVar5 + 4) = *(int *)((int)local_294 + iVar5 + 4) + iVar13;
        piVar11 = (int *)((int)local_210 + iVar5 + 4);
        *piVar11 = *piVar11 + iVar9;
        *(int *)((int)local_18c + iVar5 + 4) = *(int *)((int)local_18c + iVar5 + 4) + local_2a4;
        *(int *)(iVar4 + param_1) = *(int *)(iVar8 + param_1) + *(int *)((int)local_108 + iVar5 + 4)
        ;
        fVar3 = fVar2 + *(float *)((int)local_84 + iVar5 + 4);
        *(int *)(iVar4 + param_2) = *(int *)(iVar8 + param_2) + *(int *)((int)local_294 + iVar5 + 4)
        ;
        iVar1 = *(int *)(iVar8 + param_3);
        *(float *)((int)local_84 + iVar5 + 4) = fVar3;
        *(int *)(iVar4 + param_3) = iVar1 + *(int *)((int)local_210 + iVar5 + 4);
        *(int *)(iVar4 + param_4) = *(int *)(iVar8 + param_4) + *(int *)((int)local_18c + iVar5 + 4)
        ;
        *(float *)(iVar4 + param_5) = fVar3 + *(float *)(iVar8 + param_5);
        local_2a6 = local_2a6 + 1;
        uVar7 = (uint)local_2a6;
        iVar5 = iVar5 + 4;
      } while (local_2a6 < 0x21);
      local_2a5 = local_2a5 + 1;
    } while (local_2a5 < 0x21);
    local_2a7 = local_2a7 + 1;
    uVar6 = (uint)local_2a7;
  } while (local_2a7 < 0x21);
  return;
}

