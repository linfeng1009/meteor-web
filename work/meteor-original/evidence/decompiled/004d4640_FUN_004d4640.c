/* Meteor.exe original x86 @ 004d4640 */
/* Caller: 004d3731 */

int FUN_004d4640(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  
  param_1 = (param_2 - param_1) / 0x48;
  iVar6 = param_3;
  if (0 < param_1) {
    iVar6 = param_3 + param_1 * -0x48;
    piVar7 = (int *)(param_3 + 0x40);
    piVar9 = (int *)(param_2 + 0x40);
    do {
      piVar10 = piVar9 + -0x12;
      piVar8 = piVar7 + -0x12;
      if (piVar9 + -0x21 != piVar7 + -0x21) {
        FUN_00403200(piVar9[-0x21],piVar9[-0x20]);
      }
      if (piVar9 + -0x1e != piVar7 + -0x1e) {
        FUN_00403200(piVar9[-0x1e],piVar9[-0x1d]);
      }
      if (piVar9 + -0x1b != piVar7 + -0x1b) {
        FUN_00403200(piVar9[-0x1b],piVar9[-0x1a]);
      }
      piVar7[-0x18] = piVar9[-0x18];
      piVar7[-0x17] = piVar9[-0x17];
      FUN_004d4000(piVar9 + -0x16);
      if (piVar9 + -0x13 != piVar7 + -0x13) {
        iVar2 = piVar9[-0x13];
        uVar3 = (*piVar10 - iVar2) / 0x28;
        iVar5 = piVar7[-0x13];
        piVar1 = piVar7 + -0x13;
        if ((uint)((piVar7[-0x11] - iVar5) / 0x28) < uVar3) {
          iVar5 = FUN_004d4180(uVar3,iVar2,*piVar10);
          iVar2 = (piVar7[-0x11] - *piVar1) / 0x28;
          if (iVar2 != 0) {
            FUN_00402e90(*piVar1,iVar2 * 0x28);
          }
          *piVar1 = iVar5;
          piVar7[-0x11] = iVar5 + uVar3 * 0x28;
        }
        else {
          uVar4 = (*piVar8 - iVar5) / 0x28;
          if (uVar4 < uVar3) {
            FUN_004d4840(iVar2,iVar2 + uVar4 * 0x28,iVar5,iVar6,0);
            FUN_0049fe20(piVar9[-0x13] + ((*piVar8 - *piVar1) / 0x28) * 0x28,*piVar10,*piVar8,iVar6)
            ;
          }
          else {
            FUN_004d4840(iVar2,*piVar10,iVar5,iVar6,0);
          }
        }
        *piVar8 = *piVar1 + uVar3 * 0x28;
      }
      param_1 = param_1 + -1;
      piVar7 = piVar8;
      piVar9 = piVar10;
    } while (param_1 != 0);
  }
  return iVar6;
}

