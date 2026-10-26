/* Original Meteor.exe static export @ 0056dad0; original sample not executed. */
/* XREF 0056e7ff DATA */

undefined4 FUN_0056dad0(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar1 = *param_1;
  iVar2 = *param_2;
  for (puVar3 = (undefined4 *)**(undefined4 **)(iVar1 + 0x260);
      puVar3 != *(undefined4 **)(iVar1 + 0x260); puVar3 = (undefined4 *)*puVar3) {
  }
  for (puVar3 = (undefined4 *)**(undefined4 **)(iVar1 + 0x264);
      puVar3 != *(undefined4 **)(iVar1 + 0x264); puVar3 = (undefined4 *)*puVar3) {
  }
  for (puVar3 = (undefined4 *)**(undefined4 **)(iVar2 + 0x260);
      puVar3 != *(undefined4 **)(iVar2 + 0x260); puVar3 = (undefined4 *)*puVar3) {
  }
  for (puVar3 = (undefined4 *)**(undefined4 **)(iVar2 + 0x264);
      puVar3 != *(undefined4 **)(iVar2 + 0x264); puVar3 = (undefined4 *)*puVar3) {
  }
  iVar4 = FUN_00581500(iVar2);
  if ((iVar4 == 0) && (iVar4 = FUN_00581530(iVar2), iVar4 == 0)) {
    iVar4 = FUN_00581500(iVar1);
    if ((iVar4 == 0) && (iVar4 = FUN_00581530(iVar1), iVar4 == 0)) {
      if (*(int *)(iVar1 + 4) == 9) {
        if (*(int *)(iVar2 + 4) != 9) {
          return 1;
        }
      }
      else if (*(int *)(iVar2 + 4) == 9) {
        return 0xffffffff;
      }
      return 0;
    }
    return 1;
  }
  return 0xffffffff;
}

