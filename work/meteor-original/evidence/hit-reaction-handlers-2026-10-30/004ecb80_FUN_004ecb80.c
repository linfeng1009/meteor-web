/* Original Meteor.exe static export @ 004ecb80; original sample not executed. */
/* XREF 00500862 UNCONDITIONAL_CALL */
/* XREF 004b6dcd UNCONDITIONAL_CALL */
/* XREF 004b6eab UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_004ecb80(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a3198;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  FUN_004ed1e0();
  local_4 = 0;
  FUN_005498c0();
  *param_1 = &PTR_FUN_005ab228;
  param_1[4] = &PTR_LAB_005ab1f8;
  FUN_004ecb20();
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

