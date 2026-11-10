/* Original Meteor.exe static export @ 004aad20; original sample not executed. */
/* XREF 004d808e UNCONDITIONAL_CALL */
/* XREF 00488e56 UNCONDITIONAL_CALL */
/* XREF 004897e2 UNCONDITIONAL_CALL */
/* XREF 00489bb9 UNCONDITIONAL_CALL */
/* XREF 0048a08a UNCONDITIONAL_CALL */

void __fastcall FUN_004aad20(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 local_91;
  int local_90;
  int local_8c [4];
  int local_7c;
  uint local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_60;
  undefined1 local_5c [8];
  undefined **local_54 [12];
  int *local_24;
  int *local_20;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0059fd8b;
  local_c = ExceptionList;
  if (*(int *)(param_1 + 0x5c) == 0) {
    ExceptionList = &local_c;
    local_74 = param_1;
    iVar3 = FUN_004d6570();
    iVar6 = *(int *)(iVar3 + 4);
    local_7c = iVar3;
    if (iVar6 != *(int *)(iVar3 + 8)) {
      do {
        if (*(int *)(iVar6 + 0x2c) == 5) {
          local_90 = iVar6;
          FUN_00492000();
          iVar5 = 0;
          local_4 = 0;
          FUN_005005b0(&local_91);
          local_54[0] = &PTR_FUN_005a9488;
          iVar1 = iVar6 + 0x28;
          local_4 = 1;
          iVar4 = FUN_004d65c0(5,*(undefined4 *)(iVar6 + 0x28),local_54);
          piVar2 = local_24;
          if (iVar4 != 0) {
            for (; piVar2 != local_20; piVar2 = piVar2 + 3) {
              if (*piVar2 == 0xb) {
                if (((piVar2 != local_20) && (piVar2 != (int *)0x0)) &&
                   (local_78 = piVar2[1], local_78 != 0)) {
                  do {
                    if ((local_78 >> ((byte)iVar5 & 0x1f) & 1) != 0) {
                      piVar2 = (int *)(local_74 + 0x58);
                      local_70 = iVar5 + 1;
                      FUN_0049d3c0(local_8c + 3,&local_70);
                      iVar6 = local_8c[3];
                      if (local_8c[3] == *piVar2) {
                        local_8c[0] = 0;
                        local_8c[1] = 0;
                        local_8c[2] = 0;
                        local_4._0_1_ = 2;
                        FUN_0049c640(0,iVar1);
                        local_6c = iVar5 + 1;
                        FUN_004b4940(local_8c);
                        local_4._0_1_ = 3;
                        FUN_004b4a50(local_5c,&local_6c);
                        local_4._0_1_ = 2;
                        iVar6 = local_60 - local_68 >> 2;
                        if (iVar6 != 0) {
                          FUN_00402e90(local_68,iVar6 << 2);
                        }
                        local_4 = CONCAT31(local_4._1_3_,1);
                        iVar6 = local_8c[2] - local_8c[0] >> 2;
                        if (iVar6 != 0) {
                          FUN_00402e90(local_8c[0],iVar6 * 4);
                        }
                      }
                      else if (*(int *)(local_8c[3] + 0x18) == *(int *)(local_8c[3] + 0x1c)) {
                        FUN_0049c640(*(int *)(local_8c[3] + 0x18),iVar1);
                      }
                      else {
                        FUN_004a8e30();
                        *(int *)(iVar6 + 0x18) = *(int *)(iVar6 + 0x18) + 4;
                      }
                    }
                    iVar5 = iVar5 + 1;
                    iVar6 = local_90;
                    iVar3 = local_7c;
                  } while (iVar5 < 6);
                }
                break;
              }
            }
          }
          local_4 = 4;
          FUN_0049b240();
          local_4 = 0xffffffff;
          FUN_004920f0();
        }
        iVar6 = iVar6 + 0x48;
      } while (iVar6 != *(int *)(iVar3 + 8));
    }
  }
  ExceptionList = local_c;
  return;
}

