/* Original Meteor.exe static export @ 004cb150; original sample not executed. */
/* XREF 005aa6cc DATA */

void __thiscall FUN_004cb150(int *param_1,undefined4 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uStack_4;
  
  if ((param_1[0xf1] == 0) && (param_1[4] != 0)) {
    uStack_4 = 0;
    switch(param_2) {
    case 0x10:
      param_1[0x1e] = 1;
      piVar1 = (int *)FUN_00487830();
      uVar2 = 0x1000;
      break;
    case 0x11:
      param_1[0x1e] = 0;
      piVar1 = (int *)FUN_00487830();
      puVar3 = &uStack_4;
      (**(code **)(*piVar1 + 0x2e8))(0x1000,puVar3);
      (**(code **)(*param_1 + 0x1a4))(puVar3,0);
      return;
    case 0x12:
      param_1[0x1f] = 1;
      piVar1 = (int *)FUN_00487830();
      uVar2 = 0x1200;
      break;
    case 0x13:
      param_1[0x1f] = 0;
      piVar1 = (int *)FUN_00487830();
      puVar3 = &uStack_4;
      (**(code **)(*piVar1 + 0x2e8))(0x1200,puVar3);
      (**(code **)(*param_1 + 0x1a4))(puVar3,0);
      return;
    default:
      goto switchD_004cb185_default;
    }
    puVar3 = &uStack_4;
    (**(code **)(*piVar1 + 0x2e8))(uVar2,puVar3);
    (**(code **)(*param_1 + 0x1a4))(puVar3,1);
  }
switchD_004cb185_default:
  return;
}

