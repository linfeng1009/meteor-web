/* Original Meteor.exe static export @ 00496250; original sample not executed. */
/* XREF 005a9100 DATA */

void __fastcall FUN_00496250(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  char *pcVar5;
  
  iVar2 = 0;
  do {
    pcVar5 = s_CModel_005c942c + iVar2;
    (&DAT_0072b6b0)[iVar2] = *pcVar5;
    iVar2 = iVar2 + 1;
  } while (*pcVar5 != '\0');
  uVar3 = 0xffffffff;
  pcVar5 = &DAT_0072b6b0;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  if (*(char *)((int)&DAT_0072b6ac + ~uVar3 + 2) == '\\') {
    *(undefined1 *)((int)&DAT_0072b6ac + ~uVar3 + 2) = 0;
  }
  FUN_00478ec0(s_TexturePatch_005c941c,1);
  puVar4 = &DAT_005c9414;
  FUN_004db420(&DAT_005c9414);
  FUN_005667b0(puVar4);
  FUN_00478ec0(s_etexture__005c9408,0);
  FUN_00479160(*(undefined4 *)(param_1 + 0x22cc));
  FUN_00474860(*(undefined4 *)(param_1 + 0x22d0));
  pcVar5 = s_SFX_effect_lst_005c93f8;
  FUN_004db420(s_SFX_effect_lst_005c93f8);
  FUN_00566940(pcVar5);
  return;
}

