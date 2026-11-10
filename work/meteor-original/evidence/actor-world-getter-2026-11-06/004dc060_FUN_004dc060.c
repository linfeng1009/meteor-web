/* Original Meteor.exe static export @ 004dc060; original sample not executed. */
/* XREF 005aa974 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004dc060(float *param_1,float *param_2,float *param_3)

{
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (param_1 != (float *)0x0) {
    FUN_00477d30(3,&local_18);
    *param_1 = local_18;
    param_1[1] = local_14;
    param_1[2] = local_10;
  }
  if (param_2 != (float *)0x0) {
    FUN_00477d30(1,&local_18);
    local_18 = local_18 * _DAT_005a8430;
    local_14 = local_14 * _DAT_005a8430;
    local_10 = local_10 * _DAT_005a8430;
    *param_2 = local_18;
    param_2[1] = local_14;
    param_2[2] = local_10;
    local_c = local_18;
    local_8 = local_14;
    local_4 = local_10;
  }
  if (param_3 != (float *)0x0) {
    FUN_00477d30(2,&local_18);
    *param_3 = local_18;
    param_3[1] = local_14;
    param_3[2] = local_10;
  }
  return;
}

