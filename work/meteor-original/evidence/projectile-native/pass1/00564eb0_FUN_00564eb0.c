/* Original Meteor.exe static export @ 00564eb0; original sample not executed. */
/* XREF 0048f9f2 UNCONDITIONAL_CALL */

void __fastcall FUN_00564eb0(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  char *pcVar6;
  int local_8;
  
  local_8 = 0;
  piVar4 = *(int **)(param_1 + 0x4b4);
  if (0 < *(int *)(param_1 + 0x4b0)) {
    do {
      iVar3 = -1;
      piVar4[5] = 0;
      *(undefined1 *)(piVar4 + 3) = 1;
      pcVar6 = (char *)(piVar4[10] + 0x68);
      do {
        if (iVar3 == 0) break;
        iVar3 = iVar3 + -1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar1 != '\0');
      if ((iVar3 != -2) && (iVar3 = FUN_00567230((char *)(piVar4[10] + 0x68),0), iVar3 != 0)) {
        puVar2 = (undefined4 *)FUN_0047b740();
        puVar5 = (undefined4 *)(piVar4[10] + 0x98);
        for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar2 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar2 = puVar2 + 1;
        }
        FUN_00566200(1);
      }
      if ((*piVar4 < 10) || (0xf < *piVar4)) {
        *(undefined1 *)(piVar4 + 2) = 1;
      }
      else {
        *(bool *)(piVar4 + 2) = piVar4[0xb] != 0;
      }
      local_8 = local_8 + 1;
      piVar4 = piVar4 + 0x2b;
    } while (local_8 < *(int *)(param_1 + 0x4b0));
  }
  FUN_00564140();
  return;
}

