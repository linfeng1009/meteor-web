/* Original Meteor.exe static export @ 004db580; original sample not executed. */
/* XREF 004db563 UNCONDITIONAL_CALL */
/* XREF 004db465 UNCONDITIONAL_CALL */

void __fastcall FUN_004db580(undefined4 *param_1)

{
  int *piVar1;
  uint uVar2;
  LONG LVar3;
  uint uVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005a26e7;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  *param_1 = &PTR_FUN_005aa94c;
  local_4 = 0;
  piVar1 = *(int **)param_1[10];
  if (piVar1 != (undefined4 *)param_1[10]) {
    do {
      piVar5 = piVar1;
      piVar1 = (int *)*piVar5;
      FUN_00402330();
      *piVar5 = (int)DAT_005d59ac;
      DAT_005d59e8 = 0;
      DAT_005d59ac = piVar5;
    } while (piVar1 != (int *)param_1[10]);
  }
  *(undefined4 *)param_1[10] = param_1[10];
  *(undefined4 *)(param_1[10] + 4) = param_1[10];
  piVar1 = (int *)param_1[10];
  LVar3 = InterlockedExchange(&DAT_005d59e8,1);
  uVar2 = DAT_005c4248;
  if (LVar3 != 0) {
    uVar6 = 0;
    if (DAT_005c4248 != 0) {
      uVar4 = DAT_005d59ec >> 1;
      do {
        if (((uVar4 <= uVar6) && (DAT_005d59e8 == 0)) &&
           (LVar3 = InterlockedExchange(&DAT_005d59e8,1), LVar3 == 0)) {
          DAT_005c4248 = 1000;
          DAT_005d59ec = uVar6;
          goto LAB_004db6e7;
        }
        uVar6 = uVar6 + 1;
      } while (uVar6 < uVar2);
    }
    DAT_005c4248 = 0x1e;
    iVar8 = 6;
    while( true ) {
      iVar7 = iVar8;
      if (0x1b < iVar8) {
        iVar7 = 0x1b;
      }
      LVar3 = InterlockedExchange(&DAT_005d59e8,1);
      if (LVar3 == 0) break;
      if (iVar7 < 0x15) {
        Sleep(0);
        iVar8 = iVar8 + 1;
      }
      else {
        Sleep(1 << ((char)iVar7 - 0x14U & 0x1f));
        iVar8 = iVar8 + 1;
      }
    }
  }
LAB_004db6e7:
  local_4 = 0xffffffff;
  *piVar1 = (int)DAT_005d59ac;
  DAT_005d59e8 = 0;
  DAT_005d59ac = piVar1;
  FUN_005665b0();
  ExceptionList = local_c;
  return;
}

