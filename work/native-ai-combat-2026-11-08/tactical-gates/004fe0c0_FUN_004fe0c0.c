/* Original Meteor.exe static export @ 004fe0c0; original sample not executed. */
/* XREF 004fb88c UNCONDITIONAL_CALL */

undefined1 FUN_004fe0c0(void)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = FUN_00501130();
  if (cVar1 == '\0') {
    return 0;
  }
  uVar2 = _rand();
  uVar2 = uVar2 & 0x80000007;
  if ((int)uVar2 < 0) {
    uVar2 = (uVar2 - 1 | 0xfffffff8) + 1;
  }
  if (uVar2 == 0) {
    cVar1 = FUN_004fcc10(0x66,0x42480000);
    if (cVar1 != '\0') {
      FUN_00500be0(1,0);
      return 1;
    }
  }
  else if (uVar2 == 1) {
    cVar1 = FUN_004fcc10(0x62,0x42480000);
    if (cVar1 != '\0') {
      FUN_00500be0(0xffffffff,0);
      return 1;
    }
  }
  else if (uVar2 == 2) {
    cVar1 = FUN_004fcc10(0x6c,0x42480000);
    if (cVar1 != '\0') {
      FUN_00500be0(0,0xffffffff);
      return 1;
    }
  }
  else if (uVar2 == 3) {
    cVar1 = FUN_004fcc10(0x72,0x42480000);
    if (cVar1 != '\0') {
      FUN_00500be0(0,1);
      return 1;
    }
  }
  else if (uVar2 == 4) {
    FUN_00500c90(0,0);
  }
  return 1;
}

