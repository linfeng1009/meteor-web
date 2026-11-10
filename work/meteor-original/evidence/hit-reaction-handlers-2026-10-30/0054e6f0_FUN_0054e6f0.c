/* Original Meteor.exe static export @ 0054e6f0; original sample not executed. */
/* XREF 004acb30 UNCONDITIONAL_CALL */
/* XREF 004acafb UNCONDITIONAL_CALL */

void __thiscall
FUN_0054e6f0(int param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_4;
  if ((*(int *)(param_1 + 0x14) == 1) && (-1 < param_4)) {
    FUN_00553830();
    DAT_00724e24 = 0x7f;
    DAT_00724e25 = 4;
    FUN_0054f670(&DAT_00724e20,param_5);
    param_4 = param_2;
    FUN_005538e0(&param_4,2);
    FUN_005538e0(param_3,iVar3);
    iVar3 = *(int *)(*(int *)(param_1 + 4) + 8);
    if (iVar3 != *(int *)(param_1 + 4)) {
      do {
        FUN_0054f760(&DAT_00724e20);
        iVar2 = *(int *)(iVar3 + 0xc);
        if (iVar2 == 0) {
          iVar2 = *(int *)(iVar3 + 4);
          if (iVar3 == *(int *)(iVar2 + 0xc)) {
            do {
              iVar3 = iVar2;
              iVar2 = *(int *)(iVar3 + 4);
            } while (iVar3 == *(int *)(iVar2 + 0xc));
          }
          if (*(int *)(iVar3 + 0xc) != iVar2) {
            iVar3 = iVar2;
          }
        }
        else {
          for (iVar1 = *(int *)(iVar2 + 8); iVar3 = iVar2, iVar1 != 0; iVar1 = *(int *)(iVar1 + 8))
          {
            iVar2 = iVar1;
          }
        }
      } while (iVar3 != *(int *)(param_1 + 4));
    }
  }
  return;
}

