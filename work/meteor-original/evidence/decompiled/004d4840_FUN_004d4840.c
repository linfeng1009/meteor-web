/* Meteor.exe original x86 @ 004d4840 */
/* Caller: 004d47ba */
/* Caller: 004d47d2 */
/* Caller: 004d6709 */
/* Caller: 004d6721 */
/* Caller: 004d3ac2 */
/* Caller: 004d3af7 */

void FUN_004d4840(undefined4 *param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar2 = (param_2 - (int)param_1) / 0x28;
  if (0 < iVar2) {
    do {
      iVar2 = iVar2 + -1;
      puVar3 = param_1;
      puVar4 = param_3;
      for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      param_3 = param_3 + 10;
      param_1 = param_1 + 10;
    } while (iVar2 != 0);
  }
  return;
}

