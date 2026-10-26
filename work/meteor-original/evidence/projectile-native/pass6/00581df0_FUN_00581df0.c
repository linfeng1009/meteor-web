/* Original Meteor.exe static export @ 00581df0; original sample not executed. */
/* XREF 005b0e88 DATA */
/* XREF 005b0f10 DATA */
/* XREF 005b0f98 DATA */
/* XREF 005b1020 DATA */
/* XREF 005b10a8 DATA */
/* XREF 005b1130 DATA */
/* XREF 005b11b8 DATA */
/* XREF 005b1240 DATA */
/* XREF 005b12c8 DATA */
/* XREF 005b1350 DATA */
/* XREF 005b13d8 DATA */
/* XREF 005b1460 DATA */
/* XREF 005b14e8 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00581df0(int *param_1)

{
  undefined4 *puVar1;
  int *piVar2;
  float fVar3;
  undefined4 *puVar4;
  int iVar5;
  float10 fVar6;
  float fStack_2c;
  undefined1 auStack_c [12];
  
  iVar5 = param_1[0x7b];
  if ((*(char *)(iVar5 + 0x28) != '\0') && (*(char *)(param_1[2] + 0x58) != '\0')) {
    fVar3 = *(float *)(iVar5 + 0x1c) * _DAT_005b0e9c;
    *(undefined4 *)(iVar5 + 0x34) = 0;
    iVar5 = param_1[0x7b];
    if ((*(int *)(iVar5 + 0x1fc) != 0) && (*(char *)(iVar5 + 0x29) != '\0')) {
      *(undefined4 *)(iVar5 + 0x200) = 0;
      iVar5 = param_1[0x7b];
      fStack_2c = *(float *)(iVar5 + 0x14);
      if (fStack_2c < *(float *)(iVar5 + 0x18)) {
        do {
          if (0x31 < *(int *)(iVar5 + 0x200)) break;
          if ((int *)param_1[0x79] != (int *)0x0) {
            (**(code **)(*(int *)param_1[0x79] + 0x40))(fStack_2c);
          }
          piVar2 = (int *)param_1[0x7a];
          if ((piVar2 != (int *)0x0) && (piVar2 != (int *)param_1[0x79])) {
            (**(code **)(*piVar2 + 0x40))(fStack_2c);
          }
          (**(code **)(*param_1 + 0x40))(fStack_2c);
          if (param_1[1] == 10) {
            puVar4 = (undefined4 *)FUN_00476e80(auStack_c,param_1 + 0xf,param_1[0x77]);
            puVar1 = (undefined4 *)
                     (*(int *)(param_1[0x7b] + 0x1fc) + *(int *)(param_1[0x7b] + 0x200) * 0x18);
            *puVar1 = *puVar4;
            puVar1[1] = puVar4[1];
            puVar1[2] = puVar4[2];
          }
          else {
            FUN_00477d30(3,*(int *)(param_1[0x7b] + 0x1fc) + *(int *)(param_1[0x7b] + 0x200) * 0x18)
            ;
          }
          if (0 < *(int *)(param_1[0x7b] + 0x200)) {
            iVar5 = param_1[0x7b];
            fVar6 = (float10)FUN_0047ecf0();
            *(float *)(iVar5 + 0x34) = (float)(fVar6 + (float10)*(float *)(iVar5 + 0x34));
          }
          fStack_2c = fStack_2c + fVar3;
          *(undefined4 *)
           (*(int *)(param_1[0x7b] + 0x1fc) + 0xc + *(int *)(param_1[0x7b] + 0x200) * 0x18) =
               0xffffffff;
          puVar1 = (undefined4 *)
                   (*(int *)(param_1[0x7b] + 0x1fc) + 0x10 + *(int *)(param_1[0x7b] + 0x200) * 0x18)
          ;
          *puVar1 = 0;
          puVar1[1] = 0;
          *(int *)(param_1[0x7b] + 0x200) = *(int *)(param_1[0x7b] + 0x200) + 1;
          iVar5 = param_1[0x7b];
        } while (fStack_2c < *(float *)(iVar5 + 0x18));
      }
      (**(code **)(*param_1 + 0x40))(*(undefined4 *)(param_1[2] + 0x2c));
    }
  }
  return;
}

