/* Original Meteor.exe static export @ 004fcb00; original sample not executed. */
/* XREF 0050446e UNCONDITIONAL_CALL */

uint __thiscall FUN_004fcb00(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((param_2 != 0) && (uVar1 = *(uint *)(param_1 + 0x58), -1 < (int)uVar1)) {
    uVar1 = FUN_004fced0();
    return uVar1;
  }
  return uVar1 & 0xffffff00;
}

