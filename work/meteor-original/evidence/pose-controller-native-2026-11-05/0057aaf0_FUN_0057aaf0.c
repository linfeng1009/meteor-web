/* Original Meteor.exe static export @ 0057aaf0; original sample not executed. */
/* XREF 0055c6ad UNCONDITIONAL_CALL */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0057aaf0(void)

{
  short *psVar1;
  char cVar2;
  short sVar3;
  int *piVar4;
  char *pcVar5;
  uint uVar6;
  char *pcVar7;
  int *piVar8;
  int iVar9;
  uint uVar10;
  undefined4 *puVar11;
  uint uVar12;
  int *piVar13;
  int iVar14;
  int iVar15;
  undefined *puVar16;
  undefined4 local_984 [199];
  undefined1 auStack_666 [402];
  undefined **local_4d4 [67];
  undefined **local_3c8 [67];
  undefined **local_2bc [67];
  undefined **local_1b0 [67];
  undefined1 local_a4 [12];
  undefined1 local_98 [12];
  undefined1 local_8c [12];
  int *local_80;
  undefined1 local_7c [12];
  int local_70;
  undefined1 local_6a;
  undefined1 local_69;
  undefined4 *local_68;
  undefined1 local_62;
  undefined1 local_61;
  undefined4 *local_60;
  char *local_5c;
  int local_58;
  undefined4 *local_54;
  char *local_50;
  int local_4c;
  int local_48;
  int *local_44;
  int *local_40;
  char *local_3c;
  undefined4 *local_38;
  int local_34;
  int *local_30;
  int *local_2c;
  int *local_28;
  int local_24;
  char *local_20;
  int *local_1c;
  int *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005a63ad;
  local_10 = ExceptionList;
  local_68 = local_984;
  local_48 = 0;
  local_28 = (int *)(auStack_666 + 2);
  local_24 = 200;
  ExceptionList = &local_10;
  if (DAT_0072b9a8 != 0) {
    ExceptionList = &local_10;
    FUN_00509f22(&DAT_005ca980,s_Starting_parse_005d2674);
  }
  piVar4 = (int *)0x0;
  local_34 = 0;
  DAT_0072b98c = 0;
  DAT_0072b9ac = 0xfffffffe;
  local_14 = local_984;
  piVar8 = (int *)(auStack_666 + 2);
  piVar13 = (int *)auStack_666;
LAB_0057ab71:
  do {
    while( true ) {
      iVar9 = local_24;
      piVar13 = (int *)((int)piVar13 + 2);
      local_18 = piVar4;
      local_2c = piVar13;
      *(short *)piVar13 = (short)piVar4;
      if ((int *)((int)piVar8 + iVar9 * 2 + -2) <= piVar13) {
        iVar14 = (int)piVar13 - (int)piVar8 >> 1;
        iVar15 = iVar14 + 1;
        local_38 = local_68;
        local_1c = piVar8;
        if (9999 < iVar9) {
          FUN_0057bee0(s_parser_stack_overflow_005d23f8);
          ExceptionList = local_10;
          return 2;
        }
        local_24 = iVar9 * 2;
        if (10000 < local_24) {
          local_24 = 10000;
        }
        FUN_00509ce0();
        iVar9 = iVar15 * 2;
        local_28 = (int *)&stack0xfffff670;
        FUN_0057bec0(local_1c,&stack0xfffff670,iVar9);
        FUN_00509ce0();
        local_68 = (undefined4 *)&stack0xfffff670;
        FUN_0057bec0(local_38,&stack0xfffff670,iVar15 * 4);
        piVar13 = (int *)((int)local_984 + iVar9 + -0xe);
        local_2c = piVar13;
        local_14 = local_68 + iVar14;
        if (DAT_0072b9a8 != 0) {
          FUN_00509f22(&DAT_005ca980,s_Stack_size_increased_to__d_005d2658,local_24);
        }
        if ((int *)((int)local_28 + local_24 * 2 + -2) <= piVar13) {
          ExceptionList = local_10;
          return 1;
        }
      }
      if (DAT_0072b9a8 != 0) {
        FUN_00509f22(&DAT_005ca980,s_Entering_state__d_005d2644,local_18);
      }
      sVar3 = *(short *)(&DAT_005af450 + (int)local_18 * 2);
      iVar9 = local_48;
      if (sVar3 == -0x8000) break;
      if (DAT_0072b9ac == 0xfffffffe) {
        if (DAT_0072b9a8 != 0) {
          FUN_00509f22(&DAT_005ca980,s_Reading_a_token__005d2630);
        }
        DAT_0072b9ac = FUN_00579e90();
      }
      if ((int)DAT_0072b9ac < 1) {
        iVar9 = 0;
        local_48 = 0;
        DAT_0072b9ac = 0;
        if (DAT_0072b9a8 != 0) {
          FUN_00509f22(&DAT_005ca980,s_Now_at_end_of_input__005d2618);
        }
      }
      else {
        if (DAT_0072b9ac < 0x129) {
          iVar9 = (int)(char)(&DAT_005ae880)[DAT_0072b9ac];
        }
        else {
          iVar9 = 0x6b;
        }
        local_48 = iVar9;
        if (DAT_0072b9a8 != 0) {
          FUN_00509f22(&DAT_005ca980,s_Next_token_is__d___s_005d2600,DAT_0072b9ac,
                       (&PTR_DAT_005aee80)[iVar9]);
          FUN_00509f22(&DAT_005ca980,&DAT_005d25fc);
        }
      }
      iVar14 = sVar3 + iVar9;
      if (((iVar14 < 0) || (0x1a9 < iVar14)) ||
         (*(short *)((int)&PTR_LAB_005af9b8 + iVar14 * 2) != iVar9)) break;
      piVar4 = (int *)(int)*(short *)((int)&
                                           PTR_s_nknown_Adobe_color_transform_cod_005d005c_1_005af660
                                     + iVar14 * 2);
      if ((int)piVar4 < 0) {
        if (piVar4 == (int *)0xffff8000) goto LAB_0057aec8;
LAB_0057ad72:
        puVar11 = (undefined4 *)-(int)piVar4;
        local_38 = puVar11;
        goto LAB_0057ad77;
      }
      if (piVar4 == (int *)0x0) goto LAB_0057aec8;
      if (piVar4 == (int *)0xc4) {
        ExceptionList = local_10;
        return 0;
      }
      if (DAT_0072b9a8 != 0) {
        FUN_00509f22(&DAT_005ca980,s_Shifting_token__d___s___005d25b4,DAT_0072b9ac,
                     (&PTR_DAT_005aee80)[iVar9]);
      }
      if (DAT_0072b9ac != 0) {
        DAT_0072b9ac = 0xfffffffe;
      }
      local_14 = local_14 + 1;
      *local_14 = DAT_0072b988;
      piVar8 = local_28;
      if (local_34 != 0) {
        local_34 = local_34 + -1;
      }
    }
    puVar11 = (undefined4 *)(int)*(short *)(&DAT_005af240 + (int)local_18 * 2);
    local_38 = puVar11;
    if (puVar11 == (undefined4 *)0x0) {
LAB_0057aec8:
      if (local_34 == 0) {
        DAT_0072b98c = DAT_0072b98c + 1;
        FUN_0057bee0(s_parse_error_005d25a8);
      }
      else if (local_34 == 3) {
        if (DAT_0072b9ac == 0) {
          ExceptionList = local_10;
          return 1;
        }
        if (DAT_0072b9a8 != 0) {
          FUN_00509f22(&DAT_005ca980,s_Discarding_token__d___s___005d258c,DAT_0072b9ac,
                       (&PTR_DAT_005aee80)[iVar9]);
        }
        DAT_0072b9ac = 0xfffffffe;
      }
      piVar8 = local_28;
      local_34 = 3;
LAB_0057af31:
      if (((*(short *)(&DAT_005af450 + (int)local_18 * 2) != -0x8000) &&
          (iVar9 = *(short *)(&DAT_005af450 + (int)local_18 * 2) + 1, -1 < iVar9)) &&
         ((iVar9 < 0x1aa && (*(short *)((int)&PTR_LAB_005af9b8 + iVar9 * 2) == 1)))) {
        piVar4 = (int *)(int)*(short *)((int)&
                                             PTR_s_nknown_Adobe_color_transform_cod_005d005c_1_005af660
                                       + iVar9 * 2);
        if ((int)piVar4 < 0) {
          if (piVar4 != (int *)0xffff8000) goto LAB_0057ad72;
        }
        else if (piVar4 != (int *)0x0) break;
      }
      if (piVar13 == piVar8) {
        ExceptionList = local_10;
        return 1;
      }
      psVar1 = (short *)((int)piVar13 + -2);
      piVar13 = (int *)((int)piVar13 + -2);
      local_18 = (int *)(int)*psVar1;
      local_2c = piVar13;
      local_14 = local_14 + -1;
      if (DAT_0072b9a8 != 0) {
        piVar4 = (int *)((int)piVar8 + -2);
        FUN_00509f22(&DAT_005ca980,s_Error__state_stack_now_005d2574);
        for (; piVar4 != piVar13; piVar4 = (int *)((int)piVar4 + 2)) {
          FUN_00509f22(&DAT_005ca980,&PTR_DAT_005d2570,(int)*(short *)((int)piVar4 + 2));
        }
        FUN_00509f22(&DAT_005ca980,&DAT_005c4540);
      }
      goto LAB_0057af31;
    }
LAB_0057ad77:
    local_70 = (int)*(short *)(&DAT_005af138 + (int)puVar11 * 2);
    if (0 < local_70) {
      local_20 = (char *)local_14[1 - local_70];
    }
    local_38 = puVar11;
    if (DAT_0072b9a8 != 0) {
      FUN_00509f22(&DAT_005ca980,s_Reducing_via_rule__d__line__d___005d25d8,puVar11,
                   (int)*(short *)(&DAT_005aed78 + (int)puVar11 * 2));
      puVar16 = &DAT_005aeab8 + *(short *)(&DAT_005ae9b0 + (int)puVar11 * 2) * 2;
      sVar3 = *(short *)(&DAT_005aeab8 + *(short *)(&DAT_005ae9b0 + (int)puVar11 * 2) * 2);
      while (0 < sVar3) {
        FUN_00509f22(&DAT_005ca980,&DAT_005d18bc,(&PTR_DAT_005aee80)[sVar3]);
        psVar1 = (short *)(puVar16 + 2);
        puVar16 = puVar16 + 2;
        sVar3 = *psVar1;
      }
      FUN_00509f22(&DAT_005ca980,s__>__s_005d25d0,
                   (&PTR_DAT_005aee80)[*(short *)(&DAT_005af030 + (int)puVar11 * 2)]);
    }
    pcVar5 = local_20;
    switch(puVar11) {
    case (undefined4 *)0x3:
      FUN_0057a7e0(s_Pose_Structure_Error_005d2540);
      break;
    case (undefined4 *)0x4:
      FUN_00575180();
      DAT_0072b9bc = 0;
      break;
    case (undefined4 *)0x5:
      FUN_0057bef0(&DAT_0072b870);
      iVar9 = DAT_0072b86c;
      piVar13 = *(int **)(DAT_0072b86c + 0x630);
      if (piVar13 == *(int **)(DAT_0072b86c + 0x634)) {
        FUN_0057bf70(piVar13,&DAT_0072b870);
      }
      else {
        local_30 = piVar13;
        local_1c = piVar13;
        local_8 = 0;
        if (piVar13 != (int *)0x0) {
          FUN_0057c3d0(&DAT_0072b870);
        }
        local_8 = 0xffffffff;
        *(int *)(iVar9 + 0x630) = *(int *)(iVar9 + 0x630) + 0xac;
      }
      break;
    case (undefined4 *)0x7:
      FUN_0057a7e0(s_____expected_in_pose_005d2528);
      break;
    case (undefined4 *)0x8:
    case (undefined4 *)0xb:
      FUN_0057a7e0(s_____expected_in_pose_005d2510);
      break;
    case (undefined4 *)0xa:
    case (undefined4 *)0xd:
      FUN_0057a7e0(s___expected_in_pose_005d24fc);
      break;
    case (undefined4 *)0x21:
      FUN_0057a7e0(s_Pose_field_error_005d24e8);
      break;
    case (undefined4 *)0x22:
      pcVar7 = &DAT_0072b870;
      pcVar5 = (char *)*local_14;
      do {
        cVar2 = *pcVar5;
        pcVar5 = pcVar5 + 1;
        *pcVar7 = cVar2;
        pcVar7 = pcVar7 + 1;
      } while (cVar2 != '\0');
      FUN_005089fd(*local_14);
      break;
    case (undefined4 *)0x23:
      _DAT_0072b880 = __ftol();
      break;
    case (undefined4 *)0x24:
      switch(DAT_0072b9bc) {
      case 0:
        _DAT_0072b884 = __ftol();
        break;
      case 1:
      case 2:
        _DAT_0072b9b0 = __ftol();
        break;
      case 3:
        _DAT_0072b920 = __ftol();
        break;
      case 4:
        _DAT_0072b8b8 = __ftol();
        break;
      case 5:
        _DAT_0072b990 = __ftol();
      }
      break;
    case (undefined4 *)0x25:
      switch(DAT_0072b9bc) {
      case 0:
        _DAT_0072b888 = __ftol();
        break;
      case 1:
      case 2:
        _DAT_0072b9b4 = __ftol();
        break;
      case 3:
        _DAT_0072b924 = __ftol();
        break;
      case 4:
        _DAT_0072b8bc = __ftol();
        break;
      case 5:
        _DAT_0072b994 = __ftol();
      }
      break;
    case (undefined4 *)0x26:
      _DAT_0072b8b4 = __ftol();
      break;
    case (undefined4 *)0x27:
      _DAT_0072b88c = __ftol();
      break;
    case (undefined4 *)0x28:
      _DAT_0072b890 = __ftol();
      break;
    case (undefined4 *)0x29:
      _DAT_0072b894 = __ftol();
      break;
    case (undefined4 *)0x2c:
      local_54 = (undefined4 *)0x0;
      local_50 = (char *)0x0;
      local_4c = 0;
      uVar6 = 0xffffffff;
      puVar11 = (undefined4 *)0x0;
      pcVar7 = local_20;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar2 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar2 != '\0');
      uVar6 = ~uVar6;
      local_8 = 1;
      if (uVar6 == 0xffffffff) {
        FUN_00402570(s_basic_string_005c42c8,&local_61);
        local_8 = CONCAT31(local_8._1_3_,2);
        FUN_00402850(local_8c);
        local_1b0[0] = &PTR_FUN_005a83c0;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(local_1b0,&DAT_005b3c50);
      }
      if (uVar6 != 0) {
        puVar11 = (undefined4 *)FUN_00402bf0(uVar6);
      }
      local_4c = uVar6 + (int)puVar11;
      local_54 = puVar11;
      local_50 = (char *)puVar11;
      FUN_005092c0(puVar11,local_20,uVar6 - 1);
      local_50 = pcVar5 + (int)puVar11 + ((uVar6 - 1) - (int)local_20);
      FUN_00402a70();
      piVar13 = DAT_0072b8a8;
      local_8 = 3;
      if (DAT_0072b8a8 == DAT_0072b8ac) {
        FUN_0047a010(DAT_0072b8a8,&local_54);
      }
      else {
        local_30 = DAT_0072b8a8;
        local_1c = DAT_0072b8a8;
        if (DAT_0072b8a8 != (int *)0x0) {
          *DAT_0072b8a8 = 0;
          piVar13[1] = 0;
          piVar13[2] = 0;
          local_8 = 5;
          FUN_00402ac0(local_54,local_50);
        }
        DAT_0072b8a8 = DAT_0072b8a8 + 3;
      }
      puVar11 = local_54;
      uVar6 = local_4c - (int)local_54;
      local_8 = 0xffffffff;
      if ((local_54 != (undefined4 *)0x0) && (uVar6 != 0)) {
        if (0x80 < uVar6) {
          FUN_005089fd(local_54);
          FUN_005089fd(local_20);
          break;
        }
        FUN_00402330();
        *puVar11 = *(undefined4 *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = puVar11;
        DAT_005d59e8 = 0;
      }
      FUN_005089fd(local_20);
      break;
    case (undefined4 *)0x2d:
      local_60 = (undefined4 *)0x0;
      local_5c = (char *)0x0;
      local_58 = 0;
      uVar6 = 0xffffffff;
      puVar11 = (undefined4 *)0x0;
      pcVar7 = local_20;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar2 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar2 != '\0');
      uVar6 = ~uVar6;
      local_8 = 6;
      if (uVar6 == 0xffffffff) {
        FUN_00402570(s_basic_string_005c42c8,&local_69);
        local_8 = CONCAT31(local_8._1_3_,7);
        FUN_00402850(local_98);
        local_3c8[0] = &PTR_FUN_005a83c0;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(local_3c8,&DAT_005b3c50);
      }
      if (uVar6 != 0) {
        puVar11 = (undefined4 *)FUN_00402bf0(uVar6);
      }
      local_58 = uVar6 + (int)puVar11;
      local_60 = puVar11;
      local_5c = (char *)puVar11;
      FUN_005092c0(puVar11,local_20,uVar6 - 1);
      local_5c = pcVar5 + (int)puVar11 + ((uVar6 - 1) - (int)local_20);
      FUN_00402a70();
      pcVar5 = local_5c;
      puVar11 = local_60;
      piVar13 = DAT_0072b8a8;
      local_8 = 8;
      if (DAT_0072b8a8 == DAT_0072b8ac) {
        FUN_0047a010(DAT_0072b8a8,&local_60);
      }
      else {
        local_30 = DAT_0072b8a8;
        local_1c = DAT_0072b8a8;
        if (DAT_0072b8a8 != (int *)0x0) {
          *DAT_0072b8a8 = 0;
          piVar13[1] = 0;
          piVar13[2] = 0;
          local_8 = 10;
          FUN_004608a0(local_5c + (1 - (int)local_60));
          iVar9 = FUN_004da870(puVar11,pcVar5,*piVar13);
          piVar13[1] = iVar9;
          FUN_00402a70();
        }
        DAT_0072b8a8 = DAT_0072b8a8 + 3;
      }
      puVar11 = local_60;
      uVar6 = local_58 - (int)local_60;
      local_8 = 0xffffffff;
      if ((local_60 != (undefined4 *)0x0) && (uVar6 != 0)) {
        if (0x80 < uVar6) {
          FUN_005089fd(local_60);
          FUN_005089fd(local_20);
          break;
        }
        FUN_00402330();
        *puVar11 = *(undefined4 *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
        *(undefined4 **)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4) = puVar11;
        DAT_005d59e8 = 0;
      }
      FUN_005089fd(local_20);
      break;
    case (undefined4 *)0x2e:
      FUN_00574c90();
      _DAT_0072b920 = __ftol();
      _DAT_0072b924 = _DAT_0072b920;
      FUN_005754d0(&DAT_0072b920);
      break;
    case (undefined4 *)0x2f:
      if (0 < DAT_0072b9bc) {
        if (DAT_0072b9bc < 3) {
          _DAT_0072b9b8 = *local_14;
        }
        else if (DAT_0072b9bc == 3) {
          _DAT_0072b92c = *local_14;
        }
      }
      break;
    case (undefined4 *)0x30:
      _DAT_0072b950 = __ftol();
      break;
    case (undefined4 *)0x31:
      _DAT_0072b954 = __ftol();
      break;
    case (undefined4 *)0x32:
      _DAT_0072b960 = *local_14;
      break;
    case (undefined4 *)0x33:
      _DAT_0072b95c = *local_14;
      break;
    case (undefined4 *)0x34:
      _DAT_0072b958 = __ftol();
      break;
    case (undefined4 *)0x35:
      _DAT_0072b964 = __ftol();
      break;
    case (undefined4 *)0x36:
      _DAT_0072b97c = *local_14;
      break;
    case (undefined4 *)0x37:
      _DAT_0072b980 = *local_14;
      break;
    case (undefined4 *)0x38:
      _DAT_0072b984 = *local_14;
      break;
    case (undefined4 *)0x39:
      _DAT_0072b968 = __ftol();
      break;
    case (undefined4 *)0x3a:
      _DAT_0072b96c = __ftol();
      break;
    case (undefined4 *)0x3b:
      _DAT_0072b970 = __ftol();
      break;
    case (undefined4 *)0x3c:
      _DAT_0072b974 = __ftol();
      break;
    case (undefined4 *)0x3d:
      _DAT_0072b978 = __ftol();
      break;
    case (undefined4 *)0x3e:
      FUN_00574c10();
      DAT_0072b9bc = 1;
      break;
    case (undefined4 *)0x3f:
      DAT_0072b9bc = 0;
      FUN_005753b0(&DAT_0072b9b0);
      break;
    case (undefined4 *)0x41:
      FUN_0057a7e0(s_____expected_in_blend_005d24d0);
      break;
    case (undefined4 *)0x42:
      FUN_0057a7e0(s_____expected_in_blend_005d24b8);
      break;
    case (undefined4 *)0x48:
      FUN_00574c10();
      DAT_0072b9bc = 2;
      break;
    case (undefined4 *)0x49:
      FUN_00575410(&DAT_0072b9b0);
      DAT_0072b9bc = 0;
      break;
    case (undefined4 *)0x4b:
      FUN_0057a7e0(s_____expected_in_action_005d24a0);
      break;
    case (undefined4 *)0x4c:
      FUN_0057a7e0(s_____expected_in_action_005d2488);
      break;
    case (undefined4 *)0x4d:
      FUN_00574c90();
      DAT_0072b9bc = 3;
      break;
    case (undefined4 *)0x4e:
      FUN_005754d0(&DAT_0072b920);
      DAT_0072b9bc = 0;
      break;
    case (undefined4 *)0x50:
      FUN_0057a7e0(s_____expected_in_attack_005d2470);
      break;
    case (undefined4 *)0x51:
      FUN_0057a7e0(s_____expected_in_attack_005d2458);
      break;
    case (undefined4 *)0x52:
      _DAT_0072b94c = __ftol();
      break;
    case (undefined4 *)0x6b:
      local_44 = (int *)0x0;
      local_40 = (int *)0x0;
      pcVar5 = (char *)*local_14;
      local_3c = (char *)0x0;
      uVar6 = 0xffffffff;
      local_8 = 0xb;
      pcVar7 = pcVar5;
      do {
        if (uVar6 == 0) break;
        uVar6 = uVar6 - 1;
        cVar2 = *pcVar7;
        pcVar7 = pcVar7 + 1;
      } while (cVar2 != '\0');
      local_1c = (int *)(pcVar5 + ((~uVar6 - 1) - (int)pcVar5));
      pcVar7 = (char *)((int)local_1c + 1);
      if (pcVar7 == (char *)0xffffffff) {
        FUN_00402570(s_basic_string_005c42c8,&local_62);
        local_8 = CONCAT31(local_8._1_3_,0xc);
        FUN_00402850(local_a4);
        local_2bc[0] = &PTR_FUN_005a83c0;
                    /* WARNING: Subroutine does not return */
        __CxxThrowException_8(local_2bc,&DAT_005b3c50);
      }
      if (pcVar7 == (char *)0x0) {
        piVar13 = (int *)0x0;
      }
      else {
        piVar13 = (int *)FUN_00402bf0(pcVar7);
      }
      local_3c = pcVar7 + (int)piVar13;
      local_44 = piVar13;
      local_40 = piVar13;
      FUN_005092c0(piVar13,pcVar5,local_1c);
      local_40 = (int *)(pcVar5 + (int)((int)piVar13 + ((~uVar6 - 1) - (int)pcVar5)));
      FUN_00402a70();
      uVar6 = 0;
      local_8 = 0xd;
      if (local_40 != local_44) {
        do {
          if (*(char *)(uVar6 + (int)local_44) == ' ') {
            *(char *)(uVar6 + (int)local_44) = '_';
          }
          uVar6 = uVar6 + 1;
        } while (uVar6 < (uint)((int)local_40 - (int)local_44));
      }
      FUN_005089fd(*local_14);
      piVar13 = DAT_0072b934;
      if (DAT_0072b934 == DAT_0072b938) {
        FUN_0047a010(DAT_0072b934,&local_44);
      }
      else {
        local_30 = DAT_0072b934;
        local_80 = DAT_0072b934;
        if (DAT_0072b934 != (int *)0x0) {
          *DAT_0072b934 = 0;
          piVar13[1] = 0;
          piVar13[2] = 0;
          local_1c = local_40;
          local_8._0_1_ = 0xf;
          local_18 = local_44;
          pcVar5 = (char *)((int)local_40 + (1 - (int)local_44));
          if (pcVar5 == (char *)0xffffffff) {
            FUN_005005b0(&local_6a);
            local_8._0_1_ = 0x10;
            iVar9 = FUN_0057bea0(s_basic_string_005c42c8);
            FUN_00402ac0(s_basic_string_005c42c8,s_basic_string_005c42c8 + iVar9);
            local_8 = CONCAT31(local_8._1_3_,0x11);
            FUN_00402850(local_7c);
            local_4d4[0] = &PTR_FUN_005a83c0;
                    /* WARNING: Subroutine does not return */
            __CxxThrowException_8(local_4d4,&DAT_005b3c50);
          }
          if (pcVar5 == (char *)0x0) {
            iVar9 = 0;
          }
          else {
            iVar9 = FUN_00402bf0(pcVar5);
          }
          *piVar13 = iVar9;
          piVar13[1] = iVar9;
          piVar13[2] = (int)(pcVar5 + iVar9);
          FUN_005092c0(iVar9,local_18,(int)local_1c - (int)local_18);
          piVar13[1] = (int)((iVar9 - (int)local_18) + (int)local_1c);
          FUN_00402a70();
        }
        DAT_0072b934 = DAT_0072b934 + 3;
      }
      uVar6 = (int)local_3c - (int)local_44;
      local_8 = 0xffffffff;
      if ((local_44 != (int *)0x0) && (uVar6 != 0)) {
        if (uVar6 < 0x81) {
          local_30 = local_44;
          local_1c = (int *)(&DAT_005d59a4 + (uVar6 + 7 >> 3) * 4);
          iVar9 = FUN_00443110(&DAT_005d59e8,1);
          uVar6 = DAT_005c4248;
          if (iVar9 != 0) {
            uVar12 = 0;
            local_18 = (int *)0x11;
            if (DAT_005c4248 != 0) {
              uVar10 = DAT_005d59ec >> 1;
              do {
                if ((uVar12 < uVar10) || (DAT_005d59e8 != 0)) {
                  iVar9 = (int)local_18 * (int)local_18 * (int)local_18 * (int)local_18;
                  iVar9 = iVar9 * iVar9;
                  local_18 = (int *)(iVar9 * iVar9);
                }
                else {
                  iVar9 = FUN_00443110(&DAT_005d59e8,1);
                  if (iVar9 == 0) {
                    DAT_005c4248 = 1000;
                    DAT_005d59ec = uVar12;
                    goto LAB_0057b9aa;
                  }
                }
                uVar12 = uVar12 + 1;
              } while (uVar12 < uVar6);
            }
            DAT_005c4248 = 0x1e;
            iVar9 = 6;
            while( true ) {
              iVar14 = iVar9;
              if (0x1b < iVar9) {
                iVar14 = 0x1b;
              }
              iVar15 = FUN_00443110(&DAT_005d59e8,1);
              if (iVar15 == 0) break;
              FUN_00443130(iVar14);
              iVar9 = iVar9 + 1;
            }
          }
LAB_0057b9aa:
          *local_30 = *local_1c;
          *local_1c = (int)local_30;
          DAT_005d59e8 = 0;
        }
        else {
          FUN_005089fd(local_44);
        }
      }
      break;
    case (undefined4 *)0x6c:
      DAT_0072b9bc = 5;
      break;
    case (undefined4 *)0x6d:
      FUN_00575470(&DAT_0072b990);
    case (undefined4 *)0x77:
      DAT_0072b9bc = 0;
      break;
    case (undefined4 *)0x75:
      _DAT_0072b998 = __ftol();
      _DAT_0072b99c = __ftol();
      _DAT_0072b9a0 = __ftol();
      break;
    case (undefined4 *)0x76:
      DAT_0072b9bc = 4;
      break;
    case (undefined4 *)0x79:
      FUN_0057a7e0(s_____expected_in_nextitem_005d243c);
      break;
    case (undefined4 *)0x7a:
      FUN_0057a7e0(s_____expected_in_nextitem_005d2420);
      break;
    case (undefined4 *)0x80:
      if (DAT_0072b9bc == 4) {
        _DAT_0072b8c0 = *local_14;
      }
      else if (DAT_0072b9bc == 5) {
        _DAT_0072b9a4 = *local_14;
      }
    }
    puVar11 = local_14;
    iVar9 = local_70;
    piVar4 = (int *)((int)local_2c + local_70 * -2);
    local_2c = piVar4;
    if (DAT_0072b9a8 != 0) {
      piVar13 = (int *)((int)local_28 + -2);
      FUN_00509f22(&DAT_005ca980,s_state_stack_now_005d2410);
      for (; piVar13 != piVar4; piVar13 = (int *)((int)piVar13 + 2)) {
        FUN_00509f22(&DAT_005ca980,&PTR_DAT_005d2570,(int)*(short *)((int)piVar13 + 2));
      }
      FUN_00509f22(&DAT_005ca980,&DAT_005c4540);
    }
    local_14 = puVar11 + (1 - iVar9);
    puVar11[1 - iVar9] = local_20;
    iVar9 = (int)*(short *)(&DAT_005af586 + *(short *)(&DAT_005af030 + (int)local_38 * 2) * 2) +
            (int)(short)*piVar4;
    piVar8 = local_28;
    piVar13 = local_2c;
    if (((iVar9 < 0) || (0x1a9 < iVar9)) ||
       (*(short *)((int)&PTR_LAB_005af9b8 + iVar9 * 2) != (short)*piVar4)) {
      piVar4 = (int *)(int)L"KJ01k"[*(short *)(&DAT_005af030 + (int)local_38 * 2)];
    }
    else {
      piVar4 = (int *)(int)*(short *)((int)&
                                           PTR_s_nknown_Adobe_color_transform_cod_005d005c_1_005af660
                                     + iVar9 * 2);
    }
  } while( true );
  if (piVar4 == (int *)0xc4) {
    ExceptionList = local_10;
    return 0;
  }
  if (DAT_0072b9a8 != 0) {
    FUN_00509f22(&DAT_005ca980,s_Shifting_error_token__005d2558);
  }
  local_14 = local_14 + 1;
  *local_14 = DAT_0072b988;
  goto LAB_0057ab71;
}

