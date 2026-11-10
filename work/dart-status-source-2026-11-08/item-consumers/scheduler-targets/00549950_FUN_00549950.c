/* Original Meteor.exe static export @ 00549950; original sample not executed. */
/* XREF 004ed3c9 UNCONDITIONAL_CALL */
/* XREF 004ed414 UNCONDITIONAL_CALL */
/* XREF 0048593d UNCONDITIONAL_CALL */
/* XREF 0048770f UNCONDITIONAL_CALL */
/* XREF 00487720 UNCONDITIONAL_CALL */
/* XREF 00487752 UNCONDITIONAL_CALL */
/* XREF 004b8368 UNCONDITIONAL_CALL */
/* XREF 004b9812 UNCONDITIONAL_CALL */
/* XREF 004abe98 UNCONDITIONAL_CALL */
/* XREF 004abebf UNCONDITIONAL_CALL */
/* XREF 004abeec UNCONDITIONAL_CALL */
/* XREF 004abf07 UNCONDITIONAL_CALL */
/* XREF 004abf18 UNCONDITIONAL_CALL */
/* XREF 004abf33 UNCONDITIONAL_CALL */
/* XREF 004ecb57 UNCONDITIONAL_CALL */
/* XREF 004e7e55 UNCONDITIONAL_CALL */
/* XREF 004accbc UNCONDITIONAL_CALL */
/* XREF 0048844a UNCONDITIONAL_CALL */
/* XREF 00488908 UNCONDITIONAL_CALL */
/* XREF 00488930 UNCONDITIONAL_CALL */
/* XREF 004a0668 UNCONDITIONAL_CALL */
/* XREF 004e7df1 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_00549950(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined8 uVar1;
  
  if (_DAT_005a84b8 < (double)CONCAT44(param_3,param_2)) {
    *(undefined4 *)(param_1 + 8) = param_2;
    *(undefined4 *)(param_1 + 0xc) = param_3;
  }
  *(double *)(param_1 + 0x10) = (double)*(longlong *)(param_1 + 0x38) / *(double *)(param_1 + 8);
  uVar1 = __ftol();
  *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x20) + (uint)uVar1;
  *(uint *)(param_1 + 0x2c) =
       *(int *)(param_1 + 0x24) + (int)((ulonglong)uVar1 >> 0x20) +
       (uint)CARRY4(*(uint *)(param_1 + 0x20),(uint)uVar1);
  return;
}

