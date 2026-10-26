/* Original Meteor.exe static export @ 005955e3; original sample not executed. */

float10 FUN_005955e3(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  float10 fVar2;
  double local_c;
  
  iVar1 = (**(code **)(*param_1 + 0x18))
                    (param_1[7],param_2,param_3,param_1[6],param_4,param_5,param_6,&local_c);
  if (iVar1 == 0) {
    fVar2 = (float10)local_c;
  }
  else {
    FUN_00596780(s_interpolation_error_005d3b00,s_E__ftp_gsl_1_0_interpolation_int_005d3ad8,0xca,
                 iVar1);
    fVar2 = (float10)FUN_00596830();
  }
  return fVar2;
}

