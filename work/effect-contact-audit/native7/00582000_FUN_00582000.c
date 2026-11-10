/* Original Meteor.exe static export @ 00582000; original sample not executed. */
/* XREF 00585d54 UNCONDITIONAL_CALL */
/* XREF 00587bb0 UNCONDITIONAL_CALL */
/* XREF 00588af3 UNCONDITIONAL_CALL */
/* XREF 0058a315 UNCONDITIONAL_CALL */
/* XREF 005b0e60 DATA */
/* XREF 005b1080 DATA */
/* XREF 00584e58 UNCONDITIONAL_CALL */
/* XREF 00585406 UNCONDITIONAL_CALL */
/* XREF 005881a9 UNCONDITIONAL_CALL */
/* XREF 00588ed8 UNCONDITIONAL_CALL */
/* XREF 005893e6 UNCONDITIONAL_CALL */
/* XREF 00589a49 UNCONDITIONAL_CALL */

void __fastcall FUN_00582000(undefined4 *param_1)

{
  int iVar1;
  void *pvVar2;
  
  if ((*(char *)(param_1[0x7b] + 0x28) != '\0') && (*(char *)(param_1[2] + 0x58) != '\0')) {
    iVar1 = *(int *)(param_1[0x7b] + 0x1fc);
    if (iVar1 != 0) {
      FUN_00507850(iVar1);
      *(undefined4 *)(param_1[0x7b] + 0x1fc) = 0;
    }
    pvVar2 = operator_new(0x4b0);
    *(void **)(param_1[0x7b] + 0x1fc) = pvVar2;
  }
  (**(code **)*param_1)(*(undefined4 *)(param_1[0x7b] + 0xc));
  FUN_0058e540();
  param_1[0x7e] = 0;
  param_1[0x7d] = 0;
  param_1[0x7c] = 0;
  param_1[0x81] = 0;
  param_1[0x80] = 0;
  param_1[0x7f] = 0;
  return;
}

