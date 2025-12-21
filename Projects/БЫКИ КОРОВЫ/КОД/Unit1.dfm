object Form1: TForm1
  Left = 0
  Top = 0
  Margins.Left = 6
  Margins.Top = 6
  Margins.Right = 6
  Margins.Bottom = 6
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Bulls and Cows (2 Players)'
  ClientHeight = 1120
  ClientWidth = 1540
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -22
  Font.Name = 'Tahoma'
  Font.Style = []
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 192
  TextHeight = 27
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 1540
    Height = 1120
    Margins.Left = 6
    Margins.Top = 6
    Margins.Right = 6
    Margins.Bottom = 6
    ActivePage = TabGame
    Align = alClient
    TabOrder = 0
    object TabGame: TTabSheet
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'Game'
      object LabelTitle: TLabel
        Left = 32
        Top = 24
        Width = 448
        Height = 36
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'Bulls and Cows (Two Players)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -30
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object LabelInfo: TLabel
        Left = 32
        Top = 80
        Width = 1440
        Height = 36
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        AutoSize = False
        Caption = 'Info'
      end
      object LabelP1: TLabel
        Left = 32
        Top = 144
        Width = 208
        Height = 27
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'Player 1 secret word:'
      end
      object LabelP2: TLabel
        Left = 32
        Top = 224
        Width = 208
        Height = 27
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'Player 2 secret word:'
      end
      object LabelTurn: TLabel
        Left = 32
        Top = 304
        Width = 141
        Height = 27
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'Current turn: -'
      end
      object EditSecretP1: TEdit
        Left = 320
        Top = 136
        Width = 440
        Height = 35
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        TabOrder = 0
      end
      object BtnSetP1: TButton
        Left = 792
        Top = 132
        Width = 260
        Height = 50
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'Set P1 Secret'
        TabOrder = 1
        OnClick = BtnSetP1Click
      end
      object EditSecretP2: TEdit
        Left = 320
        Top = 216
        Width = 440
        Height = 35
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        TabOrder = 2
      end
      object BtnSetP2: TButton
        Left = 792
        Top = 212
        Width = 260
        Height = 50
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'Set P2 Secret'
        TabOrder = 3
        OnClick = BtnSetP2Click
      end
      object EditGuess: TEdit
        Left = 32
        Top = 352
        Width = 440
        Height = 35
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        TabOrder = 4
      end
      object BtnGuess: TButton
        Left = 496
        Top = 348
        Width = 240
        Height = 50
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'Make Guess'
        TabOrder = 5
        OnClick = BtnGuessClick
      end
      object BtnSurrenderP1: TButton
        Left = 768
        Top = 348
        Width = 240
        Height = 50
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'P1 Surrender'
        TabOrder = 6
        OnClick = BtnSurrenderP1Click
      end
      object BtnSurrenderP2: TButton
        Left = 1024
        Top = 348
        Width = 240
        Height = 50
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'P2 Surrender'
        TabOrder = 7
        OnClick = BtnSurrenderP2Click
      end
      object BtnReset: TButton
        Left = 1280
        Top = 348
        Width = 200
        Height = 50
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Caption = 'Reset'
        TabOrder = 8
        OnClick = BtnResetClick
      end
      object StringGrid1: TStringGrid
        Left = 32
        Top = 432
        Width = 1448
        Height = 600
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        ColCount = 6
        DefaultColWidth = 220
        DefaultRowHeight = 48
        FixedCols = 0
        RowCount = 2
        TabOrder = 9
      end
    end
    object TabRules: TTabSheet
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Caption = 'Rules'
      object MemoRules: TMemo
        Left = 0
        Top = 0
        Width = 1524
        Height = 1065
        Margins.Left = 6
        Margins.Top = 6
        Margins.Right = 6
        Margins.Bottom = 6
        Align = alClient
        Lines.Strings = (
          '')
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
end
