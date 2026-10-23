/* Original Meteor.exe @ 004d6190; stat virtual-call signatures annotated from x86 calling convention */

int __thiscall FUN_004d6190(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (**(code **)(*param_1 + 0x40))(param_1,param_2);
  iVar2 = (**(code **)(*param_3 + 0x34))(param_3,4,(void *)0x0);
  return iVar1 - iVar2;
}

