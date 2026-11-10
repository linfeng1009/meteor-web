/* Original Meteor.exe static export @ 004f3ad0; original sample not executed. */
/* XREF 005aa0d0 DATA */
/* XREF 005ab558 DATA */
/* XREF 005ab998 DATA */
/* XREF 005ab318 DATA */

undefined4 __fastcall FUN_004f3ad0(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined1 auStack_2c [4];
  undefined1 auStack_28 [8];
  undefined1 auStack_20 [4];
  undefined4 uStack_1c;
  uint uStack_18;
  undefined4 uStack_14;
  uint uStack_10;
  uint uStack_c;
  uint uStack_4;
  
  iVar2 = (**(code **)(*param_1 + 0x48))();
  if (iVar2 != 0) {
    iVar3 = FUN_0055ddd0();
    (**(code **)(*param_1 + 0xe4))(auStack_20,auStack_2c);
    iVar4 = FUN_00487830();
    iVar4 = *(int *)(*(int *)(iVar4 + 0x2188) + 8);
    iVar5 = FUN_00487830();
    if (iVar4 != *(int *)(iVar5 + 0x2188)) {
      do {
        if ((*(int *)(iVar4 + 0x14) != iVar2 + 0x65c) &&
           (iVar5 = (**(code **)(*param_1 + 0x128))(*(undefined4 *)(iVar4 + 0x10)), iVar5 != 0)) {
          if (*(int *)(iVar4 + 0x14) == 0) {
            iVar5 = 0;
          }
          else {
            iVar5 = *(int *)(iVar4 + 0x14) + -0x65c;
          }
          piVar6 = (int *)FUN_00487830();
          iVar5 = (**(code **)(*piVar6 + 0x1a4))(iVar5,auStack_28,&stack0xffffffcc,0x3f800000);
          if ((0 < iVar5) && (iVar3 != 0)) {
            uStack_1c = *(undefined4 *)(iVar4 + 0x10);
            uStack_18 = *(int *)(iVar3 + 0x30) << 10 | uStack_4;
            piVar6 = (int *)(**(code **)(*param_1 + 0x44))();
            iVar5 = (**(code **)(*piVar6 + 0x1a8))();
            uStack_18 = uStack_18 | iVar5 << 0x10;
            uStack_14 = *(undefined4 *)(iVar3 + 0x48);
            iVar5 = __ftol();
            uStack_10 = __ftol();
            uStack_10 = iVar5 << 0x10 | uStack_10;
            iVar5 = __ftol();
            uStack_c = __ftol();
            uStack_c = iVar5 << 0x10 | uStack_c;
            FUN_0054a6c0(5,&uStack_1c,0x14,0);
          }
        }
        iVar5 = *(int *)(iVar4 + 0xc);
        if (iVar5 == 0) {
          iVar5 = *(int *)(iVar4 + 4);
          if (iVar4 == *(int *)(iVar5 + 0xc)) {
            do {
              iVar4 = iVar5;
              iVar5 = *(int *)(iVar4 + 4);
            } while (iVar4 == *(int *)(iVar5 + 0xc));
          }
          if (*(int *)(iVar4 + 0xc) != iVar5) {
            iVar4 = iVar5;
          }
        }
        else {
          for (iVar1 = *(int *)(iVar5 + 8); iVar4 = iVar5, iVar1 != 0; iVar1 = *(int *)(iVar1 + 8))
          {
            iVar5 = iVar1;
          }
        }
        iVar5 = FUN_00487830();
      } while (iVar4 != *(int *)(iVar5 + 0x2188));
    }
  }
  return 0xffffffff;
}

