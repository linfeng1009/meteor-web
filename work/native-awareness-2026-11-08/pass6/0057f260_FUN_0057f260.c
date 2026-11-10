/* Original Meteor.exe static export @ 0057f260; original sample not executed. */
/* XREF 00569fbf UNCONDITIONAL_CALL */

/* WARNING: Removing unreachable block (ram,0x0057f85d) */
/* WARNING: Removing unreachable block (ram,0x0057f85f) */
/* WARNING: Removing unreachable block (ram,0x0057f86a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0057f260(void)

{
  float fVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  float *pfVar10;
  int iVar11;
  undefined *puVar12;
  short *psVar13;
  short *psVar14;
  int iVar15;
  float local_4e0 [199];
  short sStack_1c2;
  short local_1c0 [200];
  int local_30;
  undefined4 local_2c;
  float local_28;
  int local_24;
  float *local_20;
  int local_1c;
  int local_18;
  short *local_14;
  short *local_10;
  int local_c;
  float *local_8;
  
  local_14 = local_1c0;
  local_20 = local_4e0;
  local_24 = 0;
  local_18 = 200;
  if (DAT_0072ba0c != 0) {
    FUN_00509f22(&DAT_005ca980,s_Starting_parse_005d2674);
  }
  local_8 = local_4e0;
  local_1c = 0;
  DAT_0072b9fc = 0;
  DAT_0072b9f4 = 0xfffffffe;
  local_10 = &sStack_1c2;
  local_c = 0;
LAB_0057f2cd:
  do {
    while( true ) {
      psVar13 = local_14;
      iVar4 = local_18;
      psVar14 = local_10 + 1;
      local_10 = psVar14;
      *psVar14 = (short)local_c;
      pfVar10 = local_20;
      if (psVar13 + iVar4 + -1 <= psVar14) {
        local_20 = (float *)psVar13;
        iVar15 = (int)psVar14 - (int)psVar13 >> 1;
        if (9999 < iVar4) {
          thunk_FUN_005808a0(s_parser_stack_overflow_005d23f8);
          return 2;
        }
        local_18 = iVar4 * 2;
        if (10000 < local_18) {
          local_18 = 10000;
        }
        FUN_00509ce0();
        local_14 = (short *)&stack0xfffffb14;
        FUN_0057bec0(local_20,&stack0xfffffb14,(iVar15 + 1) * 2);
        FUN_00509ce0();
        local_20 = (float *)&stack0xfffffb14;
        FUN_0057bec0(pfVar10,&stack0xfffffb14,(iVar15 + 1) * 4);
        local_10 = local_14 + iVar15;
        local_8 = local_20 + iVar15;
        if (DAT_0072ba0c != 0) {
          FUN_00509f22(&DAT_005ca980,s_Stack_size_increased_to__d_005d2658,local_18);
        }
        if (local_14 + local_18 + -1 <= local_10) {
          return 1;
        }
      }
      iVar4 = local_c;
      if (DAT_0072ba0c != 0) {
        FUN_00509f22(&DAT_005ca980,s_Entering_state__d_005d2644,local_c);
      }
      sVar3 = *(short *)(&DAT_005b04d8 + iVar4 * 2);
      iVar15 = local_24;
      if (sVar3 == -0x8000) break;
      if (DAT_0072b9f4 == 0xfffffffe) {
        if (DAT_0072ba0c != 0) {
          FUN_00509f22(&DAT_005ca980,s_Reading_a_token__005d2630);
        }
        DAT_0072b9f4 = FUN_0057ff40();
      }
      if ((int)DAT_0072b9f4 < 1) {
        iVar15 = 0;
        local_24 = 0;
        DAT_0072b9f4 = 0;
        if (DAT_0072ba0c != 0) {
          FUN_00509f22(&DAT_005ca980,s_Now_at_end_of_input__005d2618);
        }
      }
      else {
        if (DAT_0072b9f4 < 0x126) {
          iVar15 = (int)(char)(&DAT_005afd20)[DAT_0072b9f4];
        }
        else {
          iVar15 = 0x4d;
        }
        local_24 = iVar15;
        if (DAT_0072ba0c != 0) {
          FUN_00509f22(&DAT_005ca980,s_Next_token_is__d___s_005d2600,DAT_0072b9f4,
                       (&PTR_DAT_005b0128)[iVar15]);
          FUN_00509f22(&DAT_005ca980,&DAT_005d25fc);
        }
      }
      iVar11 = sVar3 + iVar15;
      if (((iVar11 < 0) || (0x80 < iVar11)) || (*(short *)(&DAT_005b0738 + iVar11 * 2) != iVar15))
      break;
      iVar11 = (int)*(short *)((int)&PTR_DAT_005b0630 + iVar11 * 2);
      if (iVar11 < 0) {
        if (iVar11 == -0x8000) goto LAB_0057f622;
LAB_0057f4cb:
        iVar11 = -iVar11;
        goto LAB_0057f4d0;
      }
      if (iVar11 == 0) goto LAB_0057f622;
      if (iVar11 == 0x86) {
        return 0;
      }
      if (DAT_0072ba0c != 0) {
        FUN_00509f22(&DAT_005ca980,s_Shifting_token__d___s___005d25b4,DAT_0072b9f4,
                     (&PTR_DAT_005b0128)[iVar15]);
      }
      if (DAT_0072b9f4 != 0) {
        DAT_0072b9f4 = 0xfffffffe;
      }
      local_8 = local_8 + 1;
      *local_8 = DAT_0072b9f8;
      local_c = iVar11;
      if (local_1c != 0) {
        local_1c = local_1c + -1;
      }
    }
    iVar11 = (int)*(short *)(&DAT_005b0380 + iVar4 * 2);
    local_c = iVar11;
    if (iVar11 == 0) {
LAB_0057f622:
      if (local_1c == 0) {
        DAT_0072b9fc = DAT_0072b9fc + 1;
        thunk_FUN_005808a0(s_parse_error_005d25a8);
      }
      else if (local_1c == 3) {
        if (DAT_0072b9f4 == 0) {
          return 1;
        }
        if (DAT_0072ba0c != 0) {
          FUN_00509f22(&DAT_005ca980,s_Discarding_token__d___s___005d258c,DAT_0072b9f4,
                       (&PTR_DAT_005b0128)[iVar15]);
        }
        DAT_0072b9f4 = 0xfffffffe;
      }
      local_1c = 3;
LAB_0057f68b:
      if (((*(short *)(&DAT_005b04d8 + iVar4 * 2) != -0x8000) &&
          (iVar4 = *(short *)(&DAT_005b04d8 + iVar4 * 2) + 1, -1 < iVar4)) &&
         ((iVar4 < 0x81 && (*(short *)(&DAT_005b0738 + iVar4 * 2) == 1)))) {
        iVar11 = (int)*(short *)((int)&PTR_DAT_005b0630 + iVar4 * 2);
        if (iVar11 < 0) {
          if (iVar11 != -0x8000) goto LAB_0057f4cb;
        }
        else if (iVar11 != 0) break;
      }
      if (local_10 == local_14) {
        return 1;
      }
      iVar4 = (int)local_10[-1];
      local_10 = local_10 + -1;
      local_8 = local_8 + -1;
      if (DAT_0072ba0c != 0) {
        psVar13 = local_14 + -1;
        FUN_00509f22(&DAT_005ca980,s_Error__state_stack_now_005d2574);
        psVar14 = local_10;
        for (; psVar13 != psVar14; psVar13 = psVar13 + 1) {
          FUN_00509f22(&DAT_005ca980,&PTR_DAT_005d2570,(int)psVar13[1]);
        }
        FUN_00509f22(&DAT_005ca980,&DAT_005c4540);
      }
      goto LAB_0057f68b;
    }
LAB_0057f4d0:
    local_30 = (int)*(short *)(&DAT_005b02f0 + iVar11 * 2);
    if (0 < local_30) {
      local_28 = local_8[1 - local_30];
    }
    local_c = iVar11;
    if (DAT_0072ba0c != 0) {
      FUN_00509f22(&DAT_005ca980,s_Reducing_via_rule__d__line__d___005d25d8,iVar11,
                   (int)*(short *)(&DAT_005b0098 + iVar11 * 2));
      puVar12 = &DAT_005afed8 + *(short *)(&DAT_005afe48 + iVar11 * 2) * 2;
      sVar3 = *(short *)(&DAT_005afed8 + *(short *)(&DAT_005afe48 + iVar11 * 2) * 2);
      while (0 < sVar3) {
        FUN_00509f22(&DAT_005ca980,&DAT_005d18bc,(&PTR_DAT_005b0128)[sVar3]);
        psVar13 = (short *)(puVar12 + 2);
        puVar12 = puVar12 + 2;
        sVar3 = *psVar13;
      }
      FUN_00509f22(&DAT_005ca980,s__>__s_005d25d0,
                   (&PTR_DAT_005b0128)[*(short *)(&DAT_005b0260 + iVar11 * 2)]);
    }
    pfVar10 = local_8;
    switch(local_c) {
    case 2:
      iVar4 = __ftol();
      if (iVar4 != *(int *)(*(int *)(DAT_0072ba10 + 0x120) + 0x40)) {
        *(int *)(*(int *)(DAT_0072ba10 + 0x120) + 0x40) = iVar4;
        FUN_00568780(1);
      }
      break;
    case 5:
      pcVar6 = (char *)(DAT_0072ba14 + 8);
      pcVar8 = (char *)*local_8;
      do {
        cVar2 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        *pcVar6 = cVar2;
        pcVar6 = pcVar6 + 1;
      } while (cVar2 != '\0');
      pcVar8 = (char *)*local_8;
      goto LAB_0057fcf8;
    case 6:
      if (((int)DAT_0072ba04 - DAT_0072ba00 & 0xfffffffcU) == 0) {
        *(undefined4 *)(DAT_0072ba14 + 0x218) = 0xffffffff;
      }
      else {
        uVar5 = 0;
        *(undefined4 *)(DAT_0072ba14 + 0x218) = 0;
        if ((int)DAT_0072ba04 - DAT_0072ba00 >> 2 != 0) {
          do {
            iVar4 = uVar5 * 4;
            uVar5 = uVar5 + 1;
            *(uint *)(DAT_0072ba14 + 0x218) =
                 *(uint *)(DAT_0072ba14 + 0x218) |
                 1 << ((byte)*(undefined4 *)(DAT_0072ba00 + iVar4) & 0x1f);
          } while (uVar5 < (uint)((int)DAT_0072ba04 - DAT_0072ba00 >> 2));
        }
        DAT_0072ba04 = DAT_0072ba04 + -((int)DAT_0072ba04 - DAT_0072ba00 >> 2);
      }
      DAT_0072ba18 = DAT_0072ba18 + 1;
      DAT_0072ba14 = FUN_0056ae80(DAT_0072ba18);
      break;
    case 0xe:
      *(float *)(DAT_0072ba14 + 0x1b8) = local_8[-2];
      *(float *)(DAT_0072ba14 + 0x1bc) = local_8[-1];
      *(float *)(DAT_0072ba14 + 0x1c0) = *local_8;
      break;
    case 0xf:
      *(float *)(DAT_0072ba14 + 0x1b4) = local_8[-3];
      *(float *)(DAT_0072ba14 + 0x1a8) = local_8[-2];
      *(float *)(DAT_0072ba14 + 0x1ac) = local_8[-1];
      *(float *)(DAT_0072ba14 + 0x1b0) = *local_8;
      FUN_0047ed40();
      break;
    case 0x10:
      iVar4 = __ftol();
      *(bool *)(DAT_0072ba14 + 0x1c4) = iVar4 != 0;
      iVar4 = DAT_0072ba14;
      fVar1 = *pfVar10;
      *(float *)(DAT_0072ba14 + 0x1c8) = pfVar10[-1];
      *(float *)(iVar4 + 0x1cc) = fVar1;
      break;
    case 0x29:
      *(undefined4 *)(DAT_0072ba14 + 0x1e4) = 1;
      break;
    case 0x2a:
      *(undefined4 *)(DAT_0072ba14 + 0x1e4) = 0;
      break;
    case 0x2b:
      iVar4 = __ftol();
      if (iVar4 == 0) {
        *(undefined4 *)(DAT_0072ba14 + 0x1d0) = 0;
      }
      else if (iVar4 == 1) {
        *(undefined4 *)(DAT_0072ba14 + 0x1d0) = 1;
      }
      else if (iVar4 == 2) {
        *(undefined4 *)(DAT_0072ba14 + 0x1d0) = 2;
      }
      break;
    case 0x2c:
      *(undefined1 *)(DAT_0072ba14 + 0x1d4) = 1;
      break;
    case 0x2d:
      *(undefined1 *)(DAT_0072ba14 + 0x1d4) = 0;
      break;
    case 0x2e:
      *(undefined1 *)(DAT_0072ba14 + 0x1d5) = 1;
      break;
    case 0x2f:
      *(undefined1 *)(DAT_0072ba14 + 0x1d5) = 0;
      break;
    case 0x30:
      iVar4 = __ftol();
      if (iVar4 == 1) {
        *(undefined4 *)(DAT_0072ba14 + 0x1d8) = 1;
      }
      else if (iVar4 == 2) {
        *(undefined4 *)(DAT_0072ba14 + 0x1d8) = 0;
      }
      break;
    case 0x31:
      *(float *)(DAT_0072ba14 + 0x1ec) = *local_8;
      break;
    case 0x32:
      *(float *)(DAT_0072ba14 + 0x1f0) = *local_8;
      break;
    case 0x33:
      *(float *)(DAT_0072ba14 + 500) = *local_8;
      break;
    case 0x34:
      *(undefined4 *)(DAT_0072ba14 + 0x1e8) = 0;
      pcVar8 = (char *)*local_8;
      FUN_00593634(pcVar8);
      uVar5 = 0xffffffff;
      pcVar6 = pcVar8;
      do {
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        cVar2 = *pcVar6;
        pcVar6 = pcVar6 + 1;
      } while (cVar2 != '\0');
      iVar4 = 0;
      if (0 < (int)(~uVar5 - 1)) {
        do {
          switch(pcVar8[iVar4]) {
          case 'c':
            uVar9 = *(uint *)(DAT_0072ba14 + 0x1e8) | 8;
            break;
          default:
            goto switchD_0057fb03_caseD_64;
          case 'p':
            uVar9 = *(uint *)(DAT_0072ba14 + 0x1e8) | 0x10;
            break;
          case 'x':
            uVar9 = *(uint *)(DAT_0072ba14 + 0x1e8) | 1;
            break;
          case 'y':
            uVar9 = *(uint *)(DAT_0072ba14 + 0x1e8) | 2;
            break;
          case 'z':
            uVar9 = *(uint *)(DAT_0072ba14 + 0x1e8) | 4;
          }
          *(uint *)(DAT_0072ba14 + 0x1e8) = uVar9;
switchD_0057fb03_caseD_64:
          iVar4 = iVar4 + 1;
        } while (iVar4 < (int)(~uVar5 - 1));
      }
      goto LAB_0057fcf8;
    case 0x35:
      pcVar7 = (char *)(DAT_0072ba14 + 0x68);
      pcVar8 = (char *)*local_8;
      pcVar6 = pcVar8;
      do {
        cVar2 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        *pcVar7 = cVar2;
        pcVar7 = pcVar7 + 1;
      } while (cVar2 != '\0');
      goto LAB_0057fcf8;
    case 0x36:
      *(undefined4 *)(DAT_0072ba14 + 0x1f8) = 1;
      *(undefined1 *)(DAT_0072ba14 + 0x1fc) = 0;
      *(undefined1 *)(DAT_0072ba14 + 0x1d5) = 0;
      *(undefined1 *)(DAT_0072ba14 + 0x1d4) = 0;
      break;
    case 0x37:
      *(undefined4 *)(DAT_0072ba14 + 0x1f8) = 0;
      break;
    case 0x38:
      *(undefined4 *)(DAT_0072ba14 + 0x1f8) = 2;
      break;
    case 0x39:
      if (*local_8 == _DAT_005a83e4) {
        *(undefined1 *)(DAT_0072ba14 + 0x1fc) = 0;
      }
      else {
        *(undefined1 *)(DAT_0072ba14 + 0x1fc) = 1;
      }
      break;
    case 0x3a:
      *(undefined1 *)(DAT_0072ba14 + 0x1fc) = 1;
      break;
    case 0x3b:
      *(undefined1 *)(DAT_0072ba14 + 0x1fc) = 0;
      break;
    case 0x3e:
      FUN_00593634(*local_8);
      pcVar8 = (char *)*pfVar10;
      pcVar6 = (char *)(DAT_0072ba14 + 0x28);
      do {
        cVar2 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        *pcVar6 = cVar2;
        pcVar6 = pcVar6 + 1;
      } while (cVar2 != '\0');
      pcVar8 = (char *)*pfVar10;
      goto LAB_0057fcf8;
    case 0x3f:
      pcVar6 = (char *)(DAT_0072ba14 + 0x48);
      pcVar8 = (char *)*local_8;
      do {
        cVar2 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        *pcVar6 = cVar2;
        pcVar6 = pcVar6 + 1;
      } while (cVar2 != '\0');
      pcVar8 = (char *)*local_8;
      goto LAB_0057fcf8;
    case 0x43:
      local_2c = __ftol();
      if (DAT_0072ba04 == DAT_0072ba08) {
        FUN_0046ecb0(DAT_0072ba04,&local_2c);
      }
      else {
        if (DAT_0072ba04 != (undefined4 *)0x0) {
          *DAT_0072ba04 = local_2c;
        }
        DAT_0072ba04 = DAT_0072ba04 + 1;
      }
      break;
    case 0x44:
      pcVar6 = (char *)*local_8;
      pcVar8 = (char *)(DAT_0072ba14 + 0x88);
      do {
        cVar2 = *pcVar6;
        pcVar6 = pcVar6 + 1;
        *pcVar8 = cVar2;
        pcVar8 = pcVar8 + 1;
      } while (cVar2 != '\0');
      pcVar8 = (char *)*local_8;
      goto LAB_0057fcf8;
    case 0x46:
      pcVar8 = (char *)local_8[-1];
LAB_0057fcf8:
      FUN_005089fd(pcVar8);
    }
    pfVar10 = local_8;
    iVar4 = local_30;
    psVar13 = local_10 + -local_30;
    local_10 = psVar13;
    if (DAT_0072ba0c != 0) {
      psVar14 = local_14 + -1;
      FUN_00509f22(&DAT_005ca980,s_state_stack_now_005d2410);
      for (; psVar14 != psVar13; psVar14 = psVar14 + 1) {
        FUN_00509f22(&DAT_005ca980,&PTR_DAT_005d2570,(int)psVar14[1]);
      }
      FUN_00509f22(&DAT_005ca980,&DAT_005c4540);
    }
    pfVar10 = pfVar10 + (1 - iVar4);
    *pfVar10 = local_28;
    iVar4 = (int)*(short *)(&DAT_005b0592 + *(short *)(&DAT_005b0260 + local_c * 2) * 2) +
            (int)*psVar13;
    local_8 = pfVar10;
    if (((iVar4 < 0) || (0x80 < iVar4)) || (*(short *)(&DAT_005b0738 + iVar4 * 2) != *psVar13)) {
      local_c = (int)*(short *)(&DAT_005b043a + *(short *)(&DAT_005b0260 + local_c * 2) * 2);
    }
    else {
      local_c = (int)*(short *)((int)&PTR_DAT_005b0630 + iVar4 * 2);
    }
  } while( true );
  if (iVar11 == 0x86) {
    return 0;
  }
  if (DAT_0072ba0c != 0) {
    FUN_00509f22(&DAT_005ca980,s_Shifting_error_token__005d2558);
  }
  local_8 = local_8 + 1;
  *local_8 = DAT_0072b9f8;
  local_c = iVar11;
  goto LAB_0057f2cd;
}

