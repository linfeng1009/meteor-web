/* Original Meteor.exe static export @ 0055aed0; original sample not executed. */
/* XREF 0055b239 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0055aed0(int param_1)

{
  int iVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  undefined4 uVar11;
  int iStack_24;
  int iStack_20;
  
  if (*(int *)(param_1 + 0x1678) != 0) {
    iVar3 = (*(code *)PTR_FUN_005d186c)(0x15,0,0);
    iVar4 = (*(code *)PTR_FUN_005d186c)(0x14,0,iVar3);
    iVar5 = (*(code *)PTR_FUN_005d186c)(0x16,0,iVar4);
    iVar6 = (*(code *)PTR_FUN_005d186c)(0x18,0,0);
    iStack_24 = param_1 + 0x500;
    iStack_20 = param_1 + 2000;
    if (iVar4 == 1) {
      iStack_24 = param_1 + 0x5f0;
      iStack_20 = param_1 + 0x8c0;
    }
    else if (iVar4 == 2) {
      iStack_24 = param_1 + 0x6e0;
      iStack_20 = param_1 + 0x9b0;
    }
    piVar10 = *(int **)(*(int *)(param_1 + 0x1678) + 0x24c);
    piVar7 = (int *)*piVar10;
    if (piVar7 != piVar10) {
      do {
        iVar1 = piVar7[2];
        iVar8 = FUN_005565c0();
        iVar9 = (*(code *)PTR_FUN_005d186c)(0x14,0,iVar8);
        if (iVar9 == iVar4) {
          if (iVar8 == iVar3) {
            uVar11 = *(undefined4 *)(param_1 + 0xab8);
          }
          else {
            if ((iVar8 != iVar5) && (iVar8 != iVar6)) {
              FUN_0055ae30(iVar1,iStack_24,*(undefined4 *)(param_1 + 0xac0));
              goto LAB_0055aff4;
            }
            uVar11 = *(undefined4 *)(param_1 + 0xabc);
          }
          FUN_0055acf0(iVar1,iStack_24,uVar11);
        }
LAB_0055aff4:
        piVar7 = (int *)*piVar7;
      } while (piVar7 != (int *)*(int *)(*(int *)(param_1 + 0x1678) + 0x24c));
    }
    piVar10 = (int *)**(int **)(param_1 + 0x167c);
    if (piVar10 != *(int **)(param_1 + 0x167c)) {
      do {
        iVar3 = piVar10[2];
        iVar5 = piVar10[3];
        fVar2 = (float)piVar10[4];
        iVar6 = FUN_00565830(iVar3);
        if (iVar6 != 0) {
          if (iVar5 == 0) {
            uVar11 = FUN_005565c0();
            iVar3 = (*(code *)PTR_FUN_005d186c)(0x14,0,uVar11);
            if (iVar3 == iVar4) {
              iVar3 = __ftol();
              fVar2 = fVar2 - (float)iVar3;
              if (((_DAT_005a83e4 < fVar2) && (fVar2 < _DAT_005a83f0)) ||
                 ((_DAT_005a83e8 < fVar2 && (fVar2 < _DAT_005a9b34)))) {
                FUN_0055ae30(iVar6,iStack_20,*(undefined4 *)(param_1 + 0xac4));
              }
            }
          }
          else if ((iVar5 == 1) && (iVar4 = (*(code *)PTR_FUN_005d186c)(0x14,0,iVar3), -1 < iVar4))
          {
            iVar3 = iVar4 * 0xf0 + param_1;
            iStack_20 = iVar3 + 2000;
            FUN_0055ae30(iVar6,iVar3 + 0x500,*(undefined4 *)(param_1 + 0xac0));
            iVar3 = __ftol();
            fVar2 = fVar2 - (float)iVar3;
            if (((_DAT_005a83e4 < fVar2) && (fVar2 < _DAT_005a83f0)) ||
               ((_DAT_005a83e8 < fVar2 && (fVar2 < _DAT_005a9b34)))) {
              FUN_0055ae30(iVar6,iStack_20,*(undefined4 *)(param_1 + 0xac4));
            }
          }
        }
        piVar10 = (int *)*piVar10;
      } while (piVar10 != (int *)*(int *)(param_1 + 0x167c));
    }
  }
  return;
}

