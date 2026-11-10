/* Original Meteor.exe static export @ 00407c10; original sample not executed. */
/* XREF 004a5801 UNCONDITIONAL_CALL */
/* XREF 00417870 UNCONDITIONAL_CALL */
/* XREF 004f58ca UNCONDITIONAL_CALL */
/* XREF 004f60a0 UNCONDITIONAL_CALL */
/* XREF 004f60be UNCONDITIONAL_CALL */
/* XREF 004f60e3 UNCONDITIONAL_CALL */
/* XREF 00548721 UNCONDITIONAL_CALL */
/* XREF 005487e4 UNCONDITIONAL_CALL */
/* XREF 004f61e1 UNCONDITIONAL_CALL */
/* XREF 004f6318 UNCONDITIONAL_CALL */
/* XREF 004f6445 UNCONDITIONAL_CALL */
/* XREF 004f6a41 UNCONDITIONAL_CALL */
/* XREF 004f6a51 UNCONDITIONAL_CALL */
/* XREF 0048ab8f UNCONDITIONAL_CALL */
/* XREF 004a532c UNCONDITIONAL_CALL */
/* XREF 004a5392 UNCONDITIONAL_CALL */
/* XREF 004a541f UNCONDITIONAL_CALL */
/* XREF 004083ce UNCONDITIONAL_CALL */
/* XREF 00408554 UNCONDITIONAL_CALL */
/* XREF 004087cb UNCONDITIONAL_CALL */
/* XREF 00408947 UNCONDITIONAL_CALL */
/* XREF 0040ac2e UNCONDITIONAL_CALL */
/* XREF 0040acc7 UNCONDITIONAL_CALL */
/* XREF 0040ade3 UNCONDITIONAL_CALL */
/* XREF 0040ae72 UNCONDITIONAL_CALL */
/* XREF 004a6522 UNCONDITIONAL_CALL */
/* XREF 004a6770 UNCONDITIONAL_CALL */
/* XREF 00548cd7 UNCONDITIONAL_CALL */
/* XREF 00548d88 UNCONDITIONAL_CALL */
/* XREF 00549224 UNCONDITIONAL_CALL */
/* XREF 00549245 UNCONDITIONAL_CALL */
/* XREF 00549290 UNCONDITIONAL_CALL */
/* XREF 004a7be6 UNCONDITIONAL_CALL */
/* XREF 004bb6ea UNCONDITIONAL_CALL */
/* XREF 004bb797 UNCONDITIONAL_CALL */
/* XREF 004bc5fa UNCONDITIONAL_CALL */
/* XREF 004ce731 UNCONDITIONAL_CALL */
/* XREF 004e838a UNCONDITIONAL_CALL */
/* XREF 004f5b7c UNCONDITIONAL_CALL */
/* XREF 004f5bc1 UNCONDITIONAL_CALL */
/* XREF 004f5e88 UNCONDITIONAL_CALL */
/* XREF 004f6ca7 UNCONDITIONAL_CALL */
/* XREF 004f7435 UNCONDITIONAL_CALL */
/* XREF 004f76b2 UNCONDITIONAL_CALL */
/* XREF 004f76d0 UNCONDITIONAL_CALL */
/* XREF 004f77df UNCONDITIONAL_CALL */
/* XREF 004f789a UNCONDITIONAL_CALL */
/* XREF 004f78e9 UNCONDITIONAL_CALL */
/* XREF 004f7953 UNCONDITIONAL_CALL */
/* XREF 004f79f5 UNCONDITIONAL_CALL */
/* XREF 004f74fd UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00407c10(undefined4 param_1,undefined4 *param_2,float *param_3,float *param_4)

{
  int iVar1;
  int iVar2;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if ((DAT_005d5a00 != 0) && (iVar1 = FUN_00410a70(param_1), iVar1 != 0)) {
    FUN_00430c20(&local_30);
    iVar2 = iVar1;
    do {
      if (*(int *)(iVar2 + 0x88) != 0) {
        FUN_00431180(&local_30,&local_30,iVar2 + 8);
      }
      iVar2 = *(int *)(iVar2 + 0x124);
    } while (iVar2 != 0);
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = local_c;
      param_2[1] = local_8;
      param_2[2] = local_4;
    }
    if (param_3 != (float *)0x0) {
      iVar2 = *(int *)(iVar1 + 0xb8);
      if (iVar2 == 0) {
        local_38 = _DAT_005a83e4;
        local_34 = _DAT_005a83e4;
        local_3c = 1.0;
      }
      else if (iVar2 == 1) {
        local_3c = _DAT_005a83e4;
        local_34 = _DAT_005a83e4;
        local_38 = 1.0;
      }
      else if (iVar2 == 2) {
        local_3c = _DAT_005a83e4;
        local_38 = _DAT_005a83e4;
        local_34 = 1.0;
      }
      else if (iVar2 == 3) {
        local_38 = _DAT_005a83e4;
        local_34 = _DAT_005a83e4;
        local_3c = -1.0;
      }
      else if (iVar2 == 4) {
        local_3c = _DAT_005a83e4;
        local_34 = _DAT_005a83e4;
        local_38 = -1.0;
      }
      else if (iVar2 == 5) {
        local_3c = _DAT_005a83e4;
        local_38 = _DAT_005a83e4;
        local_34 = -1.0;
      }
      *param_3 = local_30 * local_3c + local_24 * local_38 + local_18 * local_34;
      param_3[1] = local_2c * local_3c + local_20 * local_38 + local_14 * local_34;
      param_3[2] = local_28 * local_3c + local_1c * local_38 + local_10 * local_34;
      FUN_00431a20(param_3);
    }
    if (param_4 != (float *)0x0) {
      iVar1 = *(int *)(iVar1 + 0xb4);
      if (iVar1 == 0) {
        local_38 = _DAT_005a83e4;
        local_34 = _DAT_005a83e4;
        local_3c = 1.0;
      }
      else if (iVar1 == 1) {
        local_3c = _DAT_005a83e4;
        local_34 = _DAT_005a83e4;
        local_38 = 1.0;
      }
      else if (iVar1 == 2) {
        local_3c = _DAT_005a83e4;
        local_38 = _DAT_005a83e4;
        local_34 = 1.0;
      }
      else if (iVar1 == 3) {
        local_38 = _DAT_005a83e4;
        local_34 = _DAT_005a83e4;
        local_3c = -1.0;
      }
      else if (iVar1 == 4) {
        local_3c = _DAT_005a83e4;
        local_34 = _DAT_005a83e4;
        local_38 = -1.0;
      }
      else if (iVar1 == 5) {
        local_3c = _DAT_005a83e4;
        local_38 = _DAT_005a83e4;
        local_34 = -1.0;
      }
      *param_4 = local_30 * local_3c + local_24 * local_38 + local_18 * local_34;
      param_4[1] = local_2c * local_3c + local_20 * local_38 + local_14 * local_34;
      param_4[2] = local_28 * local_3c + local_1c * local_38 + local_10 * local_34;
      FUN_00431a20(param_4);
      return;
    }
  }
  return;
}

