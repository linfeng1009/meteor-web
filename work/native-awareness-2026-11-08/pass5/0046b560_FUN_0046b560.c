/* Original Meteor.exe static export @ 0046b560; original sample not executed. */
/* XREF 00452a99 UNCONDITIONAL_CALL */
/* XREF 004705ef UNCONDITIONAL_CALL */
/* XREF 00452fcd UNCONDITIONAL_CALL */
/* XREF 004562af UNCONDITIONAL_CALL */
/* XREF 00456352 UNCONDITIONAL_CALL */
/* XREF 0045652b UNCONDITIONAL_CALL */
/* XREF 00456b22 UNCONDITIONAL_CALL */
/* XREF 00457ac0 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0046b560(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  
  if (param_2 == 1) {
    (**(code **)(**(int **)(param_1 + 0xc) + 0xc))(0);
    (**(code **)(**(int **)(param_1 + 8) + 0xc))(1);
LAB_0046b63d:
    fVar2 = (*(float *)(param_1 + 0x1c) + *(float *)(param_1 + 0x14)) - DAT_005c7b60 * _DAT_005a8dbc
    ;
    fVar1 = *(float *)(param_1 + 0x18) - *(float *)(param_1 + 0x20) * _DAT_005a8db8;
  }
  else {
    if (param_2 == 2) {
      (**(code **)(**(int **)(param_1 + 0xc) + 0xc))(1);
      (**(code **)(**(int **)(param_1 + 8) + 0xc))(0);
      goto LAB_0046b63d;
    }
    if (param_2 != 3) goto LAB_0046b675;
    (**(code **)(**(int **)(param_1 + 8) + 0xc))(1);
    (**(code **)(**(int **)(param_1 + 0xc) + 0xc))(1);
    FUN_00463980((*(float *)(param_1 + 0x18) * _DAT_005a83e8 -
                 *(float *)(param_1 + 0x20) * _DAT_005a8db8) * _DAT_005a83e8 +
                 *(float *)(param_1 + 0x10),
                 (*(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x1c)) -
                 DAT_005c7b60 * _DAT_005a8dbc);
    fVar2 = (*(float *)(param_1 + 0x14) + *(float *)(param_1 + 0x1c)) - DAT_005c7b60 * _DAT_005a8dbc
    ;
    fVar1 = (*(float *)(param_1 + 0x18) * _DAT_005a83e8 - *(float *)(param_1 + 0x20) * _DAT_005a8db8
            ) + *(float *)(param_1 + 0x18);
  }
  FUN_00463980(fVar1 * _DAT_005a83e8 + *(float *)(param_1 + 0x10),fVar2);
LAB_0046b675:
  *(int *)(param_1 + 0x54) = param_2;
  return;
}

