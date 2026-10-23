/* Original Meteor.exe @ 004af630; stat virtual-call signatures annotated from x86 calling convention */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004af630(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 unaff_EDI;
  float10 fVar6;
  undefined4 uVar7;
  int *piVar8;
  undefined4 uVar9;
  int local_1bc;
  int local_1b8;
  int local_1b4;
  int local_1b0;
  float local_1ac;
  int *local_1a8;
  undefined1 uStack_1a1;
  undefined4 uStack_1a0;
  uint local_19c;
  uint local_198;
  uint local_194;
  uint local_190;
  undefined **appuStack_184 [10];
  undefined4 uStack_15c;
  undefined4 uStack_158;
  int iStack_154;
  int aiStack_150 [2];
  int iStack_148;
  int iStack_140;
  uint local_13c;
  uint local_138;
  uint local_134;
  uint local_130;
  int local_12c;
  uint local_124;
  uint local_120;
  uint local_11c;
  uint local_118;
  int local_114;
  undefined4 uStack_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a031e;
  local_c = ExceptionList;
  uVar3 = param_3[1];
  local_198 = param_3[3] & 0xffff;
  local_1a8 = (int *)(param_3[4] & 0xffff);
  local_1b8 = *param_3;
  local_19c = (uint)*(ushort *)((int)param_3 + 0xe);
  local_194 = (uint)*(ushort *)((int)param_3 + 0x12);
  local_1ac = (float)(uVar3 >> 10 & 0x3f);
  local_190 = (uint)param_3[2] >> 0xc & 0xf;
  uVar5 = param_3[2] & 0xfff;
  uVar4 = uVar3 >> 0x10 & 0xf;
  uVar3 = uVar3 & 0x3ff;
  ExceptionList = &local_c;
  FUN_0049d3c0(&local_1bc,&local_1b8);
  if (((local_1bc != param_1[0xea]) && (*(int *)(local_1bc + 0x200) == 1)) &&
     (fVar6 = (float10)FUN_00549b00(), (float10)_DAT_005a8468 <= fVar6)) {
    local_1b0 = param_2;
    FUN_0049d3c0(&local_1b4,&local_1b0);
    if (local_1b4 != param_1[0xea]) {
      if (*(int *)(local_1b4 + 0x200) == 1) {
        if ((local_1ac == 0.0) && (*(int *)(local_1bc + 0x20c) == 1)) {
          local_120 = local_19c;
          local_124 = uVar5 << 0x10 | local_190;
          local_11c = local_194;
          local_114 = local_1b8;
          local_118 = uVar4;
          FUN_004acae0(local_1b8,0xe,&local_124,0x14,0);
          FUN_004acae0(uStack_10,0xe,&local_138,0x14,0);
          if (((*(uint *)(local_1bc + 0x208) & *(uint *)(local_1b4 + 0x208)) == 0) &&
             (iVar1 = (**(code **)(*(int *)(local_1b4 + 0x88) + 0x3c))
                                ((int *)(local_1b4 + 0x88),uVar3,(void *)(local_1bc + 0x88)),
             0 < iVar1)) {
            (**(code **)(*(int *)(local_1bc + 0x88) + 0x2c))
                      ((void *)(local_1bc + 0x88),6,(iVar1 * 0xe) / 500,(void *)0x0);
          }
        }
        else {
          local_138 = local_198;
          local_134 = (uint)local_1a8;
          local_12c = local_1b8;
          local_13c = uVar5;
          local_130 = uVar4;
          iVar1 = (**(code **)(*(int *)(local_1bc + 0x88) + 0x34))
                            ((int *)(local_1bc + 0x88),2,(void *)0x0);
          local_1ac = 1.0;
          *(undefined4 *)(local_1b4 + 0x20c) = 2;
          if ((*(uint *)(local_1bc + 0x208) & *(uint *)(local_1b4 + 0x208)) != 0) {
            local_1ac = 0.2;
          }
          local_1b0 = iVar1;
          (**(code **)(*(int *)(local_1b4 + 0x88) + 0x38))
                    ((int *)(local_1b4 + 0x88),uVar3,(void *)(local_1bc + 0x88),local_1ac);
          iVar2 = (**(code **)(*(int *)(local_1bc + 0x88) + 0x34))
                            ((int *)(local_1bc + 0x88),2,(void *)0x0);
          local_1a8 = *(int **)(local_1bc + 0x88);
          (**(code **)((int)local_1a8 + 0x2c))
                    ((int *)(local_1bc + 0x88),6,
                     (uint)((iVar1 * 8 - local_1b0) * 2 + iVar2 * -0xe) / 100,(void *)0x0);
          if (iVar2 == 0) {
            piVar8 = &local_1b8;
            uVar9 = 4;
            uVar7 = 0x18;
            iVar1 = local_1b8;
            FUN_004acae0(local_1b8,0x18,piVar8,4,1);
            uStack_1a0 = uStack_10;
            (**(code **)(*param_1 + 0x40))(0x17,&uStack_1a0,8,1);
            *(undefined4 *)(iVar1 + 0x200) = 2;
            FUN_00549a90(0,0);
            if (param_1[0xe0] == 0) {
              *(int *)(iVar1 + 0x218) = *(int *)(iVar1 + 0x218) + 1;
              piVar8[0x85] = piVar8[0x85] + 1;
            }
            FUN_00508ae6(&local_130,s_BeKill_hp_d_005c96f0,uVar9);
            (**(code **)(*param_1 + 0xe8))(&local_130,uVar7);
          }
          else {
            FUN_004acae0(param_2,0xb,&local_13c,0x14,0);
            FUN_004acae0(unaff_EDI,0xb,aiStack_150,0x14,0);
            FUN_004024a0((int)&uStack_1a0 + 1);
            uStack_4 = 0;
            FUN_004024a0((int)&uStack_1a0 + 2);
            uStack_4._0_1_ = 1;
            FUN_004024a0(&uStack_1a0);
            uStack_4 = CONCAT31(uStack_4._1_3_,2);
            FUN_005005b0(&uStack_1a1);
            uStack_158 = 0;
            appuStack_184[0] = &PTR_FUN_005a94e4;
            uStack_15c = 0;
            uStack_4 = 3;
            FUN_005005b0((int)&uStack_1a0 + 3);
            appuStack_184[0] = &PTR_FUN_005a9488;
            uStack_4 = 4;
            iVar1 = (**(code **)(*(int *)(local_1bc + 0x88) + 0x48))
                              ((void *)(local_1bc + 0x88),3,uVar3,appuStack_184);
            if ((iVar1 != 0) &&
               (iVar1 = (**(code **)(*param_1 + 0xfc))
                                  (*(undefined4 *)(local_1bc + 0x10),uStack_158,uStack_15c),
               iVar1 != 0)) {
              (**(code **)(*param_1 + 0xe8))(s_BeHit_005c96fc,local_1b8);
            }
            iVar1 = (iStack_140 - iStack_148) / 0x28;
            uStack_4 = 5;
            if (iVar1 != 0) {
              FUN_00402e90(iStack_148,iVar1 * 0x28);
            }
            appuStack_184[0] = &PTR_FUN_005a94e4;
            local_1a8 = &iStack_154;
            uStack_4._0_1_ = 9;
            uStack_4._1_3_ = 0;
            for (iVar1 = iStack_154; iVar1 != aiStack_150[0]; iVar1 = iVar1 + 0xc) {
              FUN_004d4a40(iVar1);
            }
            uStack_4._0_1_ = 8;
            FUN_0049b270();
            uStack_4._0_1_ = 7;
            FUN_00402bd0();
            uStack_4 = CONCAT31(uStack_4._1_3_,6);
            FUN_004026e0();
            uStack_4 = 0xffffffff;
            FUN_004026e0();
          }
        }
      }
      else {
        fVar6 = (float10)FUN_00549b00();
        if ((float10)_DAT_005a8418 <= fVar6) {
          (**(code **)(*param_1 + 0x11c))(0x42,param_2);
        }
      }
    }
  }
  ExceptionList = local_c;
  return;
}

