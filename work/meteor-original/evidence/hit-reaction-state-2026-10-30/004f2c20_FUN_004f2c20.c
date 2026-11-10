/* Original Meteor.exe static export @ 004f2c20; original sample not executed. */
/* XREF 005aa054 DATA */
/* XREF 005ab4dc DATA */
/* XREF 005ab91c DATA */
/* XREF 005ab29c DATA */

void __thiscall FUN_004f2c20(int *param_1,int param_2)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  LONG LVar7;
  uint uVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puStack_18;
  undefined4 *puStack_14;
  int iStack_10;
  void *pvStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_005a3858;
  pvStack_c = ExceptionList;
  ExceptionList = &pvStack_c;
  iVar3 = (**(code **)(*param_1 + 0x48))();
  if (iVar3 != 0) {
    puStack_18 = (undefined4 *)0x0;
    puStack_14 = (undefined4 *)0x0;
    iStack_10 = 0;
    uStack_4 = 0;
    iVar4 = (**(code **)(*param_1 + 0x134))();
    (**(code **)(*param_1 + 0x120))(&puStack_18,0x50);
    iVar3 = param_2;
    puVar9 = puStack_18;
    if (puStack_18 != puStack_14) {
      do {
        FUN_00487830();
        FUN_0049d3c0(&param_2,puVar9 + 1);
        iVar5 = FUN_00487830();
        if (((param_2 != *(int *)(iVar5 + 0x22ec)) && (*(int *)(param_2 + 0x200) == 2)) &&
           ((*(uint *)(iVar4 + 0x1f0) & *(uint *)(param_2 + 0x208)) != 0)) {
          puVar1 = *(undefined4 **)(iVar3 + 4);
          if (puVar1 == *(undefined4 **)(iVar3 + 8)) {
            FUN_004f4260(puVar1,puVar9);
          }
          else {
            if (puVar1 != (undefined4 *)0x0) {
              *puVar1 = *puVar9;
              puVar1[1] = puVar9[1];
              puVar1[2] = puVar9[2];
            }
            *(int *)(iVar3 + 4) = *(int *)(iVar3 + 4) + 0xc;
          }
        }
        puVar9 = puVar9 + 3;
      } while (puVar9 != puStack_14);
    }
    puVar9 = puStack_18;
    iVar3 = (iStack_10 - (int)puStack_18) / 0xc;
    if (iVar3 != 0) {
      uVar6 = iVar3 * 0xc;
      if (uVar6 < 0x81) {
        LVar7 = InterlockedExchange(&DAT_005d59e8,1);
        uVar2 = DAT_005c4248;
        if (LVar7 != 0) {
          uVar10 = 0;
          param_2 = 0x11;
          if (DAT_005c4248 != 0) {
            uVar8 = DAT_005d59ec >> 1;
            do {
              if ((uVar10 < uVar8) || (DAT_005d59e8 != 0)) {
                param_2 = param_2 * param_2 * param_2 * param_2;
                param_2 = param_2 * param_2;
                param_2 = param_2 * param_2;
              }
              else {
                LVar7 = InterlockedExchange(&DAT_005d59e8,1);
                if (LVar7 == 0) {
                  DAT_005c4248 = 1000;
                  DAT_005d59ec = uVar10;
                  goto LAB_004f2e5e;
                }
              }
              uVar10 = uVar10 + 1;
            } while (uVar10 < uVar2);
          }
          DAT_005c4248 = 0x1e;
          iVar3 = 6;
          while( true ) {
            iVar4 = iVar3;
            if (0x1b < iVar3) {
              iVar4 = 0x1b;
            }
            LVar7 = InterlockedExchange(&DAT_005d59e8,1);
            if (LVar7 == 0) break;
            if (iVar4 < 0x15) {
              Sleep(0);
              iVar3 = iVar3 + 1;
            }
            else {
              Sleep(1 << ((char)iVar4 - 0x14U & 0x1f));
              iVar3 = iVar3 + 1;
            }
          }
        }
LAB_004f2e5e:
        *puVar9 = *(undefined4 *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = puVar9;
        DAT_005d59e8 = 0;
      }
      else {
        FUN_005089fd(puStack_18);
      }
    }
  }
  ExceptionList = pvStack_c;
  return;
}

