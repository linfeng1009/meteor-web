/* Original Meteor.exe read-only FPU-policy export @ 00512761; native sample not executed. */
/* XREF 005127a4 UNCONDITIONAL_CALL */

uint FUN_00512761(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = FUN_005127ac();
  uVar1 = uVar1 & ~param_2 | param_1 & param_2;
  FUN_0051283e(uVar1);
  return uVar1;
}

