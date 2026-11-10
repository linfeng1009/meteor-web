/* Original Meteor.exe static export @ 004f3f50; original sample not executed. */
/* XREF 005aa0d4 DATA */
/* XREF 005ab55c DATA */
/* XREF 005ab99c DATA */
/* XREF 005ab31c DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_004f3f50(int *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 uVar5;
  
  uVar1 = param_2[3];
  uVar2 = *param_2;
  iVar3 = (**(code **)(*(int *)param_1[0x69] + 0x48))
                    (uVar2,(float)param_2[1] * _DAT_005a8410,3,(float)param_2[2] * _DAT_005a8410);
  if (iVar3 != 0) {
    param_1[0xd8] = 1;
    param_1[0xd9] = uVar2;
    if ((0x59 < uVar2) && (uVar2 < 0x76)) {
      piVar4 = (int *)FUN_00487830();
      iVar3 = *piVar4;
      uVar5 = (**(code **)(*param_1 + 0x4c))((uVar2 - 0x5a) + uVar1 * 0x38,0,0);
      (**(code **)(iVar3 + 0x20c))(uVar5);
    }
  }
  return 0;
}

