/* Original Meteor.exe static export @ 0054e660; original sample not executed. */
/* XREF 004acaeb UNCONDITIONAL_CALL */

void __thiscall
FUN_0054e660(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
            undefined4 param_6)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_5;
  if ((*(int *)(param_1 + 0x14) == 1) && (-1 < param_5)) {
    iVar2 = FUN_0054f530(param_2);
    if (iVar2 != 0) {
      FUN_00553830();
      DAT_00724e24 = 0x7f;
      DAT_00724e25 = 4;
      FUN_0054f670(&DAT_00724e20,param_6);
      param_5 = param_3;
      FUN_005538e0(&param_5,2);
      FUN_005538e0(param_4,iVar1);
      FUN_0054f760(&DAT_00724e20);
    }
  }
  return;
}

