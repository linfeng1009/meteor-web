/* Original Meteor.exe static export @ 00492a00; original sample not executed. */
/* XREF 005a91d4 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00492a00(int *param_1,undefined4 param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  float10 fVar4;
  
  (**(code **)(*param_1 + 0x240))(param_2);
  piVar2 = *(int **)param_1[0x84a];
  if (piVar2 != (int *)param_1[0x84a]) {
    do {
      if (piVar2[2] == 0) {
LAB_00492a4a:
        piVar1 = (int *)piVar2[1];
        piVar3 = (int *)*piVar2;
        *piVar1 = (int)piVar3;
        piVar3[1] = (int)piVar1;
        FUN_00402e90(piVar2,0xc);
      }
      else {
        fVar4 = (float10)FUN_00549b00();
        piVar1 = (int *)piVar2[2];
        if ((float10)_DAT_005a9500 < fVar4) {
          if (piVar1 != (int *)0x0) {
            (**(code **)*piVar1)(1);
          }
          goto LAB_00492a4a;
        }
        (**(code **)(*piVar1 + 4))(param_2);
        piVar3 = (int *)*piVar2;
      }
      piVar2 = piVar3;
    } while (piVar3 != (int *)param_1[0x84a]);
  }
  return;
}

