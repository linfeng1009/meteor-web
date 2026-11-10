/* Original Meteor.exe static export @ 0055da59; original sample not executed. */

int FUN_0055da59(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int unaff_ESI;
  int iVar6;
  int *piVar7;
  int iStack00000010;
  int in_stack_00000064;
  int in_stack_00000068;
  
  iVar3 = FUN_0055d540();
  iVar1 = in_stack_00000064;
  if (((iVar3 != 0) && (*(int *)(*(int *)(unaff_ESI + 0x638) + 0x60) != 0)) &&
     (cVar2 = FUN_00570b70(unaff_ESI + 0x2b8,unaff_ESI + 0x2ac,in_stack_00000064 + 0x1b8,
                           in_stack_00000064 + 0x1dc), cVar2 != '\0')) {
    pcVar4 = (char *)FUN_0055c4f0(*(undefined4 *)(unaff_ESI + 0xfc));
    in_stack_00000064 = *(int *)(*(int *)(unaff_ESI + 0x638) + 0x94) + *pcVar4 * 0x68;
    iStack00000010 = 0;
    if (0 < *(int *)(in_stack_00000064 + 0x28)) {
      do {
        iVar3 = *(int *)(*(int *)(in_stack_00000064 + 0x1c) + iStack00000010 * 4);
        if (iVar3 == 0x1000) {
          iVar3 = 0;
          if (0 < *(int *)(unaff_ESI + 0x20)) {
            iVar6 = 0;
            do {
              piVar7 = *(int **)(iVar6 + 0xa8 + *(int *)(unaff_ESI + 0x354));
              if (piVar7 != (int *)0x0) {
                (**(code **)(*piVar7 + 4))(&stack0x00000020,&stack0x00000014,0);
                iVar5 = FUN_0055d950(&stack0x00000014,&stack0x00000020,1);
                if (iVar5 != 0) {
                  return in_stack_00000064;
                }
              }
              iVar3 = iVar3 + 1;
              iVar6 = iVar6 + 0x2f0;
            } while (iVar3 < *(int *)(unaff_ESI + 0x20));
          }
        }
        else if (iVar3 == 0x1001) {
          piVar7 = (int *)**(int **)(unaff_ESI + 0x658);
          if (piVar7 != *(int **)(unaff_ESI + 0x658)) {
            do {
              if (((*(int *)(piVar7[2] + 0x140) != 1) && (DAT_00726854 != (code *)0x0)) &&
                 ((*(int *)(piVar7[2] + 300) != 0 && (iVar3 = FUN_0056f1d0(iVar1), iVar3 != 0)))) {
                if (in_stack_00000068 == 0) {
                  return in_stack_00000064;
                }
                if ((DAT_00726854 != (code *)0x0) && (iVar3 = (*DAT_00726854)(), iVar3 == 0)) {
                  return in_stack_00000064;
                }
              }
              piVar7 = (int *)*piVar7;
            } while (piVar7 != (int *)*(int *)(unaff_ESI + 0x658));
          }
        }
        else {
          iVar3 = FUN_00557f30(iVar3,&stack0x00000020,&stack0x00000014);
          if ((iVar3 != 0) &&
             (iVar3 = FUN_0055d950(&stack0x00000014,&stack0x00000020,1), iVar3 != 0)) {
            return in_stack_00000064;
          }
        }
        iStack00000010 = iStack00000010 + 1;
      } while (iStack00000010 < *(int *)(in_stack_00000064 + 0x28));
    }
  }
  return 0;
}

