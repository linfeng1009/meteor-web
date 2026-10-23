/* Decompiled from user's Meteor.exe; address: 004dbc30 */
/* String anchors: [Load Pose Fail %s, %s_300.skc, %s_800.skc, %s.amb, %s.bnc, %s.skc, Load Pose Fail %s, %s_300.skc, %s_800.skc, %s.amb, %s.bnc, %s.skc] */

undefined4 __thiscall
FUN_004dbc30(int *param_1,undefined4 param_2,int param_3,int param_4,undefined4 param_5,int param_6)

{
  int iVar1;
  char *pcVar2;
  undefined1 local_600 [256];
  undefined1 local_500 [256];
  undefined1 local_400 [256];
  undefined1 local_300 [256];
  undefined1 local_200 [256];
  undefined1 local_100 [256];
  
  if (param_3 == 0) {
    FUN_00508ae6(local_600,&DAT_005c67ac,param_2);
  }
  else {
    FUN_00508ae6(local_600,&DAT_005c4538,param_3,param_2);
  }
  FUN_00478ec0(s_ptexture__005c9e08,0);
  FUN_00508ae6(local_100,s__s_skc_005c9e00,local_600);
  FUN_00508ae6(local_200,s__s_pos_005c9df8,local_600);
  FUN_00508ae6(local_300,s__s_bnc_005c9df0,local_600);
  FUN_00508ae6(local_500,s__s_amb_005c9de8,local_600);
  FUN_005598f0(param_5);
  if (param_6 == 1) {
LAB_004dbd29:
    FUN_00508ae6(local_400,s__s_800_skc_005c9dc4,local_600);
    iVar1 = FUN_00557c70(local_400,1 - param_6);
    if (iVar1 == 0) {
      FUN_004e8500(s_Load_Skin_800_Fail__s_005c9dac,local_600);
    }
  }
  else if (param_6 != 2) {
    iVar1 = FUN_00557c70(local_100,0);
    if (iVar1 == 0) {
      FUN_004e8500(s_Load_Skin_1500_Fail__s_005c9dd0,local_600);
    }
    goto LAB_004dbd29;
  }
  FUN_00508ae6(local_400,s__s_300_skc_005c9da0,local_600);
  iVar1 = FUN_00557c70(local_400,2 - param_6);
  if (iVar1 == 0) {
    FUN_004e8500(s_Load_Skin_300_Fail__s_005c9d88,local_600);
  }
  iVar1 = FUN_00556a20(local_300);
  if (iVar1 == 0) {
    FUN_004e8500(s_Load_Bone_Fail__s_005c9d74,local_300);
  }
  if (param_4 == 0) {
    iVar1 = FUN_005571f0(local_500);
    if (iVar1 != 0) goto LAB_004dbe9b;
    FUN_00508ae6(local_500,s__s_amc_005c9d6c,local_600);
    iVar1 = FUN_005571f0(local_500);
    if (iVar1 != 0) goto LAB_004dbe9b;
    pcVar2 = s_Load_Full_Animation_Fail__s_005c9d30;
  }
  else {
    FUN_005570e0(param_4,0);
    iVar1 = FUN_00557230(local_500);
    if (iVar1 != 0) goto LAB_004dbe9b;
    FUN_00508ae6(local_500,s__s_amc_005c9d6c,local_600);
    iVar1 = FUN_00557230(local_500);
    if (iVar1 != 0) goto LAB_004dbe9b;
    pcVar2 = s_Load_Single_Animation_Fail__s_005c9d4c;
  }
  FUN_004e8500(pcVar2,local_500);
LAB_004dbe9b:
  iVar1 = FUN_0055c580(local_200);
  if (iVar1 == 0) {
    FUN_004e8500(s_Load_Pose_Fail__s_005c9d1c,local_200);
  }
  FUN_0055d260(0,1,0,0xc0a00000,1);
  if (param_1[0x214] == 0) {
    FUN_004059e0(5);
    iVar1 = FUN_00405df0(0);
    param_1[0x214] = iVar1;
  }
  (**(code **)(*param_1 + 0x78))();
  FUN_00559720(0x3df5c28f);
  return 1;
}

