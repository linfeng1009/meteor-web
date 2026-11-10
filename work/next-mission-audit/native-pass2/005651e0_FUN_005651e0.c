/* Original Meteor.exe static export @ 005651e0; original sample not executed. */
/* XREF 005651c8 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_005651e0(int param_1,float *param_2)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  int *piVar5;
  float local_a4;
  float local_a0;
  float local_9c;
  int iStack_98;
  int iStack_94;
  int *piStack_90;
  float local_8c;
  float local_88;
  float local_84;
  int local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 local_40 [64];
  
  local_58 = 0x41200000;
  local_8c = *param_2 - _DAT_005a84ac;
  local_54 = 0x41200000;
  local_50 = 0x41200000;
  local_88 = param_2[1] - _DAT_005a84ac;
  local_84 = param_2[2] - _DAT_005a84ac;
  local_a4 = *param_2 + _DAT_005a84ac;
  local_a0 = param_2[1] + _DAT_005a84ac;
  local_9c = param_2[2] + _DAT_005a84ac;
  local_80 = param_1;
  local_7c = local_a4;
  local_78 = local_a0;
  local_74 = local_9c;
  FUN_00562dd0(&local_8c,&local_7c);
  local_70 = *param_2 - _DAT_005a8b08;
  local_a4 = 40.0;
  local_a0 = 0.0;
  local_9c = 0.0;
  local_6c = param_2[1] - _DAT_005a8b08;
  local_64 = 0;
  local_60 = 0x42200000;
  local_5c = 0;
  local_4c = 0;
  local_68 = param_2[2];
  local_48 = 0;
  local_44 = 0x42200000;
  FUN_00477200();
  FUN_00477b90(0,&local_a4);
  FUN_00477b90(1,&local_64);
  FUN_00477b90(2,&local_4c);
  FUN_00477b90(3,&local_70);
  FUN_00477b10();
  FUN_00475590(1,1);
  FUN_00475800(&DAT_005c7dd4);
  FUN_00475950(&DAT_005c7df8,&DAT_005c7df0);
  FUN_00479f80(*(undefined4 *)(param_1 + 0x300));
  FUN_00475590(0x14,1);
  FUN_00475590(0x15,1);
  iStack_94 = 0;
  if (0 < *(int *)(param_1 + 0x29c)) {
    do {
      piVar5 = *(int **)(*(int *)(param_1 + 0x2a0) + iStack_94 * 4);
      piStack_90 = piVar5;
      if ((piVar5 != (int *)0x0) && (iStack_98 = 0, 0 < *piVar5)) {
        do {
          iVar1 = FUN_0056aee0(*(undefined4 *)(piVar5[1] + iStack_98 * 4));
          if ((iVar1 != 0) &&
             ((*(char *)(*(int *)(iVar1 + 4) + 0x1fc) != '\0' && (*(int *)(iVar1 + 0x50) == 0)))) {
            pfVar4 = (float *)(iVar1 + 0x1c);
            *(undefined4 *)(iVar1 + 0x50) = 1;
            iVar2 = FUN_00570260(param_2,&local_58,pfVar4,iVar1 + 0x28,iVar1 + 0x34);
            piVar5 = piStack_90;
            if ((iVar2 != 0) && (_DAT_005a8410 < *(float *)(iVar1 + 0x48))) {
              pfVar3 = (float *)(param_1 + 0x310);
              iVar1 = 3;
              do {
                pfVar3[-2] = *pfVar4;
                pfVar3[-1] = pfVar4[1];
                *pfVar3 = pfVar4[2];
                *pfVar3 = *pfVar3 + _DAT_005a8410;
                FUN_00476e80(&local_8c,pfVar3 + -2,local_40);
                param_1 = local_80;
                pfVar3[2] = local_8c;
                pfVar3[3] = local_88;
                pfVar4 = pfVar4 + 3;
                pfVar3 = pfVar3 + 6;
                iVar1 = iVar1 + -1;
              } while (iVar1 != 0);
              FUN_004754f0(0,local_80 + 0x308,3,1);
              piVar5 = piStack_90;
            }
          }
          iStack_98 = iStack_98 + 1;
        } while (iStack_98 < *piVar5);
      }
      iStack_94 = iStack_94 + 1;
    } while (iStack_94 < *(int *)(param_1 + 0x29c));
  }
  FUN_00475590(1,0);
  FUN_00475590(0x14,2);
  FUN_00475590(0x15,2);
  return;
}

