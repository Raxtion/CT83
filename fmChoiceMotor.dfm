object frmChoiceMotor: TfrmChoiceMotor
  Left = 918
  Top = 190
  BorderStyle = bsDialog
  BorderWidth = 5
  Caption = #36984#25799#39340#36948
  ClientHeight = 535
  ClientWidth = 432
  Color = 13430215
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #26032#32048#26126#39636
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 16
  object BitBtn1: TBitBtn
    Tag = 3
    Left = 120
    Top = 464
    Width = 185
    Height = 57
    TabOrder = 0
    Kind = bkClose
  end
  object BitBtn3: TBitBtn
    Tag = 12
    Left = 16
    Top = 336
    Width = 185
    Height = 65
    Caption = 'RIGHT LANE CHANGER'
    ModalResult = 1
    TabOrder = 1
    OnClick = btnPickAxisClick
  end
  object BitBtn4: TBitBtn
    Tag = 8
    Left = 16
    Top = 256
    Width = 185
    Height = 65
    Caption = 'CCD X  '
    ModalResult = 1
    TabOrder = 2
    OnClick = btnPickAxisClick
  end
  object BitBtn5: TBitBtn
    Tag = 9
    Left = 224
    Top = 256
    Width = 185
    Height = 65
    Caption = 'MAGAZINE Z'
    ModalResult = 1
    TabOrder = 3
    OnClick = btnPickAxisClick
  end
  object BitBtn6: TBitBtn
    Tag = 11
    Left = 224
    Top = 96
    Width = 185
    Height = 65
    Caption = 'SPRAY Y'
    ModalResult = 1
    TabOrder = 4
    OnClick = btnPickAxisClick
  end
  object BitBtn7: TBitBtn
    Tag = 5
    Left = 16
    Top = 16
    Width = 185
    Height = 65
    Caption = 'LOADER Y'
    ModalResult = 1
    TabOrder = 5
    OnClick = btnPickAxisClick
  end
  object BitBtn8: TBitBtn
    Tag = 4
    Left = 16
    Top = 96
    Width = 185
    Height = 65
    Caption = 'LOADER Z'
    ModalResult = 1
    TabOrder = 6
    OnClick = btnPickAxisClick
  end
  object BitBtn9: TBitBtn
    Tag = 7
    Left = 224
    Top = 16
    Width = 185
    Height = 65
    Caption = 'SPRAY X'
    ModalResult = 1
    TabOrder = 7
    OnClick = btnPickAxisClick
  end
  object BitBtn10: TBitBtn
    Tag = 10
    Left = 16
    Top = 176
    Width = 185
    Height = 65
    Caption = 'LEFT LANE CHANGER'
    ModalResult = 1
    TabOrder = 8
    OnClick = btnPickAxisClick
  end
  object BitBtn11: TBitBtn
    Tag = 6
    Left = 224
    Top = 176
    Width = 185
    Height = 65
    Caption = 'SPRAY Z'
    ModalResult = 1
    TabOrder = 9
    OnClick = btnPickAxisClick
  end
end
