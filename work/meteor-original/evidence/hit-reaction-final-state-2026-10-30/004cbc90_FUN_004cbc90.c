/* Original Meteor.exe static export @ 004cbc90; original sample not executed. */
/* XREF 005aa6d0 DATA */

void __thiscall FUN_004cbc90(int *param_1,undefined1 param_2)

{
  int *piVar1;
  undefined4 unaff_retaddr;
  int **ppiVar2;
  int *piStack_4;
  
  if (param_1[0xf1] == 0) {
    piStack_4 = param_1;
    piVar1 = (int *)FUN_00487830();
    ppiVar2 = &piStack_4;
    (**(code **)(*piVar1 + 0x2e8))(param_2,ppiVar2);
    (**(code **)(*param_1 + 0x1a4))(ppiVar2,unaff_retaddr);
  }
  return;
}

