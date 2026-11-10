/* Original Meteor.exe static export @ 0057f180; original sample not executed. */
/* XREF 0056b4fb UNCONDITIONAL_CALL */

undefined1 __thiscall FUN_0057f180(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined1 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_80 [16];
  undefined1 local_40 [64];
  
  if (*(char *)(param_4 + 0x124) == '\0') {
    iVar3 = param_1 + 0x158;
  }
  else {
    iVar3 = *(int *)(param_1 + 4) * 0x40 + *(int *)(param_4 + 0x158);
  }
  puVar2 = (undefined4 *)FUN_00476f00(local_40,iVar3,param_4 + 0x54);
  puVar4 = local_80;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar4 = puVar4 + 1;
  }
  uVar1 = FUN_00570630(param_2,param_3,param_1 + 0x198,local_80);
  return uVar1;
}

