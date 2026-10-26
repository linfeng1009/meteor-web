/* Original Meteor.exe static export @ 00560970; original sample not executed. */
/* XREF 004b848d UNCONDITIONAL_CALL */

undefined4 * __fastcall FUN_00560970(undefined4 *param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a55ae;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_0056cb80();
  param_1[0xa8] = 0;
  param_1[0xa9] = 0;
  param_1[0xaa] = 0;
  local_4._0_1_ = 1;
  local_4._1_3_ = 0;
  uVar1 = FUN_00402bf0(0xc);
  param_1[0xab] = uVar1;
  *(undefined4 *)uVar1 = uVar1;
  *(undefined4 *)(param_1[0xab] + 4) = param_1[0xab];
  local_4._0_1_ = 2;
  FUN_005711f0();
  local_4._0_1_ = 3;
  FUN_0047bfd0();
  local_4._0_1_ = 4;
  FUN_0057d5d0();
  *param_1 = &PTR_LAB_005ae1d8;
  local_4 = CONCAT31(local_4._1_3_,5);
  DAT_00726858 = param_1;
  FUN_0055bd50(&LAB_00560380);
  FUN_005714e0(s_SetScene_005d14a8,&LAB_0056c400);
  FUN_005714e0(s_SetSceneItem_005d1498,&LAB_0056bc60);
  FUN_005714e0(s_GetSceneItem_005d1488,&LAB_0056c290);
  FUN_005714e0(s_NetEvent_005d147c,&LAB_0056bbf0);
  FUN_005714e0(s_GameCallBack_005d146c,&LAB_0056bb80);
  FUN_005714e0(s_MakeString_005d1460,&LAB_0056c630);
  FUN_005714e0(s_Output_005d1458,FUN_0058e140);
  FUN_005714e0(&DAT_005d1450,&LAB_0056c770);
  FUN_005714e0(&DAT_005d1448,&LAB_0056c960);
  pcVar2 = s_CreateEffect_005d1438;
  FUN_005714e0(s_CreateEffect_005d1438,&LAB_0056c9b0);
  FUN_005714e0(s_GetTeam_005ca0b0,&LAB_0056cb10);
  *(undefined1 *)(param_1 + 0x94) = 0;
  *(undefined1 *)((int)param_1 + 0x251) = 0;
  *(undefined1 *)((int)param_1 + 0x259) = 0;
  *(undefined1 *)((int)param_1 + 0x25a) = 0;
  *(undefined1 *)(param_1 + 0x95) = 1;
  *(undefined1 *)((int)param_1 + 0x255) = 0;
  *(undefined1 *)((int)param_1 + 0x253) = 0;
  *(undefined1 *)((int)param_1 + 599) = 0;
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x12e] = 0;
  param_1[0x12f] = 0;
  param_1[0xb9] = 0;
  param_1[0xbb] = 0;
  param_1[0xba] = 0;
  param_1[0xbc] = 0;
  param_1[0x12d] = 0;
  param_1[300] = 0;
  param_1[0x9e] = 0;
  param_1[0xa2] = 0;
  param_1[0xbd] = 0;
  param_1[0xbe] = 0;
  param_1[0xbf] = 0;
  param_1[0xa7] = 0;
  param_1[0x1b4] = 0;
  param_1[0x1b3] = 0;
  param_1[0x1b2] = 0;
  param_1[0x1b1] = 0;
  param_1[0x1b5] = 0;
  FUN_00561b80(1000);
  FUN_00561b90(0x40a00000,0x40a00000);
  param_1[0xc0] = 0;
  param_1[0xd1] = 0xffffffff;
  param_1[0xcb] = 0xffffffff;
  param_1[0xc5] = 0xffffffff;
  FUN_0047c3a0(0x41200000,0x41200000);
  ExceptionList = pcVar2;
  return param_1;
}

