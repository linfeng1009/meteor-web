/* Original Meteor.exe static export @ 0055dc20; original sample not executed. */
/* XREF 0056567b UNCONDITIONAL_CALL */

int __thiscall FUN_0055dc20(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int local_50;
  undefined1 local_4c [12];
  undefined1 local_40 [64];
  
  iVar2 = FUN_0055d540();
  if (((iVar2 != 0) && (*(int *)(*(int *)(param_1 + 0x638) + 0x60) != 0)) &&
     (cVar1 = FUN_00570630(param_1 + 0x2b8,param_1 + 0x2c4,param_2,param_3), cVar1 != '\0')) {
    pcVar3 = (char *)FUN_0055c4f0(*(undefined4 *)(param_1 + 0xfc));
    iVar2 = *(int *)(*(int *)(param_1 + 0x638) + 0x94) + *pcVar3 * 0x68;
    local_50 = 0;
    if (0 < *(int *)(iVar2 + 0x28)) {
      do {
        iVar4 = *(int *)(*(int *)(iVar2 + 0x1c) + local_50 * 4);
        if (iVar4 == 0x1000) {
          iVar4 = 0;
          if (0 < *(int *)(param_1 + 0x20)) {
            iVar5 = 0;
            do {
              piVar6 = *(int **)(*(int *)(param_1 + 0x354) + 0xa8 + iVar5);
              if (piVar6 != (int *)0x0) {
                (**(code **)(*piVar6 + 4))(local_40,local_4c,0);
                cVar1 = FUN_00570630(local_4c,local_40,param_2,param_3);
                if (cVar1 != '\0') {
                  return iVar2;
                }
              }
              iVar4 = iVar4 + 1;
              iVar5 = iVar5 + 0x2f0;
            } while (iVar4 < *(int *)(param_1 + 0x20));
          }
        }
        else if (iVar4 == 0x1001) {
          piVar6 = (int *)**(int **)(param_1 + 0x658);
          if (piVar6 != *(int **)(param_1 + 0x658)) {
            do {
              if (((*(int *)(piVar6[2] + 0x140) != 1) && (*(int *)(piVar6[2] + 300) != 0)) &&
                 (iVar4 = FUN_0056f260(param_2,param_3), iVar4 != 0)) {
                return iVar2;
              }
              piVar6 = (int *)*piVar6;
            } while (piVar6 != (int *)*(int *)(param_1 + 0x658));
          }
        }
        else {
          FUN_00557f30(iVar4,local_40,local_4c);
          cVar1 = FUN_00570630(local_4c,local_40,param_2,param_3);
          if (cVar1 != '\0') {
            return iVar2;
          }
        }
        local_50 = local_50 + 1;
      } while (local_50 < *(int *)(iVar2 + 0x28));
    }
  }
  return 0;
}

