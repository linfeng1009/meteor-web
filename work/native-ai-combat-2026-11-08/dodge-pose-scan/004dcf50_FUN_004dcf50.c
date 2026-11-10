/* Original Meteor.exe read-only export. Sample not executed. */

/* WARNING: Removing unreachable block (ram,0x004dcfe2) */
/* WARNING: Removing unreachable block (ram,0x004dcfc3) */

int __thiscall FUN_004dcf50(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_2[4] == 0) {
    return 0;
  }
  iVar1 = (**(code **)(*param_2 + 0x9c))(1);
  if (iVar1 != 99999) {
    iVar2 = (**(code **)(*param_2 + 0xa4))(iVar1,4);
    if (iVar2 == 3) {
      return 0;
    }
    param_2[0xd6] = 1;
    (**(code **)(*param_2 + 300))(3);
    (**(code **)(*param_1 + 0x14))(param_2,iVar1);
  }
  return iVar1;
}

