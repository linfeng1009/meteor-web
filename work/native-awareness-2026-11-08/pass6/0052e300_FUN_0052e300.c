/* Original Meteor.exe static export @ 0052e300; original sample not executed. */
/* XREF 0052e8ea UNCONDITIONAL_CALL */

int * FUN_0052e300(uint param_1,uint param_2)

{
  int *piVar1;
  byte *pbVar2;
  char cVar3;
  byte bVar4;
  undefined1 uVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  int iVar13;
  undefined4 *puVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  int local_18;
  int local_10;
  int iStack_8;
  
  iVar7 = param_1;
  iVar11 = 0;
  local_10 = 1;
  local_18 = 0;
  piVar6 = (int *)FUN_00530dc0(1,0x7c);
  if (piVar6 == (int *)0x0) {
    return (int *)0x0;
  }
  FUN_0052cb10(piVar6,param_1);
  if ((((*(int *)(DAT_0072329c + 0x2c) == 0) || (*(int *)(DAT_0072329c + 0x30) == 0)) ||
      (*(int *)(DAT_0072329c + 0x34) == 0x400)) || (*(char *)(DAT_0072329c + 0xc) != '\x01')) {
LAB_0052e85e:
    FUN_0052c1a0(piVar6);
    FUN_00530d00(0x506);
  }
  else {
    if ((param_2 != 0x1909) && (param_2 != 0x190a)) {
      piVar6[8] = param_2;
      cVar3 = FUN_00530eb0(param_2);
      iVar13 = DAT_0072329c;
      if (cVar3 != '\0') {
        FUN_0052c4a0(piVar6);
        if (0x1908 < param_2) {
          if (param_2 == 0x80e0) {
            uVar15 = 0x404;
          }
          else {
            if (param_2 != 0x80e1) {
LAB_0052e460:
              FUN_0052c1a0(piVar6);
              FUN_00530d00(0x510);
              return (int *)0x0;
            }
            uVar15 = 0x405;
          }
LAB_0052e486:
          cVar3 = FUN_00535620(uVar15);
          uVar16 = 1;
          uVar15 = FUN_00530eb0(param_2);
          FUN_0052cd50(piVar6,*piVar6,piVar6[1],piVar6[2],uVar15,uVar16);
          if (cVar3 == '\0') {
            FUN_0052c4a0(iVar13);
            FUN_0052c1a0(piVar6);
            return (int *)0x0;
          }
          uVar8 = FUN_00530f60(piVar6[0xd]);
          piVar1 = (int *)(param_1 + 0x18);
          param_1 = 0;
          if (*piVar1 != 0) {
            uVar10 = (uint)*(byte *)(piVar6 + 3);
            do {
              uVar9 = 0;
              if (uVar10 != 0) {
                do {
                  iVar11 = (uint)*(byte *)(param_1 + *(int *)(iVar7 + 0x14)) * (uVar8 & 0xff) +
                           uVar9;
                  iVar13 = uVar10 * param_1 + uVar9;
                  uVar9 = uVar9 + 1;
                  *(undefined1 *)(iVar13 + piVar6[5]) = *(undefined1 *)(iVar11 + piVar6[0xb]);
                  uVar10 = (uint)*(byte *)(piVar6 + 3);
                } while (uVar9 < uVar10);
              }
              param_1 = param_1 + 1;
            } while (param_1 < *(uint *)(iVar7 + 0x18));
          }
          FUN_00530db0(piVar6[0xb]);
          piVar6[0xd] = 0x400;
          piVar6[0xb] = 0;
          piVar6[0xc] = 0;
          FUN_0052c4a0(1);
          return piVar6;
        }
        if (param_2 == 0x1908) {
          uVar15 = 0x402;
          goto LAB_0052e486;
        }
        if (param_2 != 0x1900) {
          if (param_2 != 0x1907) goto LAB_0052e460;
          uVar15 = 0x401;
          goto LAB_0052e486;
        }
        iVar7 = FUN_00530d80(*(undefined4 *)(iVar13 + 0x18));
        piVar6[5] = iVar7;
        iVar11 = local_18;
        if (iVar7 != 0) {
          iVar7 = FUN_00530d80(*(undefined4 *)(DAT_0072329c + 0x30));
          piVar6[0xb] = iVar7;
          if (iVar7 != 0) {
            uVar8 = *(uint *)(iVar13 + 0x18);
            puVar12 = *(undefined4 **)(iVar13 + 0x14);
            puVar14 = (undefined4 *)piVar6[5];
            for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
              *puVar14 = *puVar12;
              puVar12 = puVar12 + 1;
              puVar14 = puVar14 + 1;
            }
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined1 *)puVar14 = *(undefined1 *)puVar12;
              puVar12 = (undefined4 *)((int)puVar12 + 1);
              puVar14 = (undefined4 *)((int)puVar14 + 1);
            }
            uVar8 = *(uint *)(param_1 + 0x30);
            puVar12 = *(undefined4 **)(param_1 + 0x2c);
            puVar14 = (undefined4 *)piVar6[0xb];
            for (uVar10 = uVar8 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
              *puVar14 = *puVar12;
              puVar12 = puVar12 + 1;
              puVar14 = puVar14 + 1;
            }
            for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
              *(undefined1 *)puVar14 = *(undefined1 *)puVar12;
              puVar12 = (undefined4 *)((int)puVar12 + 1);
              puVar14 = (undefined4 *)((int)puVar14 + 1);
            }
            piVar6[0xc] = *(int *)(param_1 + 0x30);
            piVar6[0xd] = *(int *)(param_1 + 0x34);
            FUN_0052c4a0(iVar13);
            return piVar6;
          }
        }
        goto LAB_0052e803;
      }
      goto LAB_0052e85e;
    }
    if (piVar6[0xb] != 0) {
      FUN_00530db0(piVar6[0xb]);
    }
    if (param_2 == 0x190a) {
      local_10 = 2;
    }
    switch(*(undefined4 *)(DAT_0072329c + 0x34)) {
    case 0x401:
    case 0x402:
    case 0x403:
      bVar4 = FUN_00530f60(*(undefined4 *)(param_1 + 0x34));
      iVar11 = FUN_00530d80((uint)(*(int *)(param_1 + 0x30) * local_10) / (uint)bVar4);
      if (iVar11 != 0) {
        uVar8 = FUN_00530f60(*(undefined4 *)(param_1 + 0x34));
        uVar8 = uVar8 & 0xff;
        iVar13 = 0;
        piVar1 = (int *)(param_1 + 0x30);
        param_1 = 0;
        if (*piVar1 != 0) {
          do {
            uVar10 = 0;
            if (uVar8 != 0) {
              do {
                uVar10 = uVar10 + 1;
              } while (uVar10 < uVar8);
            }
            uVar5 = __ftol();
            *(undefined1 *)(iVar13 + iVar11) = uVar5;
            if (local_10 == 2) {
              if (*(int *)(DAT_0072329c + 0x34) == 0x403) {
                *(undefined1 *)(iVar13 + 1 + iVar11) =
                     *(undefined1 *)(*(int *)(iVar7 + 0x2c) + 3 + param_1);
              }
              else {
                *(undefined1 *)(iVar13 + 1 + iVar11) = 0xff;
              }
            }
            param_1 = param_1 + uVar8;
            iVar13 = iVar13 + local_10;
          } while (param_1 < *(uint *)(iVar7 + 0x30));
        }
        goto switchD_0052e595_default;
      }
      break;
    case 0x404:
    case 0x405:
    case 0x406:
      bVar4 = FUN_00530f60(*(undefined4 *)(param_1 + 0x34));
      iVar11 = FUN_00530d80((uint)(*(int *)(param_1 + 0x30) * local_10) / (uint)bVar4);
      if (iVar11 == 0) break;
      uVar10 = FUN_00530f60(*(undefined4 *)(param_1 + 0x34));
      piVar1 = (int *)(param_1 + 0x30);
      uVar10 = uVar10 & 0xff;
      param_1 = 0;
      iStack_8 = 0;
      uVar8 = uVar10;
      if (*piVar1 != 0) {
        do {
          for (; uVar8 != 0; uVar8 = uVar8 - 1) {
          }
          uVar5 = __ftol();
          *(undefined1 *)(iStack_8 + iVar11) = uVar5;
          if (local_10 == 2) {
            if (*(int *)(DAT_0072329c + 0x34) == 0x403) {
              *(undefined1 *)(iStack_8 + 1 + iVar11) =
                   *(undefined1 *)(*(int *)(iVar7 + 0x2c) + 3 + param_1);
            }
            else {
              *(undefined1 *)(iStack_8 + 1 + iVar11) = 0xff;
            }
          }
          iStack_8 = iStack_8 + local_10;
          param_1 = param_1 + uVar10;
          uVar8 = uVar10;
        } while (param_1 < *(uint *)(iVar7 + 0x30));
      }
    default:
switchD_0052e595_default:
      piVar6[0xb] = 0;
      piVar6[0xc] = 0;
      piVar6[0xd] = 0x400;
      *(char *)(piVar6 + 3) = (char)local_10;
      iVar13 = piVar6[1] * *piVar6 * local_10;
      piVar6[8] = param_2;
      piVar6[4] = *piVar6 * local_10;
      piVar6[7] = iVar13;
      piVar6[6] = iVar13;
      iVar13 = FUN_00530d80(iVar13);
      piVar6[5] = iVar13;
      if (iVar13 != 0) {
        if (local_10 == 2) {
          uVar8 = 0;
          if (*(int *)(iVar7 + 0x18) != 0) {
            do {
              *(undefined1 *)(piVar6[5] + uVar8 * 2) =
                   *(undefined1 *)(iVar11 + (uint)*(byte *)(uVar8 + *(int *)(iVar7 + 0x14)) * 2);
              pbVar2 = (byte *)(uVar8 + *(int *)(iVar7 + 0x14));
              uVar8 = uVar8 + 1;
              *(undefined1 *)(piVar6[5] + -1 + uVar8 * 2) =
                   *(undefined1 *)(iVar11 + 1 + (uint)*pbVar2 * 2);
            } while (uVar8 < *(uint *)(iVar7 + 0x18));
            FUN_00530db0(iVar11);
            return piVar6;
          }
        }
        else {
          uVar8 = 0;
          if (*(int *)(iVar7 + 0x18) != 0) {
            do {
              uVar10 = uVar8 + 1;
              *(undefined1 *)(uVar8 + piVar6[5]) =
                   *(undefined1 *)((uint)*(byte *)(uVar8 + *(int *)(iVar7 + 0x14)) + iVar11);
              uVar8 = uVar10;
            } while (uVar10 < *(uint *)(iVar7 + 0x18));
          }
        }
        FUN_00530db0(iVar11);
        return piVar6;
      }
    }
LAB_0052e803:
    FUN_00530db0(iVar11);
    FUN_0052c1a0(piVar6);
    if (local_10 != DAT_0072329c) {
      FUN_0052c4a0(local_10);
      return (int *)0x0;
    }
  }
  return (int *)0x0;
}

