/* Original Meteor.exe static export @ 0057d990; original sample not executed. */
/* XREF 00561b86 UNCONDITIONAL_CALL */
/* XREF 0056c615 UNCONDITIONAL_CALL */
/* XREF 005615cd UNCONDITIONAL_CALL */

void __thiscall FUN_0057d990(int *param_1,int param_2)

{
  void *pvVar1;
  void *extraout_EDX;
  int iVar2;
  int iVar3;
  int iVar4;
  
  FUN_0057d910();
  param_1[0x5b] = param_2;
  pvVar1 = operator_new(param_2 * 0x2c);
  iVar2 = 0;
  if (pvVar1 == (void *)0x0) {
    pvVar1 = (void *)0x0;
  }
  else if (-1 < param_2 + -1) {
    do {
      FUN_0057d140();
      param_2 = param_2 + -1;
      pvVar1 = extraout_EDX;
    } while (param_2 != 0);
  }
  *param_1 = (int)pvVar1;
  FUN_0047c140(4);
  FUN_0047c1e0(param_1[0x5b] * 6,param_1[0x5b] * 2,0);
  iVar3 = 0;
  FUN_00481b30();
  param_2 = 0;
  if (0 < param_1[0x5b]) {
    do {
      *(int **)(*param_1 + iVar2) = param_1;
      FUN_0057d150();
      FUN_00481d00(iVar3,0xffffffff);
      FUN_00481d40(iVar3,0,0,0xffffffff);
      FUN_00481d00(iVar3 + 1,0xffffffff);
      FUN_00481d40(iVar3 + 1,0x3f800000,0,0xffffffff);
      FUN_00481d00(iVar3 + 2,0xffffffff);
      FUN_00481d40(iVar3 + 2,0x3f800000,0x3f800000,0xffffffff);
      FUN_00481d00(iVar3 + 3,0xffffffff);
      FUN_00481d40(iVar3 + 3,0,0,0xffffffff);
      FUN_00481d00(iVar3 + 4,0xffffffff);
      iVar4 = iVar3 + 5;
      FUN_00481d40(iVar3 + 4,0x3f800000,0x3f800000,0xffffffff);
      FUN_00481d00(iVar4,0xffffffff);
      iVar3 = iVar3 + 6;
      FUN_00481d40(iVar4,0,0x3f800000,0xffffffff);
      param_2 = param_2 + 1;
      iVar2 = iVar2 + 0x2c;
    } while (param_2 < param_1[0x5b]);
  }
  FUN_00481b90();
  return;
}

