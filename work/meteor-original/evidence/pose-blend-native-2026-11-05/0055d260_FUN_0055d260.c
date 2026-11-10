/* Original Meteor.exe static export @ 0055d260; original sample not executed. */
/* XREF 004dbed2 UNCONDITIONAL_CALL */
/* XREF 0055d089 UNCONDITIONAL_CALL */
/* XREF 0055d641 UNCONDITIONAL_CALL */
/* XREF 0055d66c UNCONDITIONAL_CALL */
/* XREF 0055d73b UNCONDITIONAL_CALL */
/* XREF 004dbf9c UNCONDITIONAL_CALL */
/* XREF 00584020 UNCONDITIONAL_CALL */

undefined4 __thiscall
FUN_0055d260(int *param_1,int param_2,uint param_3,uint param_4,int param_5,char param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((param_2 < 0) || (param_1[0x177] <= param_2)) {
    return 0;
  }
  if (param_6 != '\0') {
    *(short *)(param_1 + 0x185) = (short)param_1[0x185] + 1;
  }
  param_1[0x184] = param_2;
  param_1[0x178] = param_2;
  param_1[0x181] = 0;
  iVar1 = param_1[0x18b] + param_2 * 0xac;
  param_1[0x17d] = param_3 & 2;
  param_1[0x17a] = param_4 & 1;
  param_1[0x18e] = iVar1;
  param_1[0x179] = param_3 & 1;
  param_1[0x182] = param_5;
  if ((param_4 & 1) == 0) {
    (**(code **)(*param_1 + 0x10))((float)*(int *)(iVar1 + 0x14));
    FUN_0055d1e0(param_1[0x18e]);
  }
  if (param_1[0x17c] == 0) {
    param_1[0x17f] = 0;
    if (param_1[0x17a] != 0) {
      param_1[0x17f] = 4;
    }
    if (param_1[0x179] != 0) {
      param_1[0x17f] = param_1[0x17f] | 8;
    }
  }
  iVar1 = *(int *)(param_1[0x18e] + 0x14);
  if (param_1[0x17a] == 0) {
    param_1[0x3f] = iVar1;
    param_1[0x3e] = (int)(float)iVar1;
    if (param_1[0x179] == 0) {
      param_1[400] = 1;
      return 1;
    }
    param_1[400] = 0;
    return 1;
  }
  param_1[400] = 3;
  param_1[0x17b] = 0;
  FUN_005596c0(param_1[0x3f]);
  if ((param_4 & 2) == 0) {
    FUN_005596e0(iVar1);
    return 1;
  }
  iVar3 = *(int *)(param_1[0x18e] + 0x14);
  iVar2 = *(int *)(param_1[0x18e] + 0x18);
  iVar4 = iVar1;
  if (iVar3 <= iVar2) {
    while (iVar4 = iVar3, iVar3 = FUN_0055c4f0(iVar4), *(char *)(iVar3 + 4) != '\0') {
      iVar3 = iVar4 + 1;
      if (iVar2 < iVar4 + 1) {
        FUN_005596e0(iVar1);
        return 1;
      }
    }
  }
  FUN_005596e0(iVar4);
  return 1;
}

