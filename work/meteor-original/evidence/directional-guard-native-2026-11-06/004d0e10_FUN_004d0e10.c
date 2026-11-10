/* Original Meteor.exe static export @ 004d0e10; original sample not executed. */
/* XREF 004cad47 UNCONDITIONAL_CALL */

void __fastcall FUN_004d0e10(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_10;
  undefined4 local_c;
  undefined1 local_8 [8];
  
  puVar2 = (undefined4 *)(param_1 + 0x48);
  for (iVar1 = 0x42; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(param_1 + 0x44) = 0;
  FUN_0049aff0();
  local_10 = 0x20;
  local_c = 0;
  FUN_0049c330(local_8,&local_10);
  local_10 = 0x45;
  local_c = 1;
  FUN_0049c330(local_8,&local_10);
  local_10 = 0x47;
  local_c = 2;
  FUN_0049c330(local_8,&local_10);
  local_10 = 0x1200;
  local_c = 3;
  FUN_0049c330(local_8,&local_10);
  local_10 = 0x1000;
  local_c = 4;
  FUN_0049c330(local_8,&local_10);
  local_10 = 0x51;
  local_c = 5;
  FUN_0049c330(local_8,&local_10);
  local_10 = 0x27;
  local_c = 6;
  FUN_0049c330(local_8,&local_10);
  local_10 = 0x25;
  local_c = 7;
  FUN_0049c330(local_8,&local_10);
  local_10 = 0x59;
  local_c = 8;
  FUN_0049c330(local_8,&local_10);
  return;
}

