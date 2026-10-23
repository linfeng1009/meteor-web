/* Meteor.exe original x86 @ 004d4000 */
/* Caller: 004d46ef */
/* Caller: 004d664b */
/* Caller: 004d3e45 */
/* Caller: 004d39db */
/* Caller: 004d573c */
/* Caller: 004d57fc */
/* Caller: 004d5869 */
/* Caller: 004d592f */
/* Caller: 004d599c */
/* Caller: 004d64ea */

int * __thiscall FUN_004d4000(int *param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int local_4;
  
  if (param_2 != param_1) {
    iVar1 = param_2[1];
    puVar6 = (undefined4 *)*param_2;
    uVar2 = (iVar1 - (int)puVar6) / 0xc;
    puVar5 = (undefined4 *)*param_1;
    if ((uint)((param_1[2] - (int)puVar5) / 0xc) < uVar2) {
      iVar4 = FUN_004d43e0(uVar2,puVar6,iVar1);
      iVar1 = (param_1[2] - *param_1) / 0xc;
      if (iVar1 != 0) {
        FUN_00402e90(*param_1,iVar1 * 0xc);
      }
      *param_1 = iVar4;
      param_1[2] = iVar4 + uVar2 * 0xc;
    }
    else {
      uVar3 = (param_1[1] - (int)puVar5) / 0xc;
      if (uVar3 < uVar2) {
        local_4 = (int)(uVar3 * 0xc) / 0xc;
        if (0 < local_4) {
          do {
            *puVar5 = *puVar6;
            puVar5[1] = puVar6[1];
            local_4 = local_4 + -1;
            puVar5[2] = puVar6[2];
            puVar5 = puVar5 + 3;
            puVar6 = puVar6 + 3;
          } while (local_4 != 0);
        }
        FUN_004f4800(*param_2 + ((param_1[1] - *param_1) / 0xc) * 0xc,param_2[1],param_1[1],param_2)
        ;
      }
      else {
        param_2 = (int *)((iVar1 - (int)puVar6) / 0xc);
        if (0 < (int)param_2) {
          do {
            *puVar5 = *puVar6;
            puVar5[1] = puVar6[1];
            puVar5[2] = puVar6[2];
            param_2 = (int *)((int)param_2 + -1);
            puVar5 = puVar5 + 3;
            puVar6 = puVar6 + 3;
          } while (param_2 != (int *)0x0);
        }
      }
    }
    param_1[1] = *param_1 + uVar2 * 0xc;
  }
  return param_1;
}

