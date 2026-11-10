/* Original Meteor.exe static export @ 004c8a70; original sample not executed. */
/* XREF 004c88cf UNCONDITIONAL_CALL */
/* XREF 005aa664 DATA */

/* WARNING: Removing unreachable block (ram,0x004c8b6b) */
/* WARNING: Removing unreachable block (ram,0x004c8b7d) */
/* WARNING: Removing unreachable block (ram,0x004c8b79) */

void __fastcall FUN_004c8a70(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_4;
  
  iVar2 = param_1[2];
  if (iVar2 != param_1[3]) {
    do {
      if (*(int *)(iVar2 + 4) != 0) {
        FUN_00507850(*(int *)(iVar2 + 4));
      }
      iVar2 = iVar2 + 0x10;
    } while (iVar2 != param_1[3]);
  }
  iVar2 = param_1[2];
  iVar1 = param_1[3];
  FUN_004cab30(iVar1,iVar1,iVar2,local_4,0);
  param_1[3] = param_1[3] + (iVar1 - iVar2 >> 4) * -0x10;
  iVar2 = param_1[6];
  iVar1 = param_1[7];
  FUN_004cab80(iVar1,iVar1,iVar2,local_4,0);
  iVar2 = (int)((ulonglong)((longlong)(iVar1 - iVar2) * -0x2aaaaaab) >> 0x20);
  param_1[7] = param_1[7] + ((iVar2 >> 1) - (iVar2 >> 0x1f)) * 0xc;
  iVar2 = param_1[0x12];
  iVar1 = param_1[0x13];
  FUN_004cab80(iVar1,iVar1,iVar2,local_4,0);
  iVar2 = (int)((ulonglong)((longlong)(iVar1 - iVar2) * -0x2aaaaaab) >> 0x20);
  param_1[0x13] = param_1[0x13] + ((iVar2 >> 1) - (iVar2 >> 0x1f)) * 0xc;
  iVar2 = param_1[10];
  iVar1 = param_1[0xb];
  FUN_004c6050(iVar1,iVar1,iVar2,local_4,0);
  param_1[0xb] = param_1[0xb] + (iVar1 - iVar2 >> 3) * -8;
  param_1[0xf] = param_1[0xf] + (param_1[0xf] - param_1[0xe] >> 4) * -0x10;
                    /* WARNING: Could not recover jumptable at 0x004c8bc2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*param_1 + 0xc))();
  return;
}

