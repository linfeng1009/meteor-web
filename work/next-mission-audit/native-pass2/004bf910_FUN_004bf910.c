/* Original Meteor.exe static export @ 004bf910; original sample not executed. */
/* XREF 0049377d UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_004bf910(int param_1,int param_2,char *param_3,int param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  uint uVar12;
  char *pcVar13;
  char *pcVar14;
  undefined1 local_c [12];
  
  if ((param_2 != 0) && (param_3 != (char *)0x0)) {
    FUN_004ff200();
    *(int *)(param_1 + 0x508) = param_2;
    FUN_004f8340(param_1);
    uVar11 = 0xffffffff;
    piVar10 = (int *)(param_1 + 0x50c);
    pcVar14 = param_3;
    do {
      if (uVar11 == 0) break;
      uVar11 = uVar11 - 1;
      cVar4 = *pcVar14;
      pcVar14 = pcVar14 + 1;
    } while (cVar4 != '\0');
    pcVar14 = (char *)*piVar10;
    uVar12 = *(int *)(param_1 + 0x510) - (int)pcVar14;
    uVar5 = (int)(param_3 + (~uVar11 - 1)) - (int)param_3;
    if (uVar12 < uVar5) {
      pcVar13 = param_3;
      for (uVar5 = uVar12 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)pcVar13;
        pcVar13 = pcVar13 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar12 = uVar12 & 3; uVar12 != 0; uVar12 = uVar12 - 1) {
        *pcVar14 = *pcVar13;
        pcVar13 = pcVar13 + 1;
        pcVar14 = pcVar14 + 1;
      }
      FUN_00403490(param_3 + (*(int *)(param_1 + 0x510) - *piVar10),param_3 + (~uVar11 - 1));
    }
    else {
      for (uVar11 = uVar5 >> 2; uVar11 != 0; uVar11 = uVar11 - 1) {
        *(undefined4 *)pcVar14 = *(undefined4 *)param_3;
        param_3 = param_3 + 4;
        pcVar14 = pcVar14 + 4;
      }
      for (uVar11 = uVar5 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
        *pcVar14 = *param_3;
        param_3 = param_3 + 1;
        pcVar14 = pcVar14 + 1;
      }
      FUN_00402b30(*piVar10 + uVar5,*(undefined4 *)(param_1 + 0x510));
    }
    puVar6 = (undefined4 *)FUN_0056d7a0(local_c);
    *(undefined4 *)(param_1 + 0x4dc) = *puVar6;
    *(undefined4 *)(param_1 + 0x4e0) = puVar6[1];
    *(undefined4 *)(param_1 + 0x4e4) = puVar6[2];
    puVar6 = (undefined4 *)FUN_0056d7d0(local_c);
    *(undefined4 *)(param_1 + 0x4e8) = *puVar6;
    *(undefined4 *)(param_1 + 0x4ec) = puVar6[1];
    *(undefined4 *)(param_1 + 0x4f0) = puVar6[2];
    iVar7 = __ftol();
    fVar1 = *(float *)(param_1 + 0x4ec);
    fVar2 = *(float *)(param_1 + 0x4e0);
    *(int *)(param_1 + 0x4f4) = iVar7;
    iVar8 = __ftol();
    *(int *)(param_1 + 0x4f8) = iVar8;
    if (10 < iVar7) {
      *(undefined4 *)(param_1 + 0x4f4) = 10;
    }
    if (10 < iVar8) {
      *(undefined4 *)(param_1 + 0x4f8) = 10;
    }
    iVar7 = __ftol();
    *(int *)(param_1 + 0x4d4) = iVar7;
    iVar8 = __ftol();
    *(int *)(param_1 + 0x4d8) = iVar8;
    if ((0 < iVar7) && (0 < iVar8)) {
      FUN_004c41a0(0x14);
      iVar7 = *(int *)(param_1 + 0x10);
      iVar8 = *(int *)(param_1 + 0x14);
      iVar9 = FUN_004c61e0(iVar8,iVar8,iVar7,fVar1 - fVar2,0);
      iVar3 = *(int *)(param_1 + 0x14);
      for (; iVar9 != iVar3; iVar9 = iVar9 + 0x1c) {
        FUN_004c68f0(0);
      }
      iVar8 = iVar8 - iVar7;
      iVar8 = (int)((ulonglong)((longlong)iVar8 * 0x6db6db6d) >> 0x20) - iVar8;
      *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + ((iVar8 >> 4) - (iVar8 >> 0x1f)) * 0x1c;
      *(undefined4 *)(param_1 + 0x1c) = 0;
      *(undefined4 *)(param_1 + 0x20) = 0;
      if (param_4 == 0) {
        iVar8 = *(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518);
        uVar11 = 0;
        iVar7 = iVar8 >> 0x1f;
        if (iVar8 / 0x124 + iVar7 != iVar7) {
          do {
            FUN_004fb730();
            uVar11 = uVar11 + 1;
          } while (uVar11 < (uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124))
          ;
        }
        cVar4 = FUN_004bf650(*piVar10);
        if ((cVar4 != '\0') &&
           (piVar10 = (int *)FUN_005715d0(s_OnStart_005c9b10), piVar10 != (int *)0x0)) {
          (**(code **)(*piVar10 + 4))();
        }
      }
      else {
        cVar4 = FUN_004c2de0();
        if (cVar4 == '\0') {
          FUN_00553800(s_Load__s_wp_error_005c9afc,*piVar10);
          return 0;
        }
        cVar4 = FUN_004bfc00(param_4);
        if (cVar4 == '\0') {
          FUN_00553800(s_Load_NPC__s_pst_error_005c9b18,param_4);
          return 1;
        }
      }
      return 1;
    }
  }
  return 0;
}

