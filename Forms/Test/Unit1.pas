Unit Unit1;

Interface

Uses
    Winapi.Windows,
    Winapi.Messages,
    System.SysUtils,
    System.Variants,
    System.Classes,
    Vcl.Graphics,
    Vcl.Controls,
    Vcl.Forms,
    Vcl.Dialogs,
    Unit2,
    Unit3,
    Vcl.StdCtrls,
    Vcl.Menus, Vcl.ExtDlgs, IdBaseComponent, IdMessage;

Type
    ERROR_CODES = (NO_ERROROS,
                   NUMBER_NOT_VALID,
                   FILE_NOT_EXIST,
                   FILE_CLOSE_TO_READ,
                   FILE_CLOSE_TO_WRITE);
    TMainForm = Class(TForm)
    NumberOneEdit: TEdit;
    ResultButton: TButton;
    MainMenu1: TMainMenu;
    FileTab: TMenuItem;
    OpenTab: TMenuItem;
    SaveTab: TMenuItem;
    Separator1: TMenuItem;
    LeaveTab: TMenuItem;
    InstructionTab: TMenuItem;
    AboutDeveloperTab: TMenuItem;
    OpenTextFileDialog1: TOpenTextFileDialog;
    SaveTextFileDialog1: TSaveTextFileDialog;
    TaskLabel: TLabel;
    NumberOneLabel: TLabel;
    NumberTwoEdit: TEdit;
    NumberTwoLabel: TLabel;
    AnswerLabel: TLabel;
    procedure LeaveTabClick(Sender: TObject);
    procedure NumberOneEditKeyPress(Sender: TObject; var Key: Char);
    procedure NumberOneEditChange(Sender: TObject);
    procedure NumberTwoEditKeyPress(Sender: TObject; var Key: Char);
    procedure NumberTwoEditChange(Sender: TObject);
    procedure AboutDeveloperTabClick(Sender: TObject);
    procedure ResultButtonClick(Sender: TObject);
    procedure OpenTabClick(Sender: TObject);
    //procedure NumberOneEditKeyDown(Sender: TObject; var Key: Word;
   //   Shift: TShiftState);

        //Procedure Button1Click(Sender: TObject);
    Private
        { Private declarations }
    Public
        { Public declarations }
    End;

Const
    BACKSPACE = #8;
    //ENTER = #13;
    NONE_CHAR = #0;
    DIGITS = ['0'..'9'];
    ERROR_TEXT: Array [ERROR_CODES] Of String = ('',
                                                 'Строка файла имеет некорректный ввод числа.',
                                                 'Файл не найден.',
                                                 'Файл закрыть для чтения.',
                                                 'Файл закрыть для записи.');

Var
    MainForm: TMainForm;
    IsPointInFirstStringAllowed:  Boolean = True;
    IsPointInSecondStringAllowed: Boolean = True;
//    IsMinusInFirstStringAllowed:  Boolean = True;
//    IsMinusInSecondStringAllowed: Boolean = True;
    IsFirstNumberCorrect:         Boolean = False;
    IsSecondNumberCorrect:        Boolean = False;

Implementation

{$R *.dfm}

//Procedure TMainForm.Button1Click(Sender: TObject);
//Var
//    lolForm: TForm2;
//Begin
//    lolForm := TForm2.Create(Self);
//    lolForm.Label1.Caption := Edit1.Text;
//    lolForm.ShowModal;
//    lolForm.Free;
//End;

procedure TMainForm.AboutDeveloperTabClick(Sender: TObject);
Var
    AboutDeveloperForm: TAboutDeveloperForm;
begin
    AboutDeveloperForm := TAboutDeveloperForm.Create(Self);
    AboutDeveloperForm.ShowModal;
    AboutDeveloperForm.Free;
end;

procedure TMainForm.LeaveTabClick(Sender: TObject);
Var
    IsFormShouldClose: Integer;

Begin
    IsFormShouldClose := Application.MessageBox(PChar('Вы хотите выйти?'), PChar('Выход'), MB_YESNO+MB_ICONQUESTION);

    If IsFormShouldClose = mrYes Then
        Close;

End;

Function CheckStringOnEdit(TestString: String; Var IsPointAllowed{, IsMinusAllowed}: Boolean): Boolean;
Var
    FirstChar, LastChar: Char;
    IsStringReadible, IsFirstAndLastCharFine, IsPointValid: Boolean;
    I, CountOfPoints, CountOfMinuses, PointIndex: Integer;

Begin
    IsStringReadible       := False;
    IsFirstAndLastCharFine := False;
    IsPointValid           := False;

    CountOfPoints   := 0;
    PointIndex      := 0;

    If Length(TestString) = 0 Then
        IsStringReadible := False
    Else
    Begin
        FirstChar := TestString[Low(TestString)];
        LastChar  := TestString[High(TestString)];

        // Проверка строки
        IsFirstAndLastCharFine := (FirstChar in DIGITS)
                              And (LastChar in DIGITS);

        For I := Low(TestString) To High(TestString) Do
        Begin
            If TestString[I] = ',' Then
            Begin
                CountOfPoints := CountOfPoints + 1;
                PointIndex := I;
            End;
        End;

        If CountOfPoints = 0 Then
        Begin
            IsPointValid := True;
            IsPointAllowed := True;
        End;

        If (CountOfPoints = 1) And (Length(TestString) > 2)
            And (PointIndex < High(TestString))
            And (PointIndex > Low(TestString))
            And (TestString[PointIndex + 1] in DIGITS)
            And (TestString[PointIndex - 1] in DIGITS) Then
            IsPointValid := True;

        IsStringReadible := IsFirstAndLastCharFine And IsPointValid;
    End;

    CheckStringOnEdit := IsStringReadible;
End;

procedure TMainForm.NumberOneEditChange(Sender: TObject);

begin
    IsFirstNumberCorrect := CheckStringOnEdit(NumberOneEdit.Text, IsPointInFirstStringAllowed);
    ResultButton.Enabled := IsFirstNumberCorrect And IsSecondNumberCorrect;
end;

procedure TMainForm.NumberTwoEditChange(Sender: TObject);
begin
    IsSecondNumberCorrect := CheckStringOnEdit(NumberTwoEdit.Text, IsPointInSecondStringAllowed);
    ResultButton.Enabled := IsFirstNumberCorrect And IsSecondNumberCorrect;
end;

procedure TMainForm.NumberOneEditKeyPress(Sender: TObject; var Key: Char);
Var
    WrittenString: String;
    IsKeyAllowed: Boolean;

begin
    IsKeyAllowed := False;
    WrittenString := NumberOneEdit.Text;

    // Проверяем первый символ будущей строки
    If ( (Length(WrittenString) = 0) And (Key in DIGITS) ) Then
        IsKeyAllowed := True;

    // Проверяем возможные вторые символы строки
    If ( (Length(WrittenString) = 1) And ((Key in DIGITS) Or (Key = ',')) ) Then
        IsKeyAllowed := True;

    // Проверяем ввод остальных символов строки
    If ( (Length(WrittenString) > 1) And (Length(WrittenString) <= 10) And ((Key in DIGITS) Or (Key = ',')) ) Then
    Begin
        If (Key = ',') And IsPointInFirstStringAllowed Then
        Begin
            IsKeyAllowed := True;
            IsPointInFirstStringAllowed := False;
        End;

        If (Key in DIGITS) Then
            IsKeyAllowed := True;
    End;

    If Key = BACKSPACE Then
        IsKeyAllowed := True;

    If Not IsKeyAllowed Then
        Key := #0;
end;

procedure TMainForm.NumberTwoEditKeyPress(Sender: TObject; var Key: Char);
Var
    WrittenString: String;
    IsKeyAllowed: Boolean;

begin
    IsKeyAllowed := False;
    WrittenString := NumberTwoEdit.Text;

    // Проверяем первый символ будущей строки
    If ( (Length(WrittenString) = 0) And (Key in DIGITS) ) Then
        IsKeyAllowed := True;

    // Проверяем возможные вторые символы строки
    If ( (Length(WrittenString) = 1) And ((Key in DIGITS) Or (Key = ',')) ) Then
        IsKeyAllowed := True;

    // Проверяем ввод остальных символов строки
    If ( (Length(WrittenString) > 1) And (Length(WrittenString) <= 10) And ((Key in DIGITS) Or (Key = ',')) ) Then
    Begin
        If (Key = ',') And IsPointInSecondStringAllowed Then
        Begin
            IsKeyAllowed := True;
            IsPointInSecondStringAllowed := False;
        End;

        If (Key in DIGITS) Then
            IsKeyAllowed := True;
    End;

    If Key = BACKSPACE Then
        IsKeyAllowed := True;

    If Not IsKeyAllowed Then
        Key := #0;
end;

procedure TMainForm.OpenTabClick(Sender: TObject);
begin
     SaveTextFileDialog1.Execute;
end;

procedure TMainForm.ResultButtonClick(Sender: TObject);
Var
    NumberOne, NumberTwo, ArithmeticMean, GeometricMean: Double;
    AnswerString: String;

begin
    NumberOne := StrToFloat(NumberOneEdit.Text);
    NumberTwo := StrToFloat(NumberTwoEdit.Text);

    ArithmeticMean := (NumberOne + NumberTwo) / 2;
    GeometricMean := Sqrt(NumberOne * NumberTwo);

    AnswerString := 'Среднее арифметическое: ' + FloatToStr(ArithmeticMean)+ #13#10 + 'Среднее геометрическое: ' + FloatToStr(GeometricMean) + #13#10 + FloatToStr(ArithmeticMean) + ' >= ' + FloatToStr(GeometricMean);

    AnswerLabel.Caption := AnswerString;
end;

End.
