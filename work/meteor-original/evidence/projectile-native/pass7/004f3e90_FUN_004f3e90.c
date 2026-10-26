/* Original Meteor.exe static export @ 004f3e90; original sample not executed. */
/* XREF 005aa0c8 DATA */
/* XREF 005ab550 DATA */
/* XREF 005ab990 DATA */
/* XREF 005ab310 DATA */

undefined4 __thiscall FUN_004f3e90(int *param_1,int param_2)

{
  int iVar1;
  float10 fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 *puStack_1c;
  float fStack_10;
  float *pfStack_c;
  
  iVar1 = (**(code **)(*param_1 + 0x48))();
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  uVar7 = 0;
  puVar5 = &uStack_30;
  uVar6 = 0;
  (**(code **)(*(int *)(param_2 + 0x65c) + 4))(puVar5,0,0);
  uVar4 = 0;
  uVar3 = 0;
  (**(code **)(*(int *)(iVar1 + 0x65c) + 4))(&uStack_30,0,0);
  uStack_30 = uVar6;
  uStack_2c = uVar7;
  uStack_24 = uVar3;
  uStack_20 = uVar4;
  puStack_1c = puVar5;
  fVar2 = (float10)FUN_0047ecc0(&uStack_30);
  if (pfStack_c != (float *)0x0) {
    *pfStack_c = (float)fVar2;
  }
  if (fVar2 < (float10)fStack_10 != (fVar2 == (float10)fStack_10)) {
    return 1;
  }
  return 0;
}

