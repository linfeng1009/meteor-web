/* Meteor.exe original x86 @ 004f1ca0 */
/* Caller: 005ab4fc */
/* Caller: 005ab93c */
/* Caller: 004bc52f */
/* Caller: 005ab2bc */

int __thiscall FUN_004f1ca0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined1 local_100 [256];
  
  FUN_00508ae6(local_100,&PTR_DAT_005c936c,param_2);
  iVar1 = (**(code **)(*param_1 + 0x90))(local_100,param_3,param_4);
  if (iVar1 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = iVar1 + -0x65c;
  }
  *(undefined4 *)(iVar2 + 0x848) = 1;
  if (iVar1 != 0) {
    FUN_0054a6c0(4,&stack0xfffffeec,8,1);
  }
  return iVar1;
}

