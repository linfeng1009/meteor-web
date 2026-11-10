/* Original Meteor.exe static export @ 00557c70; original sample not executed. */
/* XREF 004dbd0e UNCONDITIONAL_CALL */
/* XREF 004dbd55 UNCONDITIONAL_CALL */
/* XREF 004dbd9c UNCONDITIONAL_CALL */
/* XREF 00583e43 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_00557c70(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  char *unaff_retaddr;
  int aiStack_38 [10];
  void *pvStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a4fdb;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  FUN_00559070(&DAT_005d1368);
  iVar2 = FUN_00509f8f(unaff_retaddr,&DAT_005ca380);
  uVar4 = 0;
  if (iVar2 != 0) {
    iVar6 = param_1 - (int)unaff_retaddr;
    do {
      cVar1 = *unaff_retaddr;
      unaff_retaddr[iVar6 + 0x74] = cVar1;
      unaff_retaddr = unaff_retaddr + 1;
    } while (cVar1 != '\0');
    FUN_00571c70(iVar2,2);
    FUN_0050b600(iVar2,s__s__s__d__s__s__d_005d1354,&stack0xffffffa8,&stack0xffffffa8,
                 (int *)(param_1 + 8),&stack0xffffffa8,&stack0xffffffa8,(int *)(param_1 + 0xc));
    *(int *)(param_1 + 4) = *(int *)(param_1 + 8) + *(int *)(param_1 + 0xc);
    iVar6 = *(int *)(param_1 + 0x358 + param_2 * 4);
    if (iVar6 != 0) {
      FUN_0050ace3(iVar6,0x3c,*(undefined4 *)(iVar6 + -4),FUN_00573650);
      FUN_00507850(iVar6 + -4);
      *(undefined4 *)(param_1 + 0x358 + param_2 * 4) = 0;
    }
    iVar6 = *(int *)(param_1 + 4);
    piVar3 = operator_new(iVar6 * 0x3c + 4);
    puStack_8 = (undefined1 *)0x0;
    if (piVar3 == (int *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = piVar3 + 1;
      *piVar3 = iVar6;
      FUN_0050ac61(piVar5,0x3c,iVar6,&LAB_00573620,FUN_00573650);
    }
    iVar7 = 0;
    *(int **)(param_1 + 0x380) = piVar5;
    puStack_8 = (undefined1 *)0xffffffff;
    *(int **)(param_1 + 0x358 + param_2 * 4) = piVar5;
    iVar6 = *(int *)(param_1 + 0x380);
    if (iVar6 == 0) {
      FUN_00509e57(iVar2);
      uVar4 = 0;
    }
    else {
      *(undefined4 *)(param_1 + 0x14) = 0;
      *(undefined4 *)(param_1 + 0x10) = 0;
      if (0 < *(int *)(param_1 + 8)) {
        do {
          *(int *)(iVar6 + 0x38) = param_1;
          FUN_0050b600(iVar2,s__s__s__s_005d1348,&stack0xffffffa8,&stack0xffffffa8,iVar6);
          FUN_00571c70(iVar2,1);
          FUN_005572d0(iVar2,iVar6);
          FUN_00571c70(iVar2,1);
          iVar7 = iVar7 + 1;
          iVar6 = iVar6 + 0x3c;
        } while (iVar7 < *(int *)(param_1 + 8));
      }
      iVar7 = 0;
      if (0 < *(int *)(param_1 + 0xc)) {
        do {
          *(int *)(iVar6 + 0x38) = param_1;
          FUN_0050b600(iVar2,s__s__s__s_005d1348,&stack0xffffffa8,&stack0xffffffa8,iVar6);
          FUN_00571c70(iVar2,1);
          FUN_00557ab0(iVar2,iVar6);
          FUN_00571c70(iVar2,1);
          iVar7 = iVar7 + 1;
          iVar6 = iVar6 + 0x3c;
        } while (iVar7 < *(int *)(param_1 + 0xc));
      }
      FUN_00509e57(iVar2);
      *(undefined4 *)(param_1 + 0x44) = 1;
      if (*(int *)(param_1 + 0x40) != 0) {
        FUN_00558600();
      }
      iVar2 = *(int *)(param_1 + 0x380);
      piVar3 = aiStack_38;
      for (iVar6 = 10; iVar6 != 0; iVar6 = iVar6 + -1) {
        *piVar3 = 0;
        piVar3 = piVar3 + 1;
      }
      iVar6 = *(int *)(param_1 + 4);
      if (0 < iVar6) {
        piVar3 = (int *)(iVar2 + 0x10);
        do {
          iVar2 = *piVar3;
          if (0 < iVar2) {
            piVar5 = (int *)(piVar3[4] + 0x20);
            do {
              iVar7 = *piVar5;
              if ((-1 < iVar7) && (iVar7 < 10)) {
                aiStack_38[iVar7] = aiStack_38[iVar7] + 1;
              }
              piVar5 = piVar5 + 0xb;
              iVar2 = iVar2 + -1;
            } while (iVar2 != 0);
          }
          piVar3 = piVar3 + 0xf;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      FUN_00557c10(param_2);
      uVar4 = 1;
    }
  }
  ExceptionList = pvStack_10;
  return uVar4;
}

