/* Original Meteor.exe static export @ 004d0350; original sample not executed. */
/* XREF 005aa74c DATA */

int __thiscall FUN_004d0350(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined2 uStack_8;
  undefined2 uStack_6;
  undefined2 uStack_4;
  undefined2 uStack_2;
  
  iVar1 = param_1[4];
  if (iVar1 == 0) {
    return 0;
  }
  iVar2 = FUN_004dbfd0(param_2,param_3);
  if (iVar2 != 3) {
    if (iVar2 == 1) {
      uStack_8 = FUN_0055c4d0();
      uStack_4 = *(undefined2 *)(iVar1 + -0x48);
      uStack_6 = 0;
      uStack_2 = 10;
      (**(code **)(*param_1 + 0xc))(8,&uStack_8,8);
    }
    param_1[0xee] = param_1[0xe4];
    param_1[0xef] = param_1[0xe5];
    param_1[0xf0] = param_1[0xe6];
  }
  return iVar2;
}

