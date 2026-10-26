/* Original Meteor.exe static export @ 0054ec50; original sample not executed. */
/* XREF 004bed40 UNCONDITIONAL_CALL */
/* XREF 004b1d6a UNCONDITIONAL_CALL */
/* XREF 004be823 UNCONDITIONAL_CALL */

void __fastcall FUN_0054ec50(int *param_1)

{
  int iVar1;
  DWORD DVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  int local_24;
  undefined4 uStack_20;
  DWORD local_1c;
  int iStack_18;
  undefined1 local_14 [8];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a493b;
  local_c = ExceptionList;
  if (param_1[5] == 1) {
    ExceptionList = &local_c;
    DVar2 = timeGetTime();
    local_1c = DVar2;
    if (200 < DVar2 - param_1[10]) {
      param_1[10] = DVar2;
      local_24 = *(int *)(param_1[1] + 8);
      if (local_24 != param_1[1]) {
        do {
          iVar5 = *(int *)(local_24 + 0x14);
          FUN_005542f0(300);
          uVar3 = FUN_0054feb0();
          if (uVar3 < DVar2 - *(int *)(iVar5 + 0x18)) {
            *(undefined1 *)(iVar5 + 0x9c) = 1;
            *(undefined4 *)(iVar5 + 0xa0) = 3;
          }
          if (*(char *)(iVar5 + 0x9c) == '\0') {
            iVar5 = *(int *)(local_24 + 0xc);
            if (iVar5 == 0) {
              iVar5 = *(int *)(local_24 + 4);
              if (local_24 == *(int *)(iVar5 + 0xc)) {
                do {
                  local_24 = iVar5;
                  iVar5 = *(int *)(local_24 + 4);
                } while (local_24 == *(int *)(iVar5 + 0xc));
              }
              if (*(int *)(local_24 + 0xc) != iVar5) {
                local_24 = iVar5;
              }
            }
            else {
              for (iVar1 = *(int *)(iVar5 + 8); local_24 = iVar5, iVar1 != 0;
                  iVar1 = *(int *)(iVar1 + 8)) {
                iVar5 = iVar1;
              }
            }
          }
          else {
            (**(code **)(*param_1 + 8))(*(undefined4 *)(iVar5 + 0x10),*(undefined4 *)(iVar5 + 0xa0))
            ;
            FUN_0043c6c0();
            iVar1 = param_1[1];
            puVar4 = (undefined4 *)FUN_0048ea60(local_24,iVar1 + 4,iVar1 + 8,iVar1 + 0xc);
            FUN_00402330();
            *puVar4 = DAT_005d59b0;
            DAT_005d59e8 = 0;
            DAT_005d59b0 = puVar4;
            param_1[2] = param_1[2] + -1;
            uStack_4 = 1;
            iStack_18 = iVar5;
            FUN_00553c20();
            uStack_4 = 0xffffffff;
            FUN_00507850(iVar5);
            param_1[4] = param_1[4] + -1;
            DVar2 = local_1c;
          }
        } while (local_24 != param_1[1]);
      }
    }
    FUN_004736a0();
    uStack_4 = 2;
    uStack_20 = 0xffffffff;
    iVar5 = FUN_0054f310(&DAT_007253a8,local_14,&uStack_20);
    while (0 < iVar5) {
      (**(code **)(*param_1 + 0x1c))(&DAT_007253a8,local_14,uStack_20);
      iVar5 = FUN_0054f310(&DAT_007253a8,local_14,&uStack_20);
    }
  }
  ExceptionList = local_c;
  return;
}

