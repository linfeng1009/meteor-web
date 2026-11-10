/* Original Meteor.exe static export @ 004c33e0; original sample not executed. */
/* XREF 004fc284 UNCONDITIONAL_CALL */
/* XREF 004f8ced UNCONDITIONAL_CALL */
/* XREF 004f8d0f UNCONDITIONAL_CALL */
/* XREF 004f8d4d UNCONDITIONAL_CALL */
/* XREF 004f8d6f UNCONDITIONAL_CALL */

int __thiscall FUN_004c33e0(int param_1,char *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  bool bVar9;
  
  iVar2 = 7;
  bVar9 = true;
  pcVar7 = param_2;
  pcVar8 = s_player_005c9c0c;
  do {
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    bVar9 = *pcVar7 == *pcVar8;
    pcVar7 = pcVar7 + 1;
    pcVar8 = pcVar8 + 1;
  } while (bVar9);
  if (bVar9) {
    iVar3 = *(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518);
    uVar6 = 0;
    iVar2 = iVar3 >> 0x1f;
    if (iVar3 / 0x124 + iVar2 != iVar2) {
      iVar2 = *(int *)(param_1 + 0x518);
      do {
        if ((-1 < *(int *)(iVar2 + 8)) && (*(int *)(iVar2 + 4) == 1)) {
          return iVar2;
        }
        uVar6 = uVar6 + 1;
        iVar2 = iVar2 + 0x124;
      } while (uVar6 < (uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124));
    }
  }
  else {
    iVar2 = 4;
    bVar9 = true;
    pcVar7 = param_2;
    pcVar8 = &DAT_005c9c08;
    do {
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      bVar9 = *pcVar7 == *pcVar8;
      pcVar7 = pcVar7 + 1;
      pcVar8 = pcVar8 + 1;
    } while (bVar9);
    if (bVar9) {
      iVar3 = *(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518);
      uVar6 = 0;
      iVar2 = iVar3 >> 0x1f;
      if (iVar3 / 0x124 + iVar2 != iVar2) {
        iVar2 = *(int *)(param_1 + 0x518);
        while (((*(int *)(iVar2 + 8) < 0 || (*(char *)(iVar2 + 0x60) == '\0')) ||
               (*(int *)(iVar2 + 0x4c) != param_3))) {
          uVar6 = uVar6 + 1;
          iVar2 = iVar2 + 0x124;
          if ((uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124) <= uVar6) {
            return 0;
          }
        }
        return iVar2;
      }
    }
    else {
      iVar2 = 9;
      bVar9 = true;
      pcVar7 = param_2;
      pcVar8 = &DAT_005c9bfc;
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar9 = *pcVar7 == *pcVar8;
        pcVar7 = pcVar7 + 1;
        pcVar8 = pcVar8 + 1;
      } while (bVar9);
      if (bVar9) {
        iVar3 = *(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518);
        uVar6 = 0;
        iVar2 = iVar3 >> 0x1f;
        if (iVar3 / 0x124 + iVar2 != iVar2) {
          iVar2 = *(int *)(param_1 + 0x518);
          while (((*(int *)(iVar2 + 8) < 0 || (*(char *)(iVar2 + 0x60) == '\0')) ||
                 (*(int *)(iVar2 + 0x4c) == param_3))) {
            uVar6 = uVar6 + 1;
            iVar2 = iVar2 + 0x124;
            if ((uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124) <= uVar6) {
              return 0;
            }
          }
          return iVar2;
        }
      }
      else {
        iVar2 = 5;
        bVar9 = true;
        pcVar7 = param_2;
        pcVar8 = &DAT_005c9bf4;
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar9 = *pcVar7 == *pcVar8;
          pcVar7 = pcVar7 + 1;
          pcVar8 = pcVar8 + 1;
        } while (bVar9);
        if (bVar9) {
          iVar3 = *(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518);
          uVar6 = 0;
          iVar2 = iVar3 >> 0x1f;
          if (iVar3 / 0x124 + iVar2 != iVar2) {
            iVar2 = *(int *)(param_1 + 0x518);
            while ((*(int *)(iVar2 + 8) < 0 || (*(char *)(iVar2 + 0x61) == '\0'))) {
              uVar6 = uVar6 + 1;
              iVar2 = iVar2 + 0x124;
              if ((uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124) <= uVar6)
              {
                return 0;
              }
            }
            return iVar2;
          }
        }
        else {
          iVar3 = *(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518);
          uVar6 = 0;
          iVar2 = iVar3 >> 0x1f;
          if (iVar3 / 0x124 + iVar2 != iVar2) {
            iVar2 = *(int *)(param_1 + 0x518);
            do {
              if ((-1 < *(int *)(iVar2 + 8)) && (iVar3 = *(int *)(iVar2 + 0xc), iVar3 != 0)) {
                uVar4 = 0xffffffff;
                pcVar7 = param_2;
                do {
                  if (uVar4 == 0) break;
                  uVar4 = uVar4 - 1;
                  cVar1 = *pcVar7;
                  pcVar7 = pcVar7 + 1;
                } while (cVar1 != '\0');
                iVar5 = ~uVar4 - 1;
                if (*(int *)(iVar3 + 0x41c) - (int)*(char **)(iVar3 + 0x418) == iVar5) {
                  bVar9 = true;
                  pcVar7 = *(char **)(iVar3 + 0x418);
                  pcVar8 = param_2;
                  do {
                    if (iVar5 == 0) break;
                    iVar5 = iVar5 + -1;
                    bVar9 = *pcVar7 == *pcVar8;
                    pcVar7 = pcVar7 + 1;
                    pcVar8 = pcVar8 + 1;
                  } while (bVar9);
                  if (bVar9) {
                    return iVar2;
                  }
                }
              }
              uVar6 = uVar6 + 1;
              iVar2 = iVar2 + 0x124;
              if ((uint)((*(int *)(param_1 + 0x51c) - *(int *)(param_1 + 0x518)) / 0x124) <= uVar6)
              {
                return 0;
              }
            } while( true );
          }
        }
      }
    }
  }
  return 0;
}

