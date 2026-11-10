/* Original Meteor.exe static export @ 0055d450; original sample not executed. */
/* XREF 0055d876 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_0055d450(int param_1,int param_2)

{
  if ((-1 < param_2) && (param_2 < *(int *)(param_1 + 0x5dc))) {
    *(undefined4 *)(param_1 + 0x620) = 1;
    *(undefined4 *)(param_1 + 0x5e8) = 1;
    *(undefined4 *)(param_1 + 0x5ec) = 0;
    *(undefined4 *)(param_1 + 0x640) = 3;
    FUN_00559720(*(undefined4 *)(*(int *)(param_1 + 0x638) + 0x50));
    *(short *)(param_1 + 0x614) = *(short *)(param_1 + 0x614) + 1;
    *(int *)(param_1 + 0x610) = param_2;
    *(int *)(param_1 + 0x5e0) = param_2;
    *(int *)(param_1 + 0x638) = *(int *)(param_1 + 0x62c) + param_2 * 0xac;
    FUN_005596c0(*(undefined4 *)(param_1 + 0xfc));
    FUN_005596e0(*(undefined4 *)(*(int *)(param_1 + 0x638) + 0x40));
    if (*(int *)(*(int *)(param_1 + 0x638) + 0x6c) == 0) {
      if ((*(byte *)(param_1 + 0x5fc) & 8) != 0) {
        *(undefined4 *)(param_1 + 0x5e4) = 1;
        return 1;
      }
      *(undefined4 *)(param_1 + 0x5e4) = 0;
    }
    return 1;
  }
  return 0;
}

