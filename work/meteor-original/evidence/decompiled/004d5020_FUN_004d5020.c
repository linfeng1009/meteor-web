/* Meteor.exe original x86 @ 004d5020; function boundary recovered from direct vtable/code reference */
/* Caller: 005a9494 */

int __thiscall FUN_004d5020(int *param_1,float param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  undefined4 *puVar4;
  float fVar5;
  float fVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  uint uVar11;
  int iStack_18;
  
  piVar9 = *(int **)param_1[0x14];
  iStack_18 = 0;
  if (piVar9 == (int *)param_1[0x14]) {
    return 0;
  }
  do {
    piVar1 = piVar9 + 2;
    for (piVar10 = (int *)piVar9[0xe]; (piVar10 != (int *)piVar9[0xf] && (*piVar10 != 2));
        piVar10 = piVar10 + 3) {
    }
    uVar11 = -(uint)(piVar10 != (int *)piVar9[0xf]) & (uint)piVar10;
    for (piVar10 = (int *)piVar9[0xe]; (piVar10 != (int *)piVar9[0xf] && (*piVar10 != 8));
        piVar10 = piVar10 + 3) {
    }
    uVar7 = -(uint)(piVar10 != (int *)piVar9[0xf]) & (uint)piVar10;
    if (uVar11 == 0) {
      if (param_3 != 0) {
        if (*(int *)(param_3 + 4) == *(int *)(param_3 + 8)) {
          FUN_004d3690(*(int *)(param_3 + 4),piVar1);
        }
        else {
          FUN_004d6e60();
          *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 0x48;
        }
      }
      puVar4 = (undefined4 *)piVar9[1];
      piVar10 = (int *)*piVar9;
      *puVar4 = piVar10;
      piVar10[1] = (int)puVar4;
      (**(code **)*piVar1)(0);
LAB_004d516c:
      FUN_00402e90(piVar9,0x50);
    }
    else {
      if (uVar7 != 0) {
        uVar2 = *(uint *)(uVar11 + 4);
        fVar5 = (float)*(uint *)(uVar7 + 4) * param_2;
        fVar6 = (float)uVar2;
        if (fVar6 < fVar5 != (fVar6 == fVar5)) {
          if (param_3 != 0) {
            if (*(int *)(param_3 + 4) == *(int *)(param_3 + 8)) {
              FUN_004d3690(*(int *)(param_3 + 4),piVar1);
            }
            else {
              FUN_004d6e60();
              *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 0x48;
            }
          }
          piVar3 = (int *)piVar9[1];
          piVar10 = (int *)*piVar9;
          *piVar3 = (int)piVar10;
          piVar10[1] = (int)piVar3;
          (**(code **)*piVar1)(0);
          goto LAB_004d516c;
        }
        iVar8 = __ftol();
        *(uint *)(uVar11 + 4) = uVar2 - iVar8;
        iVar8 = (**(code **)(*param_1 + 0x4c))(param_2,piVar1,param_4);
        if (iVar8 != 0) {
          iStack_18 = iStack_18 + 1;
        }
      }
      piVar10 = (int *)*piVar9;
    }
    piVar9 = piVar10;
    if (piVar10 == (int *)param_1[0x14]) {
      return iStack_18;
    }
  } while( true );
}

