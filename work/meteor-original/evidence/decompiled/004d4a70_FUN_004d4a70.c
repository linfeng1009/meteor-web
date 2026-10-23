/* Meteor.exe original x86 @ 004d4a70 */
/* Caller: 004d4a5c */
/* Caller: 004ac46f */
/* Caller: 004d6552 */

void __fastcall FUN_004d4a70(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar3 = *(int *)(param_1 + 0x30);
  iVar1 = *(int *)(param_1 + 0x34);
  FUN_00576490(iVar1,iVar1,iVar3);
  iVar3 = (int)((ulonglong)((longlong)(iVar1 - iVar3) * -0x2aaaaaab) >> 0x20);
  local_4 = 0;
  local_c = 2;
  *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + ((iVar3 >> 1) - (iVar3 >> 0x1f)) * 0xc;
  uVar2 = __ftol();
  iVar3 = *(int *)(param_1 + 0x34);
  local_8 = uVar2;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 1;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    local_8 = uVar2;
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    local_8 = uVar2;
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 6;
  local_8 = 0;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 7;
  local_8 = 100;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 5;
  local_8 = 100;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 3;
  local_8 = 0;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 4;
  local_8 = 0;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 9;
  local_8 = 100;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 10;
  local_8 = 0;
  if (iVar3 == *(int *)(param_1 + 0x38)) {
    FUN_004d6b20(iVar3,&local_c);
  }
  else {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
  }
  iVar3 = *(int *)(param_1 + 0x34);
  local_c = 0xb;
  local_8 = 0;
  if (iVar3 != *(int *)(param_1 + 0x38)) {
    FUN_004d27d0(iVar3,&local_c);
    *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 0xc;
    return;
  }
  FUN_004d6b20(iVar3,&local_c);
  return;
}

