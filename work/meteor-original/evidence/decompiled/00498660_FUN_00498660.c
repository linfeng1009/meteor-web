/* Decompiled from user's Meteor.exe; address: 00498660 */
/* String anchors: [common\character.act, PscriptLib\jug.pst, PscriptLib\chair.pst, PscriptLib\desk.pst, PscriptLib\box.pst, PscriptLib\def.pst, common\character.act] */

undefined4 __thiscall FUN_00498660(int *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  undefined8 uVar4;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059eddb;
  local_c = ExceptionList;
  if (param_1[0x902] == 0) {
    ExceptionList = &local_c;
    puVar1 = operator_new(8);
    param_1[0x902] = (int)puVar1;
    *puVar1 = 0;
    puVar1[1] = 0;
    uVar4 = FUN_00476120(s_common_character_act_005c967c);
    *(int *)(param_1[0x902] + 4) = *(int *)(param_1[0x902] + 4) + (int)((ulonglong)uVar4 >> 0x20);
    *(int *)param_1[0x902] = *(int *)param_1[0x902] + (int)uVar4;
    if (param_1[0x860] == 0) {
      pvVar2 = operator_new(0x2a0);
      local_4 = 0;
      if (pvVar2 == (void *)0x0) {
        iVar3 = 0;
      }
      else {
        iVar3 = FUN_004e7e00();
      }
      local_4 = 0xffffffff;
      param_1[0x860] = iVar3;
      (**(code **)(*param_1 + 0x68))(iVar3,1);
    }
    uVar4 = FUN_00476120(s_PscriptLib_def_pst_005c9668);
    *(int *)(param_1[0x902] + 4) = *(int *)(param_1[0x902] + 4) + (int)((ulonglong)uVar4 >> 0x20);
    *(int *)param_1[0x902] = *(int *)param_1[0x902] + (int)uVar4;
    uVar4 = FUN_00476120(s_PscriptLib_box_pst_005c9654);
    *(int *)(param_1[0x902] + 4) = *(int *)(param_1[0x902] + 4) + (int)((ulonglong)uVar4 >> 0x20);
    *(int *)param_1[0x902] = *(int *)param_1[0x902] + (int)uVar4;
    uVar4 = FUN_00476120(s_PscriptLib_desk_pst_005c9640);
    *(int *)(param_1[0x902] + 4) = *(int *)(param_1[0x902] + 4) + (int)((ulonglong)uVar4 >> 0x20);
    *(int *)param_1[0x902] = *(int *)param_1[0x902] + (int)uVar4;
    uVar4 = FUN_00476120(s_PscriptLib_chair_pst_005c9628);
    *(int *)(param_1[0x902] + 4) = *(int *)(param_1[0x902] + 4) + (int)((ulonglong)uVar4 >> 0x20);
    *(int *)param_1[0x902] = *(int *)param_1[0x902] + (int)uVar4;
    uVar4 = FUN_00476120(s_PscriptLib_jug_pst_005c9614);
    *(int *)(param_1[0x902] + 4) = *(int *)(param_1[0x902] + 4) + (int)((ulonglong)uVar4 >> 0x20);
    *(int *)param_1[0x902] = *(int *)param_1[0x902] + (int)uVar4;
  }
  puVar1 = (undefined4 *)param_1[0x902];
  *param_2 = *puVar1;
  param_2[1] = puVar1[1];
  ExceptionList = local_c;
  return 1;
}

