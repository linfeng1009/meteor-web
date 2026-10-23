/* Meteor.exe original x86 @ 0047ae40 */
/* Caller: 004747fc */

undefined4 FUN_0047ae40(void)

{
  HMODULE pHVar1;
  int iVar2;
  undefined *puVar3;
  
  pHVar1 = GetModuleHandleA((LPCSTR)0x0);
  iVar2 = DirectInputCreateEx(pHVar1,0x700,&DAT_005ad2a0,&DAT_005ef6ac,0);
  if (iVar2 < 0) {
    return 0;
  }
  puVar3 = &DAT_005ad280;
  iVar2 = (**(code **)(*DAT_005ef6ac + 0x24))
                    (DAT_005ef6ac,&DAT_005ad1e0,&DAT_005ad280,&DAT_005ef6b0,0);
  if (iVar2 < 0) {
    return 0;
  }
  (**(code **)(*DAT_005ef6b0 + 0x34))(DAT_005ef6b0,puVar3,6);
  (**(code **)(*DAT_005ef6b0 + 0x2c))(DAT_005ef6b0,&DAT_005ad340);
  (**(code **)(*DAT_005ef6b0 + 0x1c))(DAT_005ef6b0);
  GetCursorPos((LPPOINT)&DAT_005ef6a4);
  ScreenToClient(DAT_005e0388,(LPPOINT)&DAT_005ef6a4);
  DAT_005ef69c = DAT_005ef6a4;
  DAT_005ef6a0 = DAT_005ef6a8;
  iVar2 = (**(code **)(*DAT_005ef6ac + 0x24))
                    (DAT_005ef6ac,&DAT_005ad1d0,&DAT_005ad280,&DAT_005ef6b4,0);
  if (iVar2 < 0) {
    return 0;
  }
  (**(code **)(*DAT_005ef6b4 + 0x34))(DAT_005ef6b4,puVar3,6);
  (**(code **)(*DAT_005ef6b4 + 0x2c))(DAT_005ef6b4,&DAT_005ad328);
  (**(code **)(*DAT_005ef6b4 + 0x1c))(DAT_005ef6b4);
  iVar2 = (**(code **)(*DAT_005ef6ac + 0x10))(DAT_005ef6ac,4,&LAB_0047af90,0,1);
  if (iVar2 < 0) {
    return 0;
  }
  if (DAT_005ef6b8 != (int *)0x0) {
    (**(code **)(*DAT_005ef6b8 + 0x34))(DAT_005ef6b8,puVar3,6);
    (**(code **)(*DAT_005ef6b8 + 0x2c))(DAT_005ef6b8,&DAT_005ad310);
    (**(code **)(*DAT_005ef6b8 + 0x1c))(DAT_005ef6b8);
  }
  return 1;
}

