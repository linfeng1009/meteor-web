/* Original Meteor.exe static export @ 004cdf90; original sample not executed. */
/* XREF 005aa798 DATA */

undefined4 __thiscall FUN_004cdf90(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1[0x18];
  if ((iVar1 == 0) && (param_1[0x19] == 0)) {
    if (param_1[0xde] != 1) {
      uVar2 = (**(code **)(*param_1 + 200))
                        ((float)(double)CONCAT44(param_3,param_2),param_1 + 0x34,0x3f800000);
      return uVar2;
    }
    (**(code **)(*param_1 + 0xf8))();
    return 0;
  }
  if (0 < iVar1) {
    param_2 = 0x66;
  }
  if (iVar1 < 0) {
    param_2 = 0x62;
  }
  if (0 < param_1[0x19]) {
    param_2 = 0x72;
  }
  if (param_1[0x19] < 0) {
    param_2 = 0x6c;
  }
  (**(code **)(*param_1 + 0x114))(param_2,0);
  return 0;
}

