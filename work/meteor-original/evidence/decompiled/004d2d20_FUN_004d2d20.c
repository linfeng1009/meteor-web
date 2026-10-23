/* Meteor.exe original x86 @ 004d2d20 */
/* Caller: 004d2b56 */

/* WARNING: Removing unreachable block (ram,0x004d2d70) */
/* WARNING: Removing unreachable block (ram,0x004d2d74) */
/* WARNING: Removing unreachable block (ram,0x004d2d82) */
/* WARNING: Removing unreachable block (ram,0x004d2d84) */
/* WARNING: Removing unreachable block (ram,0x004d2d86) */

void __thiscall FUN_004d2d20(int *param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  uVar1 = (iVar2 - *param_1) / 0x28;
  if (uVar1 <= param_2) {
    FUN_004d2e90(iVar2,param_2 - uVar1,param_3);
    return;
  }
  iVar2 = (int)((ulonglong)((longlong)(int)(iVar2 - (*param_1 + param_2 * 0x28)) * -0x66666667) >>
               0x20);
  param_1[1] = param_1[1] + ((iVar2 >> 4) - (iVar2 >> 0x1f)) * 0x28;
  return;
}

