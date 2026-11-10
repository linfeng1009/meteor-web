/* Original Meteor.exe static export @ 004e90b0; original sample not executed. */
/* XREF 004e8c93 UNCONDITIONAL_CALL */

void __fastcall FUN_004e90b0(int *param_1)

{
  int *piVar1;
  uint *puVar2;
  int *piVar3;
  char cVar4;
  int *piVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  void *pvVar9;
  char *pcVar10;
  void *pvVar11;
  undefined4 *puVar12;
  uint uVar13;
  char *pcVar14;
  undefined4 *puVar15;
  uint local_ba0;
  int local_b9c;
  uint local_b98;
  int local_b94;
  int local_b90;
  int local_b8c;
  int local_b88;
  int local_b84;
  int local_b80;
  int local_b7c;
  uint local_b78;
  void *local_b74;
  int local_b70;
  void *local_b6c;
  undefined4 local_b68;
  undefined4 local_b64;
  undefined4 local_b60;
  char local_b5c [32];
  undefined4 local_b3c;
  undefined1 local_b38 [2];
  char acStack_b36 [234];
  undefined4 uStack_a4c;
  char acStack_a48 [8];
  char acStack_a40 [4];
  char acStack_a3c [4];
  char acStack_a38 [4];
  char acStack_a34 [4];
  char acStack_a30 [4];
  char acStack_a2c [4];
  char acStack_a28 [4];
  char acStack_a24 [4];
  char acStack_a20 [12];
  char acStack_a14 [12];
  char acStack_a08 [2556];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_005a30ee;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  local_b6c = operator_new(0x18);
  local_4 = 0;
  if (local_b6c == (void *)0x0) {
    piVar5 = (int *)0x0;
  }
  else {
    piVar5 = (int *)FUN_0049fe50(param_1 + 1);
  }
  local_4 = 0xffffffff;
  if (*piVar5 != -1) {
    local_b7c = 0;
    local_b3c = 0;
    param_1[0x19] = 0;
    param_1[0x1b] = 0;
    param_1[0x20] = 0;
    iVar6 = FUN_0049ff70();
    while (0 < iVar6) {
      FUN_0049fff0(1);
      FUN_004a0220(local_b5c,2);
      iVar6 = FUN_00514de0(local_b5c,s_BeginBase_005c6848,9);
      if (iVar6 == 0) {
        FUN_004a0050();
        FUN_004a00e0(param_1 + 0x1c,2);
        FUN_004a0220(param_1 + 0x15,2);
        FUN_004a00e0(local_b38,2);
        FUN_004a0220(local_b5c,2);
        FUN_004a0180(&local_b3c,0);
        iVar6 = FUN_004e8ca0(0x40800000);
        param_1[0x1f] = iVar6;
      }
      else {
        iVar6 = FUN_00514de0(local_b5c,s_BeginObject_005c6810,0xb);
        if (iVar6 == 0) {
          local_b80 = 0;
          local_b8c = 0;
          FUN_004a00e0(&local_b90,2);
          local_b90 = local_b90 + -1;
          FUN_004a0220(acStack_b36 + 0x66,0);
          FUN_004a0220(local_b5c,2);
          iVar6 = FUN_00514de0(local_b5c,s_Morph_005c6800,5);
          uVar13 = (uint)(iVar6 == 0);
          if (uVar13 == 0) {
            iVar6 = param_1[0x19];
            acStack_b36[local_b90 * 2 + 2] = '\0';
            acStack_b36[local_b90 * 2 + 3] = (char)iVar6;
          }
          else {
            iVar6 = param_1[0x1b];
            acStack_b36[local_b90 * 2 + 2] = '\x01';
            acStack_b36[local_b90 * 2 + 3] = (char)iVar6;
          }
          local_b7c = local_b7c + 1;
          local_b78 = uVar13;
          iVar6 = FUN_00514de0(local_b5c,s_Dummy_005c9f6c,5);
          if (iVar6 == 0) {
            FUN_0049fff0(0);
            uVar7 = FUN_004e8ef0(0x40800000,0x40800000,0x40800000);
          }
          else {
            FUN_004a0050();
            FUN_004a00e0(&local_b98,2);
            FUN_004a0050();
            FUN_004a00e0(&local_b94,0);
            local_ba0 = 0;
            if (0 < (int)local_b98) {
              do {
                FUN_004a0050();
                FUN_004a0050();
                FUN_004a0220(acStack_b36 + local_ba0 * 0x58 + 0xda,2);
                FUN_004a00e0(&local_b9c,2);
                acStack_b36[local_ba0 * 0x58 + 0xea] = (char)local_b9c;
                FUN_004a00e0(&local_b9c,2);
                acStack_b36[local_ba0 * 0x58 + 0xeb] = (char)local_b9c;
                FUN_004a00e0(&local_b9c,2);
                acStack_b36[local_ba0 * 0x58 + 0xec] = (char)local_b9c;
                if ((acStack_b36[local_ba0 * 0x58 + 0xda] == 'k') ||
                   (acStack_b36[local_ba0 * 0x58 + 0xda] == 'K')) {
                  iVar6 = 1;
                }
                else {
                  iVar6 = 0;
                }
                FUN_004a00e0(&local_b9c,2);
                acStack_b36[local_ba0 * 0x58 + 0xef] = (char)local_b9c;
                FUN_004a00e0(&local_b9c,0);
                iVar8 = local_ba0 * 0x58;
                acStack_b36[iVar8 + 0xf0] = (char)local_b9c;
                if ((iVar6 != 0) && (*(int *)(acStack_b36 + iVar8 + 0xea) == 0xff0000)) {
                  local_b8c = 1;
                }
                acStack_b36[iVar8 + 0xee] = (char)local_b94;
                if (local_b94 == 0) {
                  pcVar10 = acStack_b36 + iVar8 + 0xf2;
                  pcVar10[0] = '\0';
                  pcVar10[1] = '\0';
                  pcVar10[2] = -0x80;
                  pcVar10[3] = '>';
                  pcVar10 = acStack_b36 + iVar8 + 0xf6;
                  pcVar10[0] = -0x33;
                  pcVar10[1] = -0x34;
                  pcVar10[2] = 'L';
                  pcVar10[3] = '=';
                  pcVar10 = acStack_b36 + iVar8 + 0xfa;
                  pcVar10[0] = '\0';
                  pcVar10[1] = '\0';
                  pcVar10[2] = -0x80;
                  pcVar10[3] = '?';
                  pcVar10 = acStack_b36 + iVar8 + 0xfe;
                  pcVar10[0] = '\x02';
                  pcVar10[1] = '\0';
                  pcVar10[2] = '\0';
                  pcVar10[3] = '\0';
                  pcVar10 = acStack_b36 + iVar8 + 0x102;
                  pcVar10[0] = '\0';
                  pcVar10[1] = '\0';
                  pcVar10[2] = '\0';
                  pcVar10[3] = '\0';
                  pcVar10 = acStack_b36 + iVar8 + 0x106;
                  pcVar10[0] = '\0';
                  pcVar10[1] = '\0';
                  pcVar10[2] = '\0';
                  pcVar10[3] = '\0';
                }
                else {
                  FUN_004a0050();
                  FUN_004a0180(acStack_b36 + local_ba0 * 0x58 + 0xf2,0);
                  FUN_004a0050();
                  FUN_004a0180(acStack_b36 + local_ba0 * 0x58 + 0xf6,0);
                  FUN_004a0050();
                  FUN_004a0180(acStack_b36 + local_ba0 * 0x58 + 0xfa,2);
                  FUN_004a00e0(acStack_b36 + local_ba0 * 0x58 + 0xfe,0);
                  FUN_004a0050();
                  FUN_004a0180(acStack_b36 + local_ba0 * 0x58 + 0x102,0);
                  FUN_004a0050();
                  FUN_004a00e0(acStack_b36 + local_ba0 * 0x58 + 0x106,0);
                }
                FUN_004a0050();
                FUN_004a01b0(acStack_b36 + local_ba0 * 0x58 + 0x10a,0,3);
                FUN_004a0050();
                FUN_004a01b0(acStack_b36 + local_ba0 * 0x58 + 0x116,0,3);
                FUN_004a0050();
                FUN_004a01b0(acStack_b36 + local_ba0 * 0x58 + 0x122,0,3);
                if (*param_1 == 0) {
                  local_b60 = 0x3f800000;
                }
                else {
                  local_b60 = *(undefined4 *)(acStack_b36 + local_ba0 * 0x58 + 0x102);
                }
                iVar8 = local_ba0 * 0x58;
                pcVar10 = acStack_b36 + iVar8 + 0x10a;
                pcVar14 = acStack_b36 + iVar8 + 0x112;
                pcVar14[0] = '\0';
                pcVar14[1] = '\0';
                pcVar14[2] = -0x80;
                pcVar14[3] = '?';
                pcVar14 = acStack_b36 + iVar8 + 0x10e;
                pcVar14[0] = '\0';
                pcVar14[1] = '\0';
                pcVar14[2] = -0x80;
                pcVar14[3] = '?';
                pcVar10[0] = '\0';
                pcVar10[1] = '\0';
                pcVar10[2] = -0x80;
                pcVar10[3] = '?';
                local_b68 = local_b60;
                local_b64 = local_b60;
                uVar7 = FUN_0040ed80(pcVar10,acStack_b36 + iVar8 + 0x116,acStack_b36 + iVar8 + 0x122
                                     ,&local_b68,*(undefined4 *)(acStack_b36 + iVar8 + 0xf2),
                                     acStack_b36 + iVar8 + 0xda,(int)acStack_b36[iVar8 + 0xef],iVar6
                                     ,CONCAT31(0x3f8000,acStack_b36[iVar8 + 0xea]),
                                     CONCAT31((int3)(local_ba0 * 5 >> 8),acStack_b36[iVar8 + 0xeb]),
                                     CONCAT31(0x3f8000,acStack_b36[iVar8 + 0xec]));
                uVar13 = local_ba0 + 1;
                *(undefined4 *)(acStack_b36 + local_ba0 * 0x58 + 0x12e) = uVar7;
                local_ba0 = uVar13;
              } while ((int)uVar13 < (int)local_b98);
            }
            FUN_004a0050();
            FUN_004a00e0(&local_b84,2);
            FUN_004a0220(local_b5c,2);
            FUN_004a00e0(&local_b70,2);
            FUN_004a00e0(&local_b80,2);
            if (local_b80 == 0) {
              FUN_0049fff0(0);
            }
            else {
              if ((param_1[0x20] & 3U) == 0) {
                iVar6 = FUN_005099a7(param_1[0x21],(param_1[0x20] * 3 + 0xc) * 4);
                param_1[0x21] = iVar6;
                if (iVar6 == 0) {
                  FUN_004e8500(s_moveUV_alloc_error__005c9f58);
                }
              }
              FUN_004a01b0(param_1[0x21] + 4 + param_1[0x20] * 0xc,0,2);
            }
            pvVar11 = _malloc(local_b84 << 5);
            local_b94 = 0;
            local_b74 = pvVar11;
            if (0 < local_b84) {
              do {
                local_ba0 = local_b94 << 3;
                FUN_004a01b0((void *)((int)pvVar11 + local_b94 * 0x20),2,3);
                if (local_b5c[0] == 'T') {
                  FUN_004a01b0((int)pvVar11 + local_ba0 * 4 + 0x18,2,2);
                }
                if (local_b70 == 0) {
                  *(undefined4 *)((int)pvVar11 + local_ba0 * 4 + 0x14) = 0;
                  *(undefined4 *)((int)pvVar11 + local_ba0 * 4 + 0x10) = 0;
                  *(undefined4 *)((int)pvVar11 + local_ba0 * 4 + 0xc) = 0;
                }
                else {
                  FUN_004a01b0((int)pvVar11 + local_ba0 * 4 + 0xc,2,3);
                }
                FUN_0049fff0(1);
                local_b94 = local_b94 + 1;
              } while (local_b94 < local_b84);
            }
            FUN_004a0050();
            FUN_004a00e0(&local_b88,0);
            pvVar9 = _malloc(local_b88 * 0x18);
            local_b94 = 0;
            if (0 < local_b88) {
              do {
                local_ba0 = local_b94 * 6;
                FUN_004a0050();
                *(undefined4 *)((int)pvVar9 + local_ba0 * 4) = 1;
                FUN_004a00e0(&local_b98,2);
                if (local_b98 == 0xffffffff) {
                  local_b98 = 0;
                }
                *(undefined4 *)((int)pvVar9 + local_ba0 * 4 + 4) =
                     *(undefined4 *)(acStack_b36 + local_b98 * 0x58 + 0x12e);
                *(undefined4 *)((int)pvVar9 + local_ba0 * 4 + 8) =
                     *(undefined4 *)(acStack_b36 + local_b98 * 0x58 + 0x106);
                FUN_004a0110((int)pvVar9 + local_ba0 * 4 + 0xc,0,3);
                local_b94 = local_b94 + 1;
              } while (local_b94 < local_b88);
            }
            FUN_004059e0(6);
            if (local_b70 != 0) {
              FUN_00406520(0,1);
            }
            FUN_0040c900(0,pvVar11,local_b84,pvVar9,local_b88 * 6,local_b88,1);
            if (local_b80 == 0) {
              FUN_004054e0(0,10,2);
            }
            uVar7 = FUN_00405df0(0);
            FUN_00405660(uVar7,*(undefined4 *)(acStack_b36 + local_b98 * 0x58 + 0xfa));
            if (*param_1 != 0) {
              FUN_004ebb40(uVar7,*(undefined4 *)(acStack_b36 + local_b98 * 0x58 + 0xfe));
            }
            if (local_b8c != 0) {
              FUN_004054e0(uVar7,3,0);
            }
            FUN_005089fd(local_b74);
            FUN_005089fd(pvVar9);
            FUN_004065c0(uVar7,1);
            FUN_004065c0(uVar7,2);
            uVar13 = local_b78;
          }
          if (uVar13 == 0) {
            if ((param_1[0x19] & 3U) == 0) {
              iVar6 = FUN_005099a7(param_1[0x12],(param_1[0x19] * 0xb + 0x2c) * 4);
              param_1[0x12] = iVar6;
              if (iVar6 == 0) {
                FUN_004e8500(s_Spart_memory_alloc_error__005c9f20);
              }
            }
            pcVar14 = acStack_b36 + 0x66;
            pcVar10 = (char *)(param_1[0x12] + param_1[0x19] * 0x2c);
            do {
              cVar4 = *pcVar14;
              pcVar14 = pcVar14 + 1;
              *pcVar10 = cVar4;
              pcVar10 = pcVar10 + 1;
            } while (cVar4 != '\0');
            *(undefined4 *)(param_1[0x12] + 0x10 + param_1[0x19] * 0x2c) = uVar7;
            if (local_b80 != 0) {
              *(undefined2 *)(param_1[0x21] + param_1[0x20] * 0xc) = 0;
              *(short *)(param_1[0x21] + 2 + param_1[0x20] * 0xc) = (short)param_1[0x19];
              param_1[0x20] = param_1[0x20] + 1;
            }
            param_1[0x19] = param_1[0x19] + 1;
          }
          else {
            if ((param_1[0x1b] & 3U) == 0) {
              iVar6 = FUN_005099a7(param_1[0x13],(param_1[0x1b] * 0xb + 0x2c) * 4);
              param_1[0x13] = iVar6;
              if (iVar6 == 0) {
                FUN_004e8500(s_VApart_memory_alloc_error__005c9f3c);
              }
            }
            iVar6 = param_1[0x13] + param_1[0x1b] * 0x2c;
            pcVar10 = acStack_b36 + 0x66;
            do {
              cVar4 = *pcVar10;
              pcVar10[iVar6 - (int)(acStack_b36 + 0x66)] = cVar4;
              pcVar10 = pcVar10 + 1;
            } while (cVar4 != '\0');
            *(undefined4 *)(iVar6 + 0x10) = uVar7;
            *(int *)(iVar6 + 0x14) = param_1[0x1c];
            local_b8c = iVar6;
            pvVar11 = _malloc(param_1[0x1c] << 2);
            *(void **)(iVar6 + 0x28) = pvVar11;
            puVar12 = (undefined4 *)FUN_0040bb20(uVar7,&local_b84,0,&local_b88);
            local_ba0 = local_b88 * local_b84 * 4;
            pvVar11 = _malloc(local_ba0);
            **(undefined4 **)(iVar6 + 0x28) = pvVar11;
            puVar15 = (undefined4 *)**(undefined4 **)(iVar6 + 0x28);
            for (uVar13 = local_ba0 >> 2; uVar13 != 0; uVar13 = uVar13 - 1) {
              *puVar15 = *puVar12;
              puVar12 = puVar12 + 1;
              puVar15 = puVar15 + 1;
            }
            for (uVar13 = local_ba0 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
              *(undefined1 *)puVar15 = *(undefined1 *)puVar12;
              puVar12 = (undefined4 *)((int)puVar12 + 1);
              puVar15 = (undefined4 *)((int)puVar15 + 1);
            }
            pvVar11 = _malloc(param_1[0x1c] << 2);
            *(void **)(local_b8c + 0x24) = pvVar11;
            local_b94 = 0;
            if (0 < param_1[0x1c]) {
              do {
                *(float *)(*(int *)(local_b8c + 0x24) + local_b94 * 4) = (float)local_b94;
                local_b94 = local_b94 + 1;
              } while (local_b94 < param_1[0x1c]);
            }
            if (local_b80 != 0) {
              *(undefined2 *)(param_1[0x21] + param_1[0x20] * 0xc) = 1;
              *(short *)(param_1[0x21] + 2 + param_1[0x20] * 0xc) = (short)param_1[0x1b];
              param_1[0x20] = param_1[0x20] + 1;
            }
            param_1[0x1b] = param_1[0x1b] + 1;
          }
        }
        else {
          iVar6 = FUN_00514de0(local_b5c,s_BeginRelationship_005c67ec,0x11);
          if (iVar6 == 0) {
            FUN_004a00e0(&local_b94,0);
            local_ba0 = 0;
            if (0 < local_b94) {
              do {
                FUN_004a0050();
                FUN_004a00e0(&local_b98,0);
                local_b98 = 0;
                acStack_b36[local_ba0 + 0xa6] = '\0';
                local_ba0 = local_ba0 + 1;
              } while ((int)local_ba0 < local_b94);
            }
            local_b9c = 0;
            if (0 < local_b7c) {
              do {
                uVar13 = (uint)(byte)acStack_b36[local_b9c + 0xa6];
                if (acStack_b36[local_b9c * 2 + 2] == '\0') {
                  if (uVar13 == 0) {
                    *(undefined4 *)
                     (param_1[0x12] + 0x24 + (uint)(byte)acStack_b36[local_b9c * 2 + 3] * 0x2c) = 1;
                    *(int *)(param_1[0x12] + 0x20 +
                            (uint)(byte)acStack_b36[local_b9c * 2 + 3] * 0x2c) = param_1[0x1f];
                  }
                  else {
                    local_ba0 = (uint)(byte)acStack_b36[uVar13 * 2 + 1];
                    if (acStack_b36[uVar13 * 2] == '\0') {
                      iVar6 = param_1[0x12];
                    }
                    else {
                      iVar6 = param_1[0x13];
                    }
                    *(undefined4 *)
                     (param_1[0x12] + 0x20 + (uint)(byte)acStack_b36[local_b9c * 2 + 3] * 0x2c) =
                         *(undefined4 *)(iVar6 + 0x10 + local_ba0 * 0x2c);
                    *(undefined4 *)
                     (param_1[0x12] + 0x24 + (uint)(byte)acStack_b36[local_b9c * 2 + 3] * 0x2c) = 0;
                  }
                  local_b98 = (uint)(byte)acStack_b36[local_b9c * 2 + 3];
                  uVar7 = *(undefined4 *)(param_1[0x12] + 0x20 + local_b98 * 0x2c);
                  iVar6 = param_1[0x12] + local_b98 * 0x2c;
                }
                else {
                  if (uVar13 == 0) {
                    *(undefined4 *)
                     (param_1[0x13] + 0x1c + (uint)(byte)acStack_b36[local_b9c * 2 + 3] * 0x2c) = 1;
                    *(int *)(param_1[0x13] + 0x18 +
                            (uint)(byte)acStack_b36[local_b9c * 2 + 3] * 0x2c) = param_1[0x1f];
                  }
                  else {
                    local_ba0 = (uint)(byte)acStack_b36[uVar13 * 2 + 1];
                    if (acStack_b36[uVar13 * 2] == '\0') {
                      iVar6 = param_1[0x12];
                    }
                    else {
                      iVar6 = param_1[0x13];
                    }
                    *(undefined4 *)
                     (param_1[0x13] + 0x18 + (uint)(byte)acStack_b36[local_b9c * 2 + 3] * 0x2c) =
                         *(undefined4 *)(iVar6 + 0x10 + local_ba0 * 0x2c);
                    *(undefined4 *)
                     (param_1[0x13] + 0x1c + (uint)(byte)acStack_b36[local_b9c * 2 + 3] * 0x2c) = 0;
                  }
                  local_b98 = (uint)(byte)acStack_b36[local_b9c * 2 + 3];
                  uVar7 = *(undefined4 *)(param_1[0x13] + 0x18 + local_b98 * 0x2c);
                  iVar6 = param_1[0x13] + local_b98 * 0x2c;
                }
                FUN_0040b100(*(undefined4 *)(iVar6 + 0x10),uVar7);
                local_b9c = local_b9c + 1;
              } while (local_b9c < local_b7c);
            }
          }
          else {
            iVar6 = FUN_00514de0(local_b5c,s_BeginPose_005c9f14,9);
            if (iVar6 == 0) {
              piVar1 = param_1 + 0x1a;
              FUN_004a00e0(piVar1,0);
              pvVar11 = _malloc(*piVar1 * 0x18);
              param_1[0x14] = (int)pvVar11;
              local_ba0 = 0;
              if (0 < *piVar1) {
                do {
                  FUN_004a0050();
                  FUN_004a00e0(param_1[0x14] + 4 + local_ba0 * 0x18,2);
                  FUN_004a00e0(param_1[0x14] + 8 + local_ba0 * 0x18,2);
                  FUN_004a00e0(param_1[0x14] + 0xc + local_ba0 * 0x18,2);
                  FUN_004a00e0(param_1[0x14] + 0x10 + local_ba0 * 0x18,2);
                  FUN_004a00e0(param_1[0x14] + 0x14 + local_ba0 * 0x18,0);
                  piVar3 = (int *)(param_1[0x14] + local_ba0 * 0x18);
                  *piVar3 = (*(int *)(param_1[0x14] + 8 + local_ba0 * 0x18) - piVar3[1]) + 1;
                  local_ba0 = local_ba0 + 1;
                } while ((int)local_ba0 < *piVar1);
              }
            }
            else {
              iVar6 = FUN_00514de0(local_b5c,s_BeginMove_005c683c,9);
              if (iVar6 == 0) {
                local_b98 = param_1[0x1c];
                pvVar11 = _malloc(local_b98 * 0xc);
                param_1[0x1d] = (int)pvVar11;
                FUN_0049fff0(0);
                local_b94 = 0;
                if (0 < (int)local_b98) {
                  do {
                    FUN_004a00e0(&local_ba0,2);
                    FUN_004a01b0(pvVar11,0,3);
                    pvVar11 = (void *)((int)pvVar11 + 0xc);
                    local_b94 = local_b94 + 1;
                  } while (local_b94 < (int)local_b98);
                }
              }
              else {
                iVar6 = FUN_00514de0(local_b5c,s_BeginFrame_005c682c,10);
                if (iVar6 == 0) {
                  FUN_004a00e0(&local_b90,2);
                  local_b90 = local_b90 + -1;
                  iVar6 = param_1[0x12] + (uint)(byte)acStack_b36[local_b90 * 2 + 3] * 0x2c;
                  FUN_004a01b0(iVar6 + 0x14,2,3);
                  puVar2 = (uint *)(iVar6 + 0x24);
                  FUN_004a00e0(puVar2,2);
                  FUN_004a00e0(&local_b6c,0);
                  local_b98 = 0xc;
                  if (local_b6c != (void *)0x0) {
                    *puVar2 = *puVar2 | 0x80;
                  }
                  pvVar11 = _malloc(param_1[0x1c] * 0x30);
                  *(void **)(iVar6 + 0x28) = pvVar11;
                  local_b94 = 0;
                  local_ba0 = 0;
                  if (0 < param_1[0x1c]) {
                    do {
                      FUN_004a0050();
                      FUN_004a01b0(*(int *)(iVar6 + 0x28) + local_ba0 * 4,0,local_b98);
                      local_b94 = local_b94 + 1;
                      local_ba0 = local_ba0 + local_b98;
                    } while (local_b94 < param_1[0x1c]);
                  }
                }
                else {
                  iVar6 = FUN_00514de0(local_b5c,s_BeginMorphdata_005c9f04,0xe);
                  if (iVar6 == 0) {
                    FUN_004a00e0(&local_b90,2);
                    local_b90 = local_b90 + -1;
                    iVar6 = param_1[0x13] + (uint)(byte)acStack_b36[local_b90 * 2 + 3] * 0x2c;
                    FUN_004a00e0((int *)(iVar6 + 0x14),0);
                    FUN_004a0220(local_b5c,2);
                    iVar8 = FUN_00514de0(local_b5c,s_FrameWeight_005c9ef8,0xb);
                    if (iVar8 == 0) {
                      FUN_0049fff0(0);
                      FUN_004a01b0(*(undefined4 *)(iVar6 + 0x24),2,param_1[0x1c]);
                      FUN_004a0050();
                    }
                    FUN_004a00e0(&local_b98,2);
                    FUN_004a0220(local_b5c,0);
                    local_b8c = *(int *)(iVar6 + 0x10);
                    local_b94 = 1;
                    local_b78 = (uint)(local_b5c[0] == 'T');
                    if (1 < *(int *)(iVar6 + 0x14)) {
                      do {
                        pvVar11 = _malloc(local_b98 << 5);
                        *(void **)(*(int *)(iVar6 + 0x28) + local_b94 * 4) = pvVar11;
                        FUN_0049fff0(0);
                        local_ba0 = 0;
                        if (0 < (int)local_b98) {
                          do {
                            local_b9c = local_ba0 << 3;
                            FUN_004a01b0((void *)((int)pvVar11 + local_ba0 * 0x20),2,3);
                            *(undefined4 *)((int)pvVar11 + local_b9c * 4 + 0xc) =
                                 *(undefined4 *)(**(int **)(iVar6 + 0x28) + 0xc + local_b9c * 4);
                            *(undefined4 *)((int)pvVar11 + local_b9c * 4 + 0x10) =
                                 *(undefined4 *)(**(int **)(iVar6 + 0x28) + 0x10 + local_b9c * 4);
                            *(undefined4 *)((int)pvVar11 + local_b9c * 4 + 0x14) =
                                 *(undefined4 *)(**(int **)(iVar6 + 0x28) + 0x14 + local_b9c * 4);
                            if (local_b78 == 0) {
                              *(undefined4 *)((int)pvVar11 + local_b9c * 4 + 0x18) =
                                   *(undefined4 *)(**(int **)(iVar6 + 0x28) + 0x18 + local_b9c * 4);
                              *(undefined4 *)((int)pvVar11 + local_b9c * 4 + 0x1c) =
                                   *(undefined4 *)(**(int **)(iVar6 + 0x28) + 0x1c + local_b9c * 4);
                            }
                            else {
                              FUN_004a01b0((int)pvVar11 + local_b9c * 4 + 0x18,2,2);
                            }
                            FUN_0049fff0(1);
                            local_ba0 = local_ba0 + 1;
                          } while ((int)local_ba0 < (int)local_b98);
                        }
                        local_b74 = (void *)FUN_0040bb20(local_b8c,0,0,0);
                        iVar8 = local_b8c;
                        FUN_0040bb90(local_b8c,pvVar11);
                        FUN_004065c0(iVar8,1);
                        FUN_004065c0(iVar8,2);
                        FUN_0040bb90(iVar8,local_b74);
                        local_b94 = local_b94 + 1;
                      } while (local_b94 < *(int *)(iVar6 + 0x14));
                    }
                  }
                  else {
                    FUN_0049fff0(0);
                  }
                }
              }
            }
          }
        }
      }
      iVar6 = FUN_0049ff70();
    }
  }
  thunk_FUN_0049feb0();
  FUN_00507850(piVar5);
  ExceptionList = local_c;
  return;
}

