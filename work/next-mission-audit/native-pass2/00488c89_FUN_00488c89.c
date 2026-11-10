/* Original Meteor.exe static export @ 00488c89; original sample not executed. */

undefined4
FUN_00488c89(undefined4 param_1,int param_2,char *param_3,char *param_4,int param_5,
            undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint uVar6;
  char *unaff_EBX;
  char *unaff_EBP;
  int *unaff_ESI;
  undefined1 *in_stack_00000038;
  undefined1 *in_stack_0000003c;
  undefined4 in_stack_00000044;
  undefined4 in_stack_00000048;
  int in_stack_0000004c;
  void *in_stack_000000ec;
  undefined1 uStack000000f4;
  undefined3 uStack000000f5;
  undefined4 in_stack_00000104;
  undefined1 in_stack_00000118;
  undefined4 in_stack_00000128;
  char *pcVar7;
  undefined1 *puStack_4;
  
  puStack_4 = (undefined1 *)0x488c8e;
  FUN_004bf650();
  if (DAT_005e0328 == unaff_EBX) {
    puStack_4 = (undefined1 *)0x488ca2;
    param_4 = operator_new(0x33c);
    if (param_4 == unaff_EBX) {
      DAT_005e0328 = (char *)0x0;
    }
    else {
      DAT_005e0328 = (char *)FUN_0044d020();
    }
  }
  puStack_4 = &stack0x000000c4;
  FUN_0045a430();
  puStack_4 = (undefined1 *)0x8;
  FUN_00402b70((int)&param_5 + 3);
  puStack_4 = (undefined1 *)0x488d04;
  FUN_00402a70();
  puStack_4 = (undefined1 *)((int)&param_5 + 2);
  FUN_004024a0();
  puStack_4 = (undefined1 *)((int)&param_5 + 1);
  FUN_004024a0();
  puStack_4 = (undefined1 *)0x488d44;
  FUN_00499700();
  in_stack_0000004c = 2;
  uVar6 = 0xffffffff;
  pcVar7 = &stack0x00000084;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  puStack_4 = &stack0x00000083 + ~uVar6;
  FUN_00403200(&stack0x00000084);
  in_stack_00000048 = in_stack_00000128;
  uVar6 = 0xffffffff;
  pcVar7 = s_Single_005c91a4;
  do {
    if (uVar6 == 0) break;
    uVar6 = uVar6 - 1;
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  puStack_4 = (undefined1 *)(~uVar6 + 0x5c91a3);
  FUN_00403200(s_Single_005c91a4);
  puStack_4 = (undefined1 *)0x488dec;
  in_stack_00000044 = FUN_004c3850();
  if (in_stack_00000038 != in_stack_0000003c) {
    *in_stack_00000038 = (char)unaff_EBX;
    in_stack_0000003c = in_stack_00000038;
  }
  in_stack_0000004c = 0x10;
  puStack_4 = (undefined1 *)0x488e22;
  iVar3 = FUN_004c3860();
  puStack_4 = (undefined1 *)0x488e5b;
  FUN_004aad20();
  puStack_4 = &stack0x00000020;
  (**(code **)(*(int *)unaff_ESI[0x84b] + 0xa0))();
  *(undefined4 *)(unaff_ESI[0x84b] + 0x3a0) = 2;
  (**(code **)(*(int *)unaff_ESI[0x84b] + 0x88))();
  (**(code **)(*unaff_ESI + 0x2ec))(100000000);
  FUN_004736a0();
  in_stack_00000118 = 8;
  FUN_004736b0(s_127_0_0_1_005c9198);
  iVar2 = unaff_ESI[0x922];
  param_5 = CONCAT22(param_5._2_2_,0x628e);
  unaff_ESI[0x856] = (int)param_4;
  pcVar7 = s_Agent_005c9190;
  unaff_ESI[0x857] = param_5;
  uVar4 = FUN_004c3880();
  FUN_004c3870(uVar4);
  (**(code **)(iVar2 + 0x16c))();
  (**(code **)(unaff_ESI[0x922] + 0x198))(&puStack_4,param_7,1);
  (**(code **)(*unaff_ESI + 0x80))(2);
  uStack000000f4 = 0xc;
  uStack000000f5 = 0;
  if ((char *)(iVar3 * 0x3c) != unaff_EBX) {
    FUN_0049cf70(*(undefined4 *)(in_stack_0000004c + 4));
    *(int *)(in_stack_0000004c + 8) = in_stack_0000004c;
    *(char **)(in_stack_0000004c + 4) = unaff_EBX;
    *(int *)(in_stack_0000004c + 0xc) = in_stack_0000004c;
  }
  uStack000000f4 = 0xb;
  FUN_00402e90(in_stack_0000004c,0x20);
  pcVar5 = (char *)(param_5 - (int)param_3);
  uStack000000f4 = 10;
  if ((param_3 != unaff_EBX) && (pcVar5 != unaff_EBX)) {
    if (pcVar5 < (char *)0x81) {
      FUN_00402330();
      *(undefined4 *)param_3 = *(undefined4 *)(&DAT_005d59a4 + ((uint)(pcVar5 + 7) >> 3) * 4);
      *(char **)(&DAT_005d59a4 + ((uint)(pcVar5 + 7) >> 3) * 4) = param_3;
      FUN_00443330();
    }
    else {
      FUN_005089fd(param_3);
    }
  }
  _uStack000000f4 = CONCAT31(uStack000000f5,9);
  if ((unaff_EBP != unaff_EBX) && ((char *)(param_2 - (int)unaff_EBP) != unaff_EBX)) {
    FUN_00402e90(unaff_EBP,(char *)(param_2 - (int)unaff_EBP));
  }
  pcVar5 = puStack_4 + -(int)pcVar7;
  _uStack000000f4 = 0xffffffff;
  if ((pcVar7 != unaff_EBX) && (pcVar5 != unaff_EBX)) {
    if (pcVar5 < (char *)0x81) {
      FUN_00402330();
      *(undefined4 *)pcVar7 = *(undefined4 *)(&DAT_005d59a4 + ((uint)(pcVar5 + 7) >> 3) * 4);
      *(char **)(&DAT_005d59a4 + ((uint)(pcVar5 + 7) >> 3) * 4) = pcVar7;
      FUN_00443330();
    }
    else {
      FUN_005089fd(pcVar7);
    }
  }
  ExceptionList = in_stack_000000ec;
  return 1;
}

