/* Original Meteor.exe static export @ 00570630; original sample not executed. */
/* XREF 0056b4d4 UNCONDITIONAL_CALL */
/* XREF 0057f1f4 UNCONDITIONAL_CALL */
/* XREF 0055dc5f UNCONDITIONAL_CALL */
/* XREF 0055dcf8 UNCONDITIONAL_CALL */
/* XREF 0055dd84 UNCONDITIONAL_CALL */
/* XREF 0056f2b2 UNCONDITIONAL_CALL */
/* XREF 00564bfc UNCONDITIONAL_CALL */
/* XREF 00564d03 UNCONDITIONAL_CALL */
/* XREF 0055d9ab UNCONDITIONAL_CALL */
/* XREF 0055d9eb UNCONDITIONAL_CALL */

void FUN_00570630(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined1 local_60 [12];
  undefined1 local_54 [12];
  undefined1 local_48 [36];
  undefined1 local_24 [36];
  
  FUN_00477d30(3,local_54);
  FUN_00477d30(3,local_60);
  iVar2 = 0;
  iVar1 = 0;
  do {
    FUN_00477d30(iVar2,local_24 + iVar1);
    FUN_00477d30(iVar2,local_48 + iVar1);
    iVar1 = iVar1 + 0xc;
    iVar2 = iVar2 + 1;
  } while (iVar1 < 0x24);
  FUN_005706c0(param_1,local_54,local_24,param_3,local_60,local_48);
  return;
}

