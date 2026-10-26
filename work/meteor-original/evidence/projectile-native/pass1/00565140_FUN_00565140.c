/* Original Meteor.exe static export @ 00565140; original sample not executed. */
/* XREF 005626f8 UNCONDITIONAL_CALL */
/* XREF 00562738 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00565140(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 local_18 [8];
  float local_10;
  undefined1 local_c [12];
  
  if (*(int *)(param_1 + 0x300) != 0) {
    local_24 = 0;
    local_20 = 0;
    local_1c = 0xbf800000;
    piVar2 = (int *)**(int **)(param_1 + 0x24c);
    if (piVar2 != *(int **)(param_1 + 0x24c)) {
      do {
        if ((piVar2[2] != 0) && (*(int *)(piVar2[2] + 0x6c) != 0)) {
          FUN_00477d30(3,local_18);
          local_10 = local_10 + _DAT_005a8410;
          iVar1 = FUN_00564920(local_18,&local_24,local_c);
          if (iVar1 != 0) {
            FUN_005651e0(local_c);
          }
        }
        piVar2 = (int *)*piVar2;
      } while (piVar2 != (int *)*(int *)(param_1 + 0x24c));
    }
  }
  return;
}

