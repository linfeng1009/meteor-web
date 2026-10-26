/* Original Meteor.exe static export @ 00564140; original sample not executed. */
/* XREF 0056411c UNCONDITIONAL_CALL */
/* XREF 00564f72 UNCONDITIONAL_CALL */

void __fastcall FUN_00564140(int param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  int *piVar3;
  int local_44;
  undefined1 local_38 [20];
  undefined **ppuStack_24;
  undefined4 uStack_20;
  int iStack_1c;
  undefined4 *puStack_18;
  undefined4 *puStack_14;
  undefined4 *puStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a56e8;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  if (*(int **)(param_1 + 0x6cc) != (int *)0x0) {
    ExceptionList = &pvStack_c;
    (**(code **)(**(int **)(param_1 + 0x6cc) + 4))();
  }
  if (*(int *)(param_1 + 0x4b4) != 0) {
    local_44 = 0;
    if (0 < *(int *)(param_1 + 0x4b0)) {
      piVar3 = (int *)(*(int *)(param_1 + 0x4b4) + 0x34);
      do {
        if (*piVar3 != 0) {
          FUN_005783a0();
          uStack_4 = 0;
          puStack_18 = (undefined4 *)0x0;
          puStack_14 = (undefined4 *)0x0;
          puStack_10 = (undefined4 *)0x0;
          puStack_18 = (undefined4 *)FUN_00402bf0(8);
          puStack_10 = puStack_18 + 2;
          uStack_4._0_1_ = 3;
          puStack_14 = puStack_18;
          FUN_00402a70();
          uStack_20 = 0;
          ppuStack_24 = &PTR_LAB_005ab82c;
          uStack_4 = CONCAT31(uStack_4._1_3_,4);
          iStack_1c = local_44;
          FUN_005785c0(&ppuStack_24);
          FUN_00570fc0(local_38);
          (**(code **)(*(int *)*piVar3 + 4))();
          puVar1 = puStack_18;
          uVar2 = (int)puStack_10 - (int)puStack_18;
          ppuStack_24 = &PTR_LAB_005ab82c;
          if ((puStack_18 != (undefined4 *)0x0) && (uVar2 != 0)) {
            if (uVar2 < 0x81) {
              FUN_00402330();
              *puVar1 = *(undefined4 *)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4);
              *(undefined4 **)(&DAT_005d59a4 + (uVar2 + 7 >> 3) * 4) = puVar1;
              FUN_00443330();
            }
            else {
              FUN_005089fd(puStack_18);
            }
          }
          uStack_4 = 0xffffffff;
          FUN_005783c0();
        }
        local_44 = local_44 + 1;
        piVar3 = piVar3 + 0x2b;
      } while (local_44 < *(int *)(param_1 + 0x4b0));
    }
  }
  ExceptionList = pvStack_c;
  return;
}

