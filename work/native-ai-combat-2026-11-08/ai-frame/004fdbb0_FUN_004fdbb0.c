/* Original Meteor.exe static export @ 004fdbb0; original sample not executed. */
/* XREF 004f9961 UNCONDITIONAL_CALL */

void __fastcall FUN_004fdbb0(int param_1)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  int local_10;
  int local_c;
  int local_8;
  
  iVar8 = *(int *)(param_1 + 0x68);
  if (iVar8 != *(int *)(param_1 + 0x6c)) {
    iVar4 = iVar8 + 0x30;
    local_c = iVar8;
    local_8 = iVar4;
    do {
      if (*(undefined **)(iVar4 + -0x24) == &DAT_00504be0) {
        if ((iVar4 != *(int *)(param_1 + 0x6c)) &&
           (local_10 = (*(int *)(param_1 + 0x6c) - iVar4) / 0x30, 0 < local_10)) {
          piVar3 = (int *)(iVar4 + 0x20);
          do {
            piVar3[-0x14] = piVar3[-8];
            piVar3[-0x13] = piVar3[-7];
            piVar3[-0x12] = piVar3[-6];
            piVar3[-0x11] = piVar3[-5];
            if (piVar3 + -4 != piVar3 + -0x10) {
              FUN_00403200(piVar3[-4],piVar3[-3]);
            }
            if (piVar3 + -1 != piVar3 + -0xd) {
              iVar8 = *piVar3;
              puVar5 = (undefined4 *)piVar3[-1];
              puVar7 = (undefined4 *)piVar3[-0xd];
              uVar1 = iVar8 - (int)puVar5;
              uVar2 = piVar3[-0xc] - (int)puVar7;
              if (uVar2 < uVar1) {
                puVar6 = puVar5;
                for (uVar1 = uVar2 >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
                  *puVar7 = *puVar6;
                  puVar6 = puVar6 + 1;
                  puVar7 = puVar7 + 1;
                }
                for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
                  *(undefined1 *)puVar7 = *(undefined1 *)puVar6;
                  puVar6 = (undefined4 *)((int)puVar6 + 1);
                  puVar7 = (undefined4 *)((int)puVar7 + 1);
                }
                FUN_00403490((undefined1 *)((piVar3[-0xc] - piVar3[-0xd]) + (int)puVar5),iVar8);
              }
              else {
                for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
                  *puVar7 = *puVar5;
                  puVar5 = puVar5 + 1;
                  puVar7 = puVar7 + 1;
                }
                for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
                  *(undefined1 *)puVar7 = *(undefined1 *)puVar5;
                  puVar5 = (undefined4 *)((int)puVar5 + 1);
                  puVar7 = (undefined4 *)((int)puVar7 + 1);
                }
                FUN_00402b30(piVar3[-0xd] + uVar1,piVar3[-0xc]);
              }
            }
            piVar3[-10] = piVar3[2];
            piVar3[-9] = piVar3[3];
            piVar3 = piVar3 + 0xc;
            local_10 = local_10 + -1;
            iVar4 = local_8;
            iVar8 = local_c;
          } while (local_10 != 0);
        }
        *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + -0x30;
        FUN_004c82d0();
      }
      else {
        iVar8 = iVar8 + 0x30;
        iVar4 = iVar4 + 0x30;
        local_c = iVar8;
        local_8 = iVar4;
      }
    } while (iVar8 != *(int *)(param_1 + 0x6c));
  }
  return;
}

