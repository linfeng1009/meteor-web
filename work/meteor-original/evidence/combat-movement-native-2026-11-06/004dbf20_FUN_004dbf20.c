/* Original Meteor.exe static export @ 004dbf20; original sample not executed. */
/* XREF 005aaa70 DATA */

void __fastcall FUN_004dbf20(int *param_1)

{
  undefined4 uStack_38;
  undefined1 auStack_30 [48];
  
  if (param_1[0x214] != 0) {
    uStack_38 = 2;
    (**(code **)(*param_1 + 0x6c))(auStack_30);
    thunk_FUN_0040c620(param_1[0x214],&uStack_38,0);
  }
  return;
}

