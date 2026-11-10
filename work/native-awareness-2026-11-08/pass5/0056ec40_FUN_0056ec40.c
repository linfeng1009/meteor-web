/* Original Meteor.exe static export @ 0056ec40; original sample not executed. */
/* XREF 005664a0 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_0056ec40(int param_1)

{
  int *piVar1;
  int iVar2;
  float10 fVar3;
  undefined1 uStack_68;
  undefined1 uStack_67;
  undefined1 uStack_66;
  undefined1 uStack_65;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  undefined1 auStack_40 [64];
  
  if (*(char *)(param_1 + 0x58) != '\0') {
    FUN_0056eb40();
    if ((*(int *)(param_1 + 0x128) == 0) && (*(int **)(param_1 + 300) != (int *)0x0)) {
      (**(code **)(**(int **)(param_1 + 300) + 0x74))();
    }
  }
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x40)) {
    do {
      piVar1 = *(int **)(*(int *)(param_1 + 0x4c) + iVar2 * 4);
      fVar3 = (float10)FUN_00583560();
      if ((fVar3 <= (float10)*(float *)(param_1 + 0x24)) && (*(char *)(piVar1[0x7b] + 0x5d) == '\0')
         ) {
        (**(code **)(*piVar1 + 0x74))();
        if ((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 0x59) != '\0')) {
          (**(code **)(*piVar1 + 0x78))();
        }
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(param_1 + 0x40));
  }
  FUN_00475590(0x12,0);
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0x40)) {
    do {
      piVar1 = *(int **)(*(int *)(param_1 + 0x4c) + iVar2 * 4);
      fVar3 = (float10)FUN_00583560();
      if ((fVar3 <= (float10)*(float *)(param_1 + 0x24)) && (*(char *)(piVar1[0x7b] + 0x5d) != '\0')
         ) {
        (**(code **)(*piVar1 + 0x74))();
        if ((*(char *)(param_1 + 0x58) != '\0') && (*(char *)(param_1 + 0x59) != '\0')) {
          (**(code **)(*piVar1 + 0x78))();
        }
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(param_1 + 0x40));
  }
  FUN_00475590(0x12,1);
  if (*(char *)(param_1 + 0x3c) != '\0') {
    uStack_68 = 0;
    uStack_67 = 0xff;
    uStack_65 = 0xff;
    uStack_66 = 0;
    fStack_4c = (*(float *)(param_1 + 0xc4) + *(float *)(param_1 + 0xb8)) * _DAT_005a83e8;
    fStack_48 = (*(float *)(param_1 + 200) + *(float *)(param_1 + 0xbc)) * _DAT_005a83e8;
    fStack_44 = (*(float *)(param_1 + 0xcc) + *(float *)(param_1 + 0xc0)) * _DAT_005a83e8;
    fStack_64 = *(float *)(param_1 + 0xc4) - fStack_4c;
    fStack_60 = *(float *)(param_1 + 200) - fStack_48;
    fStack_5c = *(float *)(param_1 + 0xcc) - fStack_44;
    fStack_58 = fStack_64;
    fStack_54 = fStack_60;
    fStack_50 = fStack_5c;
    FUN_00477200();
    FUN_00477b90(3,&fStack_4c);
    FUN_00479f80(0);
    FUN_00475400(&fStack_64,auStack_40,&uStack_68);
  }
  return;
}

