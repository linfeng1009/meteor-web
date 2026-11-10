/* Original Meteor.exe static export @ 004fb8b0; original sample not executed. */
/* XREF 004c0881 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004fb8b0(int param_1)

{
  code *pcVar1;
  char *pcVar2;
  float10 fVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  undefined1 local_60 [32];
  undefined1 local_40 [64];
  
  if (*(int *)(param_1 + 4) == 3) {
    FUN_00501830(local_40);
    FUN_00477d30(3,&local_6c);
    local_84 = local_6c - *(float *)(param_1 + 0x18);
    local_80 = local_68 - *(float *)(param_1 + 0x1c);
    local_7c = local_64 - *(float *)(param_1 + 0x20);
    local_78 = local_84;
    local_74 = local_80;
    local_70 = local_7c;
    fVar3 = (float10)FUN_0047ecf0();
    if (fVar3 <= (float10)_DAT_005ab84c) {
      pcVar1 = *(code **)(param_1 + 100);
      pcVar2 = (char *)&DAT_005d5a24;
      if (pcVar1 == (code *)&LAB_005038e0) {
        pcVar2 = &DAT_005ca1f4;
      }
      else if (pcVar1 == (code *)&LAB_00503970) {
        pcVar2 = &DAT_005ca1ec;
      }
      else if (pcVar1 == (code *)&DAT_00503910) {
        pcVar2 = s_GotoGoal_005ca1e0;
      }
      else if (pcVar1 == (code *)&LAB_00503a00) {
        pcVar2 = s_Patrol_005ca1d8;
      }
      else if (pcVar1 == (code *)&LAB_00503b30) {
        pcVar2 = s_Follow_005ca1d0;
      }
      else if (pcVar1 == FUN_00503d00) {
        pcVar2 = s_RandomRun_005ca1c4;
      }
      else if (pcVar1 == (code *)&LAB_00503e00) {
        pcVar2 = s_Combat_005ca1bc;
      }
      else if (pcVar1 == (code *)&LAB_00504670) {
        pcVar2 = &DAT_005ca1b4;
      }
      else if (pcVar1 == (code *)&LAB_00504560) {
        pcVar2 = s_Dodge_005ca1ac;
      }
      else if (pcVar1 == (code *)&LAB_00504700) {
        pcVar2 = s_AvoidObstacle_005ca19c;
      }
      else if (pcVar1 == (code *)&LAB_005048f0) {
        pcVar2 = s_GetItem_005ca194;
      }
      else if (pcVar1 == (code *)&LAB_005049d0) {
        pcVar2 = s_FastLook_005ca188;
      }
      else if (pcVar1 == (code *)&LAB_00504a70) {
        pcVar2 = s_AttackGoal_005ca17c;
      }
      else if (pcVar1 == (code *)&DAT_00504be0) {
        pcVar2 = s_Perform_005ca050;
      }
      FUN_00508ae6(local_60,s__d_s__d__005ca170,*(undefined4 *)(param_1 + 8),pcVar2,
                   *(undefined4 *)(param_1 + 0x48));
      FUN_00501d90(6);
      if (*(int *)(param_1 + 0x4c) == 1) {
        uVar6 = 0x3f800000;
        uVar5 = 0;
        uVar4 = 0;
      }
      else {
        uVar6 = 0;
        if (*(int *)(param_1 + 0x4c) == 2) {
          uVar5 = 0;
        }
        else {
          uVar5 = 0x3f800000;
        }
        uVar4 = 0x3f800000;
      }
      FUN_00501c90(uVar4,uVar5,uVar6);
      local_84 = *(float *)(param_1 + 0x18);
      local_80 = *(float *)(param_1 + 0x1c);
      local_7c = *(float *)(param_1 + 0x20) + _DAT_005a8e7c;
      FUN_00501780(local_60,&local_84,0x40800000,1);
      FUN_00501d10(6);
    }
  }
  return;
}

