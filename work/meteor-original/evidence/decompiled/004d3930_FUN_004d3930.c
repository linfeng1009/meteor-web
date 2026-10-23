/* Meteor.exe original x86 @ 004d3930 */
/* Caller: 004d298a */

int FUN_004d3930(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  
  iVar7 = (param_2 - param_1) / 0x48;
  iVar6 = param_3;
  if (0 < iVar7) {
    iVar3 = param_3 - param_1;
    iVar6 = param_3 + iVar7 * 0x48;
    piVar9 = (int *)(param_3 + 0x3c);
    piVar8 = (int *)(param_1 + 0x40);
    param_1 = iVar7;
    do {
      if (piVar8 + -0xf != piVar9 + -0xe) {
        FUN_00403200(piVar8[-0xf],piVar8[-0xe]);
      }
      if (piVar8 + -0xc != piVar9 + -0xb) {
        FUN_00403200(piVar8[-0xc],piVar8[-0xb]);
      }
      if (piVar8 + -9 != piVar9 + -8) {
        FUN_00403200(piVar8[-9],piVar8[-8]);
      }
      piVar9[-5] = piVar8[-6];
      piVar9[-4] = piVar8[-5];
      FUN_004d4000(piVar8 + -4);
      if (piVar8 + -1 != piVar9) {
        iVar7 = *piVar8;
        iVar5 = piVar8[-1];
        iVar4 = *piVar9;
        uVar1 = (iVar7 - iVar5) / 0x28;
        if ((uint)((piVar9[2] - iVar4) / 0x28) < uVar1) {
          iVar4 = FUN_004d4180(uVar1,iVar5,iVar7);
          iVar5 = *(int *)(iVar3 + (int)piVar8);
          for (iVar7 = *piVar9; iVar7 != iVar5; iVar7 = iVar7 + 0x28) {
            FUN_004d4a40(iVar7);
          }
          iVar7 = (piVar9[2] - *piVar9) / 0x28;
          if (iVar7 != 0) {
            FUN_00402e90(*piVar9,iVar7 * 0x28);
          }
          *piVar9 = iVar4;
          piVar9[2] = iVar4 + uVar1 * 0x28;
        }
        else {
          uVar2 = (*(int *)(iVar3 + (int)piVar8) - iVar4) / 0x28;
          if (uVar2 < uVar1) {
            FUN_004d4840(iVar5,iVar5 + uVar2 * 0x28,iVar4,iVar3,0);
            FUN_0049fe20(piVar8[-1] + ((*(int *)(iVar3 + (int)piVar8) - *piVar9) / 0x28) * 0x28,
                         *piVar8,*(int *)(iVar3 + (int)piVar8),iVar3);
          }
          else {
            iVar5 = FUN_004d4840(iVar5,iVar7,iVar4,iVar3,0);
            iVar7 = *(int *)(iVar3 + (int)piVar8);
            for (; iVar5 != iVar7; iVar5 = iVar5 + 0x28) {
              FUN_004d4a40(iVar5);
            }
          }
        }
        piVar9[1] = *piVar9 + uVar1 * 0x28;
      }
      piVar8 = piVar8 + 0x12;
      piVar9 = piVar9 + 0x12;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
  }
  return iVar6;
}

