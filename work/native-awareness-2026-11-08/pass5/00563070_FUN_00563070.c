/* Original Meteor.exe static export @ 00563070; original sample not executed. */
/* XREF 004c1352 UNCONDITIONAL_CALL */
/* XREF 004cf461 UNCONDITIONAL_CALL */
/* XREF 004dc5e0 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_00563070(int param_1,float *param_2,float *param_3,undefined4 *param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  undefined1 local_40 [64];
  
  if (((*param_3 < *param_2) || (param_3[1] < param_2[1])) || (param_3[2] < param_2[2])) {
    local_70 = *param_3;
    local_6c = param_3[1];
    local_68 = param_3[2];
    local_7c = *param_2;
    local_78 = param_2[1];
    local_74 = param_2[2];
  }
  else {
    local_70 = *param_2;
    local_6c = param_2[1];
    local_68 = param_2[2];
    local_7c = *param_3;
    local_78 = param_3[1];
    local_74 = param_3[2];
  }
  FUN_00562dd0(&local_70,&local_7c);
  if ((*(char *)(param_1 + 0x251) != '\0') && (*(int *)(param_1 + 0x29c) != 0)) {
    local_70 = (local_7c + local_70) * _DAT_005a83e8;
    local_6c = (local_78 + local_6c) * _DAT_005a83e8;
    local_68 = (local_74 + local_68) * _DAT_005a83e8;
    local_64 = local_7c - local_70;
    local_60 = local_78 - local_6c;
    local_5c = local_74 - local_68;
    local_58 = local_70;
    local_54 = local_6c;
    local_50 = local_68;
    local_4c = local_64;
    local_48 = local_60;
    local_44 = local_5c;
    FUN_00477200();
    FUN_00477b90(3,&local_58);
    local_80 = 0;
    if (0 < *(int *)(param_1 + 0x29c)) {
      do {
        iVar4 = 0;
        piVar1 = *(int **)(*(int *)(param_1 + 0x2a0) + local_80 * 4);
        if (0 < *piVar1) {
          do {
            iVar2 = FUN_0056aee0(*(undefined4 *)(piVar1[1] + iVar4 * 4));
            if (*(int *)(iVar2 + 0x50) == 0) {
              *(undefined4 *)(iVar2 + 0x50) = 1;
              iVar3 = FUN_00570260(&local_58,&local_4c,iVar2 + 0x1c,iVar2 + 0x28,iVar2 + 0x34);
              if (iVar3 != 0) {
                if (param_4 == (undefined4 *)0x0) {
                  return 1;
                }
                *param_4 = *(undefined4 *)(iVar2 + 0x40);
                param_4[1] = *(undefined4 *)(iVar2 + 0x44);
                param_4[2] = *(undefined4 *)(iVar2 + 0x48);
                return 1;
              }
            }
            iVar4 = iVar4 + 1;
          } while (iVar4 < *piVar1);
        }
        uVar5 = 0;
        if (piVar1[0x14] - piVar1[0x13] >> 2 != 0) {
          do {
            iVar4 = *(int *)(piVar1[0x13] + uVar5 * 4);
            if (((*(char *)(iVar4 + 8) != '\0') && (*(char *)(iVar4 + 10) != '\0')) &&
               ((*(int *)(iVar4 + 0x2c) != 0 &&
                (iVar4 = FUN_0056b4a0(&local_4c,local_40), iVar4 != 0)))) {
              return 1;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 < (uint)(piVar1[0x14] - piVar1[0x13] >> 2));
        }
        local_80 = local_80 + 1;
      } while (local_80 < *(int *)(param_1 + 0x29c));
    }
  }
  return 0;
}

