/* Original Meteor.exe static export @ 0058e150; original sample not executed. */
/* XREF 00581b01 UNCONDITIONAL_CALL */
/* XREF 00581b51 UNCONDITIONAL_CALL */
/* XREF 00582612 UNCONDITIONAL_CALL */
/* XREF 00582bbd UNCONDITIONAL_CALL */
/* XREF 00580fd5 UNCONDITIONAL_CALL */
/* XREF 00588a24 UNCONDITIONAL_CALL */
/* XREF 00588a56 UNCONDITIONAL_CALL */

void __thiscall FUN_0058e150(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  *param_1 = &PTR_LAB_005b24f8;
  DAT_0072c180 = DAT_0072c180 + 1;
  param_1[0x18] = 0x40a00000;
  param_1[0x19] = 0x40a00000;
  param_1[1] = 0xffffffff;
  param_1[3] = 0xbf800000;
  param_1[2] = 0xbf800000;
  param_1[4] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[8] = 0;
  param_1[0xb] = 0;
  param_1[10] = 0;
  param_1[9] = 0;
  param_1[0xc] = 0;
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0x3f800000;
  param_1[0x12] = 0x3f800000;
  param_1[0x11] = 0x3f800000;
  param_1[0x10] = 0x3f800000;
  param_1[5] = param_2;
  if (param_2 != 0) {
    iVar1 = *(int *)(param_2 + 0x1ec);
    param_1[0x13] = *(undefined4 *)(iVar1 + 0x80);
    param_1[0x14] = *(undefined4 *)(iVar1 + 0x84);
    param_1[0x15] = *(undefined4 *)(iVar1 + 0x88);
    param_1[0x16] = *(undefined4 *)(iVar1 + 0xb8);
    param_1[0x17] = *(undefined4 *)(iVar1 + 0xbc);
  }
  return;
}

