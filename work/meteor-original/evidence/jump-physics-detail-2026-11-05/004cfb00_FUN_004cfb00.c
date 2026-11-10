/* Original Meteor.exe static export @ 004cfb00; original sample not executed. */
/* XREF 005aa71c DATA */

void __thiscall FUN_004cfb00(int *param_1,uint param_2,int param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint uStack_20;
  
  iVar1 = (**(code **)(*param_1 + 0x94))();
  if (iVar1 != 0) {
    (**(code **)(*param_1 + 0x1a0))();
    if ((param_3 != 0) && (uVar2 = (**(code **)(*param_1 + 0x134))(), uVar2 == param_2)) {
      return;
    }
    FUN_0055de10();
    uStack_20 = param_4;
    (**(code **)(*param_1 + 0x58))(param_2,param_2);
    (**(code **)(*(int *)param_1[0xd2] + 0x6c))(param_1);
    uStack_20 = param_2 << 8 | param_2;
    __ftol();
    __ftol();
    (**(code **)(*param_1 + 0xc))(4,&uStack_20,8);
  }
  return;
}

