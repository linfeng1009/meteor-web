/* Original Meteor.exe static export @ 004f3310; original sample not executed. */
/* XREF 005aa130 DATA */
/* XREF 005ab5b8 DATA */
/* XREF 005ab9f8 DATA */
/* XREF 005ab378 DATA */

int __fastcall FUN_004f3310(int *param_1)

{
  int iVar1;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined4 local_c;
  undefined4 *local_8;
  undefined4 local_4;
  
  local_c = 0;
  local_8 = (undefined4 *)0x0;
  local_4 = 0;
  iVar1 = (**(code **)(*param_1 + 0x154))(&local_c);
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 0xcc))(unaff_EDI);
    if (local_8 != (undefined4 *)0x0) {
      *local_8 = 200;
      local_8[1] = unaff_EDI;
      local_8[2] = unaff_ESI;
    }
  }
  return iVar1;
}

