/* Original Meteor.exe static export @ 004cdef0; original sample not executed. */
/* XREF 005aa780 DATA */

undefined4 __thiscall FUN_004cdef0(int *param_1,double param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = FUN_0055c300();
  if (iVar2 != 4) {
    cVar1 = FUN_0055de50();
    if (cVar1 != '\0') {
      FUN_0055de20();
      (**(code **)(*param_1 + 0xc))(0x13,0,0);
    }
    (**(code **)(*param_1 + 200))((float)param_2,param_1 + 0x34,0x3f800000);
    return 1;
  }
  if (param_1[0xd8] != 0) {
    (**(code **)(*param_1 + 300))(1);
    return 0;
  }
  (**(code **)(*param_1 + 300))(0);
  return 0;
}

