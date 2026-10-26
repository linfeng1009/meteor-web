/* Original Meteor.exe static export @ 004aea30; original sample not executed. */
/* XREF 005a9c6c DATA */
/* XREF 005aa3dc DATA */
/* XREF 005aa534 DATA */

undefined4 __thiscall FUN_004aea30(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  bool bVar8;
  uint *in_stack_00000064;
  undefined1 local_6c [4];
  uint local_68 [2];
  undefined4 local_60 [24];
  
  piVar1 = (int *)(param_1 + 0x3b4);
  do {
    uVar3 = _rand();
    uVar3 = uVar3 % 0x7fff;
    FUN_00549a90(0,0);
    puVar7 = local_60;
    puVar6 = (undefined4 *)register0x00000010;
    for (iVar5 = 0x18; puVar6 = puVar6 + 1, iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar7 = puVar7 + 1;
    }
    iVar5 = *piVar1;
    bVar8 = true;
    iVar2 = iVar5;
    iVar4 = *(int *)(iVar5 + 4);
    while (iVar4 != 0) {
      bVar8 = uVar3 < *(uint *)(iVar4 + 0x10);
      iVar2 = iVar4;
      if (bVar8) {
        iVar4 = *(int *)(iVar4 + 8);
      }
      else {
        iVar4 = *(int *)(iVar4 + 0xc);
      }
    }
    local_68[0] = uVar3;
    if (bVar8) {
      if (iVar2 == *(int *)(iVar5 + 8)) {
        if ((iVar2 == *piVar1) || (uVar3 < *(uint *)(iVar2 + 0x10))) {
          iVar4 = FUN_0049f670(local_68);
          *(int *)(iVar2 + 8) = iVar4;
          iVar5 = *piVar1;
          if (iVar2 == iVar5) {
            *(int *)(iVar5 + 4) = iVar4;
            *(int *)(*piVar1 + 0xc) = iVar4;
          }
          else if (iVar2 == *(int *)(iVar5 + 8)) {
            *(int *)(iVar5 + 8) = iVar4;
          }
        }
        else {
          iVar4 = FUN_0049f670(local_68);
          *(int *)(iVar2 + 0xc) = iVar4;
          if (iVar2 == *(int *)(*piVar1 + 0xc)) {
            *(int *)(*piVar1 + 0xc) = iVar4;
          }
        }
        *(int *)(iVar4 + 4) = iVar2;
        *(undefined4 *)(iVar4 + 8) = 0;
        *(undefined4 *)(iVar4 + 0xc) = 0;
        FUN_00460be0(iVar4,*piVar1 + 4);
        *(int *)(param_1 + 0x3b8) = *(int *)(param_1 + 0x3b8) + 1;
        goto LAB_004aead6;
      }
      FUN_0044cf00();
    }
  } while (local_68[0] <= *(uint *)(iVar2 + 0x10));
  FUN_0049ebb0(local_6c,0,iVar2,local_68);
LAB_004aead6:
  *in_stack_00000064 = uVar3;
  return 1;
}

