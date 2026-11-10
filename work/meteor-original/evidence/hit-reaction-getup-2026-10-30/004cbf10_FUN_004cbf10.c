/* Original Meteor.exe static export @ 004cbf10; original sample not executed. */
/* XREF 005aa7bc DATA */

void __thiscall FUN_004cbf10(int *param_1,undefined1 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = (**(code **)(*param_1 + 0x130))();
  if (((param_3 == 0) && (iVar1 != 1)) && (iVar1 != 0xb)) {
    return;
  }
  iVar1 = (**(code **)(*param_1 + 0x180))();
  if (iVar1 != 0) {
    return;
  }
  switch(param_2) {
  case 0x62:
    iVar1 = (**(code **)(*param_1 + 0x110))();
    if (iVar1 != 0) {
      (**(code **)(*param_1 + 0x74))(0xb3);
      goto switchD_004cbf5d_caseD_63;
    }
    uVar2 = 0xad;
    goto LAB_004cc034;
  default:
    goto switchD_004cbf5d_caseD_63;
  case 0x66:
    iVar1 = (**(code **)(*param_1 + 0x110))();
    if (iVar1 != 0) {
      (**(code **)(*param_1 + 0x74))(0xb0);
      goto switchD_004cbf5d_caseD_63;
    }
    iVar1 = *param_1;
    uVar2 = (**(code **)(*(int *)param_1[0xd2] + 0x28))(param_1,0xa4,0,1,0xbf800000);
    break;
  case 0x6c:
    iVar1 = (**(code **)(*param_1 + 0x110))();
    if (iVar1 != 0) {
      (**(code **)(*param_1 + 0x74))(0xb2);
      goto switchD_004cbf5d_caseD_63;
    }
    iVar1 = *param_1;
    uVar2 = (**(code **)(*(int *)param_1[0xd2] + 0x28))(param_1,0xaa,0,1,0xbf800000);
    break;
  case 0x72:
    iVar1 = (**(code **)(*param_1 + 0x110))();
    if (iVar1 != 0) {
      (**(code **)(*param_1 + 0x74))(0xb1,0,1,0xbf800000);
      goto switchD_004cbf5d_caseD_63;
    }
    uVar2 = 0xa7;
LAB_004cc034:
    iVar1 = *param_1;
    uVar2 = (**(code **)(*(int *)param_1[0xd2] + 0x28))(param_1,uVar2,0,1,0xbf800000);
  }
  (**(code **)(iVar1 + 0x74))(uVar2);
switchD_004cbf5d_caseD_63:
  (**(code **)(*param_1 + 300))(6);
  param_1[0xee] = param_1[0xe4];
  param_1[0xef] = param_1[0xe5];
  param_1[0xf0] = param_1[0xe6];
  return;
}

