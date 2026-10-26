/* Meteor.exe original x86 @ 0056e490; function boundary recovered from direct vtable/code reference */
/* Caller: 00566348 */

undefined4 __thiscall FUN_0056e490(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  void *pvVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  char *pcVar8;
  char *pcVar9;
  bool bVar10;
  int local_a4;
  int local_a0;
  undefined1 local_9c [15];
  char acStack_8d [129];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a5bba;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar2 = FUN_00509f8f(param_2,&DAT_005c4580);
  uVar3 = 0;
  if (iVar2 != 0) {
    uVar6 = 0xffffffff;
    pcVar8 = s_PonEF_V1_00_005d1890;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar8;
      pcVar8 = pcVar8 + 1;
    } while (cVar1 != '\0');
    FUN_0050a118(acStack_8d + 1,~uVar6 - 1,1,iVar2);
    acStack_8d[~uVar6] = '\0';
    pcVar8 = acStack_8d;
    iVar7 = 0xc;
    bVar10 = true;
    pcVar9 = s_PonEF_V1_00_005d1890;
    do {
      pcVar8 = pcVar8 + 1;
      if (iVar7 == 0) break;
      iVar7 = iVar7 + -1;
      bVar10 = *pcVar8 == *pcVar9;
      pcVar9 = pcVar9 + 1;
    } while (bVar10);
    if (bVar10) {
      FUN_0056e050();
      FUN_0050a118(&local_a4,4,1,iVar2);
      DAT_0072b730 = 0;
      local_a0 = 0;
      if (0 < local_a4) {
        do {
          FUN_0050a118(local_9c,0x10,1,iVar2);
          uVar3 = FUN_0058a700(local_9c);
          switch(uVar3) {
          case 2:
            pvVar4 = operator_new(0x280);
            local_4 = 0;
            if (pvVar4 == (void *)0x0) {
LAB_0056e785:
              piVar5 = (int *)0x0;
            }
            else {
              piVar5 = (int *)FUN_0058a1f0(param_1,1);
            }
            break;
          case 3:
            pvVar4 = operator_new(0x274);
            local_4 = 2;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_00589970(param_1,1);
            break;
          case 4:
            pvVar4 = operator_new(0x270);
            local_4 = 1;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_00589330(param_1,1);
            break;
          case 5:
            pvVar4 = operator_new(0x27c);
            local_4 = 3;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_00588e10(param_1,1);
            break;
          case 6:
            pvVar4 = operator_new(0x2ac);
            local_4 = 5;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_00588720(param_1,1);
            break;
          case 7:
            pvVar4 = operator_new(0x280);
            local_4 = 4;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_005880d0(param_1,1);
            break;
          case 8:
            pvVar4 = operator_new(0x2f4);
            local_4 = 6;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_00587a60(param_1,1);
            break;
          case 9:
            pvVar4 = operator_new(0x344);
            local_4 = 7;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_00585940(param_1,1);
            break;
          case 10:
            pvVar4 = operator_new(0x268);
            local_4 = 8;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_005856c0(param_1,1);
            break;
          case 0xb:
            pvVar4 = operator_new(0x270);
            local_4 = 9;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_00585360(param_1,1);
            break;
          case 0xc:
            pvVar4 = operator_new(0x284);
            local_4 = 10;
            if (pvVar4 == (void *)0x0) goto LAB_0056e785;
            piVar5 = (int *)FUN_00584d80(param_1,1);
            break;
          default:
            FUN_0056e050();
            FUN_00509e57(iVar2);
            ExceptionList = local_c;
            return 0;
          }
          local_4 = 0xffffffff;
          (**(code **)(*piVar5 + 0x2c))(iVar2);
          (**(code **)(*piVar5 + 0x48))();
          FUN_0056dff0(piVar5);
          if ((piVar5[1] != 2) && (((char)piVar5[9] == 'a' || ((char)piVar5[9] == 'A')))) {
            *(undefined1 *)(param_1 + 0x3e) = 1;
          }
          local_a0 = local_a0 + 1;
        } while (local_a0 < local_a4);
      }
      FUN_00509e57(iVar2);
      FUN_0056ded0();
      FUN_0056df30();
      FUN_0056ee30();
      FUN_0050af1e(*(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x40),4,&LAB_0056dad0);
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  ExceptionList = local_c;
  return uVar3;
}

