/* Original Meteor.exe static export @ 004f0c50; original sample not executed. */
/* XREF 005aa0f4 DATA */
/* XREF 005ab57c DATA */
/* XREF 005ab9bc DATA */
/* XREF 005ab33c DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_004f0c50(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  float10 fVar7;
  uint *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  uint uStack_64;
  uint uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [36];
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar1 = (**(code **)(*param_1 + 0x48))();
  if ((iVar1 != 0) && (piVar5 = *(int **)param_1[0x8f], piVar5 != (int *)param_1[0x8f])) {
    do {
      if (piVar5[2] == 0) {
LAB_004f0e9d:
        piVar4 = (int *)piVar5[1];
        piVar6 = (int *)*piVar5;
        *piVar4 = (int)piVar6;
        piVar6[1] = (int)piVar4;
        FUN_00402e90(piVar5,0xc);
      }
      else {
        fVar7 = (float10)FUN_00549b00();
        if ((float10)_DAT_005a9500 < fVar7) {
LAB_004f0e90:
          if ((undefined4 *)piVar5[2] != (undefined4 *)0x0) {
            (*(code *)**(undefined4 **)piVar5[2])(1);
          }
          goto LAB_004f0e9d;
        }
        FUN_0047b740();
        FUN_00477eb0(auStack_30);
        uStack_50 = uStack_c;
        uStack_4c = uStack_8;
        uStack_48 = uStack_4;
        (**(code **)(*(int *)piVar5[2] + 4))(param_2);
        FUN_0047b740();
        FUN_00477eb0(auStack_30);
        uStack_5c = uStack_c;
        uStack_58 = uStack_8;
        uStack_54 = uStack_4;
        iVar2 = FUN_00487830();
        iVar2 = *(int *)(*(int *)(iVar2 + 0x2188) + 8);
        iVar3 = FUN_00487830();
        if (iVar2 != *(int *)(iVar3 + 0x2188)) {
          do {
            if ((*(int *)(iVar2 + 0x14) != iVar1 + 0x65c) &&
               (iVar3 = (**(code **)(*param_1 + 0x128))(*(undefined4 *)(iVar2 + 0x10)), iVar3 != 0))
            {
              if (*(int *)(iVar2 + 0x14) == 0) {
                iVar3 = 0;
              }
              else {
                iVar3 = *(int *)(iVar2 + 0x14) + -0x65c;
              }
              piVar4 = (int *)FUN_00487830();
              iVar3 = (**(code **)(*piVar4 + 0x1a4))(iVar3,&uStack_50,&uStack_5c,0x3f800000);
              if (0 < iVar3) {
                uStack_44 = *(undefined4 *)(iVar2 + 0x10);
                iVar3 = piVar5[2];
                uStack_40 = *(undefined4 *)(iVar3 + 0x54);
                uStack_3c = *(undefined4 *)(iVar3 + 0x58);
                uStack_38 = *(undefined4 *)(iVar3 + 0x5c);
                uStack_34 = *(undefined4 *)(iVar3 + 0x60);
                FUN_0054a6c0(5,&uStack_44,0x14,0);
                break;
              }
            }
            FUN_0043c6c0();
            iVar3 = FUN_00487830();
          } while (iVar2 != *(int *)(iVar3 + 0x2188));
        }
        iVar3 = FUN_00487830();
        if (iVar2 != *(int *)(iVar3 + 0x2188)) {
          uStack_64 = param_1[0x95] << 0xc | *(uint *)(piVar5[2] + 0x68);
          puVar8 = &uStack_64;
LAB_004f0e86:
          FUN_0054a6c0(10,puVar8,4,0);
          goto LAB_004f0e90;
        }
        puVar10 = &uStack_5c;
        puVar9 = &uStack_50;
        FUN_00487830(puVar9,puVar10);
        FUN_00562dd0(puVar9,puVar10);
        puVar10 = &uStack_5c;
        puVar9 = &uStack_50;
        FUN_00487830(puVar9,puVar10);
        iVar2 = FUN_00564760(puVar9,puVar10);
        if (iVar2 != 0) {
          uStack_60 = param_1[0x95] << 0xc | *(uint *)(piVar5[2] + 0x68);
          puVar8 = &uStack_60;
          goto LAB_004f0e86;
        }
        piVar6 = (int *)*piVar5;
      }
      piVar5 = piVar6;
    } while (piVar6 != (int *)param_1[0x8f]);
  }
  return;
}

