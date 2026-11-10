/* Original Meteor.exe static export @ 004e8400; original sample not executed. */

void FUN_004e8400(void)

{
  int iVar1;
  int *piVar2;
  int *unaff_EBX;
  int unaff_EBP;
  int *piVar3;
  int unaff_EDI;
  
  while( true ) {
    iVar1 = __ftol();
    if (*(int *)(unaff_EBP + 0x298) < iVar1) {
      iVar1 = *(int *)(unaff_EBP + 0x298);
    }
    FUN_00557c10(iVar1);
    if ((iVar1 < 1) || (*(int *)(unaff_EDI + 0x8a4) != 0)) {
      *(undefined4 *)(unaff_EDI + 0x348) = 1;
    }
    else {
      *(undefined4 *)(unaff_EDI + 0x348) = 0;
    }
    unaff_EBX = (int *)*unaff_EBX;
    if (unaff_EBX == (int *)*(int *)(unaff_EBP + 600)) break;
    if (unaff_EBX[2] == 0) {
      unaff_EDI = 0;
    }
    else {
      unaff_EDI = unaff_EBX[2] + -0x65c;
    }
    (**(code **)(*(int *)(unaff_EDI + 0x65c) + 4))(&stack0x00000014,0,0);
  }
  piVar3 = (int *)**(int **)(unaff_EBP + 600);
  if (piVar3 != *(int **)(unaff_EBP + 600)) {
    do {
      if (piVar3[2] == 0) {
        piVar2 = (int *)0x0;
      }
      else {
        piVar2 = (int *)(piVar3[2] + -0x65c);
      }
      (**(code **)(*piVar2 + 0x30))();
      if (piVar3[2] == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = piVar3[2] + -0x65c;
      }
      if (*(int *)(iVar1 + 0x848) == 0) {
        (**(code **)(*(int *)piVar3[2] + 0x58))();
      }
      piVar3 = (int *)*piVar3;
    } while (piVar3 != (int *)*(int *)(unaff_EBP + 600));
  }
  return;
}

