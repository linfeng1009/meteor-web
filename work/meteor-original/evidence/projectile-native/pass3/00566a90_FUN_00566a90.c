/* Original Meteor.exe static export @ 00566a90; original sample not executed. */
/* XREF 00566a85 UNCONDITIONAL_CALL */
/* XREF 0055d21a UNCONDITIONAL_CALL */
/* XREF 00567265 UNCONDITIONAL_CALL */
/* XREF 004db733 UNCONDITIONAL_CALL */

int __thiscall FUN_00566a90(int *param_1,int param_2,undefined4 param_3)

{
  void *pvVar1;
  int iVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a5896;
  local_c = ExceptionList;
  if ((-1 < param_2) && (param_2 < *param_1)) {
    ExceptionList = &local_c;
    pvVar1 = operator_new(0x144);
    local_4 = 0;
    if (pvVar1 == (void *)0x0) {
      iVar2 = 0;
    }
    else {
      iVar2 = FUN_00565ee0(param_1);
    }
    local_4 = 0xffffffff;
    if (iVar2 != 0) {
      iVar4 = *(int *)(param_1[1] + param_2 * 4);
      puVar3 = (undefined1 *)(iVar2 + 4);
      do {
        *puVar3 = puVar3[iVar4 - iVar2];
        puVar3 = puVar3 + 1;
      } while (puVar3 + (-4 - iVar2) < (undefined1 *)0x10);
      puVar7 = (undefined4 *)(iVar4 + 0x14);
      puVar8 = (undefined4 *)(iVar2 + 0x14);
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      puVar7 = (undefined4 *)(iVar4 + 0x54);
      puVar8 = (undefined4 *)(iVar2 + 0x54);
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      puVar7 = (undefined4 *)(iVar4 + 0x94);
      puVar8 = (undefined4 *)(iVar2 + 0x94);
      for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *puVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar8 = puVar8 + 1;
      }
      *(undefined4 *)(iVar2 + 0xd4) = *(undefined4 *)(iVar4 + 0xd4);
      *(undefined1 *)(iVar2 + 0xd8) = *(undefined1 *)(iVar4 + 0xd8);
      *(undefined1 *)(iVar2 + 0xd9) = *(undefined1 *)(iVar4 + 0xd9);
      *(undefined1 *)(iVar2 + 0xda) = *(undefined1 *)(iVar4 + 0xda);
      FUN_00567270(iVar4 + 0xdc);
      *(undefined4 *)(iVar2 + 0xe0) = *(undefined4 *)(iVar4 + 0xe0);
      *(undefined4 *)(iVar2 + 0xe4) = *(undefined4 *)(iVar4 + 0xe4);
      *(undefined4 *)(iVar2 + 0xe8) = *(undefined4 *)(iVar4 + 0xe8);
      *(undefined4 *)(iVar2 + 0xec) = *(undefined4 *)(iVar4 + 0xec);
      *(undefined4 *)(iVar2 + 0xf0) = *(undefined4 *)(iVar4 + 0xf0);
      *(undefined4 *)(iVar2 + 0xf4) = *(undefined4 *)(iVar4 + 0xf4);
      *(undefined4 *)(iVar2 + 0xf8) = *(undefined4 *)(iVar4 + 0xf8);
      *(undefined4 *)(iVar2 + 0xfc) = *(undefined4 *)(iVar4 + 0xfc);
      *(undefined4 *)(iVar2 + 0x100) = *(undefined4 *)(iVar4 + 0x100);
      *(undefined4 *)(iVar2 + 0x104) = *(undefined4 *)(iVar4 + 0x104);
      *(undefined4 *)(iVar2 + 0x108) = *(undefined4 *)(iVar4 + 0x108);
      *(undefined4 *)(iVar2 + 0x10c) = *(undefined4 *)(iVar4 + 0x10c);
      *(undefined4 *)(iVar2 + 0x110) = *(undefined4 *)(iVar4 + 0x110);
      *(undefined4 *)(iVar2 + 0x114) = *(undefined4 *)(iVar4 + 0x114);
      *(undefined4 *)(iVar2 + 0x118) = *(undefined4 *)(iVar4 + 0x118);
      *(undefined4 *)(iVar2 + 0x11c) = *(undefined4 *)(iVar4 + 0x11c);
      if ((undefined4 *)(iVar4 + 0x120) != (undefined4 *)(iVar2 + 0x120)) {
        FUN_00403200(*(undefined4 *)(iVar4 + 0x120),*(undefined4 *)(iVar4 + 0x124));
      }
      *(undefined4 *)(iVar2 + 300) = *(undefined4 *)(iVar4 + 300);
      *(undefined4 *)(iVar2 + 0x130) = *(undefined4 *)(iVar4 + 0x130);
      *(undefined4 *)(iVar2 + 0x134) = *(undefined4 *)(iVar4 + 0x134);
      *(undefined1 *)(iVar2 + 0x138) = *(undefined1 *)(iVar4 + 0x138);
      *(undefined1 *)(iVar2 + 0x139) = *(undefined1 *)(iVar4 + 0x139);
      *(undefined4 *)(iVar2 + 0x13c) = *(undefined4 *)(iVar4 + 0x13c);
      *(undefined4 *)(iVar2 + 0x140) = *(undefined4 *)(iVar4 + 0x140);
      pvVar1 = operator_new(0x130);
      local_4 = 1;
      if (pvVar1 == (void *)0x0) {
        iVar4 = 0;
      }
      else {
        iVar4 = FUN_0056db90();
      }
      local_4 = 0xffffffff;
      *(int *)(iVar2 + 300) = iVar4;
      if (iVar4 != 0) {
        FUN_00566380(param_3);
        FUN_0056ee70(*(undefined4 *)(iVar2 + 300));
        uVar5 = FUN_00567200();
        *(undefined4 *)(iVar2 + 0x13c) = uVar5;
        *(undefined4 *)(iVar2 + 0x140) = 0;
        FUN_00566dd0(iVar2);
        ExceptionList = local_c;
        return iVar2;
      }
    }
  }
  ExceptionList = local_c;
  return 0;
}

