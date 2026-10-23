/* Meteor.exe original x86 @ 004d2dd0 */
/* Caller: 004d2ad6 */

/* WARNING: Removing unreachable block (ram,0x004d2e14) */
/* WARNING: Removing unreachable block (ram,0x004d2e27) */
/* WARNING: Removing unreachable block (ram,0x004d2e49) */
/* WARNING: Removing unreachable block (ram,0x004d2e23) */

void __thiscall FUN_004d2dd0(int *param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_1[1];
  uVar1 = (iVar2 - *param_1) / 0xc;
  if (uVar1 <= param_2) {
    FUN_004d3290(iVar2,param_2 - uVar1,param_3);
    return;
  }
  iVar2 = (int)((ulonglong)((longlong)(int)(iVar2 - (*param_1 + param_2 * 0xc)) * -0x2aaaaaab) >>
               0x20);
  param_1[1] = param_1[1] + ((iVar2 >> 1) - (iVar2 >> 0x1f)) * 0xc;
  return;
}

