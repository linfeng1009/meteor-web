/* Original Meteor.exe static export @ 004f5fa0; original sample not executed. */
/* XREF 005ab714 DATA */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004f5fa0(int *param_1)

{
  uint uVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float fStack_248;
  float fStack_244;
  float fStack_240;
  float fStack_23c;
  float fStack_238;
  float fStack_234;
  float fStack_230;
  float fStack_22c;
  float fStack_228;
  float fStack_224;
  float fStack_220;
  float fStack_21c;
  float fStack_218;
  float fStack_214;
  float fStack_210;
  float fStack_20c;
  float fStack_208;
  float fStack_204;
  float fStack_200;
  float fStack_1fc;
  float fStack_1f8;
  float fStack_1f4;
  float fStack_1f0;
  float fStack_1ec;
  float fStack_1e8;
  float fStack_1e4;
  float fStack_1e0;
  float fStack_1dc;
  float fStack_1d8;
  float fStack_1d4;
  float fStack_1d0;
  float fStack_1cc;
  undefined4 local_1c8;
  undefined4 uStack_1c4;
  float afStack_1bc [2];
  float fStack_1b4;
  float fStack_1b0;
  float fStack_1ac;
  float fStack_1a8;
  float afStack_1a4 [3];
  undefined1 auStack_198 [8];
  float fStack_190;
  undefined1 auStack_18c [12];
  undefined1 auStack_180 [12];
  undefined1 auStack_174 [12];
  undefined1 auStack_168 [36];
  undefined1 auStack_144 [12];
  undefined1 auStack_138 [48];
  CHAR local_108 [260];
  
  local_1c8 = 0;
  uStack_1c4 = 0;
  FUN_005499a0(&local_1c8);
  if ((double)CONCAT44(uStack_1c4,local_1c8) < _DAT_005a84b8) {
    FUN_00508ae6(local_108,s_performance_counter_Error__005c9f9c);
    OutputDebugStringA(local_108);
  }
  (**(code **)(*param_1 + 100))();
  if ((DAT_006667f0 & 1) == 0) {
    DAT_006667f0 = DAT_006667f0 | 1;
    FUN_005089bc(&DAT_004f6c60);
  }
  if ((DAT_006667f0 & 2) == 0) {
    DAT_006667f0 = DAT_006667f0 | 2;
    FUN_005498c0();
    FUN_005089bc(&DAT_004f6c50);
  }
  if (param_1[0x20] == 0) {
    return;
  }
  uVar3 = FUN_00410ce0();
  FUN_0040b100(uVar3,param_1[0x1c]);
  FUN_00407c10(param_1[0x20],&fStack_21c,&fStack_1b0,afStack_1a4);
  FUN_00407c10(param_1[0x1e],&fStack_210,auStack_180,auStack_18c);
  thunk_FUN_0040c6f0(param_1[0x1c],auStack_138,1);
  FUN_00407c10(param_1[0x1c],auStack_174,0,0);
  fStack_1e8 = fStack_20c;
  fStack_1ec = fStack_210;
  fStack_1e4 = fStack_214;
  switch(param_1[0x27]) {
  case 0:
  case 1:
    fStack_214 = fStack_214 + (float)param_1[0x24];
    fStack_20c = fStack_218;
    fStack_210 = fStack_21c;
    if ((double)CONCAT44(uStack_1c4,local_1c8) <= _DAT_005a8c90) {
      fVar5 = (float10)(double)CONCAT44(uStack_1c4,local_1c8) * (float10)_DAT_005a9508;
    }
    else {
      fVar5 = (float10)_DAT_005a8468;
    }
    fStack_230 = (float)(((float10)fStack_214 - (float10)fStack_208) * fVar5);
    fVar2 = _DAT_005a9518;
    if ((float10)_DAT_005a83f4 < (float10)fStack_214 - (float10)fStack_208) {
      fVar2 = _DAT_005a83e8;
    }
    fStack_208 = fStack_230 * fVar2 + fStack_208;
    thunk_FUN_00407260(param_1[0x1e],&fStack_210,&fStack_1b0,afStack_1a4);
    FUN_00407c10(param_1[0x23],&fStack_1f8,&fStack_1b0,afStack_1a4);
    fStack_1b4 = fStack_1f0;
    fStack_1d0 = fStack_20c;
    fStack_1d4 = fStack_210;
    fStack_1cc = fStack_208 - fStack_230 * _DAT_005a9518;
    fStack_248 = fStack_210 - fStack_1f8;
    fStack_244 = fStack_20c - fStack_1f4;
    fStack_240 = fStack_1cc - fStack_1f0;
    fStack_1e0 = fStack_248;
    fStack_1dc = fStack_244;
    fStack_1d8 = fStack_240;
    FUN_0047ec40();
    fStack_1b0 = fStack_248;
    fStack_1ac = fStack_244;
    fStack_1a8 = fStack_240;
    thunk_FUN_00407260(param_1[0x1c],&fStack_1f8,&fStack_1b0,afStack_1a4);
    fStack_1ec = fStack_1d4;
    fStack_1e8 = fStack_1d0;
    fStack_1e4 = fStack_1cc;
    break;
  case 2:
    if (param_1[0x21] == 0) {
      param_1[0x27] = 0;
      return;
    }
    fStack_220 = 4.0;
    if (param_1[0x28] == 1) {
      fStack_220 = 2.0;
    }
    FUN_00407c10(param_1[0x21],&fStack_210,0,0);
    fVar2 = _DAT_005a83f4 / fStack_220;
    fStack_204 = (fStack_210 - fStack_21c) * fVar2 + fStack_21c;
    fStack_200 = (fStack_20c - fStack_218) * fVar2 + fStack_218;
    fStack_1fc = (fStack_208 - fStack_214) * fVar2 + fStack_214 + _DAT_005ab600;
    if ((double)CONCAT44(uStack_1c4,local_1c8) <= _DAT_005a8f90) {
      fVar5 = (float10)(double)CONCAT44(uStack_1c4,local_1c8) * (float10)_DAT_005a94f0;
    }
    else {
      fVar5 = (float10)_DAT_005a8468;
    }
    fStack_1f8 = (fStack_204 - fStack_1ec) * _DAT_005a83e8;
    fStack_1f0 = (fStack_1fc - fStack_1e4) * _DAT_005a83e8;
    fStack_248 = (float)((float10)fStack_1f8 * fVar5);
    fStack_244 = (float)(((float10)fStack_200 - (float10)fStack_1e8) * (float10)_DAT_005a83e8 *
                        fVar5);
    fStack_1ec = fStack_248 + fStack_1ec;
    fStack_1e8 = fStack_244 + fStack_1e8;
    fStack_1e4 = (float)(fVar5 * (float10)fStack_1f0 + (float10)fStack_1e4);
    fStack_1b4 = fStack_1e4;
    thunk_FUN_00407260(param_1[0x1e],&fStack_1ec,auStack_180,auStack_18c);
    FUN_00407c10(param_1[0x1c],&fStack_1e0,0,0);
    fStack_1d4 = fStack_204 - fStack_1e0;
    fStack_1cc = 0.0;
    fStack_224 = 0.0;
    fStack_1d0 = fStack_200 - fStack_1dc;
    fStack_23c = fStack_21c - fStack_210;
    fStack_238 = fStack_218 - fStack_20c;
    fStack_234 = fStack_214 - fStack_208;
    fStack_22c = -fStack_238;
    fStack_228 = fStack_23c;
    FUN_0047ec40();
    FUN_00529c40(&fStack_1d4,&fStack_23c,auStack_198);
    fVar5 = (float10)FUN_0047ecf0();
    fStack_230 = (float)fVar5;
    fStack_248 = _DAT_005a9ec8;
    if ((float10)_DAT_005a83f4 <= fVar5) {
      fStack_248 = _DAT_005a9ec8 / fStack_230;
    }
    fStack_240 = fStack_224 * fStack_248;
    fStack_244 = fStack_228 * fStack_248;
    fStack_248 = fStack_22c * fStack_248;
    fStack_22c = fStack_248;
    fStack_228 = fStack_244;
    fStack_224 = fStack_240;
    if (fStack_190 <= _DAT_005a83e4) {
      if (DAT_00666850 < 0) {
        DAT_00666850 = 0;
      }
      else if (DAT_00666850 != 0) {
        fStack_22c = fStack_248 * _DAT_005a8430;
        fStack_228 = fStack_244 * _DAT_005a8430;
        fStack_224 = fStack_240 * _DAT_005a8430;
      }
LAB_004f65e7:
      fStack_22c = fStack_22c * _DAT_005a8430;
      fStack_228 = fStack_228 * _DAT_005a8430;
      fStack_224 = fStack_224 * _DAT_005a8430;
    }
    else if (DAT_00666850 < 1) {
      if (DAT_00666850 != 0) goto LAB_004f65e7;
    }
    else {
      DAT_00666850 = 0;
    }
    fStack_248 = fStack_22c;
    fStack_244 = fStack_228;
    fStack_240 = fStack_224;
    if ((param_1[0x28] == 1) &&
       (_DAT_005a83e4 < fStack_1d4 * fStack_23c + fStack_1d0 * fStack_238 + fStack_1cc * fStack_234)
       ) {
      fStack_248 = fStack_23c * _DAT_005a8430;
      fStack_244 = fStack_238 * _DAT_005a8430;
      fStack_240 = fStack_234 * _DAT_005a8430;
      fStack_23c = fStack_248;
      fStack_238 = fStack_244;
      fStack_234 = fStack_240;
    }
    FUN_0047ec40();
    fStack_248 = fStack_22c + fStack_23c;
    fStack_244 = fStack_228 + fStack_238;
    fStack_240 = fStack_224 + fStack_234;
    fStack_23c = fStack_248;
    fStack_238 = fStack_244;
    fStack_234 = fStack_240;
    FUN_0047ec40();
    if (param_1[0x28] == 1) {
      fVar2 = fStack_230 * _DAT_005ab79c + _DAT_005aa938;
      fStack_1f4 = fVar2 * fStack_238;
      fStack_1f0 = fVar2 * fStack_234;
      fVar6 = (float10)1.4426950408889634 * (float10)fStack_230 * (float10)_DAT_005ab798;
      fVar5 = ROUND(fVar6);
      fVar6 = (float10)f2xm1(fVar6 - fVar5);
      fVar5 = (float10)fscale((float10)1 + fVar6,fVar5);
      fStack_220 = (float)(fVar5 + (float10)_DAT_005a8418);
      fStack_248 = fStack_23c * fVar2 * fStack_220;
      fStack_244 = fStack_1f4 * fStack_220;
      fStack_240 = fStack_1f0 * fStack_220;
    }
    else {
      fStack_248 = fStack_23c * _DAT_005aa638;
      fStack_244 = fStack_238 * _DAT_005aa638;
      fStack_240 = fStack_234 * _DAT_005aa638;
    }
    fStack_248 = fStack_248 + fStack_204;
    fStack_244 = fStack_244 + fStack_200;
    fStack_240 = fStack_1fc + fStack_240;
    fStack_234 = fStack_240 + _DAT_005a84ac;
    if (fStack_234 < fStack_1fc) {
      fStack_234 = (fStack_1fc + fStack_234) * _DAT_005a83e8;
    }
    fStack_23c = fStack_248;
    fStack_238 = fStack_244;
    if (param_1[0x29] != 0) {
      iVar4 = FUN_005644f0(&fStack_204,&fStack_23c,afStack_1bc,0);
      if (iVar4 == 0) {
        param_1[0x29] = 0;
      }
      if (param_1[0x29] != 0) break;
    }
    fStack_1d4 = fStack_1e0;
    fStack_1d0 = fStack_1dc;
    fStack_1cc = fStack_1d8;
    if ((double)CONCAT44(uStack_1c4,local_1c8) <= _DAT_005aa8b8) {
      fVar5 = (float10)(double)CONCAT44(uStack_1c4,local_1c8) * (float10)_DAT_005ab790;
    }
    else {
      fVar5 = (float10)_DAT_005a8468;
    }
    afStack_1bc[0] = (float)((float10)((fStack_23c - fStack_1e0) * _DAT_005ab79c) * fVar5);
    fStack_1b4 = (float)((float10)((fStack_234 - fStack_1d8) * _DAT_005ab79c) * fVar5);
    fStack_248 = afStack_1bc[0] + fStack_1e0;
    fStack_244 = (float)(((float10)fStack_238 - (float10)fStack_1dc) * (float10)_DAT_005ab79c *
                         fVar5 + (float10)fStack_1dc);
    fStack_240 = fStack_1d8 + fStack_1b4;
    fStack_204 = fStack_204 - fStack_248;
    fStack_200 = fStack_200 - fStack_244;
    fStack_1fc = fStack_1fc - fStack_240;
    fStack_23c = fStack_248;
    fStack_238 = fStack_244;
    fStack_234 = fStack_240;
    fStack_1f8 = fStack_204;
    fStack_1f4 = fStack_200;
    fStack_1f0 = fStack_1fc;
    FUN_0047ec40();
    fStack_1b0 = fStack_204;
    fStack_1ac = fStack_200;
    fStack_1a8 = fStack_1fc;
    fStack_210 = fStack_23c;
    fStack_20c = fStack_238;
    fStack_208 = fStack_234;
    thunk_FUN_00407260(param_1[0x1c],&fStack_210,&fStack_1b0,0);
    break;
  case 3:
    fStack_214 = fStack_214 + (float)param_1[0x24];
    thunk_FUN_00407260(param_1[0x1e],&fStack_21c,&fStack_1b0,afStack_1a4);
    FUN_00407c10(param_1[0x23],&fStack_21c,&fStack_1b0,afStack_1a4);
    FUN_00407c10(param_1[0x1c],&fStack_248,0,0);
    fVar5 = (float10)(double)CONCAT44(uStack_1c4,local_1c8) * (float10)_DAT_005a94f0;
    fStack_214 = (float)(((float10)fStack_214 - (float10)fStack_240) * (float10)_DAT_005a83e8 *
                         fVar5 + (float10)fStack_240);
    fStack_218 = (float)(((float10)fStack_218 - (float10)fStack_244) * (float10)_DAT_005a83e8 *
                         fVar5 + (float10)fStack_244);
    fStack_21c = (float)(((float10)fStack_21c - (float10)fStack_248) * (float10)_DAT_005a83e8 *
                         fVar5 + (float10)fStack_248);
    thunk_FUN_00407260(param_1[0x1c],&fStack_21c,&fStack_1b0,afStack_1a4);
  }
  if ((param_1[0x22] != 0) && (param_1[0x26] != 0)) {
    thunk_FUN_0040c6f0(param_1[0x1c],auStack_168,2);
    uVar1 = param_1[0x27];
    fStack_230 = 2.0;
    if (uVar1 != 2) {
      fStack_230 = 1.0;
    }
    fStack_220 = 0.0;
    if (uVar1 < 2) {
      _DAT_0066684c =
           (**(code **)(*param_1 + 0x50))
                     (&fStack_1ec,auStack_144,afStack_1bc,&fStack_220,fStack_230);
    }
    else if (uVar1 == 2) {
      if (param_1[0x29] != 0) {
        (**(code **)(*param_1 + 0x54))(&fStack_1ec,0x42c80000);
        return;
      }
      _DAT_0066684c =
           (**(code **)(*param_1 + 0x50))
                     (&fStack_1ec,auStack_144,afStack_1bc,&fStack_220,fStack_230);
      if ((_DAT_0066684c != 0) && (fStack_234 < _DAT_005a8e78 != (fStack_234 == _DAT_005a8e78))) {
        fVar5 = (float10)FUN_00549b00();
        if ((float10)_DAT_005ab788 < fVar5) {
          FUN_00549a90(0,0);
          DAT_00666850 = -1;
          if (afStack_1a4[0] <= _DAT_005a83e4) {
            DAT_00666850 = 1;
          }
        }
        if (fStack_234 < _DAT_005a8e7c != (fStack_234 == _DAT_005a8e7c)) {
          param_1[0x29] = 1;
          return;
        }
      }
    }
  }
  return;
}

