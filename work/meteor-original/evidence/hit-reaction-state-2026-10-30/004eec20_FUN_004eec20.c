/* Original Meteor.exe static export @ 004eec20; original sample not executed. */
/* XREF 005aa068 DATA */
/* XREF 005ab4f0 DATA */
/* XREF 005ab930 DATA */
/* XREF 005ab2b0 DATA */

void __fastcall FUN_004eec20(int *param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  short sVar7;
  undefined1 auStack_38 [12];
  undefined1 auStack_2c [12];
  undefined2 uStack_20;
  undefined2 uStack_1e;
  undefined2 uStack_1c;
  undefined2 uStack_1a;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined2 uStack_14;
  undefined2 uStack_12;
  ushort uStack_10;
  undefined2 uStack_e;
  
  iVar3 = (**(code **)(*param_1 + 0x48))();
  if ((iVar3 != 0) && ((int *)(iVar3 + 0x65c) != (int *)0x0)) {
    (**(code **)(*(int *)(iVar3 + 0x65c) + 4))(auStack_38,&uStack_20,0);
    iVar4 = FUN_0055c4d0();
    if (iVar4 != param_1[0xd9]) {
      param_1[0xd8] = 0;
    }
    iVar2 = *(int *)(iVar3 + 0x8ac);
    uVar1 = *(undefined2 *)(iVar3 + 0x614);
    piVar5 = (int *)(**(code **)(*param_1 + 0x44))();
    sVar7 = 0;
    if (piVar5 != (int *)0x0) {
      (**(code **)(*piVar5 + 0x3c))(auStack_38);
      iVar3 = (**(code **)(*piVar5 + 0x168))();
      if (iVar3 != 0) {
        sVar7 = 1;
      }
    }
    uStack_20 = __ftol();
    uStack_1e = __ftol();
    uStack_1c = __ftol();
    uStack_1a = __ftol();
    uStack_18 = __ftol();
    uStack_16 = __ftol();
    uStack_14 = __ftol();
    uStack_12 = __ftol();
    uStack_10 = (*(ushort *)(param_1 + 0xd8) | sVar7 * 2) << 0xb |
                (ushort)iVar4 | (ushort)(iVar2 << 0xd);
    uStack_e = uVar1;
    piVar5 = (int *)FUN_00487830();
    iVar3 = *piVar5;
    uVar6 = (**(code **)(*param_1 + 0x4c))(&uStack_20,0x14);
    (**(code **)(iVar3 + 0x330))(uVar6);
    FUN_0054a6c0(1,auStack_2c,0x14,0);
  }
  return;
}

