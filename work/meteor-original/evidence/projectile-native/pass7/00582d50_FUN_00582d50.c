/* Original Meteor.exe static export @ 00582d50; original sample not executed. */
/* XREF 005b0e44 DATA */
/* XREF 005b0ecc DATA */
/* XREF 005b1064 DATA */
/* XREF 0058738c UNCONDITIONAL_CALL */
/* XREF 00587f89 UNCONDITIONAL_CALL */
/* XREF 00588699 UNCONDITIONAL_CALL */
/* XREF 00588d69 UNCONDITIONAL_CALL */
/* XREF 005892b9 UNCONDITIONAL_CALL */
/* XREF 00589649 UNCONDITIONAL_CALL */
/* XREF 00589e09 UNCONDITIONAL_CALL */
/* XREF 0058a4d9 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_00582d50(int *param_1,undefined4 param_2)

{
  void *pvVar1;
  
  FUN_0058a620(param_1 + 9,param_2);
  FUN_0050a118(param_1[0x7b] + 8,4,1,param_2);
  FUN_0050a118(param_1[0x7b] + 0xc,4,1,param_2);
  FUN_0050a118(param_1[0x7b] + 4,4,1,param_2);
  FUN_0050a118(param_1[0x7b] + 0x24,4,1,param_2);
  FUN_0058a560(param_1[0x7b] + 0xf4,param_2);
  FUN_0058a560(param_1[0x7b] + 0x100,param_2);
  (**(code **)(*(int *)(param_1[0x7b] + 0x38) + 4))(param_2);
  (**(code **)(*param_1 + 8))(param_2);
  if (*(int *)(param_1[0x7b] + 0x30) != 0) {
    FUN_00507850(*(int *)(param_1[0x7b] + 0x30));
    *(undefined4 *)(param_1[0x7b] + 0x30) = 0;
  }
  FUN_0050a118(param_1[0x7b] + 0x2c,4,1,param_2);
  if (*(uint *)(param_1[0x7b] + 0x2c) != 0) {
    pvVar1 = operator_new(*(uint *)(param_1[0x7b] + 0x2c));
    *(void **)(param_1[0x7b] + 0x30) = pvVar1;
    FUN_0050a118(*(undefined4 *)(param_1[0x7b] + 0x30),1,*(undefined4 *)(param_1[0x7b] + 0x2c),
                 param_2);
  }
  return 1;
}

