object MainForm: TMainForm
  Left = 0
  Top = 0
  Margins.Left = 6
  Margins.Top = 6
  Margins.Right = 6
  Margins.Bottom = 6
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = '551004 '#1055#1077#1076#1100#1082#1086' '#1042#1083#1072#1076#1080#1089#1083#1072#1074' Lab1.1'
  ClientHeight = 690
  ClientWidth = 1324
  Color = clBtnFace
  Constraints.MaxHeight = 800
  Constraints.MaxWidth = 1350
  Constraints.MinHeight = 760
  Constraints.MinWidth = 1350
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -24
  Font.Name = 'Segoe UI'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  Position = poDesktopCenter
  Visible = True
  ShowInTaskBar = True
  PixelsPerInch = 192
  TextHeight = 32
  object TaskLabel: TLabel
    Left = 31
    Top = 27
    Width = 1130
    Height = 100
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    AutoSize = False
    BiDiMode = bdLeftToRight
    Caption = 
      #1055#1088#1086#1075#1088#1072#1084#1084#1072' '#1087#1086#1079#1074#1086#1083#1103#1077#1090' '#1074#1074#1077#1089#1090#1080' '#1076#1074#1072' '#1087#1086#1083#1086#1078#1080#1090#1077#1083#1100#1085#1099#1093' '#1095#1080#1089#1083#1072' '#1080' '#1087#1086#1082#1072#1079#1099#1074#1072#1077#1090',' +
      ' '#1095#1090#1086' '#1089#1088#1077#1076#1085#1077#1077' '#1072#1088#1080#1092#1084#1077#1090#1080#1095#1077#1089#1082#1086#1077' '#1101#1090#1080#1093' '#1095#1080#1089#1077#1083' '#1085#1077' '#1084#1077#1085#1100#1096#1077' '#1080#1093' '#1089#1088#1077#1076#1085#1077#1075#1086' '#1075#1077#1086 +
      #1084#1077#1090#1088#1080#1095#1077#1089#1082#1086#1075#1086'.'
    Constraints.MaxHeight = 100
    Constraints.MaxWidth = 1130
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Segoe UI'
    Font.Style = [fsBold]
    ParentBiDiMode = False
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    WordWrap = True
    StyleName = 'Windows'
  end
  object NumberOneLabel: TLabel
    Left = 31
    Top = 180
    Width = 256
    Height = 32
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1087#1077#1088#1074#1086#1077' '#1095#1080#1089#1083#1086':'
  end
  object NumberTwoLabel: TLabel
    Left = 576
    Top = 180
    Width = 253
    Height = 32
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1074#1090#1086#1088#1086#1077' '#1095#1080#1089#1083#1086':'
  end
  object AnswerLabel: TLabel
    Left = 31
    Top = 488
    Width = 9
    Height = 45
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object NumberOneEdit: TEdit
    Left = 31
    Top = 244
    Width = 242
    Height = 40
    Hint = #1055#1077#1088#1074#1086#1077' '#1095#1080#1089#1083#1086
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    TabOrder = 0
    TextHint = #1055#1077#1088#1074#1086#1077' '#1095#1080#1089#1083#1086
    OnChange = NumberOneEditChange
    OnKeyPress = NumberOneEditKeyPress
  end
  object ResultButton: TButton
    Left = 31
    Top = 371
    Width = 209
    Height = 49
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
    Enabled = False
    TabOrder = 2
    OnClick = ResultButtonClick
  end
  object NumberTwoEdit: TEdit
    Left = 576
    Top = 244
    Width = 242
    Height = 40
    Hint = #1042#1090#1086#1088#1086#1077' '#1095#1080#1089#1083#1086
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    TabOrder = 1
    TextHint = #1042#1090#1086#1088#1086#1077' '#1095#1080#1089#1083#1086
    OnChange = NumberTwoEditChange
    OnKeyPress = NumberTwoEditKeyPress
  end
  object MainMenu1: TMainMenu
    Left = 1168
    Top = 424
    object FileTab: TMenuItem
      Caption = #1060#1072#1081#1083
      object OpenTab: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        ShortCut = 16463
        OnClick = OpenTabClick
      end
      object SaveTab: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        ShortCut = 16467
      end
      object Separator1: TMenuItem
        Caption = '-'
      end
      object LeaveTab: TMenuItem
        Caption = #1042#1099#1081#1090#1080
        OnClick = LeaveTabClick
      end
    end
    object InstructionTab: TMenuItem
      Caption = #1048#1085#1089#1090#1088#1091#1082#1094#1080#1103
    end
    object AboutDeveloperTab: TMenuItem
      Caption = #1054' '#1056#1072#1079#1088#1072#1073#1086#1090#1095#1080#1082#1077
      OnClick = AboutDeveloperTabClick
    end
  end
  object OpenTextFileDialog1: TOpenTextFileDialog
    Left = 1168
    Top = 200
  end
  object SaveTextFileDialog1: TSaveTextFileDialog
    Left = 1168
    Top = 312
  end
end
