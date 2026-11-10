/* Original Meteor.exe static export @ 00583cb0; original sample not executed. */
/* XREF 005b0ee8 DATA */

/* WARNING: Removing unreachable block (ram,0x00584157) */
/* WARNING: Removing unreachable block (ram,0x00584130) */
/* WARNING: Removing unreachable block (ram,0x0058410c) */
/* WARNING: Removing unreachable block (ram,0x005840da) */
/* WARNING: Removing unreachable block (ram,0x005840b6) */
/* WARNING: Removing unreachable block (ram,0x00583f5f) */
/* WARNING: Removing unreachable block (ram,0x00583f5b) */
/* WARNING: Removing unreachable block (ram,0x00583f83) */
/* WARNING: Removing unreachable block (ram,0x00583f8b) */
/* WARNING: Removing unreachable block (ram,0x00583fa0) */
/* WARNING: Removing unreachable block (ram,0x00583f92) */
/* WARNING: Removing unreachable block (ram,0x005840ba) */
/* WARNING: Removing unreachable block (ram,0x005840de) */
/* WARNING: Removing unreachable block (ram,0x00584110) */
/* WARNING: Removing unreachable block (ram,0x00584134) */
/* WARNING: Removing unreachable block (ram,0x0058415b) */

void __fastcall FUN_00583cb0(int param_1)

{
  char cVar1;
  char *pcVar2;
  void *pvVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  undefined1 auStack_8c [128];
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a695c;
  pvStack_c = ExceptionList;
  if ((*(char *)(*(int *)(param_1 + 8) + 0x58) != '\0') &&
     (*(int *)(param_1 + 0x26c) != *(int *)(param_1 + 0x268))) {
    ExceptionList = &pvStack_c;
    pcVar2 = (char *)FUN_004807d0(*(int *)(param_1 + 0x268));
    uVar6 = 0xffffffff;
    uStack_4 = 0;
    pcVar7 = pcVar2;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    FUN_00402ac0(pcVar2,pcVar2 + (~uVar6 - 1));
    uStack_4 = 1;
    pcVar2 = (char *)FUN_004807f0(*(undefined4 *)(param_1 + 0x268));
    uVar6 = 0xffffffff;
    uStack_4._0_1_ = 2;
    pcVar7 = pcVar2;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    FUN_00402ac0(pcVar2,pcVar2 + (~uVar6 - 1));
    uStack_4._0_1_ = 3;
    pcVar2 = (char *)FUN_00478ea0(0);
    uVar6 = 0xffffffff;
    uStack_4._0_1_ = 4;
    pcVar7 = pcVar2;
    do {
      if (uVar6 == 0) break;
      uVar6 = uVar6 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    FUN_00402ac0(pcVar2,pcVar2 + (~uVar6 - 1));
    iVar5 = *(int *)(param_1 + 0x274);
    uStack_4._0_1_ = 5;
    if (iVar5 != 0) {
      FUN_0055beb0();
      FUN_00507850(iVar5);
      *(undefined4 *)(param_1 + 0x274) = 0;
    }
    pvVar3 = operator_new(0x65c);
    uStack_4._0_1_ = 6;
    if (pvVar3 == (void *)0x0) {
      uVar4 = 0;
    }
    else {
      uVar4 = FUN_0055bd60();
    }
    uStack_4._0_1_ = 5;
    *(undefined4 *)(param_1 + 0x274) = uVar4;
    FUN_00478ec0(0,0);
    FUN_00508ae6(auStack_8c,s__s_s_skc_005d2f00,0,0);
    iVar5 = FUN_00557c70(auStack_8c,0);
    if (iVar5 == 0) {
      pcVar7 = s_Load_Skin_Fail__005d2ee8;
    }
    else {
      FUN_00508ae6(auStack_8c,s__s_s_bnc_005d2edc,0,0);
      iVar5 = FUN_00556a20(auStack_8c);
      if (iVar5 == 0) {
        pcVar7 = s_Load_Bone_Fail__005d2ecc;
      }
      else {
        FUN_00508ae6(auStack_8c,s__scharacter_amb_005d2ebc,0);
        iVar5 = FUN_005571f0(auStack_8c);
        if (iVar5 == 0) {
          pcVar7 = s_Load_Common_Animation_Fail__005d2ea0;
        }
        else {
          FUN_00508ae6(auStack_8c,s__s_s_amb_005d2e94,0,0);
          iVar5 = FUN_00557230(auStack_8c);
          if (iVar5 != 0) {
            FUN_00508ae6(auStack_8c,s__s_s_pos_005d15a4,0,0);
            iVar5 = FUN_0055c580(auStack_8c);
            if (iVar5 == 0) {
              MessageBoxA((HWND)0x0,s_Error_Found_in_Pose_005d2e68,s_Warning_005d2ef8,0);
            }
            FUN_0055d260(*(undefined4 *)(param_1 + 0x924),0,0,0xc0a00000,1);
            if (*(int *)(param_1 + 0x91c) != 0) {
              uStack_4._0_1_ = 7;
              FUN_00402ac0(*(undefined4 *)(param_1 + 0x8e0),*(undefined4 *)(param_1 + 0x8e4));
              uStack_4._0_1_ = 9;
              FUN_00402ac0(*(undefined4 *)(param_1 + 0x8ec),*(undefined4 *)(param_1 + 0x8f0));
              uStack_4._0_1_ = 10;
              FUN_005842d0(0,0);
              uStack_4._0_1_ = 5;
            }
            FUN_00478ec0(0,0);
            ExceptionList = pvStack_c;
            return;
          }
          pcVar7 = s_Load_Animation_Fail__005d2e7c;
        }
      }
    }
    MessageBoxA((HWND)0x0,pcVar7,s_Warning_005d2ef8,0);
    FUN_00478ec0(0,0);
    iVar5 = *(int *)(param_1 + 0x274);
    if (iVar5 != 0) {
      FUN_0055beb0();
      FUN_00507850(iVar5);
      *(undefined4 *)(param_1 + 0x274) = 0;
    }
  }
  ExceptionList = pvStack_c;
  return;
}

