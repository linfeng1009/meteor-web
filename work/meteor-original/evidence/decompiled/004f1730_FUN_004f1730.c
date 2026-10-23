/* Meteor.exe original x86 @ 004f1730 */
/* Caller: 005aa04c */
/* Caller: 005ab4d4 */
/* Caller: 005ab914 */
/* Caller: 005ab294 */

undefined4 __fastcall FUN_004f1730(int *param_1)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int local_18;
  int local_14;
  void *local_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_005a36e8;
  pvStack_c = ExceptionList;
  uVar5 = 0;
  local_18 = 0;
  local_14 = 0;
  local_10 = (void *)0x0;
  local_4 = 0;
  ExceptionList = &pvStack_c;
  (**(code **)(*param_1 + 0x74))(&local_18);
  uVar4 = (local_18 - (int)param_1) / 0xc;
  if (uVar4 == 0) {
    iVar3 = (local_14 - (int)param_1) / 0xc;
    if (iVar3 != 0) {
      uVar4 = iVar3 * 0xc;
      if (0x80 < uVar4) {
        FUN_005089fd(param_1);
        ExceptionList = local_10;
        return 0;
      }
      FUN_00402330();
      *param_1 = *(int *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
      *(int **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = param_1;
      DAT_005d59e8 = 0;
    }
    ExceptionList = local_10;
    return 0;
  }
  pvVar2 = operator_new(uVar4);
  iVar3 = local_18 - (int)param_1 >> 0x1f;
  if ((local_18 - (int)param_1) / 0xc + iVar3 != iVar3) {
    iVar3 = 0;
    do {
      iVar1 = iVar3 + 4;
      iVar3 = iVar3 + 0xc;
      *(undefined1 *)(uVar5 + (int)pvVar2) = *(undefined1 *)(iVar1 + (int)param_1);
      uVar5 = uVar5 + 1;
    } while (uVar5 < (uint)((local_18 - (int)param_1) / 0xc));
  }
  FUN_0054a6c0(0x1f,pvVar2,(local_18 - (int)param_1) / 0xc,1);
  FUN_00507850(pvVar2);
  iVar3 = (local_14 - (int)param_1) / 0xc;
  if (iVar3 != 0) {
    uVar4 = iVar3 * 0xc;
    if (0x80 < uVar4) {
      FUN_005089fd(param_1);
      ExceptionList = local_10;
      return 1;
    }
    FUN_00402330();
    *param_1 = *(int *)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4);
    *(int **)(&DAT_005d59a4 + (uVar4 + 7 >> 3) * 4) = param_1;
    DAT_005d59e8 = 0;
  }
  ExceptionList = local_10;
  return 1;
}

