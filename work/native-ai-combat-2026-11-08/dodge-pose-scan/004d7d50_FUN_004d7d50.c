/* Original Meteor.exe read-only export. Sample not executed. */

void FUN_004d7d50(int param_1)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  char *local_a0;
  undefined4 local_9c;
  int local_98;
  undefined4 *local_94;
  undefined4 local_90;
  int local_8c;
  undefined1 local_88 [4];
  undefined2 local_84;
  undefined4 local_80;
  int local_7c;
  int local_78;
  undefined4 local_74 [3];
  undefined2 local_68;
  undefined4 local_64 [16];
  char local_24 [24];
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a20e7;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_78 = FUN_00487830();
  local_78 = local_78 + 0x2498;
  local_7c = FUN_0054b910();
  iVar5 = 0;
  if (0 < local_7c) {
    do {
      FUN_004736a0();
      local_4 = 0;
      local_94 = (undefined4 *)0x0;
      local_90 = 0;
      local_8c = 0;
      FUN_004608a0(8);
      local_4._0_1_ = 1;
      FUN_00402a70();
      local_4._0_1_ = 2;
      local_a0 = (char *)0x0;
      local_9c = 0;
      local_98 = 0;
      FUN_004608a0(8);
      local_4._0_1_ = 3;
      FUN_00402a70();
      local_4 = CONCAT31(local_4._1_3_,4);
      FUN_0054b940(iVar5,local_88,&local_80,&local_94);
      puVar7 = local_64;
      for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = 0;
        puVar7 = puVar7 + 1;
      }
      local_24[0] = '\0';
      local_24[1] = '\0';
      local_24[2] = '\0';
      local_24[3] = '\0';
      local_24[4] = '\0';
      local_24[5] = '\0';
      local_24[6] = '\0';
      local_24[7] = '\0';
      local_24[8] = '\0';
      local_24[9] = '\0';
      local_24[10] = '\0';
      local_24[0xb] = '\0';
      local_24[0xc] = '\0';
      local_24[0xd] = '\0';
      local_24[0xe] = '\0';
      local_24[0xf] = '\0';
      local_24[0x14] = 0;
      local_24[0x10] = '\0';
      local_24[0x11] = '\0';
      local_24[0x12] = '\0';
      local_24[0x13] = '\0';
      iVar4 = FUN_004d76f0(&local_94,local_74);
      if (iVar4 != 0) {
        FUN_00473730(&local_a0);
        local_68 = local_84;
        pcVar2 = local_a0;
        do {
          cVar1 = *pcVar2;
          pcVar2[(int)(local_24 + -(int)local_a0)] = cVar1;
          pcVar2 = pcVar2 + 1;
        } while (cVar1 != '\0');
        local_74[2] = local_80;
        puVar7 = *(undefined4 **)(param_1 + 4);
        if (puVar7 == *(undefined4 **)(param_1 + 8)) {
          FUN_00460df0(puVar7,local_74);
        }
        else {
          if (puVar7 != (undefined4 *)0x0) {
            puVar6 = local_74;
            for (iVar4 = 0x1a; iVar4 != 0; iVar4 = iVar4 + -1) {
              *puVar7 = *puVar6;
              puVar6 = puVar6 + 1;
              puVar7 = puVar7 + 1;
            }
          }
          *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 0x68;
        }
      }
      pcVar2 = local_a0;
      local_4._0_1_ = 2;
      uVar3 = local_98 - (int)local_a0;
      if ((local_a0 != (char *)0x0) && (uVar3 != 0)) {
        if (uVar3 < 0x81) {
          FUN_00402330();
          *(undefined4 *)pcVar2 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
          *(char **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = pcVar2;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(local_a0);
        }
      }
      puVar7 = local_94;
      uVar3 = local_8c - (int)local_94;
      local_4 = (uint)local_4._1_3_ << 8;
      if ((local_94 != (undefined4 *)0x0) && (uVar3 != 0)) {
        if (uVar3 < 0x81) {
          FUN_00402330();
          *puVar7 = *(undefined4 *)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4);
          *(undefined4 **)(&DAT_005d59a4 + (uVar3 + 7 >> 3) * 4) = puVar7;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(local_94);
        }
      }
      iVar5 = iVar5 + 1;
      local_4 = 0xffffffff;
    } while (iVar5 < local_7c);
  }
  ExceptionList = local_c;
  return;
}

