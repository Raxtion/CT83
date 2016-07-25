object fmManual: TfmManual
  Left = 174
  Top = 34
  BorderStyle = bsDialog
  Caption = 'fmManual'
  ClientHeight = 649
  ClientWidth = 1044
  Color = 13430215
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 16
  object btnStopSprayer: TSpeedButton
    Left = 920
    Top = 208
    Width = 100
    Height = 89
    Hint = '78'
    Caption = 'Sprayer ('#38364')'
    OnClick = btnStopSprayerClick
  end
  object btnAutoStartFillFlux: TSpeedButton
    Tag = 74
    Left = 920
    Top = 392
    Width = 100
    Height = 65
    Hint = '78'
    Caption = #33258#21205' '#35036'Flux'
    OnClick = btnAutoStartFillFluxClick
  end
  object btnAutoStopFillFlux: TSpeedButton
    Tag = 74
    Left = 920
    Top = 464
    Width = 100
    Height = 65
    Hint = '78'
    Caption = #32066#27490' '#35036'Flux'
    OnClick = btnAutoStopFillFluxClick
  end
  object SpeedButton5: TSpeedButton
    Tag = 74
    Left = 921
    Top = 96
    Width = 96
    Height = 81
    Hint = '78'
    Caption = 'SPZ'#27512#38646
    OnClick = btnSPZToHomeClick
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 913
    Height = 649
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Auto mode'
      object GroupBox1: TGroupBox
        Left = 8
        Top = 9
        Width = 241
        Height = 592
        Caption = 'Loader'
        TabOrder = 0
        object btnLDZGo: TSpeedButton
          Left = 128
          Top = 22
          Width = 41
          Height = 28
          Caption = 'GO!'
          Enabled = False
          OnClick = btnLDZGoClick
        end
        object btnLDYGo: TSpeedButton
          Left = 128
          Top = 51
          Width = 41
          Height = 28
          Caption = 'GO!'
          Enabled = False
          OnClick = btnLDYGoClick
        end
        object SpeedButton2: TSpeedButton
          Tag = 1
          Left = 128
          Top = 80
          Width = 41
          Height = 28
          Caption = 'GO!'
          Enabled = False
          OnClick = btnLDZGoClick
        end
        object SpeedButton3: TSpeedButton
          Tag = 1
          Left = 128
          Top = 177
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLDYGoClick
        end
        object SpeedButton4: TSpeedButton
          Tag = 2
          Left = 128
          Top = 206
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLDZGoClick
        end
        object SpeedButton6: TSpeedButton
          Tag = 3
          Left = 128
          Top = 367
          Width = 41
          Height = 28
          Caption = 'GO!'
          Enabled = False
          OnClick = btnLDZGoClick
        end
        object SpeedButton7: TSpeedButton
          Tag = 2
          Left = 128
          Top = 396
          Width = 41
          Height = 28
          Caption = 'GO!'
          Enabled = False
          OnClick = btnLDYGoClick
        end
        object SpeedButton8: TSpeedButton
          Tag = 4
          Left = 128
          Top = 425
          Width = 41
          Height = 28
          Caption = 'GO!'
          Enabled = False
          OnClick = btnLDZGoClick
        end
        object btnLoaderClamper: TSpeedButton
          Tag = 11
          Left = 11
          Top = 112
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #26009#30418'('#22846#20303'\'#25918#38283')'
          OnClick = btnSimpleIOClick
        end
        object btnLDZDown1Step: TSpeedButton
          Tag = 74
          Left = 11
          Top = 241
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #19979#19968#26684
          OnClick = btnLDZDown1StepClick
        end
        object btnLoaderBusher: TSpeedButton
          Tag = 8
          Left = 11
          Top = 305
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #20837#26009#25512#26751'('#20280'\'#32302')'
          OnClick = btnLoaderBusherClick
        end
        object btnAutoStartReLoadClamper: TSpeedButton
          Left = 19
          Top = 464
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #33258#21205#35036#26009#30418#21205#20316
          OnClick = btnAutoStartReLoadClamperClick
        end
        object btnAutoStartUnLoadClamper: TSpeedButton
          Left = 19
          Top = 528
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #33258#21205#36864#26009#30418#21205#20316
          OnClick = btnAutoStartUnLoadClamperClick
        end
        object btnLDYToHome: TSpeedButton
          Tag = 74
          Left = 160
          Top = 240
          Width = 73
          Height = 57
          Hint = '78'
          Caption = 'LDY'#27512#38646
          OnClick = btnLDYToHomeClick
        end
        object btnLDZToHome: TSpeedButton
          Tag = 74
          Left = 160
          Top = 112
          Width = 73
          Height = 57
          Hint = '78'
          Caption = 'LDZ'#27512#38646
          OnClick = btnLDZToHomeClick
        end
        object StaticText5: TStaticText
          Tag = 4
          Left = 13
          Top = 26
          Width = 108
          Height = 21
          Hint = 'm_dLoaderClampMgzPos0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25235#21462#20301#32622'1 (Z)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
        object StaticText1: TStaticText
          Tag = 5
          Left = 13
          Top = 55
          Width = 108
          Height = 21
          Hint = 'm_dLoaderClampMgzPos1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25235#21462#20301#32622'2 (Y)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 1
        end
        object StaticText3: TStaticText
          Tag = 4
          Left = 13
          Top = 84
          Width = 108
          Height = 21
          Hint = 'm_dLoaderClampMgzPos2'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25235#21462#20301#32622'3 (Z)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 2
        end
        object StaticText6: TStaticText
          Tag = 5
          Left = 13
          Top = 180
          Width = 108
          Height = 21
          Hint = 'm_dMagazinePushPosY'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25512#29255#20301#32622' Y'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 3
        end
        object StaticText8: TStaticText
          Tag = 4
          Left = 13
          Top = 209
          Width = 108
          Height = 21
          Hint = 'm_dMagazinePushPosZ'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25512#29255#20301#32622' Z'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 4
        end
        object StaticText10: TStaticText
          Tag = 4
          Left = 13
          Top = 370
          Width = 108
          Height = 21
          Hint = 'm_dLoaderUnClampMgzPos0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #36864#30418#20301#32622'1 (Z)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 5
        end
        object StaticText11: TStaticText
          Tag = 5
          Left = 13
          Top = 399
          Width = 108
          Height = 21
          Hint = 'm_dLoaderUnClampMgzPos1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #36864#30418#20301#32622'2 (Y)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 6
        end
        object StaticText12: TStaticText
          Tag = 4
          Left = 13
          Top = 428
          Width = 108
          Height = 21
          Hint = 'm_dLoaderUnClampMgzPos2'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #36864#30418#20301#32622'3 (Z)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 7
        end
      end
      object GroupBox2: TGroupBox
        Left = 256
        Top = 8
        Width = 193
        Height = 209
        Caption = #20837#26009#20998#37197#27969#36947
        TabOrder = 1
        object btnRLCGo: TSpeedButton
          Left = 128
          Top = 22
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnRLCGoClick
        end
        object SpeedButton11: TSpeedButton
          Tag = 1
          Left = 128
          Top = 51
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnRLCGoClick
        end
        object SpeedButton12: TSpeedButton
          Tag = 2
          Left = 128
          Top = 80
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnRLCGoClick
        end
        object SpeedButton21: TSpeedButton
          Tag = 26
          Left = 101
          Top = 144
          Width = 89
          Height = 57
          Hint = '78'
          Caption = #27969#36947'('#21205'/'#27490')'
          OnClick = btnSimpleIOClick
        end
        object btnSimpleIO: TSpeedButton
          Tag = 27
          Left = 3
          Top = 144
          Width = 94
          Height = 57
          Hint = '78'
          Caption = #27773#32568'('#19978'/'#19979')'
          OnClick = btnSimpleIOClick
        end
        object StaticText16: TStaticText
          Tag = 10
          Left = 13
          Top = 26
          Width = 108
          Height = 21
          Hint = 'm_dLeftLaneChangerMgzPos'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25509#29255#20301#32622
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
        object StaticText19: TStaticText
          Tag = 10
          Left = 13
          Top = 84
          Width = 108
          Height = 21
          Hint = 'm_dLeftLaneChangerSprayPos0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #21069#27969#36947#20301#32622
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 1
        end
        object StaticText21: TStaticText
          Tag = 10
          Left = 13
          Top = 55
          Width = 108
          Height = 21
          Hint = 'm_dLeftLaneChangerSprayPos1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #24460#27969#36947#20301#32622
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 2
        end
      end
      object GroupBox3: TGroupBox
        Left = 256
        Top = 225
        Width = 393
        Height = 377
        Caption = #22132'FLUX'#20301#32622
        TabOrder = 2
        object btnSPXGo: TSpeedButton
          Left = 129
          Top = 37
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPXGoClick
        end
        object btnSPYGo: TSpeedButton
          Left = 129
          Top = 66
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPYGoClick
        end
        object SpeedButton15: TSpeedButton
          Tag = 1
          Left = 129
          Top = 95
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPXGoClick
        end
        object SpeedButton16: TSpeedButton
          Tag = 1
          Left = 129
          Top = 124
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPYGoClick
        end
        object btnSPZGo: TSpeedButton
          Left = 313
          Top = 78
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPZGoClick
        end
        object btnRelMoveSPX: TSpeedButton
          Left = 12
          Top = 176
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #22132'flux'#36317#38626'('#27491'X)'
          OnClick = btnRelMoveSPXClick
        end
        object SpeedButton22: TSpeedButton
          Tag = 1
          Left = 156
          Top = 176
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #22132'flux'#36317#38626'('#36000'X)'
          OnClick = btnRelMoveSPXClick
        end
        object btnRelMoveSPY: TSpeedButton
          Left = 12
          Top = 242
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #22132'flux'#38291#36317'(Y)'
          OnClick = btnRelMoveSPYClick
        end
        object btnStartFlux: TSpeedButton
          Left = 172
          Top = 242
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #22132'Flux ('#38283'\'#38364')'
          OnClick = btnStartFluxClick
        end
        object btnAutoStartSBTSprayF: TSpeedButton
          Tag = 74
          Left = 12
          Top = 312
          Width = 137
          Height = 57
          Hint = '78'
          Caption = '('#21069')'#33258#21205#22132#22615#21205#20316
          OnClick = btnAutoStartSBTSprayFClick
        end
        object btnAutoStartSBTSprayR: TSpeedButton
          Tag = 74
          Left = 156
          Top = 312
          Width = 137
          Height = 57
          Hint = '78'
          Caption = '('#24460')'#33258#21205#22132#22615#21205#20316
          OnClick = btnAutoStartSBTSprayRClick
        end
        object SpeedButton61: TSpeedButton
          Tag = 42
          Left = 280
          Top = 112
          Width = 101
          Height = 57
          Hint = '78'
          Caption = #21069#27969#36947'('#21205'/'#27490')'
          OnClick = btnSimpleIOClick
        end
        object SpeedButton62: TSpeedButton
          Tag = 44
          Left = 280
          Top = 16
          Width = 101
          Height = 57
          Hint = '78'
          Caption = #24460#27969#36947'('#21205'/'#27490')'
          OnClick = btnSimpleIOClick
        end
        object SpeedButton63: TSpeedButton
          Tag = 45
          Left = 176
          Top = 16
          Width = 101
          Height = 57
          Hint = '78'
          Caption = #24460#27773#32568'('#19978'/'#19979')'
          OnClick = btnSimpleIOClick
        end
        object SpeedButton64: TSpeedButton
          Tag = 43
          Left = 176
          Top = 112
          Width = 101
          Height = 57
          Hint = '78'
          Caption = #21069#27773#32568'('#19978'/'#19979')'
          OnClick = btnSimpleIOClick
        end
        object btnSPZToHome: TSpeedButton
          Tag = 74
          Left = 320
          Top = 224
          Width = 65
          Height = 81
          Hint = '78'
          Caption = 'SPZ'#27512#38646
          OnClick = btnSPZToHomeClick
        end
        object StaticText23: TStaticText
          Tag = 7
          Left = 14
          Top = 99
          Width = 108
          Height = 21
          Hint = 'm_dStartSprayPosX1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #21069#27969#36947#38283#22987'X'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
        object StaticText25: TStaticText
          Tag = 11
          Left = 14
          Top = 128
          Width = 108
          Height = 21
          Hint = 'm_dStartSprayPosY1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #21069#27969#36947#38283#22987'Y'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 1
        end
        object StaticText27: TStaticText
          Tag = 7
          Left = 14
          Top = 41
          Width = 108
          Height = 21
          Hint = 'm_dStartSprayPosX0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #24460#27969#36947#38283#22987'X'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 2
        end
        object StaticText28: TStaticText
          Tag = 11
          Left = 14
          Top = 70
          Width = 108
          Height = 21
          Hint = 'm_dStartSprayPosY0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #24460#27969#36947#38283#22987'Y'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 3
        end
        object StaticText31: TStaticText
          Tag = 6
          Left = 198
          Top = 82
          Width = 108
          Height = 21
          Hint = 'm_dSprayPosZ'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #22132'flux'#39640#24230'Z'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 4
        end
      end
      object GroupBox5: TGroupBox
        Left = 456
        Top = 8
        Width = 193
        Height = 209
        Caption = #20986#26009#20998#37197#27969#36947
        TabOrder = 3
        object btnLLCGo: TSpeedButton
          Left = 128
          Top = 22
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLLCGoClick
        end
        object SpeedButton24: TSpeedButton
          Tag = 1
          Left = 128
          Top = 51
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLLCGoClick
        end
        object SpeedButton27: TSpeedButton
          Tag = 33
          Left = 3
          Top = 144
          Width = 94
          Height = 57
          Hint = '78'
          Caption = #27773#32568'('#19978'/'#19979')'
          OnClick = btnSimpleIOClick
        end
        object SpeedButton69: TSpeedButton
          Tag = 32
          Left = 101
          Top = 144
          Width = 89
          Height = 57
          Hint = '78'
          Caption = #27969#36947'('#21205'/'#27490')'
          OnClick = btnSimpleIOClick
        end
        object btnCheckCCD: TSpeedButton
          Tag = 74
          Left = 14
          Top = 83
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #27298#26597#20301#32622
          OnClick = btnCheckCCDClick
        end
        object StaticText35: TStaticText
          Tag = 12
          Left = 13
          Top = 55
          Width = 108
          Height = 21
          Hint = 'm_dRightLaneChangerSprayPos0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #21069#27969#36947#20301#32622
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
        object StaticText36: TStaticText
          Tag = 12
          Left = 13
          Top = 26
          Width = 108
          Height = 21
          Hint = 'm_dRightLaneChangerSprayPos1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #24460#27969#36947#20301#32622
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 1
        end
      end
      object GroupBox8: TGroupBox
        Left = 656
        Top = 8
        Width = 193
        Height = 281
        Caption = #25490#20986#20998#37197#27969#36947
        TabOrder = 4
        object SpeedButton53: TSpeedButton
          Tag = 2
          Left = 128
          Top = 22
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLLCGoClick
        end
        object SpeedButton54: TSpeedButton
          Tag = 3
          Left = 128
          Top = 51
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLLCGoClick
        end
        object SpeedButton55: TSpeedButton
          Tag = 4
          Left = 128
          Top = 80
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLLCGoClick
        end
        object SpeedButton56: TSpeedButton
          Tag = 5
          Left = 128
          Top = 109
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLLCGoClick
        end
        object SpeedButton57: TSpeedButton
          Tag = 6
          Left = 128
          Top = 138
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLLCGoClick
        end
        object SpeedButton58: TSpeedButton
          Tag = 7
          Left = 128
          Top = 167
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnLLCGoClick
        end
        object btnRLCBusher: TSpeedButton
          Tag = 34
          Left = 13
          Top = 207
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #20986#26009#25512#26751'('#20280'\'#32302')'
          OnClick = btnRLCBusherClick
        end
        object StaticText22: TStaticText
          Tag = 12
          Left = 13
          Top = 26
          Width = 108
          Height = 21
          Hint = 'm_dConveyerPos0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25490#20986#20301#32622' (1)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
        object StaticText4: TStaticText
          Tag = 12
          Left = 13
          Top = 55
          Width = 108
          Height = 21
          Hint = 'm_dConveyerPos1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25490#20986#20301#32622' (2)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 1
        end
        object StaticText9: TStaticText
          Tag = 12
          Left = 13
          Top = 84
          Width = 108
          Height = 21
          Hint = 'm_dConveyerPos2'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25490#20986#20301#32622' (3)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 2
        end
        object StaticText29: TStaticText
          Tag = 12
          Left = 13
          Top = 113
          Width = 108
          Height = 21
          Hint = 'm_dConveyerPos3'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25490#20986#20301#32622' (4)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 3
        end
        object StaticText14: TStaticText
          Tag = 12
          Left = 13
          Top = 142
          Width = 108
          Height = 21
          Hint = 'm_dConveyerPos4'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #25490#20986#20301#32622' (5)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 4
        end
        object StaticText33: TStaticText
          Tag = 12
          Left = 13
          Top = 171
          Width = 108
          Height = 21
          Hint = 'm_dNGMagPos'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = 'Mgz. '#20301#32622
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 5
        end
      end
      object GroupBox9: TGroupBox
        Left = 656
        Top = 297
        Width = 193
        Height = 144
        Caption = 'NG Magazine'
        TabOrder = 5
        object btnMGZGo: TSpeedButton
          Left = 128
          Top = 20
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnMGZGoClick
        end
        object btnMGZDown1Step: TSpeedButton
          Tag = 74
          Left = 13
          Top = 55
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #19979#19968#26684
          OnClick = btnMGZDown1StepClick
        end
        object StaticText13: TStaticText
          Tag = 9
          Left = 13
          Top = 23
          Width = 108
          Height = 21
          Hint = 'm_dMgzStartPos'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #31532#19968#29255#20301#32622
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Manual mode'
      ImageIndex = 1
      object GroupBox4: TGroupBox
        Left = 8
        Top = 8
        Width = 193
        Height = 241
        Caption = 'Weight Scale'
        TabOrder = 0
        object SpeedButton28: TSpeedButton
          Tag = 2
          Left = 128
          Top = 19
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPXGoClick
        end
        object SpeedButton29: TSpeedButton
          Tag = 2
          Left = 128
          Top = 48
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPYGoClick
        end
        object SpeedButton30: TSpeedButton
          Tag = 1
          Left = 128
          Top = 77
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPZGoClick
        end
        object btnAutoStartFluxScaleSpray: TSpeedButton
          Tag = 74
          Left = 11
          Top = 176
          Width = 137
          Height = 57
          Hint = '78'
          Caption = '(F)Weight Scale'#21205#20316
          OnClick = btnAutoStartFluxScaleSprayClick
        end
        object SpeedButton66: TSpeedButton
          Tag = 74
          Left = 11
          Top = 112
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #22132'Flux ('#38283'\'#38364')'
          OnClick = btnStartFluxClick
        end
        object StaticText44: TStaticText
          Tag = 7
          Left = 13
          Top = 22
          Width = 108
          Height = 21
          Hint = 'm_dScaleSprayPosX0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = 'F'#31204#37325#20301#32622' (X)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
        object StaticText46: TStaticText
          Tag = 11
          Left = 13
          Top = 51
          Width = 108
          Height = 21
          Hint = 'm_dScaleSprayPosY0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = 'F'#31204#37325#20301#32622' (Y)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 1
        end
        object StaticText50: TStaticText
          Tag = 6
          Left = 13
          Top = 80
          Width = 108
          Height = 21
          Hint = 'm_dScaleSprayPosZ0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = 'F'#31204#37325#20301#32622' (Z)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 2
        end
      end
      object GroupBox7: TGroupBox
        Left = 8
        Top = 256
        Width = 193
        Height = 241
        Caption = 'Clean Sprayer'
        TabOrder = 1
        object SpeedButton31: TSpeedButton
          Tag = 3
          Left = 128
          Top = 19
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPXGoClick
        end
        object SpeedButton33: TSpeedButton
          Tag = 3
          Left = 128
          Top = 48
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPYGoClick
        end
        object SpeedButton34: TSpeedButton
          Tag = 2
          Left = 128
          Top = 77
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPZGoClick
        end
        object btnAutoStartWaterScaleSpray: TSpeedButton
          Tag = 74
          Left = 11
          Top = 176
          Width = 137
          Height = 57
          Hint = '78'
          Caption = '(W)Weight Scale'#21205#20316
          OnClick = btnAutoStartWaterScaleSprayClick
        end
        object btnStartWater: TSpeedButton
          Tag = 74
          Left = 11
          Top = 111
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #22132'Wather ('#38283'\'#38364')'
          OnClick = btnStartWaterClick
        end
        object StaticText76: TStaticText
          Tag = 7
          Left = 13
          Top = 22
          Width = 108
          Height = 21
          Hint = 'm_dScaleSprayPosX1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = 'W'#31204#37325#20301#32622' (X)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
        object StaticText78: TStaticText
          Tag = 11
          Left = 13
          Top = 51
          Width = 108
          Height = 21
          Hint = 'm_dScaleSprayPosY1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = 'W'#31204#37325#20301#32622' (Y)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 1
        end
        object StaticText80: TStaticText
          Tag = 6
          Left = 13
          Top = 80
          Width = 108
          Height = 21
          Hint = 'm_dScaleSprayPosZ1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = 'W'#31204#37325#20301#32622' (Z)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 2
        end
      end
      object GroupBox6: TGroupBox
        Left = 216
        Top = 8
        Width = 329
        Height = 489
        Caption = 'Clean Sprayer Lane'
        TabOrder = 2
        object SpeedButton41: TSpeedButton
          Tag = 2
          Left = 12
          Top = 299
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #28165#27927#36317#38626'('#27491'X)'
          OnClick = btnRelMoveSPXClick
        end
        object SpeedButton42: TSpeedButton
          Tag = 3
          Left = 160
          Top = 299
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #28165#27927#36317#38626'('#36000'X)'
          OnClick = btnRelMoveSPXClick
        end
        object SpeedButton43: TSpeedButton
          Tag = 4
          Left = 128
          Top = 19
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPXGoClick
        end
        object SpeedButton44: TSpeedButton
          Tag = 4
          Left = 128
          Top = 48
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPYGoClick
        end
        object SpeedButton45: TSpeedButton
          Tag = 5
          Left = 128
          Top = 77
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPXGoClick
        end
        object SpeedButton46: TSpeedButton
          Tag = 5
          Left = 128
          Top = 106
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPYGoClick
        end
        object SpeedButton47: TSpeedButton
          Tag = 6
          Left = 128
          Top = 135
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPXGoClick
        end
        object SpeedButton48: TSpeedButton
          Tag = 6
          Left = 128
          Top = 164
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPYGoClick
        end
        object SpeedButton49: TSpeedButton
          Tag = 7
          Left = 128
          Top = 193
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPXGoClick
        end
        object SpeedButton50: TSpeedButton
          Tag = 7
          Left = 128
          Top = 222
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPYGoClick
        end
        object SpeedButton51: TSpeedButton
          Tag = 3
          Left = 128
          Top = 252
          Width = 41
          Height = 28
          Caption = 'GO!'
          OnClick = btnSPZGoClick
        end
        object SpeedButton52: TSpeedButton
          Tag = 74
          Left = 180
          Top = 107
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #22132'Wather ('#38283'\'#38364')'
          OnClick = btnStartWaterClick
        end
        object btnAutoStartCleanSpray: TSpeedButton
          Tag = 74
          Left = 12
          Top = 395
          Width = 137
          Height = 57
          Hint = '78'
          Caption = #33258#21205#28165#27927#21205#20316
          OnClick = btnAutoStartCleanSprayClick
        end
        object StaticText2: TStaticText
          Tag = 7
          Left = 13
          Top = 21
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosX0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (X1)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 0
        end
        object StaticText7: TStaticText
          Tag = 11
          Left = 13
          Top = 50
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosY0'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (Y1)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 1
        end
        object StaticText62: TStaticText
          Tag = 7
          Left = 13
          Top = 79
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosX1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (X2)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 2
        end
        object StaticText64: TStaticText
          Tag = 11
          Left = 13
          Top = 108
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosY1'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (Y2)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 3
        end
        object StaticText66: TStaticText
          Tag = 7
          Left = 13
          Top = 137
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosX2'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (X3)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 4
        end
        object StaticText68: TStaticText
          Tag = 11
          Left = 13
          Top = 166
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosY2'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (Y3)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 5
        end
        object StaticText70: TStaticText
          Tag = 7
          Left = 13
          Top = 195
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosX3'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (X4)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 6
        end
        object StaticText72: TStaticText
          Tag = 11
          Left = 13
          Top = 224
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosY3'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (Y4)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 7
        end
        object StaticText90: TStaticText
          Tag = 6
          Left = 13
          Top = 256
          Width = 108
          Height = 21
          Hint = 'm_dCleanSprayPosZ'
          Alignment = taRightJustify
          AutoSize = False
          BevelInner = bvSpace
          BevelKind = bkSoft
          BevelOuter = bvNone
          BorderStyle = sbsSingle
          Caption = #28165#28500#20301#32622' (Z)'
          Color = clSkyBlue
          ParentColor = False
          TabOrder = 8
        end
      end
    end
  end
  object BitBtn1: TBitBtn
    Left = 914
    Top = 584
    Width = 113
    Height = 57
    TabOrder = 1
    Kind = bkClose
  end
end
