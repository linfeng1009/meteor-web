/* Original Meteor.exe static export @ 004f2b10; original sample not executed. */
/* XREF 005aa150 DATA */
/* XREF 005ab5d8 DATA */
/* XREF 005aba18 DATA */
/* XREF 005ab398 DATA */

bool __thiscall FUN_004f2b10(int *param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int **ppiVar5;
  int *piStack_4;
  
  piStack_4 = param_1;
  iVar4 = FUN_00487830();
  piVar1 = *(int **)(iVar4 + 0x22ec);
  piVar3 = piVar1;
  piVar2 = (int *)piVar1[1];
  while (piVar2 != (int *)0x0) {
    if ((int *)piVar2[4] < param_2) {
      piVar2 = (int *)piVar2[3];
    }
    else {
      piVar3 = piVar2;
      piVar2 = (int *)piVar2[2];
    }
  }
  if ((piVar3 == piVar1) || (param_2 < (int *)piVar3[4])) {
    piStack_4 = piVar1;
    ppiVar5 = &piStack_4;
  }
  else {
    ppiVar5 = &param_2;
  }
  piVar1 = *ppiVar5;
  param_2 = piVar3;
  iVar4 = FUN_00487830();
  if (piVar1 == *(int **)(iVar4 + 0x22ec)) {
    return false;
  }
  iVar4 = (**(code **)(*param_1 + 0x134))();
  return (*(uint *)(iVar4 + 0x1f0) & piVar1[0x82]) == 0;
}

