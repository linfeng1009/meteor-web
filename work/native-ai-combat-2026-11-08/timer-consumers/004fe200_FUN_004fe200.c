/* Original Meteor.exe read-only export. Sample not executed. */

void __fastcall FUN_004fe200(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  undefined4 *puVar6;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  undefined1 local_6c [12];
  int local_60;
  undefined1 local_5c [16];
  undefined1 local_4c [16];
  undefined1 local_3c [48];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005a3da8;
  local_c = ExceptionList;
  local_60 = param_1[9];
  iVar1 = param_1[6];
  iVar2 = param_1[7];
  iVar3 = param_1[8];
  local_4 = 0;
  ExceptionList = &local_c;
  FUN_004e6050(param_1 + 2);
  local_70 = local_60;
  local_7c = iVar1;
  local_78 = iVar2;
  local_74 = iVar3;
  FUN_004e6050(local_5c);
  FUN_004e6050(&local_7c);
  FUN_004e6050(local_6c);
  FUN_004e6050(local_4c);
  FUN_004e6050(local_3c);
  if (*param_1 != 0) {
    iVar1 = param_1[9];
    for (puVar6 = (undefined4 *)param_1[5]; puVar6 < (undefined4 *)(iVar1 + 4); puVar6 = puVar6 + 1)
    {
      FUN_005089fd(*puVar6);
    }
    piVar4 = (int *)*param_1;
    if (param_1[1] != 0) {
      uVar5 = param_1[1] * 4;
      if (uVar5 < 0x81) {
        FUN_00402330();
        *piVar4 = *(int *)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4);
        *(int **)(&DAT_005d59a4 + (uVar5 + 7 >> 3) * 4) = piVar4;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(piVar4);
      }
    }
  }
  ExceptionList = local_c;
  return;
}

