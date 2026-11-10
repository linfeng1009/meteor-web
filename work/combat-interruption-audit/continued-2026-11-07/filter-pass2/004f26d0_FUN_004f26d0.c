/* Original Meteor.exe static export @ 004f26d0; original sample not executed. */
/* XREF 005aa100 DATA */
/* XREF 005ab588 DATA */
/* XREF 005ab9c8 DATA */
/* XREF 005ab348 DATA */

void __thiscall FUN_004f26d0(int *param_1,int *param_2,uint param_3)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  int iVar8;
  undefined1 uStack_39;
  int iStack_38;
  undefined4 uStack_34;
  void *pvStack_30;
  uint uStack_2c;
  undefined4 uStack_28;
  int iStack_24;
  int iStack_20;
  void *pvStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a383b;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  iVar5 = (**(code **)(*param_1 + 0x48))();
  piVar1 = param_2;
  if (param_1[0xc0] == param_3) {
    if (param_1[0xbc] == 0) {
      pvVar6 = operator_new(0xc);
      uStack_4 = 0;
      pvStack_30 = pvVar6;
      if (pvVar6 == (void *)0x0) {
        pvVar6 = (void *)0x0;
      }
      else {
        FUN_005005b0(&uStack_39);
      }
      uStack_4 = 0xffffffff;
      param_1[0xbc] = (int)pvVar6;
      iVar7 = FUN_00487830();
      iStack_38 = *(int *)(*(int *)(iVar7 + 0x2188) + 8);
      iVar7 = FUN_00487830();
      if (iStack_38 != *(int *)(iVar7 + 0x2188)) {
        do {
          if (iVar5 == 0) {
            iVar7 = 0;
          }
          else {
            iVar7 = iVar5 + 0x65c;
          }
          iVar8 = *(int *)(iStack_38 + 0x14);
          if (iVar8 != iVar7) {
            if (iVar8 == 0) {
              iVar8 = 0;
            }
            else {
              iVar8 = iVar8 + -0x65c;
            }
            uStack_2c = param_3;
            uStack_28 = 0;
            iVar7 = (**(code **)(*param_1 + 0xe8))(iVar8,(float)param_3,&uStack_34);
            if (iVar7 != 0) {
              if (*(int *)(iStack_38 + 0x14) == 0) {
                iStack_18 = 0;
              }
              else {
                iStack_18 = *(int *)(iStack_38 + 0x14) + -0x65c;
              }
              uStack_14 = *(undefined4 *)(iStack_38 + 0x10);
              iVar7 = param_1[0xbc];
              uStack_10 = uStack_34;
              iVar8 = *(int *)(iVar7 + 4);
              if (iVar8 == *(int *)(iVar7 + 8)) {
                FUN_004f4260(iVar8,&iStack_18);
              }
              else {
                FUN_004d27d0(iVar8,&iStack_18);
                *(int *)(iVar7 + 4) = *(int *)(iVar7 + 4) + 0xc;
              }
            }
          }
          FUN_0043c6c0();
          iVar7 = FUN_00487830();
        } while (iStack_38 != *(int *)(iVar7 + 0x2188));
      }
    }
    piVar2 = param_2;
    piVar1 = (int *)param_1[0xbc];
    if (piVar1 != param_2) {
      param_3 = piVar1[1];
      iVar5 = *piVar1;
      iVar7 = *param_2;
      uVar3 = (int)(param_3 - iVar5) / 0xc;
      if ((uint)((param_2[2] - iVar7) / 0xc) < uVar3) {
        iVar7 = FUN_004f45a0(uVar3,iVar5,param_3);
        iVar5 = (piVar2[2] - *piVar2) / 0xc;
        if (iVar5 != 0) {
          FUN_00402e90(*piVar2,iVar5 * 0xc);
        }
        *piVar2 = iVar7;
        piVar2[2] = iVar7 + uVar3 * 0xc;
        piVar2[1] = iVar7 + uVar3 * 0xc;
      }
      else {
        uVar4 = (param_2[1] - iVar7) / 0xc;
        if (uVar4 < uVar3) {
          FUN_00576490(iVar5,iVar5 + uVar4 * 0xc,iVar7);
          FUN_004f4800(*piVar1 + ((piVar2[1] - *piVar2) / 0xc) * 0xc,piVar1[1],piVar2[1],param_3);
          piVar2[1] = *piVar2 + uVar3 * 0xc;
        }
        else {
          FUN_00576490(iVar5,param_3,iVar7);
          piVar2[1] = *piVar2 + uVar3 * 0xc;
        }
      }
    }
  }
  else {
    FUN_004f4110(*param_2,param_2[1]);
    FUN_00487830();
    FUN_004b48c0(&param_2);
    iVar7 = FUN_00487830();
    if (param_2 != *(int **)(iVar7 + 0x2188)) {
      do {
        if (iVar5 == 0) {
          iVar7 = 0;
        }
        else {
          iVar7 = iVar5 + 0x65c;
        }
        iVar8 = param_2[5];
        if (iVar8 != iVar7) {
          if (iVar8 == 0) {
            iVar8 = 0;
          }
          else {
            iVar8 = iVar8 + -0x65c;
          }
          uStack_2c = param_3;
          uStack_28 = 0;
          iVar7 = (**(code **)(*param_1 + 0xe8))(iVar8,(float)param_3,&pvStack_30);
          if (iVar7 != 0) {
            if (param_2[5] == 0) {
              iStack_24 = 0;
            }
            else {
              iStack_24 = param_2[5] + -0x65c;
            }
            iStack_20 = param_2[4];
            piVar2 = (int *)piVar1[1];
            pvStack_1c = pvStack_30;
            if (piVar2 == (int *)piVar1[2]) {
              FUN_004f4260(piVar2,&iStack_24);
            }
            else {
              if (piVar2 != (int *)0x0) {
                *piVar2 = iStack_24;
                piVar2[1] = iStack_20;
                piVar2[2] = (int)pvStack_30;
              }
              piVar1[1] = piVar1[1] + 0xc;
            }
          }
        }
        FUN_0043c6c0();
        iVar7 = FUN_00487830();
      } while (param_2 != *(int **)(iVar7 + 0x2188));
    }
  }
  ExceptionList = pvStack_c;
  return;
}

