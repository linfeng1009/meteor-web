/* Original Meteor.exe static export @ 004affd0; original sample not executed. */
/* XREF 005a9cc0 DATA */
/* XREF 005aa430 DATA */
/* XREF 005aa588 DATA */

undefined4 __thiscall FUN_004affd0(int *param_1,int param_2)

{
  int iVar1;
  undefined4 unaff_retaddr;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  if (*(int *)(param_2 + 0x1e8) == 1) {
    uStack_c = 0;
    uStack_10 = 2;
    uStack_14 = 0x4affee;
    iVar1 = (**(code **)(*(int *)(param_2 + 0x70) + 0x34))();
    if (iVar1 == 0) {
      uStack_14 = 1;
      FUN_004acae0(unaff_retaddr,0x18,&stack0x00000000,4);
      (**(code **)(*param_1 + 0x40))(0x2c,&uStack_14,4,0);
      *(undefined4 *)(param_2 + 0x1e8) = 2;
      if (param_1[0xe0] == 0) {
        *(int *)(param_2 + 0x200) = *(int *)(param_2 + 0x200) + 1;
      }
      FUN_00549a90(0,0);
      return 1;
    }
  }
  return 0;
}

