/* Decompiled from user's Meteor.exe; address: 004e82e0 */
/* String anchors: [common\character.act, common\character.amb, common\character.act, common\character.amb] */

void __fastcall FUN_004e82e0(int *param_1)

{
  int iVar1;
  
  (**(code **)(*param_1 + 0x40))(s_pmodel__005c9eec);
  FUN_00508ae6(param_1 + 0x56,s_ptexture__005c9e08);
  FUN_00574930(s_common_character_act_005c967c);
  iVar1 = FUN_00574460(s_common_character_amb_005c9ed4);
  if (iVar1 == 0) {
    FUN_00574460(s_common_character_amc_005c9ebc);
  }
  param_1[0xa6] = -1;
  return;
}

