Unit Unit1;

Interface

Uses
    Winapi.Windows,
    Winapi.Messages,
    System.SysUtils,
    System.Variants,
    System.Classes,
    System.Character,
    Vcl.Graphics,
    Vcl.Controls,
    Vcl.Forms,
    Vcl.Dialogs,
    Vcl.StdCtrls,
    Vcl.Grids,
    Vcl.ComCtrls;

Type
    TGamePhase = (GpSetupP1, GpSetupP2, GpPlay, GpFinished);

    TForm1 = Class(TForm)
        PageControl1: TPageControl;
        TabGame: TTabSheet;
        TabRules: TTabSheet;
        MemoRules: TMemo;

        LabelTitle: TLabel;
        LabelInfo: TLabel;
        LabelP1: TLabel;
        LabelP2: TLabel;
        EditSecretP1: TEdit;
        EditSecretP2: TEdit;
        BtnSetP1: TButton;
        BtnSetP2: TButton;

        LabelTurn: TLabel;
        EditGuess: TEdit;
        BtnGuess: TButton;

        BtnSurrenderP1: TButton;
        BtnSurrenderP2: TButton;
        BtnReset: TButton;

        StringGrid1: TStringGrid;

        Procedure FormCreate(Sender: TObject);
        Procedure BtnSetP1Click(Sender: TObject);
        Procedure BtnSetP2Click(Sender: TObject);
        Procedure BtnGuessClick(Sender: TObject);
        Procedure BtnResetClick(Sender: TObject);
        Procedure BtnSurrenderP1Click(Sender: TObject);
        Procedure BtnSurrenderP2Click(Sender: TObject);
    Private
        Phase: TGamePhase;

        SecretP1: String;
        SecretP2: String;

        TurnPlayer: Integer; //1 or 2
        TurnNo: Integer;

        MovesP1: Integer;
        MovesP2: Integer;

        FinishedP1: Boolean;
        FinishedP2: Boolean;

        SurrenderedBy: Integer; //0 none, 1 P1, 2 P2

        Procedure InitGrid;
        Procedure ResetGame;
        Procedure UpdateUI;

        Function NormalizeWord(Const S: String): String;
        Function OnlyLetters(Const S: String): Boolean;

        Function CurrentPlayerName: String;
        Function CurrentTargetSecret: String;

        Procedure AddRow(Const PlayerName, Guess: String; Bulls, Cows: Integer; Const Note: String);
        Procedure CalcBullsCows(Const Secret, Guess: String; Out Bulls, Cows: Integer);

        Procedure MarkWinForCurrentPlayer;
        Procedure SwitchTurnSkippingFinished;
        Procedure TryFinishByBothGuessed;
        Procedure Surrender(Player: Integer);
    Public
    End;

Var
    Form1: TForm1;

Implementation

{$R *.dfm}

Procedure TForm1.FormCreate(Sender: TObject);
Begin
    InitGrid;

    MemoRules.Clear;
    MemoRules.Lines.Add('Bulls and Cows (Two Players) - Rules');
    MemoRules.Lines.Add('');
    MemoRules.Lines.Add('1) Player 1 enters a secret word and clicks "Set P1 Secret".');
    MemoRules.Lines.Add('2) Player 2 enters a secret word (same length) and clicks "Set P2 Secret".');
    MemoRules.Lines.Add('3) Players take turns guessing the opponent''s word.');
    MemoRules.Lines.Add('4) Bulls = letters in the correct position.');
    MemoRules.Lines.Add('5) Cows = total matching letters INCLUDING bulls (as in your example).');
    MemoRules.Lines.Add('6) You can surrender with the corresponding button.');
    MemoRules.Lines.Add('7) Game ends when both guessed, or when someone surrenders.');
    MemoRules.ReadOnly := True;

    ResetGame;
End;

Procedure TForm1.InitGrid;
Begin
    StringGrid1.ColCount := 6;
    StringGrid1.FixedRows := 1;
    StringGrid1.FixedCols := 0;
    StringGrid1.RowCount := 2;

    StringGrid1.Cells[0, 0] := 'Turn';
    StringGrid1.Cells[1, 0] := 'Player';
    StringGrid1.Cells[2, 0] := 'Guess';
    StringGrid1.Cells[3, 0] := 'Bulls';
    StringGrid1.Cells[4, 0] := 'Cows';
    StringGrid1.Cells[5, 0] := 'Note';

    StringGrid1.ColWidths[0] := 55;
    StringGrid1.ColWidths[1] := 70;
    StringGrid1.ColWidths[2] := 160;
    StringGrid1.ColWidths[3] := 55;
    StringGrid1.ColWidths[4] := 55;
    StringGrid1.ColWidths[5] := 170;
End;

Procedure TForm1.ResetGame;
Begin
    Phase := GpSetupP1;

    SecretP1 := '';
    SecretP2 := '';

    TurnPlayer := 1;
    TurnNo := 0;

    MovesP1 := 0;
    MovesP2 := 0;

    FinishedP1 := False;
    FinishedP2 := False;

    SurrenderedBy := 0;

    StringGrid1.RowCount := 2;

    EditSecretP1.Text := '';
    EditSecretP2.Text := '';
    EditGuess.Text := '';

    EditSecretP1.PasswordChar := '*';
    EditSecretP2.PasswordChar := '*';

    PageControl1.ActivePage := TabGame;

    UpdateUI;
End;

Function TForm1.NormalizeWord(Const S: String): String;
Begin
    Result := LowerCase(Trim(S));
End;

Function TForm1.OnlyLetters(Const S: String): Boolean;
Var
    I: Integer;
    Ch: Char;
Begin
    Result := (S <> '');
    If Not Result Then
        Exit;

    For I := 1 To Length(S) Do
    Begin
        Ch := S[I];
        //Unicode-safe: русские/английские/Ё/и т.д.
        If Not TCharacter.IsLetter(Ch) Then
            Exit(False);
    End;
End;

Function TForm1.CurrentPlayerName: String;
Begin
    If TurnPlayer = 1 Then
        Result := 'Player 1'
    Else
        Result := 'Player 2';
End;

Function TForm1.CurrentTargetSecret: String;
Begin
    If TurnPlayer = 1 Then
        Result := SecretP2
    Else
        Result := SecretP1;
End;

Procedure TForm1.UpdateUI;
Begin
    BtnSurrenderP1.Enabled := (Phase = GpPlay) And (Not FinishedP1) And (SurrenderedBy = 0);
    BtnSurrenderP2.Enabled := (Phase = GpPlay) And (Not FinishedP2) And (SurrenderedBy = 0);

    Case Phase Of
        GpSetupP1:
            Begin
                LabelInfo.Caption := 'Player 1: enter a secret word (EN/RU) and click "Set P1 Secret".';
                LabelTurn.Caption := 'Current turn: -';

                EditSecretP1.Enabled := True;
                BtnSetP1.Enabled := True;

                EditSecretP2.Enabled := False;
                BtnSetP2.Enabled := False;

                EditGuess.Enabled := False;
                BtnGuess.Enabled := False;
            End;

        GpSetupP2:
            Begin
                LabelInfo.Caption := 'Player 2: enter a secret word (same length) and click "Set P2 Secret".';
                LabelTurn.Caption := 'Current turn: -';

                EditSecretP1.Enabled := False;
                BtnSetP1.Enabled := False;

                EditSecretP2.Enabled := True;
                BtnSetP2.Enabled := True;

                EditGuess.Enabled := False;
                BtnGuess.Enabled := False;
            End;

        GpPlay:
            Begin
                LabelTurn.Caption := 'Current turn: ' + CurrentPlayerName;
                LabelInfo.Caption := Format('%s: guess opponent''s word (length %d).', [CurrentPlayerName, Length(CurrentTargetSecret)]);

                EditSecretP1.Enabled := False;
                BtnSetP1.Enabled := False;
                EditSecretP2.Enabled := False;
                BtnSetP2.Enabled := False;

                EditGuess.Enabled := True;
                BtnGuess.Enabled := True;
                EditGuess.SetFocus;
            End;

        GpFinished:
            Begin
                EditGuess.Enabled := False;
                BtnGuess.Enabled := False;

                EditSecretP1.PasswordChar := #0;
                EditSecretP2.PasswordChar := #0;

                If SurrenderedBy = 1 Then
                    LabelInfo.Caption := Format('Game over. Player 1 surrendered. Player 2 wins! (P1 moves: %d, P2 moves: %d)',
                        [MovesP1, MovesP2])
                Else
                    If SurrenderedBy = 2 Then
                        LabelInfo.Caption := Format('Game over. Player 2 surrendered. Player 1 wins! (P1 moves: %d, P2 moves: %d)',
                            [MovesP1, MovesP2])
                    Else
                    Begin
                        If MovesP1 < MovesP2 Then
                            LabelInfo.Caption := Format('Game over. Player 1 wins! (P1 moves: %d, P2 moves: %d)', [MovesP1, MovesP2])
                        Else
                            If MovesP2 < MovesP1 Then
                                LabelInfo.Caption := Format('Game over. Player 2 wins! (P1 moves: %d, P2 moves: %d)', [MovesP1, MovesP2])
                            Else
                                LabelInfo.Caption := Format('Game over. Draw! (P1 moves: %d, P2 moves: %d)', [MovesP1, MovesP2]);
                    End;

                LabelTurn.Caption := 'Current turn: -';
            End;
    End;
End;

Procedure TForm1.AddRow(Const PlayerName, Guess: String; Bulls, Cows: Integer; Const Note: String);
Var
    R: Integer;
Begin
    R := StringGrid1.RowCount;
    StringGrid1.RowCount := R + 1;

    StringGrid1.Cells[0, R - 1] := IntToStr(TurnNo);
    StringGrid1.Cells[1, R - 1] := PlayerName;
    StringGrid1.Cells[2, R - 1] := Guess;
    StringGrid1.Cells[3, R - 1] := IntToStr(Bulls);
    StringGrid1.Cells[4, R - 1] := IntToStr(Cows);
    StringGrid1.Cells[5, R - 1] := Note;
End;

Procedure TForm1.CalcBullsCows(Const Secret, Guess: String; Out Bulls, Cows: Integer);
Var
    I, J: Integer;
    UsedS, UsedG: Array Of Boolean;
Begin
    Bulls := 0;
    Cows := 0;

    If Length(Secret) <> Length(Guess) Then
        Exit;

    SetLength(UsedS, Length(Secret) + 1);
    SetLength(UsedG, Length(Guess) + 1);

    For I := 1 To Length(Secret) Do
        If Secret[I] = Guess[I] Then
        Begin
            Inc(Bulls);
            UsedS[I] := True;
            UsedG[I] := True;
        End;

    For I := 1 To Length(Guess) Do
    Begin
        If UsedG[I] Then
            Continue;

        For J := 1 To Length(Secret) Do
        Begin
            If UsedS[J] Then
                Continue;

            If Guess[I] = Secret[J] Then
            Begin
                UsedS[J] := True;
                UsedG[I] := True;
                Inc(Cows);
                Break;
            End;
        End;
    End;

    Cows := Cows + Bulls;
End;

Procedure TForm1.MarkWinForCurrentPlayer;
Begin
    If TurnPlayer = 1 Then
        FinishedP1 := True
    Else
        FinishedP2 := True;
End;

Procedure TForm1.SwitchTurnSkippingFinished;
Begin
    If TurnPlayer = 1 Then
        TurnPlayer := 2
    Else
        TurnPlayer := 1;

    If (TurnPlayer = 1) And FinishedP1 Then
        TurnPlayer := 2
    Else
        If (TurnPlayer = 2) And FinishedP2 Then
            TurnPlayer := 1;
End;

Procedure TForm1.TryFinishByBothGuessed;
Begin
    If FinishedP1 And FinishedP2 Then
    Begin
        Phase := GpFinished;
        UpdateUI;
    End;
End;

Procedure TForm1.Surrender(Player: Integer);
Begin
    If Phase <> GpPlay Then
        Exit;

    Inc(TurnNo);
    SurrenderedBy := Player;

    If Player = 1 Then
        AddRow('Player 1', '-', 0, 0, 'Surrender')
    Else
        AddRow('Player 2', '-', 0, 0, 'Surrender');

    Phase := GpFinished;
    UpdateUI;
End;

Procedure TForm1.BtnSetP1Click(Sender: TObject);
Var
    S: String;
Begin
    If Phase <> GpSetupP1 Then
        Exit;

    S := NormalizeWord(EditSecretP1.Text);
    If Not OnlyLetters(S) Then
    Begin
        ShowMessage('Player 1 secret must contain letters only (EN/RU).');
        Exit;
    End;

    SecretP1 := S;
    Phase := GpSetupP2;
    UpdateUI;
End;

Procedure TForm1.BtnSetP2Click(Sender: TObject);
Var
    S: String;
Begin
    If Phase <> GpSetupP2 Then
        Exit;

    S := NormalizeWord(EditSecretP2.Text);
    If Not OnlyLetters(S) Then
    Begin
        ShowMessage('Player 2 secret must contain letters only (EN/RU).');
        Exit;
    End;

    If Length(SecretP1) <> Length(S) Then
    Begin
        ShowMessage(Format('Both secrets must have the same length. Player 1 length = %d.', [Length(SecretP1)]));
        Exit;
    End;

    SecretP2 := S;

    Phase := GpPlay;
    TurnPlayer := 1;
    TurnNo := 0;

    UpdateUI;
End;

Procedure TForm1.BtnGuessClick(Sender: TObject);
Var
    G, Target: String;
    Bulls, Cows: Integer;
    Note: String;
Begin
    If Phase <> GpPlay Then
        Exit;

    If (TurnPlayer = 1) And FinishedP1 Then
    Begin
        SwitchTurnSkippingFinished;
        UpdateUI;
        Exit;
    End;

    If (TurnPlayer = 2) And FinishedP2 Then
    Begin
        SwitchTurnSkippingFinished;
        UpdateUI;
        Exit;
    End;

    G := NormalizeWord(EditGuess.Text);
    If Not OnlyLetters(G) Then
    Begin
        ShowMessage('Guess must contain letters only (EN/RU).');
        Exit;
    End;

    Target := CurrentTargetSecret;
    If Length(G) <> Length(Target) Then
    Begin
        ShowMessage(Format('Guess length must be %d.', [Length(Target)]));
        Exit;
    End;

    Inc(TurnNo);
    CalcBullsCows(Target, G, Bulls, Cows);

    Note := '';
    If Bulls = Length(Target) Then
    Begin
        Note := 'Guessed!';
        MarkWinForCurrentPlayer;
    End;

    If TurnPlayer = 1 Then
        Inc(MovesP1)
    Else
        Inc(MovesP2);

    AddRow(CurrentPlayerName, G, Bulls, Cows, Note);

    //If both guessed -> end
    If FinishedP1 And FinishedP2 Then
    Begin
        Phase := GpFinished;
        UpdateUI;
        Exit;
    End;

    //Next turn
    SwitchTurnSkippingFinished;
    EditGuess.SelectAll;
    UpdateUI;

    TryFinishByBothGuessed;
End;

Procedure TForm1.BtnSurrenderP1Click(Sender: TObject);
Begin
    Surrender(1);
End;

Procedure TForm1.BtnSurrenderP2Click(Sender: TObject);
Begin
    Surrender(2);
End;

Procedure TForm1.BtnResetClick(Sender: TObject);
Begin
    ResetGame;
End;

End.
