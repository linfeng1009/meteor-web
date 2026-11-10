/* Original Meteor.exe static export @ 004cf770; original sample not executed. */
/* XREF 005aa710 DATA */

void __fastcall FUN_004cf770(int *param_1)

{
  if (0 < param_1[0x18]) {
    (**(code **)(*param_1 + 0x74))(0x97);
    return;
  }
  if (param_1[0x18] != 0) {
    (**(code **)(*param_1 + 0x74))(0x9d,0,1,0xbf800000);
    return;
  }
  if (0 < param_1[0x19]) {
    (**(code **)(*param_1 + 0x74))(0x99);
    return;
  }
  if (param_1[0x19] < 0) {
    (**(code **)(*param_1 + 0x74))(0x9b);
    return;
  }
  (**(code **)(*param_1 + 0x74))(0x97);
  return;
}

