/* Original Meteor.exe static export @ 005696a0; original sample not executed. */
/* XREF 005636b8 UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __thiscall FUN_005696a0(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  int local_64;
  int local_60;
  int local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_44;
  undefined1 local_40 [64];
  
  if (*(int *)(param_1 + 0x120) != 0) {
    iVar3 = FUN_00509f8f(param_2,&DAT_005ca380);
    if (iVar3 != 0) {
      FUN_0050ab32(local_40,0x40,iVar3);
      FUN_0050ab32(local_40,0x40,iVar3);
      FUN_0050b600(iVar3,s__s__d__s__d_005d12d0,local_40,&local_60,local_40,&local_5c);
      iVar6 = *(int *)(param_1 + 0x120);
      if ((local_60 == *(int *)(iVar6 + 0x38)) && (local_5c == *(int *)(iVar6 + 0x40))) {
        FUN_0050b600(iVar3,s__s__d__s__d__s__s_005d175c,local_40,iVar6 + 4,local_40,iVar6 + 8,
                     local_40,local_40);
        iVar6 = *(int *)(param_1 + 0x120);
        iVar5 = 0;
        if (0 < *(int *)(iVar6 + 0x38)) {
          puVar7 = (undefined4 *)(*(int *)(iVar6 + 0x3c) + 0x1a4);
          do {
            pvVar4 = operator_new(*(int *)(iVar6 + 8) * 0x1c);
            *puVar7 = pvVar4;
            iVar6 = *(int *)(param_1 + 0x120);
            iVar5 = iVar5 + 1;
            puVar7 = puVar7 + 0xac;
          } while (iVar5 < *(int *)(iVar6 + 0x38));
        }
        iVar6 = *(int *)(param_1 + 0x120);
        iVar5 = 0;
        if (0 < *(int *)(iVar6 + 0x40)) {
          puVar7 = (undefined4 *)(*(int *)(iVar6 + 0x44) + 0x1a4);
          do {
            pvVar4 = operator_new(*(int *)(iVar6 + 8) * 0x1c);
            *puVar7 = pvVar4;
            iVar6 = *(int *)(param_1 + 0x120);
            iVar5 = iVar5 + 1;
            puVar7 = puVar7 + 0xac;
          } while (iVar5 < *(int *)(iVar6 + 0x40));
        }
        local_64 = 0;
        if (0 < *(int *)(*(int *)(param_1 + 0x120) + 8)) {
          param_2 = 0;
          do {
            FUN_0050ab32(local_40,0x40,iVar3);
            FUN_0050ab32(local_40,0x40,iVar3);
            iVar6 = 0;
            if (0 < *(int *)(*(int *)(param_1 + 0x120) + 0x38)) {
              piVar8 = (int *)(*(int *)(*(int *)(param_1 + 0x120) + 0x3c) + 0x1a4);
              do {
                iVar5 = param_2 + *piVar8;
                FUN_0050b600(iVar3,s__s__f__f__f__s__f__f__f__f_005d1740,local_40,iVar5,iVar5 + 4,
                             iVar5 + 8,local_40,iVar5 + 0x18,iVar5 + 0xc,iVar5 + 0x10,iVar5 + 0x14);
                iVar6 = iVar6 + 1;
                piVar8 = piVar8 + 0xac;
              } while (iVar6 < *(int *)(*(int *)(param_1 + 0x120) + 0x38));
            }
            iVar6 = 0;
            if (0 < *(int *)(*(int *)(param_1 + 0x120) + 0x40)) {
              piVar8 = (int *)(*(int *)(*(int *)(param_1 + 0x120) + 0x44) + 0x1a4);
              do {
                iVar5 = param_2 + *piVar8;
                FUN_0050b600(iVar3,s__s__f__f__f__s__f__f__f__f_005d1740,local_40,iVar5,iVar5 + 4,
                             iVar5 + 8,local_40,iVar5 + 0x18,iVar5 + 0xc,iVar5 + 0x10,iVar5 + 0x14);
                iVar6 = iVar6 + 1;
                piVar8 = piVar8 + 0xac;
              } while (iVar6 < *(int *)(*(int *)(param_1 + 0x120) + 0x40));
            }
            FUN_0050ab32(local_40,0x40,iVar3);
            param_2 = param_2 + 0x1c;
            local_64 = local_64 + 1;
          } while (local_64 < *(int *)(*(int *)(param_1 + 0x120) + 8));
        }
        FUN_00509e57(iVar3);
        iVar3 = 0;
        if (0 < *(int *)(*(int *)(param_1 + 0x120) + 8)) {
          do {
            FUN_00569330(iVar3);
            if (*(float *)(param_1 + 0xf0) < *(float *)(*(int *)(param_1 + 0x120) + 0x4c)) {
              *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x4c) = *(undefined4 *)(param_1 + 0xf0);
            }
            if (*(float *)(param_1 + 0xf4) < *(float *)(*(int *)(param_1 + 0x120) + 0x50)) {
              *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x50) = *(undefined4 *)(param_1 + 0xf4);
            }
            if (*(float *)(param_1 + 0xf8) < *(float *)(*(int *)(param_1 + 0x120) + 0x54)) {
              *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x54) = *(undefined4 *)(param_1 + 0xf8);
            }
            if (*(float *)(*(int *)(param_1 + 0x120) + 0x58) < *(float *)(param_1 + 0xe4)) {
              *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x58) = *(undefined4 *)(param_1 + 0xe4);
            }
            if (*(float *)(*(int *)(param_1 + 0x120) + 0x5c) < *(float *)(param_1 + 0xe8)) {
              *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x5c) = *(undefined4 *)(param_1 + 0xe8);
            }
            if (*(float *)(*(int *)(param_1 + 0x120) + 0x60) < *(float *)(param_1 + 0xec)) {
              *(undefined4 *)(*(int *)(param_1 + 0x120) + 0x60) = *(undefined4 *)(param_1 + 0xec);
            }
            iVar3 = iVar3 + 1;
          } while (iVar3 < *(int *)(*(int *)(param_1 + 0x120) + 8));
        }
        FUN_00569330(0);
        iVar3 = *(int *)(param_1 + 0x120);
        local_44 = *(float *)(iVar3 + 0x54) + *(float *)(iVar3 + 0x60);
        fVar1 = (*(float *)(iVar3 + 0x50) + *(float *)(iVar3 + 0x5c)) * _DAT_005a83e8;
        *(float *)(iVar3 + 0x70) =
             (*(float *)(iVar3 + 0x58) + *(float *)(iVar3 + 0x4c)) * _DAT_005a83e8;
        fVar2 = local_44 * _DAT_005a83e8;
        *(float *)(iVar3 + 0x74) = fVar1;
        *(float *)(iVar3 + 0x78) = fVar2;
        iVar3 = *(int *)(param_1 + 0x120);
        *(float *)(iVar3 + 100) = *(float *)(iVar3 + 0x58) - *(float *)(iVar3 + 0x4c);
        *(float *)(iVar3 + 0x68) = *(float *)(iVar3 + 0x5c) - *(float *)(iVar3 + 0x50);
        *(float *)(iVar3 + 0x6c) = *(float *)(iVar3 + 0x60) - *(float *)(iVar3 + 0x54);
        iVar3 = *(int *)(param_1 + 0x120);
        local_58 = *(float *)(iVar3 + 0x58) - *(float *)(iVar3 + 0x70);
        local_54 = *(float *)(iVar3 + 0x5c) - *(float *)(iVar3 + 0x74);
        local_50 = *(float *)(iVar3 + 0x60) - *(float *)(iVar3 + 0x78);
        *(float *)(iVar3 + 0x7c) = local_58;
        *(float *)(iVar3 + 0x80) = local_54;
        *(float *)(iVar3 + 0x84) = local_50;
        FUN_00477b90(3,*(int *)(param_1 + 0x120) + 0x70);
        return 1;
      }
      FUN_00509e57(iVar3);
    }
  }
  return 0;
}

