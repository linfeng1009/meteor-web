/* Original Meteor.exe static export @ 005644f0; original sample not executed. */
/* XREF 004c13aa UNCONDITIONAL_CALL */
/* XREF 004f6841 UNCONDITIONAL_CALL */
/* XREF 00564a1b UNCONDITIONAL_CALL */
/* XREF 004ccac1 UNCONDITIONAL_CALL */
/* XREF 004ccf5b UNCONDITIONAL_CALL */
/* XREF 004cf318 UNCONDITIONAL_CALL */
/* XREF 004cf38c UNCONDITIONAL_CALL */
/* XREF 004f08d5 UNCONDITIONAL_CALL */
/* XREF 004f6f0a UNCONDITIONAL_CALL */

int __thiscall
FUN_005644f0(int param_1,float *param_2,float *param_3,float *param_4,undefined4 *param_5)

{
  float *pfVar1;
  float *pfVar2;
  float fVar3;
  int *piVar4;
  float *pfVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  float local_18;
  int local_14;
  float local_c;
  float local_8;
  float local_4;
  
  pfVar5 = param_2;
  if (*(char *)(param_1 + 0x251) != '\0') {
    FUN_00562dd0(param_2,param_3);
    fVar3 = *param_2;
    pfVar1 = param_2 + 1;
    pfVar2 = param_2 + 2;
    param_2 = (float *)0x0;
    local_14 = 0;
    local_18 = (*param_3 - fVar3) * (*param_3 - fVar3) +
               (param_3[1] - *pfVar1) * (param_3[1] - *pfVar1) +
               (param_3[2] - *pfVar2) * (param_3[2] - *pfVar2);
    if (0 < *(int *)(param_1 + 0x29c)) {
      do {
        piVar4 = *(int **)(*(int *)(param_1 + 0x2a0) + local_14 * 4);
        cVar6 = FUN_00570600(piVar4 + 3,piVar4 + 6,pfVar5,param_3,0);
        if (cVar6 != '\0') {
          iVar9 = 0;
          if (0 < *piVar4) {
            do {
              iVar7 = FUN_0056aee0(*(undefined4 *)(piVar4[1] + iVar9 * 4));
              if (*(int *)(iVar7 + 0x50) == 0) {
                *(undefined4 *)(iVar7 + 0x50) = 1;
                iVar8 = FUN_0056f5f0(pfVar5,param_3,iVar7 + 0x1c,iVar7 + 0x28,iVar7 + 0x34,&local_c)
                ;
                if ((iVar8 != 0) &&
                   (fVar3 = (local_c - *pfVar5) * (local_c - *pfVar5) +
                            (local_8 - pfVar5[1]) * (local_8 - pfVar5[1]) +
                            (local_4 - pfVar5[2]) * (local_4 - pfVar5[2]), fVar3 < local_18)) {
                  *param_4 = local_c;
                  param_4[1] = local_8;
                  param_4[2] = local_4;
                  param_2 = (float *)((int)param_2 + 1);
                  local_18 = fVar3;
                  if (param_5 != (undefined4 *)0x0) {
                    *param_5 = *(undefined4 *)(iVar7 + 0x40);
                    param_5[1] = *(undefined4 *)(iVar7 + 0x44);
                    param_5[2] = *(undefined4 *)(iVar7 + 0x48);
                  }
                }
              }
              iVar9 = iVar9 + 1;
            } while (iVar9 < *piVar4);
          }
          uVar10 = 0;
          if (piVar4[0x14] - piVar4[0x13] >> 2 != 0) {
            do {
              iVar9 = *(int *)(piVar4[0x13] + uVar10 * 4);
              if ((((iVar9 != 0) && (*(char *)(iVar9 + 8) != '\0')) && (*(int *)(iVar9 + 0x2c) != 0)
                  ) && (((*(char *)(iVar9 + 10) != '\0' &&
                         (iVar9 = FUN_0056b350(pfVar5,param_3,&local_c,param_5), iVar9 != 0)) &&
                        (fVar3 = (local_c - *pfVar5) * (local_c - *pfVar5) +
                                 (local_8 - pfVar5[1]) * (local_8 - pfVar5[1]) +
                                 (local_4 - pfVar5[2]) * (local_4 - pfVar5[2]), fVar3 < local_18))))
              {
                *param_4 = local_c;
                param_4[1] = local_8;
                param_2 = (float *)((int)param_2 + 1);
                param_4[2] = local_4;
                local_18 = fVar3;
              }
              uVar10 = uVar10 + 1;
            } while (uVar10 < (uint)(piVar4[0x14] - piVar4[0x13] >> 2));
          }
        }
        local_14 = local_14 + 1;
      } while (local_14 < *(int *)(param_1 + 0x29c));
    }
    return (int)param_2;
  }
  return 0;
}

