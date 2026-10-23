/* Meteor.exe original x86 @ 004f0ba0 */
/* Caller: 004bc5a4 */
/* Caller: 005ab4a4 */
/* Caller: 005ab8e4 */
/* Caller: 005ab264 */

undefined4 __fastcall FUN_004f0ba0(int *param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uStack_10;
  undefined4 uStack_c;
  
  uStack_c = 0x4f0ba9;
  piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
  uStack_c = 0x4f0bb3;
  iVar2 = (**(code **)(*piVar1 + 0x1e0))();
  if (iVar2 != 0) {
    uStack_c = 0x4f0bc2;
    piVar1 = (int *)(**(code **)(*param_1 + 0x44))();
    uStack_c = 0;
    uStack_10 = 0x4f0bce;
    (**(code **)(*piVar1 + 0x1dc))();
    uStack_10 = 0x4f0bd3;
    piVar1 = (int *)FUN_00487830();
    (**(code **)(*piVar1 + 0x168))(param_1[0x95]);
    FUN_0054a6c0(6,&uStack_10,4,1);
    return 1;
  }
  return 0;
}

