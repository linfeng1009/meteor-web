/* Original Meteor.exe static export @ 00564760; original sample not executed. */
/* XREF 004c1383 UNCONDITIONAL_CALL */
/* XREF 005603a2 UNCONDITIONAL_CALL */
/* XREF 004cecfb UNCONDITIONAL_CALL */
/* XREF 004cedc3 UNCONDITIONAL_CALL */
/* XREF 004f0e5f UNCONDITIONAL_CALL */
/* XREF 004f11a2 UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_00564760(int param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  undefined4 uVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined1 local_c [12];
  
  uVar2 = param_3;
  if (*(char *)(param_1 + 0x251) != '\0') {
    FUN_00562dd0(param_2,param_3);
    param_3 = 0;
    if (0 < *(int *)(param_1 + 0x29c)) {
      do {
        piVar1 = *(int **)(*(int *)(param_1 + 0x2a0) + param_3 * 4);
        cVar3 = FUN_00570600(piVar1 + 3,piVar1 + 6,param_2,uVar2,0);
        if (cVar3 != '\0') {
          iVar5 = 0;
          if (0 < *piVar1) {
            do {
              iVar4 = FUN_0056aee0(*(undefined4 *)(piVar1[1] + iVar5 * 4));
              if (*(int *)(iVar4 + 0x50) == 0) {
                *(undefined4 *)(iVar4 + 0x50) = 1;
                iVar4 = FUN_0056f5f0(param_2,uVar2,iVar4 + 0x1c,iVar4 + 0x28,iVar4 + 0x34,local_c);
                if (iVar4 != 0) {
                  return 1;
                }
              }
              iVar5 = iVar5 + 1;
            } while (iVar5 < *piVar1);
          }
          uVar6 = 0;
          if (piVar1[0x14] - piVar1[0x13] >> 2 != 0) {
            do {
              iVar5 = *(int *)(piVar1[0x13] + uVar6 * 4);
              if ((((iVar5 != 0) && (*(char *)(iVar5 + 8) != '\0')) && (*(int *)(iVar5 + 0x2c) != 0)
                  ) && ((*(char *)(iVar5 + 10) != '\0' &&
                        (iVar5 = FUN_0056b350(param_2,uVar2,local_c,0), iVar5 != 0)))) {
                return 1;
              }
              uVar6 = uVar6 + 1;
            } while (uVar6 < (uint)(piVar1[0x14] - piVar1[0x13] >> 2));
          }
        }
        param_3 = param_3 + 1;
        if (*(int *)(param_1 + 0x29c) <= param_3) {
          return 0;
        }
      } while( true );
    }
  }
  return 0;
}

