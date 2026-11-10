/* Original Meteor.exe static export @ 004fcde0; original sample not executed. */
/* XREF 00503f69 UNCONDITIONAL_CALL */
/* XREF 00504271 UNCONDITIONAL_CALL */

undefined1 __thiscall FUN_004fcde0(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int local_4;
  
  cVar1 = FUN_004fced0(0x40a00000);
  if (cVar1 == '\0') {
    return 0;
  }
  uVar4 = 0;
  uVar3 = 0;
  local_4 = 0;
  switch((char)param_2) {
  case 'b':
    uVar3 = 0xffffffff;
    local_4 = 0x28;
    break;
  case 'f':
    uVar3 = 1;
    local_4 = 200;
    break;
  case 'l':
    uVar4 = 0xffffffff;
    goto LAB_004fce4b;
  case 'r':
    uVar4 = 1;
LAB_004fce4b:
    uVar3 = 0;
    local_4 = 0x1e;
  }
  cVar1 = FUN_004fcc10(param_2,(float)local_4);
  if (cVar1 == '\0') {
    return 0;
  }
  *(undefined4 *)(param_1 + 0xbc) = uVar3;
  *(undefined4 *)(param_1 + 0xc0) = uVar4;
  FUN_00500be0(uVar3,uVar4);
  uVar2 = _rand();
  uVar2 = uVar2 & 0x80000001;
  if ((int)uVar2 < 0) {
    uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
  }
  FUN_00500c40(uVar2);
  return 1;
}

