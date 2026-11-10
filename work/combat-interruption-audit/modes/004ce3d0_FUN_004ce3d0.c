/* Original Meteor.exe static export @ 004ce3d0; original sample not executed. */
/* XREF 005aa788 DATA */

undefined4 __fastcall FUN_004ce3d0(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 unaff_ESI;
  int *piVar4;
  
  if (param_1[4] == 0) {
    piVar4 = (int *)0x0;
  }
  else {
    piVar4 = (int *)(param_1[4] + -0x65c);
  }
  if ((param_1[0xdd] != 0) && (piVar4 != (int *)0x0)) {
    iVar1 = (**(code **)(*piVar4 + 0x68))();
    if (iVar1 != 0) {
      (**(code **)(*param_1 + 0xc))(0x2d);
    }
  }
  if ((param_1[0x149] != 0) && (piVar4 != (int *)0x0)) {
    iVar1 = (**(code **)(*piVar4 + 0x68))();
    if (iVar1 != 0) {
      (**(code **)(*param_1 + 0xc))(0x30);
    }
  }
  iVar1 = (**(code **)(*param_1 + 0x164))();
  if (iVar1 != 0) {
    return 0;
  }
  FUN_0055c4e0();
  uVar2 = (**(code **)(*(int *)param_1[0xd2] + 0x48))(param_1[0xf4]);
  (**(code **)(*param_1 + 0xc))(5,&stack0xfffffff4,8);
  uVar3 = (**(code **)(*param_1 + 200))
                    ((float)(double)CONCAT44(uVar2,unaff_ESI),param_1 + 0x34,0x3f800000);
  iVar1 = FUN_0055c300();
  if (iVar1 == 3) {
    (**(code **)(*param_1 + 0x144))((float)(double)CONCAT44(uVar2,unaff_ESI),0x3f000000);
  }
  iVar1 = FUN_0055d440();
  if (iVar1 != 0) {
    FUN_0055c4d0();
    __ftol();
    (**(code **)(*param_1 + 0xc))(0x1b,&stack0xffffffe8,8);
  }
  return uVar3;
}

