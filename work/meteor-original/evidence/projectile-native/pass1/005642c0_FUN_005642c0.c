/* Original Meteor.exe static export @ 005642c0; original sample not executed. */
/* XREF 00563785 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_005642c0(int param_1)

{
  float fVar1;
  int iVar2;
  int *piVar3;
  float10 fVar4;
  int local_14;
  undefined4 local_4;
  
  piVar3 = *(int **)(param_1 + 0x4b4);
  if ((piVar3 != (int *)0x0) && (local_14 = 0, 0 < *(int *)(param_1 + 0x4b0))) {
    do {
      if (((piVar3 != (int *)0x0) &&
          ((((char)piVar3[2] == '\0' && (*piVar3 == 0xf)) && (_DAT_005a83e4 < (float)piVar3[7]))))
         && ((char)piVar3[3] != '\0')) {
        fVar4 = (float10)FUN_004748b0();
        fVar1 = (float)piVar3[5];
        piVar3[5] = (int)(float)(fVar4 + (float10)fVar1);
        if ((float10)(float)piVar3[7] < fVar4 + (float10)fVar1) {
          iVar2 = piVar3[8];
          piVar3[5] = 0;
          *(undefined1 *)(piVar3 + 2) = 1;
          (*(code *)PTR_FUN_005d1784)(1,iVar2,6,1,local_4);
          (*(code *)PTR_FUN_005d1784)(2,iVar2,6,1,local_4);
          (*(code *)PTR_FUN_005d1784)(3,iVar2,6,1,local_4);
          FUN_00564480(piVar3);
        }
      }
      local_14 = local_14 + 1;
      piVar3 = piVar3 + 0x2b;
    } while (local_14 < *(int *)(param_1 + 0x4b0));
  }
  return;
}

