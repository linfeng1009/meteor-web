/* Original Meteor.exe static export @ 004ebc10; original sample not executed. */
/* XREF 005a9e78 DATA */
/* XREF 005ab19c DATA */
/* XREF 005ab1c4 DATA */
/* XREF 005ab1ec DATA */
/* XREF 005a9e50 DATA */
/* XREF 004ec9aa UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004ebc10(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  float10 fVar8;
  undefined ***pppuVar9;
  undefined1 uStack_7d;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  int iStack_70;
  int iStack_6c;
  undefined1 auStack_68 [4];
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined **appuStack_54 [18];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a3138;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  fVar8 = (float10)FUN_00549b00();
  if (((float10)_DAT_005a9bd0 <= fVar8) &&
     (iVar7 = *(int *)(param_1[0xea] + 8), iVar7 != param_1[0xea])) {
    do {
      if (*(int *)(iVar7 + 0x200) == 1) {
        piVar3 = (int *)FUN_00487830();
        puVar1 = (undefined4 *)(iVar7 + 0x10);
        iVar4 = (**(code **)(*piVar3 + 300))(*(undefined4 *)(iVar7 + 0x10));
        if ((iVar4 != 0) && (iVar4 + -0x65c != 0)) {
          piVar3 = (int *)FUN_00487830();
          (**(code **)(*piVar3 + 0xd8))(&iStack_70,iVar4 + -0x65c);
          if (iStack_70 == 1) {
            uVar6 = FUN_005679d0(0);
            uStack_74 = uVar6;
            uStack_7c = FUN_005679d0(1);
            FUN_00492000();
            uStack_4 = 0;
            FUN_005005b0(&uStack_7d);
            appuStack_54[0] = &PTR_FUN_005a9488;
            pppuVar9 = appuStack_54;
            uStack_4 = 1;
            uStack_78 = 0;
            uVar5 = uStack_7c;
            FUN_004d6570(uVar6,uStack_7c,pppuVar9);
            FUN_004d65c0(uVar6,uVar5,pppuVar9);
            iVar4 = (**(code **)(*(int *)(iVar7 + 0x88) + 0x24))(appuStack_54,&uStack_78);
            if (iVar4 != 0) {
              uStack_64 = *puVar1;
              uVar5 = *(undefined4 *)(iStack_6c + 0x20);
              uStack_60 = uStack_74;
              uStack_5c = uStack_7c;
              uStack_58 = uVar5;
              piVar3 = (int *)FUN_00487830();
              (**(code **)(*piVar3 + 0x1ac))(uVar5);
              (**(code **)(*param_1 + 0x40))(0x2d,auStack_68,0x10,1);
              FUN_005603b0(*puVar1);
            }
            uStack_4 = 2;
            FUN_0049b240();
            uStack_4 = 0xffffffff;
            FUN_004920f0();
          }
          else if (iStack_70 == 2) {
            if ((*(int *)(iVar7 + 0x200) == 1) && (*(int *)(iVar7 + 0xdc) != 0)) {
              piVar3 = (int *)FUN_00487830();
              iVar4 = (**(code **)(*piVar3 + 0x14c))(*puVar1);
              if ((iVar4 != 0) && (iVar4 = FUN_004ab3a0(), iVar4 != 0)) {
                FUN_004acae0(*puVar1,0x18,puVar1,4,1);
                (**(code **)(*param_1 + 0x40))(0x2c,puVar1,4,0);
                *(undefined4 *)(iVar7 + 0x200) = 2;
                FUN_00549a90(0,0);
                if (param_1[0xe0] == 0) {
                  *(int *)(iVar7 + 0x218) = *(int *)(iVar7 + 0x218) + 1;
                }
                FUN_005603b0(*puVar1);
              }
            }
          }
          else if (iStack_70 == 3) {
            if ((*(int *)(iVar7 + 0x200) == 1) && (*(int *)(iVar7 + 0xdc) != 0)) {
              piVar3 = (int *)FUN_00487830();
              iVar4 = (**(code **)(*piVar3 + 0x14c))(*puVar1);
              if ((iVar4 != 0) && (iVar4 = FUN_004ab3a0(), iVar4 != 0)) {
                FUN_00549a90(0,0);
                iVar4 = *(int *)(iVar7 + 0x88);
                uVar5 = __ftol(0);
                (**(code **)(iVar4 + 0x2c))(2,uVar5);
                iVar4 = (**(code **)(*param_1 + 200))(iVar7 + 0x18,*puVar1);
                if (iVar4 == 0) {
                  FUN_004acae0(*puVar1,0x39,0,0,1);
                }
                FUN_005603b0(*puVar1);
              }
            }
          }
          else {
            FUN_005603b0(*puVar1);
          }
        }
      }
      iVar4 = *(int *)(iVar7 + 0xc);
      if (iVar4 == 0) {
        iVar4 = *(int *)(iVar7 + 4);
        if (iVar7 == *(int *)(iVar4 + 0xc)) {
          do {
            iVar7 = iVar4;
            iVar4 = *(int *)(iVar7 + 4);
          } while (iVar7 == *(int *)(iVar4 + 0xc));
        }
        if (*(int *)(iVar7 + 0xc) != iVar4) {
          iVar7 = iVar4;
        }
      }
      else {
        for (iVar2 = *(int *)(iVar4 + 8); iVar7 = iVar4, iVar2 != 0; iVar2 = *(int *)(iVar2 + 8)) {
          iVar4 = iVar2;
        }
      }
    } while (iVar7 != param_1[0xea]);
  }
  ExceptionList = local_c;
  return;
}

