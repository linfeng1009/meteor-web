/* Original Meteor.exe static export @ 004f1920; original sample not executed. */
/* XREF 005aa048 DATA */
/* XREF 005ab4d0 DATA */
/* XREF 005ab910 DATA */
/* XREF 005ab290 DATA */

undefined4 __fastcall FUN_004f1920(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  piVar1 = (int *)FUN_00487830();
  iVar3 = *piVar1;
  uVar2 = (**(code **)(*param_1 + 0x4c))();
  iVar3 = (**(code **)(iVar3 + 0x14c))(uVar2);
  if ((iVar3 != 0) && (*(char *)(iVar3 + 0x210) == '\x02')) {
    return 1;
  }
  return 0;
}

