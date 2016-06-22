object fmOption: TfmOption
  Left = 384
  Top = 227
  BorderStyle = bsDialog
  Caption = 'fmOption'
  ClientHeight = 414
  ClientWidth = 508
  Color = 13430215
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 16
  object BitBtn1: TBitBtn
    Left = 24
    Top = 352
    Width = 129
    Height = 41
    TabOrder = 0
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 344
    Top = 360
    Width = 129
    Height = 41
    TabOrder = 1
    Kind = bkCancel
  end
  object GroupBox1: TGroupBox
    Left = 16
    Top = 16
    Width = 465
    Height = 225
    Caption = #21855#29992#21151#33021
    TabOrder = 2
    object m_bIsRailLoad: TCheckBox
      Left = 24
      Top = 32
      Width = 161
      Height = 17
      Caption = #20351#29992#27969#36947#20837#26009
      TabOrder = 0
    end
    object m_bReadVenderID: TCheckBox
      Left = 24
      Top = 64
      Width = 161
      Height = 17
      Caption = #35712#21462#22522#26495' 2D Code'
      TabOrder = 1
    end
    object m_bUseFMCCD: TCheckBox
      Left = 24
      Top = 88
      Width = 161
      Height = 17
      Caption = #21855#29992#22522#26495#23450#20301
      TabOrder = 2
    end
    object m_bUseMapCCD: TCheckBox
      Left = 24
      Top = 112
      Width = 161
      Height = 17
      Caption = #21855#29992#40670#37327#21151#33021
      TabOrder = 3
    end
    object m_bUseLaserMark: TCheckBox
      Left = 24
      Top = 136
      Width = 161
      Height = 17
      Caption = #21855#29992#38647#23556#21051#21360
      TabOrder = 4
    end
    object m_bUseLaserCodeReader: TCheckBox
      Left = 24
      Top = 176
      Width = 161
      Height = 17
      Caption = #21855#29992#21051#21360#23436#27298#26597
      TabOrder = 5
    end
    object m_bUseCover: TCheckBox
      Left = 256
      Top = 24
      Width = 161
      Height = 17
      Caption = #20351#29992#19978#33995#26495
      TabOrder = 6
    end
    object m_bUseBoat: TCheckBox
      Left = 256
      Top = 48
      Width = 161
      Height = 17
      Caption = #20351#29992'BOAT'
      TabOrder = 7
    end
    object m_bEAPCoverControl: TCheckBox
      Left = 256
      Top = 80
      Width = 161
      Height = 17
      Caption = #19978#33995#26495#28165#27927#31649#25511
      TabOrder = 8
    end
    object m_bEAPBoatControl: TCheckBox
      Left = 256
      Top = 104
      Width = 161
      Height = 17
      Caption = 'BOAT'#28165#27927#31649#25511
      TabOrder = 9
    end
    object m_bIsSingleSubstrate: TCheckBox
      Left = 256
      Top = 176
      Width = 161
      Height = 17
      Caption = #19968#20491'BOAT'#19968#26781#22522#26495
      TabOrder = 10
    end
    object m_bUpLoadMapFile: TCheckBox
      Left = 256
      Top = 136
      Width = 177
      Height = 17
      Caption = #19978#20659' MAP '#27284#26696
      TabOrder = 11
    end
  end
  object m_nUseTable: TRadioGroup
    Left = 16
    Top = 248
    Width = 137
    Height = 89
    Caption = #20316#26989#24179#21488
    ItemIndex = 2
    Items.Strings = (
      #21069#24179#21488
      #24460#24179#21488
      #21069#24460#37117#35201)
    TabOrder = 3
  end
end
