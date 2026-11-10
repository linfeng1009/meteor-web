/* Original Meteor.exe static export @ 0055da50; original sample not executed. */
/* XREF 004dc618 UNCONDITIONAL_JUMP */

int __thiscall FUN_0055da50(int param_1,int param_2,int param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iStack_50;
  undefined1 auStack_4c [12];
  undefined1 auStack_40 [64];
  
  iVar2 = FUN_0055d540();
  if (((iVar2 != 0) && (*(int *)(*(int *)(param_1 + 0x638) + 0x60) != 0)) &&
     (cVar1 = FUN_00570b70(param_1 + 0x2b8,param_1 + 0x2ac,param_2 + 0x1b8,param_2 + 0x1dc),
     cVar1 != '\0')) {
    pcVar3 = (char *)FUN_0055c4f0(*(undefined4 *)(param_1 + 0xfc));
    iVar2 = *(int *)(*(int *)(param_1 + 0x638) + 0x94) + *pcVar3 * 0x68;
    iStack_50 = 0;
    if (0 < *(int *)(iVar2 + 0x28)) {
      do {
        iVar5 = *(int *)(*(int *)(iVar2 + 0x1c) + iStack_50 * 4);
        if (iVar5 == 0x1000) {
          iVar5 = 0;
          if (0 < *(int *)(param_1 + 0x20)) {
            iVar6 = 0;
            do {
              piVar7 = *(int **)(iVar6 + 0xa8 + *(int *)(param_1 + 0x354));
              if (piVar7 != (int *)0x0) {
                (**(code **)(*piVar7 + 4))(auStack_40,auStack_4c,0);
                iVar4 = FUN_0055d950(auStack_4c,auStack_40,1);
                if (iVar4 != 0) {
                  return iVar2;
                }
              }
              iVar5 = iVar5 + 1;
              iVar6 = iVar6 + 0x2f0;
            } while (iVar5 < *(int *)(param_1 + 0x20));
          }
        }
        else if (iVar5 == 0x1001) {
          piVar7 = (int *)**(int **)(param_1 + 0x658);
          if (piVar7 != *(int **)(param_1 + 0x658)) {
            do {
              if (((*(int *)(piVar7[2] + 0x140) != 1) && (DAT_00726854 != (code *)0x0)) &&
                 ((*(int *)(piVar7[2] + 300) != 0 && (iVar5 = FUN_0056f1d0(param_2), iVar5 != 0))))
              {
                if (param_3 == 0) {
                  return iVar2;
                }
                if ((DAT_00726854 != (code *)0x0) &&
                   (iVar5 = (*DAT_00726854)(param_1,param_2), iVar5 == 0)) {
                  return iVar2;
                }
              }
              piVar7 = (int *)*piVar7;
            } while (piVar7 != (int *)*(int *)(param_1 + 0x658));
          }
        }
        else {
          iVar5 = FUN_00557f30(iVar5,auStack_40,auStack_4c);
          if ((iVar5 != 0) && (iVar5 = FUN_0055d950(auStack_4c,auStack_40,1), iVar5 != 0)) {
            return iVar2;
          }
        }
        iStack_50 = iStack_50 + 1;
      } while (iStack_50 < *(int *)(iVar2 + 0x28));
    }
  }
  return 0;
}

