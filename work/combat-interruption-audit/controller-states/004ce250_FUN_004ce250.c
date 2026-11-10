/* Original Meteor.exe static export @ 004ce250; original sample not executed. */
/* XREF 005aa6f8 DATA */

undefined4 __thiscall FUN_004ce250(int param_1,uint param_2)

{
  *(uint *)(param_1 + 0x34c) =
       -(uint)(*(uint *)(param_1 + 0x34c) != param_2) & *(uint *)(param_1 + 0x34c);
  *(uint *)(param_1 + 0x350) =
       -(uint)(*(uint *)(param_1 + 0x350) != param_2) & *(uint *)(param_1 + 0x350);
  *(uint *)(param_1 + 0x354) =
       -(uint)(*(uint *)(param_1 + 0x354) != param_2) & *(uint *)(param_1 + 0x354);
  return 0;
}

