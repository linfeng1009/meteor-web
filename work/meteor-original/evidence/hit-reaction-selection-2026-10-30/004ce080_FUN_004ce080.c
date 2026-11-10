/* Original Meteor.exe static export @ 004ce080; original sample not executed. */
/* XREF 005aa774 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004ce080(int *param_1,undefined4 param_2)

{
  undefined4 unaff_retaddr;
  
  (**(code **)(*(int *)param_1[0xd2] + 0x18))(param_1);
  (**(code **)(*param_1 + 200))
            ((float)(double)CONCAT44(param_2,unaff_retaddr),param_1 + 0x34,0x3f800000);
  (**(code **)(*param_1 + 0x140))
            ((float)(double)CONCAT44(param_2,unaff_retaddr),0x3e99999a,0xbe99999a);
  if ((float)param_1[0xe6] < _DAT_005aa920) {
    (**(code **)(*param_1 + 0xbc))(0);
    (**(code **)(*param_1 + 300))(0);
  }
  return 0;
}

