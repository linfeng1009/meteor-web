/* Original Meteor.exe static export @ 00565830; original sample not executed. */
/* XREF 0055b046 UNCONDITIONAL_CALL */

int __thiscall FUN_00565830(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = (int *)**(int **)(param_1 + 0x24c);
  if (piVar3 != *(int **)(param_1 + 0x24c)) {
    do {
      iVar1 = piVar3[2];
      iVar2 = FUN_005565c0();
      if (iVar2 == param_2) {
        return iVar1;
      }
      piVar3 = (int *)*piVar3;
    } while (piVar3 != (int *)*(int *)(param_1 + 0x24c));
  }
  return 0;
}

