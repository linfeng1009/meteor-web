/* Original Meteor.exe static export @ 0059641a; original sample not executed. */
/* XREF 005b375c DATA */
/* XREF 005b3780 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_0059641a(undefined4 *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6,
            undefined4 param_7,undefined4 param_8,undefined4 param_9,double *param_10)

{
  float10 fVar1;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_5c;
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  double local_44;
  double local_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  undefined4 uStack_18;
  uint local_14;
  uint local_10;
  uint local_c;
  undefined4 *local_8;
  
  local_8 = param_1;
  if (param_5 == 0) {
    local_14 = FUN_00595770(param_2,param_6,param_7,0,param_4 + -1);
    local_10 = FUN_00595770(param_2,param_8,param_9,0,param_4 + -1);
  }
  else {
    local_14 = FUN_005957d0(param_5,param_2,param_4,param_6,param_7);
    local_10 = FUN_005957d0(param_5,param_2,param_4,param_8,param_9);
  }
  *(undefined4 *)param_10 = 0;
  *(undefined4 *)((int)param_10 + 4) = 0;
  local_c = local_14;
  while( true ) {
    if (local_10 < local_c) {
      return 0;
    }
    local_1c = *(undefined4 *)(param_2 + 8 + local_c * 8);
    uStack_18 = *(undefined4 *)(param_2 + 0xc + local_c * 8);
    local_2c = *(undefined4 *)(param_2 + local_c * 8);
    uStack_28 = *(undefined4 *)(param_2 + 4 + local_c * 8);
    local_34 = *(undefined4 *)(param_3 + local_c * 8);
    uStack_30 = *(undefined4 *)(param_3 + 4 + local_c * 8);
    local_24 = *(undefined4 *)(param_3 + 8 + local_c * 8);
    uStack_20 = *(undefined4 *)(param_3 + 0xc + local_c * 8);
    local_3c = (double)CONCAT44(uStack_18,local_1c) - (double)CONCAT44(uStack_28,local_2c);
    local_44 = (double)CONCAT44(uStack_20,local_24) - (double)CONCAT44(uStack_30,local_34);
    if (local_3c == _DAT_005a84b8) break;
    FUN_00596135(*local_8,local_44,local_3c,local_c,&local_4c,&local_5c,&local_54);
    if ((local_c == local_14) || (local_c == local_10)) {
      if (local_c == local_14) {
        local_74 = param_6;
        local_70 = param_7;
      }
      else {
        local_74 = local_2c;
        local_70 = uStack_28;
      }
      if (local_c == local_10) {
        local_7c = param_8;
        local_78 = param_9;
      }
      else {
        local_7c = local_1c;
        local_78 = uStack_18;
      }
      fVar1 = (float10)FUN_00596691(local_34,uStack_30,local_4c,uStack_48,local_5c,uStack_58,
                                    local_54,uStack_50,local_2c,uStack_28,local_74,local_70,local_7c
                                    ,local_78);
      *param_10 = (double)(fVar1 + (float10)*param_10);
    }
    else {
      *param_10 = (((_DAT_005b3788 * (double)CONCAT44(uStack_50,local_54) * local_3c +
                    (double)CONCAT44(uStack_58,local_5c) / _DAT_005a9bd0) * local_3c +
                   _DAT_005a8460 * (double)CONCAT44(uStack_48,local_4c)) * local_3c +
                  (double)CONCAT44(uStack_30,local_34)) * local_3c + *param_10;
    }
    local_c = local_c + 1;
  }
  *(undefined4 *)param_10 = 0;
  *(undefined4 *)((int)param_10 + 4) = 0;
  return 0xffffffff;
}

