/* Original Meteor.exe static export @ 004e3d30; original sample not executed. */
/* XREF 005ab008 DATA */

int __thiscall FUN_004e3d30(int param_1,int *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = FUN_004dcf50(param_2);
  if (iVar2 != 99999) {
    piVar1 = *(int **)(param_1 + 0x44);
    piVar3 = *(int **)(param_1 + 0x40);
    if (piVar3 != piVar1) {
      do {
        if (*piVar3 == iVar2) break;
        piVar3 = piVar3 + 1;
      } while (piVar3 != piVar1);
      if (piVar3 != piVar1) {
        (**(code **)(*param_2 + 0xc))(0x2c,0,0);
      }
    }
  }
  return iVar2;
}

