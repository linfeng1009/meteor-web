/* Original Meteor.exe read-only export. Sample not executed. */

undefined4 FUN_004a81c0(int param_1,int param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  char local_100 [256];
  
  if (param_1 == 0) {
    uVar2 = 0;
    pcVar1 = s_shadow1_005c96d4;
  }
  else if (param_2 == 0) {
    FUN_00508ae6(local_100,&DAT_005c67ac,s_shadow2_005c96dc);
    pcVar1 = local_100;
    uVar2 = 1;
  }
  else {
    FUN_00508ae6(local_100,&DAT_005c4538,&DAT_005c96ec,param_2 + 0x1f8);
    FUN_004a8160(local_100,local_100,0);
    FUN_00508ae6(local_100,&DAT_005c96e4,local_100,*(undefined4 *)(param_2 + 0x430));
    pcVar1 = local_100;
    uVar2 = 1;
  }
  uVar2 = FUN_00547b10(5,5,0x41a00000,0x41a00000,pcVar1,uVar2);
  FUN_00405720(uVar2,0);
  FUN_00405660(uVar2,0x3f7d70a4);
  FUN_004054e0(uVar2,0x17,4);
  FUN_004054e0(uVar2,0x16,1);
  FUN_004054e0(uVar2,10,2);
  return uVar2;
}

