/* Original Meteor.exe static export @ 00503970; original sample not executed. */
/* XREF 004f9006 DATA */
/* XREF 004fb94e DATA */

void __fastcall FUN_00503970(int param_1)

{
  char cVar1;
  int iVar2;
  
  *(undefined4 *)(param_1 + 0x80) = 0x3ecccccd;
  iVar2 = _rand();
  if (iVar2 % 100 < (int)*(short *)(*(int *)(param_1 + 0x10) + 10)) {
    FUN_00500c60(0);
    iVar2 = _rand();
    *(float *)(param_1 + 0xe0) = (float)(iVar2 % 0x168);
  }
  cVar1 = FUN_004fdd70();
  if (cVar1 == '\0') {
    cVar1 = FUN_004fdf90(0x44fa0000);
    if (cVar1 == '\0') {
      FUN_004fdf00();
      return;
    }
  }
  return;
}

