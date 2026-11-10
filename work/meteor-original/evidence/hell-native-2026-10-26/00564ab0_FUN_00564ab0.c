/* Original Meteor.exe static export @ 00564ab0; original sample not executed. */
/* XREF 0049425e UNCONDITIONAL_CALL */

void __thiscall FUN_00564ab0(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int *piVar6;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  float local_58;
  float local_54;
  float local_50;
  undefined1 local_4c [12];
  undefined1 local_40 [64];
  
  local_64 = 0;
  uVar4 = 0;
  if (param_3 != 0) {
    FUN_00477d30(3,&local_58);
    if (((((local_58 < *(float *)(param_1 + 0x1e0)) || (*(float *)(param_1 + 0x1ec) < local_58)) ||
         (local_54 < *(float *)(param_1 + 0x1e4))) ||
        ((*(float *)(param_1 + 0x1f0) < local_54 || (local_50 < *(float *)(param_1 + 0x1e8))))) ||
       (*(float *)(param_1 + 500) < local_50)) {
      uVar4 = 2;
    }
    else {
      FUN_00562dd0(param_3 + 0x1c4,param_3 + 0x1d0);
      FUN_005565f0(local_40,local_4c);
      param_3 = 0;
      if (0 < *(int *)(param_1 + 0x29c)) {
        do {
          iVar1 = *(int *)(*(int *)(param_1 + 0x2a0) + param_3 * 4);
          if ((iVar1 != 0) && (uVar5 = 0, *(int *)(iVar1 + 0x50) - *(int *)(iVar1 + 0x4c) >> 2 != 0)
             ) {
            do {
              piVar6 = *(int **)(*(int *)(iVar1 + 0x4c) + uVar5 * 4);
              if ((piVar6 != (int *)0x0) &&
                 ((((char)piVar6[2] != '\0' && ((char)piVar6[3] != '\0')) &&
                  (cVar2 = FUN_00570630(local_4c,local_40,piVar6 + 0x18,piVar6 + 0x1b),
                  cVar2 != '\0')))) {
                iVar3 = *piVar6;
                if ((iVar3 == 0xf) && (piVar6[0xb] != 0)) {
                  *param_2 = 1;
                  param_2[1] = piVar6;
                  param_2[2] = local_5c;
                  return;
                }
                if ((2 < iVar3) && (iVar3 < 8)) {
                  switch(*piVar6) {
                  case 3:
                    iVar1 = piVar6[6];
                    *param_2 = 3;
                    param_2[1] = piVar6;
                    param_2[2] = iVar1;
                    return;
                  case 4:
                    *param_2 = 2;
                    param_2[1] = piVar6;
                    param_2[2] = local_5c;
                    return;
                  case 5:
                    *param_2 = 6;
                    param_2[1] = piVar6;
                    param_2[2] = local_5c;
                    return;
                  case 6:
                    *param_2 = 7;
                    param_2[1] = piVar6;
                    param_2[2] = local_5c;
                    return;
                  case 7:
                    *param_2 = 8;
                    param_2[1] = piVar6;
                    param_2[2] = local_5c;
                    return;
                  default:
                    *param_2 = 0;
                    param_2[1] = piVar6;
                    param_2[2] = local_5c;
                    return;
                  }
                }
                if ((iVar3 == 0xc) && (piVar6[0xb] != 0)) {
                  iVar3 = FUN_0056b4a0(local_4c,local_40);
                  if (iVar3 != 0) {
                    if (*(char *)((int)piVar6 + 0xb) != '\0') {
                      iVar1 = piVar6[6];
                      *param_2 = 3;
                      param_2[1] = local_60;
                      param_2[2] = iVar1;
                      return;
                    }
LAB_00564e2a:
                    *param_2 = 5;
                    param_2[1] = piVar6;
                    param_2[2] = local_5c;
                    return;
                  }
                }
                else if (((iVar3 == 0xd) || ((iVar3 == 0xe && (piVar6[0xb] != 0)))) &&
                        (iVar3 = FUN_0056b4a0(local_4c,local_40), iVar3 != 0)) goto LAB_00564e2a;
              }
              uVar5 = uVar5 + 1;
            } while (uVar5 < (uint)(*(int *)(iVar1 + 0x50) - *(int *)(iVar1 + 0x4c) >> 2));
          }
          param_3 = param_3 + 1;
        } while (param_3 < *(int *)(param_1 + 0x29c));
      }
      piVar6 = (int *)**(int **)(param_1 + 0x2ac);
      uVar4 = local_64;
      if (piVar6 != *(int **)(param_1 + 0x2ac)) {
        do {
          iVar1 = piVar6[2];
          cVar2 = FUN_00570630(local_4c,local_40,iVar1 + 0x60,iVar1 + 0x6c);
          if (cVar2 != '\0') {
            *param_2 = 1;
            param_2[1] = iVar1;
            param_2[2] = local_5c;
            return;
          }
          piVar6 = (int *)*piVar6;
        } while (piVar6 != (int *)*(int *)(param_1 + 0x2ac));
      }
    }
  }
  *param_2 = uVar4;
  param_2[1] = local_60;
  param_2[2] = local_5c;
  return;
}

