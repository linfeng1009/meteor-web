/* Original Meteor.exe static export @ 0056b350; original sample not executed. */
/* XREF 005646b3 UNCONDITIONAL_CALL */
/* XREF 00564854 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall
FUN_0056b350(int param_1,float *param_2,undefined4 param_3,float *param_4,undefined4 *param_5)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  int local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 local_40 [64];
  
  FUN_00476f00(local_40,param_1 + 0x94,param_1 + 0x54);
  cVar1 = FUN_00570510(param_1 + 0x108,local_40,param_2,param_3,param_4);
  if (cVar1 == '\0') {
    return 0;
  }
  iVar3 = 0;
  local_74 = 0;
  if (0 < *(int *)(*(int *)(param_1 + 0x120) + 0x38)) {
    do {
      iVar2 = FUN_0057f0b0(param_2,param_3,&local_70,&local_4c,param_1);
      if (iVar2 != 0) {
        local_64 = local_70 - *param_2;
        local_60 = local_6c - param_2[1];
        local_5c = local_68 - param_2[2];
        local_58 = local_64;
        local_54 = local_60;
        local_50 = local_5c;
        fVar4 = (float10)FUN_0047ecf0();
        if (fVar4 < (float10)_DAT_005ae224) {
          *param_4 = local_70;
          param_4[1] = local_6c;
          param_4[2] = local_68;
          local_74 = local_74 + 1;
          if (param_5 != (undefined4 *)0x0) {
            *param_5 = local_4c;
            param_5[1] = local_48;
            param_5[2] = local_44;
          }
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(*(int *)(param_1 + 0x120) + 0x38));
  }
  return local_74;
}

