/* Original Meteor.exe static export @ 004deca0; original sample not executed. */
/* XREF 005aac70 DATA */

undefined4 FUN_004deca0(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  
  piVar1 = param_1;
  iVar2 = (**(code **)(*param_1 + 0x9c))(0,&param_1);
  if (((piVar1[0xdb] == 0) && (iVar2 != 0x3a)) && (iVar2 != 0x92)) {
    iVar2 = (**(code **)(*piVar1 + 0x130))();
    if (iVar2 == 1) {
      piVar1[0xdb] = 1;
      (**(code **)(*piVar1 + 0x48))(0xd4,0x3f800000,0,0);
    }
    return 0;
  }
  uVar3 = FUN_004dcf50(piVar1);
  return uVar3;
}

