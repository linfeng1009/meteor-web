/* Original Meteor.exe static export @ 004dedd0; original sample not executed. */
/* XREF 005aac88 DATA */

undefined4 FUN_004dedd0(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  piVar1 = param_1;
  uVar2 = FUN_004dd0a0(param_1);
  if (piVar1[0xdc] == 1) {
    (**(code **)(*piVar1 + 0x94))();
    iVar3 = FUN_0055ddd0();
    if (iVar3 != 0) {
      (**(code **)(*piVar1 + 0x94))();
      param_1 = (int *)FUN_0055c4e0();
      (**(code **)(*piVar1 + 0xc))(10,&param_1,4);
      piVar1[0xdc] = 0;
    }
  }
  return uVar2;
}

