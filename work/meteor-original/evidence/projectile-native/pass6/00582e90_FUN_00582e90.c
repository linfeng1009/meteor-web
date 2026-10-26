/* Original Meteor.exe static export @ 00582e90; original sample not executed. */
/* XREF 005b0e58 DATA */
/* XREF 005b0f68 DATA */
/* XREF 005b0ff0 DATA */
/* XREF 005b1078 DATA */
/* XREF 005b1188 DATA */
/* XREF 005b1210 DATA */
/* XREF 005b1320 DATA */
/* XREF 005b13a8 DATA */
/* XREF 005b1430 DATA */
/* XREF 00585f82 UNCONDITIONAL_CALL */
/* XREF 0058a3c8 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_00582e90(int *param_1,float param_2)

{
  int iVar1;
  
  iVar1 = param_1[0x7b];
  param_1[0xd] = (int)param_2;
  if (param_2 < *(float *)(iVar1 + 0x14)) {
    return 0;
  }
  if (*(float *)(iVar1 + 0x18) < param_2) {
    return 0;
  }
  (**(code **)(**(int **)(iVar1 + 0x10) + 0x24))(param_2);
  (**(code **)(*param_1 + 100))();
  iVar1 = *(int *)(param_1[0x7b] + 0x10);
  param_1[0xf] = *(int *)(iVar1 + 0x18);
  param_1[0x10] = *(int *)(iVar1 + 0x1c);
  param_1[0x11] = *(int *)(iVar1 + 0x20);
  iVar1 = *(int *)(param_1[0x7b] + 0x10);
  param_1[0x12] = *(int *)(iVar1 + 0x30);
  param_1[0x13] = *(int *)(iVar1 + 0x34);
  param_1[0x14] = *(int *)(iVar1 + 0x38);
  param_1[0x15] = *(int *)(iVar1 + 0x3c);
  (**(code **)(*param_1 + 0x20))();
  return 1;
}

