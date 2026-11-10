/* Original Meteor.exe static export @ 00596691; original sample not executed. */
/* XREF 00596623 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00596691(double param_1,double param_2,double param_3,double param_4,double param_5,
                    double param_6,double param_7)

{
  double dVar1;
  double dVar2;
  
  dVar1 = param_7 + param_6;
  dVar2 = param_7 * param_7 + param_6 * param_7 + param_6 * param_6;
  return ((float10)param_1 + (float10)((dVar1 - _DAT_005a8468 * param_5) * _DAT_005a8460 * param_2)
          + (float10)((dVar2 - (dVar1 - param_5) * _DAT_005a9bd0 * param_5) *
                     (param_3 / _DAT_005a9bd0)) +
         (float10)(((param_7 * param_7 * param_7 +
                    param_7 * param_7 * param_6 +
                    param_6 * param_6 * param_7 + param_6 * param_6 * param_6) -
                   (_DAT_005a8468 * dVar2 -
                   (_DAT_005a9bd0 * dVar1 - _DAT_005a8468 * param_5) * param_5) *
                   _DAT_005a8468 * param_5) * (param_4 / _DAT_005a9eb0))) *
         ((float10)param_7 - (float10)param_6);
}

