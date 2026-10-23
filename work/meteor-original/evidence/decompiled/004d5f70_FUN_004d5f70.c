/* Original Meteor.exe @ 004d5f70; stat virtual-call signatures annotated from x86 calling convention */

void __thiscall FUN_004d5f70(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  
  (**(code **)(*param_1 + 0x3c))(param_1,param_2,param_3);
  iVar1 = __ftol();
  if (0 < iVar1) {
    (**(code **)(*param_3 + 0x2c))(param_3,2,-iVar1,(void *)0x0);
  }
  return;
}

