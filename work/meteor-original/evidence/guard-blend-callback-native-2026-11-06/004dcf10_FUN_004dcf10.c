/* Original Meteor.exe static export @ 004dcf10; original sample not executed. */
/* XREF 005aaa94 DATA */
/* XREF 005aab1c DATA */
/* XREF 005aab8c DATA */
/* XREF 005aabfc DATA */
/* XREF 005aac6c DATA */
/* XREF 005aacdc DATA */
/* XREF 005aad4c DATA */
/* XREF 005aadbc DATA */
/* XREF 005aae2c DATA */
/* XREF 005aae9c DATA */
/* XREF 005aaf0c DATA */
/* XREF 005aaf8c DATA */
/* XREF 005ab004 DATA */

undefined4 __thiscall FUN_004dcf10(int *param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 unaff_ESI;
  undefined4 unaff_retaddr;
  
  iVar1 = (**(code **)(*param_1 + 0x68))(param_2,param_3,&param_3);
  if (iVar1 != 0) {
    uVar2 = (**(code **)(*param_2 + 0x48))(unaff_ESI,unaff_retaddr,3,param_2);
    return uVar2;
  }
  return 0;
}

