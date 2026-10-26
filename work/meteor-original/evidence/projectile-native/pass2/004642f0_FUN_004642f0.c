/* Original Meteor.exe static export @ 004642f0; original sample not executed. */
/* XREF 00438f18 UNCONDITIONAL_CALL */
/* XREF 0043901a UNCONDITIONAL_CALL */
/* XREF 0043cca8 UNCONDITIONAL_CALL */
/* XREF 004486a4 UNCONDITIONAL_CALL */
/* XREF 004487a7 UNCONDITIONAL_CALL */
/* XREF 0046c374 UNCONDITIONAL_CALL */
/* XREF 0046cd4c UNCONDITIONAL_CALL */
/* XREF 0046ce20 UNCONDITIONAL_CALL */
/* XREF 0046e653 UNCONDITIONAL_CALL */
/* XREF 0046e84c UNCONDITIONAL_CALL */

undefined4 __thiscall FUN_004642f0(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 in_stack_00000018;
  int in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined4 in_stack_00000024;
  
  puVar6 = (undefined4 *)(param_1 + 0x24);
  puVar5 = (undefined4 *)register0x00000010;
  for (iVar4 = 5; puVar5 = puVar5 + 1, iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = *puVar5;
    puVar6 = puVar6 + 1;
  }
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined2 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x3c) = in_stack_00000018;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(int *)(param_1 + 0x40) = in_stack_0000001c;
  *(undefined4 *)(param_1 + 0x44) = in_stack_00000020;
  *(undefined4 *)(param_1 + 0x48) = in_stack_00000024;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined1 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x58) = 1;
  FUN_00429990(0);
  uVar1 = __ftol();
  uVar2 = __ftol();
  FUN_00429b80(1,1,1,uVar2,uVar1);
  uVar3 = FUN_00429c30(0);
  *(undefined4 *)(param_1 + 0x38) = uVar3;
  FUN_00435120(uVar3,uVar2,uVar1,0xff,0xff,0xff);
  FUN_00429990(0);
  FUN_00429b80(1,1,1,7,1);
  uVar1 = FUN_00429c30(0);
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  FUN_00429e90(uVar1,0,200,200,10);
  FUN_00429de0(*(undefined4 *)(param_1 + 0x5c),0);
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  FUN_00429990(0);
  uVar1 = __ftol();
  uVar1 = __ftol(uVar1);
  FUN_00429b80(1,1,1,uVar1);
  uVar1 = FUN_00429c30(0);
  *(undefined4 *)(param_1 + 0x78) = uVar1;
  FUN_00429e90(uVar1,0,10,10,10);
  uVar1 = __ftol();
  uVar1 = __ftol(uVar1);
  FUN_00429d00(*(undefined4 *)(param_1 + 0x78),uVar1);
  FUN_00429de0(*(undefined4 *)(param_1 + 0x78),0);
  FUN_00429e60(*(undefined4 *)(param_1 + 0x78),&stack0x00000020,&stack0x0000001c,&stack0x00000018);
  FUN_00429d40(*(undefined4 *)(param_1 + 0x78),in_stack_00000020,in_stack_0000001c + -1,
               in_stack_00000018);
  FUN_00429de0(*(undefined4 *)(param_1 + 0x78),0);
  return 1;
}

