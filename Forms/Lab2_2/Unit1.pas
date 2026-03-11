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
    Vcl.Menus,
    Vcl.StdCtrls,
    Vcl.ExtCtrls,
    Vcl.ExtDlgs,
    Vcl.Imaging.Pngimage,
    Unit2,
    Vcl.Grids,
    Clipbrd;

Type
    TArrayOI = Array Of Integer;
    TArrayOS = Array Of String;
    ERROR_CODES = (
        NO_ERRORS,
        NUMBER_NOT_VALID,
        FILE_NOT_EXIST,
        FILE_NOT_TXT,
        FILE_CLOSE_TO_READ,
        FILE_CLOSE_TO_WRITE,
        FILE_IS_EMPTY,
        FILE_DATA_NOT_CORRECT,
        FILE_ASSIGN_ERROR,
        FILE_DATA_NOT_SAVED);

    TMainForm = Class(TForm)
        MainMenu1: TMainMenu;
        FileTab: TMenuItem;
        OpenTab: TMenuItem;
        SaveTab: TMenuItem;
        Separator1: TMenuItem;
        LeaveTab: TMenuItem;
        InstructionTab: TMenuItem;
        AboutDeveloperTab: TMenuItem;
        ResultButton: TButton;
        NumberOneEdit: TEdit;
        NumberOneLabel: TLabel;
        TaskLabel: TLabel;
        OpenTextFileDialog1: TOpenTextFileDialog;
        SaveTextFileDialog1: TSaveTextFileDialog;
        StringGridA: TStringGrid;
        LabelResult: TLabel;
    Procedure NumberOneEditKeyPress(Sender: TObject; Var Key: Char);
    procedure InstructionTabClick(Sender: TObject);
    procedure AboutDeveloperTabClick(Sender: TObject);
    procedure NumberOneEditChange(Sender: TObject);
    procedure SaveTabClick(Sender: TObject);
    procedure ResultButtonClick(Sender: TObject);
    procedure OpenTabClick(Sender: TObject);
    procedure LeaveTabClick(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);

    Private
        { Private declarations }
    Public
        { Public declarations }
    End;

    Function IsFileText(FilePath: String): Boolean;
    Function IsFileNotEmpty(Var InputFile: TextFile): Boolean;
    Function CanRead(Var InputFile: TextFile): Boolean;
    Function CanWrite(Var FileVar: TextFile): Boolean;
    Function CheckMyFile(Var InputFile: TextFile; FilePath: String; IsForWriteToFile: Boolean): ERROR_CODES;
    Function SaveDataToFile(): ERROR_CODES;
    Function LeaveFromProgram(CanClose: Boolean): Boolean;
    Function WriteDataToFile(Var SavedFile: TextFile): ERROR_CODES;
    Function ReadAndWriteOutFileData(Var ReadedFile: TextFile): ERROR_CODES;
    Function CheckEditStringOnValidity(TestString: String): Boolean;
    Procedure SetStringGridACorrect();
    Procedure NumberTheFirstCol(StringGrid: TStringGrid);
    Function CheckGridOnValidity(StringGrid: TStringGrid): Boolean;
    Function GetStringArrayFromGrid(StringGrid: TStringGrid): TArrayOS;
    Function ChangeStringArrayToIntArray(StringArray: TArrayOS): TArrayOI;
    Procedure FixStringOnInvalidValue();
    Procedure FixStringGridOnIncorrecValue();
    Function DiscoverIsNumberPrime(Number: Integer): Boolean;
    Function GetPrimeNumber(InputNum: Integer): Integer;
    Function GetMersenneNumbers(N: Integer): TArrayOI;
    Function FillGridByArrayData(FromArray: TArrayOI; ToGrid: TStringGrid): ERROR_CODES;

Const
    MAX_EDIT_NUMBER: Integer = 999_999;
    MIN_EDIT_NUMBER: Integer = 1;
    BACKSPACE = #8;
    NONE_CHAR = #0;
    DIGITS = ['0' .. '9'];
    ERROR_TEXT: Array [ERROR_CODES] Of String = (
        '',
        'Строка файла имеет некорректный ввод числа.', 'Файл не найден.',
        'Файл не соответствует формату .txt', 'Файл закрыт для чтения.',
        'Файл закрыт для записи либо во время записи возникли проблемы.',
        'Файл пустой.',
        'Файл имеет некоректный формат данных.',
        'Ошибка присоединения файла.',
        'Не удалось успешно сохранить данные в файл.');

Var
    MainForm: TMainForm;
    IsFirstNumberCorrect: Boolean = False;
    IsPointInFirstStringAllowed: Boolean = True;
    IsDataSaved: Boolean = True;
    StrGridACol: LongInt = 0;
    StrGridARow: LongInt = 1;

Implementation

{$R *.dfm}

Function DiscoverIsNumberPrime(Number: Integer): Boolean;

Var
    I, NumberP1: Integer;
    IsShouldNotStop: Boolean;

Begin

    I := 2;
    numberP1 := Number - 1;
    IsShouldNotStop := True;
    DiscoverIsNumberPrime := False;

    For I := 2 To NumberP1 Do
    Begin
        If (Number Mod I = 0) And (IsShouldNotStop) Then
        Begin
            DiscoverIsNumberPrime := False;
            IsShouldNotStop := False;
        End
        Else
            If IsShouldNotStop Then
                DiscoverIsNumberPrime := True;
    End;

    If Number = 2 Then
        DiscoverIsNumberPrime := True;

End;

Function GetPrimeNumber(InputNum: Integer): Integer;

Var
    Number, Counter: Integer;
    IsMustNotStop: Boolean;

Begin

    Number := 2;
    Counter := 0;
    IsMustNotStop := True;

    If InputNum = 1 Then
        GetPrimeNumber := 2
    Else
        If InputNum = 2 Then
            GetPrimeNumber := 3
        Else
            While (IsMustNotStop) Do
            Begin

                If DiscoverIsNumberPrime(Number) Then
                    Counter := Counter + 1;

                If Counter = InputNum Then
                Begin
                    IsMustNotStop := False;
                    GetPrimeNumber := Number;
                End;

                Number := Number + 1;

            End;
End;

Function GetMersenneNumbers(N: Integer): TArrayOI;
Const
    MIN_ANSWER: Integer = 3;
Var
    I, J, Answer, MersenneNumber, CountOfAnswers: Integer;
    ArrayOfMersenneNumbers: TArrayOI;
Begin
    ArrayOfMersenneNumbers := Nil;
    I := 1;
    J := 2;
    Answer := MIN_ANSWER;
    MersenneNumber := 2;
    CountOfAnswers := 0;

    While Answer < N Do
    Begin
        MersenneNumber := 2;

        For J := 2 To GetPrimeNumber(I) Do
            MersenneNumber := MersenneNumber * 2;

        MersenneNumber := MersenneNumber - 1;
        Answer := MersenneNumber;

        If (DiscoverIsNumberPrime(Answer) = True) And (Answer < N) Then
        Begin
            CountOfAnswers := CountOfAnswers + 1;
            SetLength(ArrayOfMersenneNumbers, CountOfAnswers);
            ArrayOfMersenneNumbers[CountOfAnswers - 1] := Answer;
        End;

        I := I + 1;
    End;

    GetMersenneNumbers := ArrayOfMersenneNumbers;
End;

Function IsFileText(FilePath: String): Boolean;

Const
    MIN_PATH_LENGTH: Integer = 3;

Var
    FileExt: String;
    IsText: Boolean;
    Index: Integer;

Begin
    Index := Length(FilePath);
    IsText := False;

    If Index > MIN_PATH_LENGTH Then
        FileExt := FilePath[Index - 3] + FilePath[Index - 2] + FilePath[Index - 1] + FilePath[Index]
    Else
        IsText := False;

    IsText := FileExt = '.txt';

    IsFileText := IsText;
End;

Function IsFileNotEmpty(Var InputFile: TextFile): Boolean;

Var
    IsNotEmpty: Boolean;

Begin
    Try
        Reset(InputFile);
        IsNotEmpty := Not EOF(InputFile);
    Finally
        CloseFile(InputFile);
    End;

    IsFileNotEmpty := IsNotEmpty;
End;

Function CanRead(Var InputFile: TextFile): Boolean;

Var
    IsReady: Boolean;

Begin

    Try
        Reset(InputFile);
        CloseFile(InputFile);
        IsReady := True;
    Except
        IsReady := False;
    End;

    CanRead := IsReady;
End;

Function CanWrite(Var FileVar: TextFile): Boolean;

Var
    IsReady: Boolean;

Begin

    Try
        Append(FileVar);
        CloseFile(FileVar);
        IsReady := True;
    Except
        IsReady := False;
    End;

    CanWrite := IsReady;
End;

Function CheckMyFile(Var InputFile: TextFile; FilePath: String; IsForWriteToFile: Boolean): ERROR_CODES;

Var
    CheckInput: Boolean;
    ERROR: ERROR_CODES;

Begin
    CheckInput := False;

    If Not FileExists(FilePath) Then
        ERROR := FILE_NOT_EXIST
    Else
        If Not IsFileText(FilePath) Then
            ERROR := FILE_NOT_TXT
        Else
            If (Not IsForWriteToFile) And (Not CanRead(InputFile)) Then
                ERROR := FILE_CLOSE_TO_READ
            Else
                If IsForWriteToFile And (Not CanWrite(InputFile)) Then
                    ERROR := FILE_CLOSE_TO_WRITE
                Else
                    If (Not IsForWriteToFile) And (Not IsFileNotEmpty(InputFile)) Then
                        ERROR := FILE_IS_EMPTY
                    Else
                    Begin
                        ERROR := NO_ERRORS;
                    End;

    CheckMyFile := ERROR;
End;

Function CheckGridOnValidity(StringGrid: TStringGrid): Boolean;
Var
    FirstChar, LastChar: Char;
    IsCellReadible, IsFirstAndLastCharFine, IsNumber, IsAllGridCorrect: Boolean;
    I, CountOfPoints, Index, ArrHigh: Integer;
    TestString: String;
    StringGridArray: TArrayOS;

Begin
    IsCellReadible        := False;
    IsFirstAndLastCharFine  := False;
    IsAllGridCorrect        := True;
    IsNumber                := True;

    CountOfPoints := 0;
    Index         := 0;
    ArrHigh       := 0;
    TestString := #0;

    StringGridArray := Nil;

    If (Length(MainForm.NumberOneEdit.Text) = 0) Or (MainForm.NumberOneEdit.Text = #0) Or (MainForm.NumberOneEdit.Text = '') Then
        IsAllGridCorrect := False
    Else
    Begin
        StringGridArray := GetStringArrayFromGrid(StringGrid);
        ArrHigh := StrToInt(MainForm.NumberOneEdit.Text) - 1;

        For Index := 0 To ArrHigh Do
        Begin
            TestString := StringGridArray[Index];
            //IsNumber := True;

            If (Length(TestString) = 0) Or (TestString = #0) Or (TestString = '') Then
                IsCellReadible := False
            Else
            Begin
                FirstChar := TestString[Low(TestString)];
                LastChar := TestString[High(TestString)];

                //Проверка если это число, или на то, если это не просто один написанный минус
                IsFirstAndLastCharFine := ((FirstChar In DIGITS) And (LastChar In DIGITS))
                                            Or ((FirstChar = '-') And (LastChar In DIGITS));

                If Length(TestString) > 1 Then
                Begin
                    If (FirstChar = '-') Then
                    Begin
                        For I := 2 To High(TestString) Do
                        Begin
                        IsNumber := IsNumber And (TestString[I] In DIGITS) And Not(TestString[2] = '0');
                        End;
                    End
                    Else
                    Begin
                        For I := 1 To High(TestString) Do
                        Begin
                            IsNumber := IsNumber And (TestString[I] In DIGITS);
                        End;
                    End;
                End;

                Try
                    StrToInt(TestString);
                    IsCellReadible := True;
                Except
                    IsCellReadible := False;
                End;

            End;

            IsAllGridCorrect := IsAllGridCorrect And IsFirstAndLastCharFine And IsNumber And IsCellReadible;

        End;
    End;

    CheckGridOnValidity := IsAllGridCorrect;
End;

Function GetStringArrayFromGrid(StringGrid: TStringGrid): TArrayOS;
Var
    StringArray: TArrayOS;
    I, ArrLength, ArrHigh: Integer;
    NumberOneText: String;
Begin
    NumberOneText := '';
    NumberOneText := MainForm.NumberOneEdit.Text;

    ArrLength := StrToInt(NumberOneText);
    ArrHigh := ArrLength - 1;

    SetLength(StringArray, ArrLength);

    For I := 0 To ArrHigh Do
    Begin
        StringArray[I] := StringGrid.Cells[I, 1];
    End;

    GetStringArrayFromGrid := StringArray;
End;

Function ChangeStringArrayToIntArray(StringArray: TArrayOS): TArrayOI;
Var
    IntArray: TArrayOI;
    I: Integer;
Begin
    IntArray := Nil;

    Setlength(IntArray, Length(StringArray));

    For I := 0 To High(IntArray) Do
        IntArray[I] := StrToInt(StringArray[I]);

    ChangeStringArrayToIntArray := IntArray;
End;

Function CheckEditStringOnValidity(TestString: String): Boolean;
Var
    IsStringReadible: Boolean;
    TestInteger: Integer;
Begin
    IsStringReadible := False;

    If Length(TestString) = 0 Then
        IsStringReadible := False
    Else
    Begin
        Try
            TestInteger := StrToInt(TestString);
            If (TestInteger >= MIN_EDIT_NUMBER) And (TestInteger <= MAX_EDIT_NUMBER) Then
                IsStringReadible := True;
        Except
            IsStringReadible := False;
        End;
    End;

    CheckEditStringOnValidity := IsStringReadible;
End;

Procedure NumberTheFirstCol(StringGrid: TStringGrid);
Var
    I: Integer;
Begin
    For I := 0 To StringGrid.ColCount Do
    Begin
        StringGrid.Cells[I, 0] := '№ ' + IntToStr(I + 1);
    End;
End;

Procedure TMainForm.NumberOneEditKeyPress(Sender: TObject; Var Key: Char);
Var
    WrittenString: String;
    IsKeyAllowed: Boolean;

Begin
    IsKeyAllowed := False;
    WrittenString := NumberOneEdit.Text;

    //Проверяем ПЕРВЫЙ символ будущей строки
    If ((Length(WrittenString) = 0) And (Key In DIGITS) And Not(Key = '0')) Then
        IsKeyAllowed := True;

    If (Length(WrittenString) > 0) And (Length(WrittenString) < 13) Then
    Begin
        If Key in DIGITS Then
        Begin
            IsKeyAllowed := True;
        End;
    End;

    If Key = BACKSPACE Then
        IsKeyAllowed := True;

    If Not IsKeyAllowed Then
        Key := #0;
End;

Procedure FixStringOnInvalidValue();
Var
    OnlyNumbersString, EditString: String;
    I, SelStart: Integer;
Begin
    OnlyNumbersString := '';
    EditString := MainForm.NumberOneEdit.Text;

    For I := 1 To High(EditString) Do
    Begin
        If (EditString[I] In DIGITS) Or (EditString[I] = '-') Then
            OnlyNumbersString := OnlyNumbersString + EditString[I];
    End;

    If OnlyNumbersString <> EditString Then
    Begin
        SelStart := MainForm.NumberOneEdit.SelStart;
        MainForm.NumberOneEdit.Text := OnlyNumbersString;
        MainForm.NumberOneEdit.SelStart := SelStart;
    End;

End;

Procedure FixStringGridOnIncorrecValue();
Var
    OnlyNumbersString, CellString: String;
    I, SelStart: Integer;
Begin
    OnlyNumbersString := '';

    CellString := MainForm.StringGridA.Cells[StrGridACol, StrGridARow];

    For I := 1 To High(CellString) Do
    Begin
        If (CellString[I] In DIGITS) Or (CellString[I] = '-') Then
            OnlyNumbersString := OnlyNumbersString + CellString[I];
    End;

    If OnlyNumbersString <> CellString Then
    Begin
        MainForm.StringGridA.Cells[StrGridACol, StrGridARow] := OnlyNumbersString;
    End;

End;

Procedure TMainForm.NumberOneEditChange(Sender: TObject);
Begin
    IsFirstNumberCorrect := CheckEditStringOnValidity(NumberOneEdit.Text);
    ResultButton.Enabled := IsFirstNumberCorrect;
    SaveTab.Enabled := IsFirstNumberCorrect;
    IsDataSaved := False;
    SetStringGridACorrect;
    LabelResult.Visible := False;
    StringGridA.Visible := False;
    FixStringOnInvalidValue()
End;

Procedure SetStringGridACorrect();
Var
    AnswerArray: TArrayOI;
Begin
    AnswerArray := Nil;
    If IsFirstNumberCorrect Then
    Begin
        AnswerArray := GetMersenneNumbers(StrToInt(MainForm.NumberOneEdit.Text));
        MainForm.StringGridA.ColCount := Length(AnswerArray);
        NumberTheFirstCol(MainForm.StringGridA);
    End;
    MainForm.StringGridA.Visible := IsFirstNumberCorrect;
End;

Procedure TMainForm.OpenTabClick(Sender: TObject);
Var
    FilePath: String;
    OpenedFile: TextFile;
    Error: ERROR_CODES;
    IsToWriteToFile: Boolean;

Begin
    IsToWriteToFile := False;
    Error := NO_ERRORS;

    If OpenTextFileDialog1.Execute Then
    Begin
        FilePath := OpenTextFileDialog1.FileName;

        Try
            AssignFile(OpenedFile, FilePath);
            Error := CheckMyFile(OpenedFile, FilePath, IsToWriteToFile);
        Except
            Error := FILE_ASSIGN_ERROR;
        End;

        If Error =NO_ERRORS Then
        Begin
            Error := ReadAndWriteOutFileData(OpenedFile);
            IsDataSaved := True;
        End;
        If Error <> NO_ERRORS Then
            Application.MessageBox(PWideChar(ERROR_TEXT[Error]), 'Ошибка', MB_OK + MB_ICONERROR);

    End;
End;

Procedure TMainForm.ResultButtonClick(Sender: TObject);
Var
    AnswerArray: TArrayOI;
    I, NumberN, ArrHigh: Integer;
    NumberNText: String;
Begin
    LabelResult.Visible := True;
    AnswerArray := Nil;
    NumberN := 0;
    ArrHigh := 0;
    NumberNText := '';

    NumberNText := MainForm.NumberOneEdit.Text;

    NumberN := StrToInt(NumberNText);

    AnswerArray := GetMersenneNumbers(NumberN);

    If AnswerArray = Nil Then
    Begin
        MainForm.LabelResult.Caption := 'Чисел Мерсенна меньших за 3 не существует.';
        MainForm.StringGridA.Visible := False;
    End
    Else
    Begin
        MainForm.LabelResult.Caption := 'Все числа Мерсенна, меньшие за ' + NumberNText + ':';
        FillGridByArrayData(AnswerArray, MainForm.StringGridA);
        MainForm.StringGridA.Visible := True;
    End;
End;

procedure TMainForm.SaveTabClick(Sender: TObject);
Begin
    SaveDataToFile();
End;

Function FillGridByArrayData(FromArray: TArrayOI; ToGrid: TStringGrid): ERROR_CODES;
Var
    Error: ERROR_CODES;
    I, GridLength, GridHigh: Integer;
Begin
    Error := NO_ERRORS; //А нужно ли?

    GridLength := 0;

    GridHigh := High(FromArray);

    ToGrid.ColCount := GridHigh + 1;
    NumberTheFirstCol(ToGrid);

    For I := 0 To GridHigh Do
    Begin
        ToGrid.Cells[I, 1] := IntToStr(FromArray[I]);
    End;

    FillGridByArrayData := Error;
End;

Procedure TMainForm.AboutDeveloperTabClick(Sender: TObject);
Var
    AboutDeveloperForm: TGuideForm;
Begin
    AboutDeveloperForm := TGuideForm.Create(Self);
    AboutDeveloperForm.GuideLabel.Caption := 'Разработчик: Педько Владислав Юрьевич'#13#10'Группа: 551004'#13#10'Telegram: @ginguare';
    AboutDeveloperForm.GuideLabel.Font.Size := 11;
    AboutDeveloperForm.Caption := 'О Разработчике';
    AboutDeveloperForm.ShowModal;
    AboutDeveloperForm.Free;
End;

Procedure TMainForm.InstructionTabClick(Sender: TObject);
Var
    InstructionForm: TGuideForm;
Begin
    InstructionForm := TGuideForm.Create(Self);
    InstructionForm.GuideLabel.Caption :=
        '1) За число n принимается целое число от 1 до 999999.'#13#10 +
        '2) Число n не должно в себе содержать никаких символов, кроме символов цифр.'#13#10 +
        ''#13#10;

    InstructionForm.GuideLabel.Font.Size := 10;
    InstructionForm.Caption := 'Инструкция';
    InstructionForm.GuideLabel.WordWrap := True;
    InstructionForm.ShowModal;
    InstructionForm.Free;
End;

Function SaveDataToFile(): ERROR_CODES;
Var
    FilePath: String;
    SavedFile: TextFile;
    Error: ERROR_CODES;
    IsToWriteToFile: Boolean;
Begin
    IsToWriteToFile := True;
    Error := NO_ERRORS;

    If MainForm.SaveTextFileDialog1.Execute Then
    Begin
        FilePath := MainForm.SaveTextFileDialog1.FileName;

        Try
            AssignFile(SavedFile, FilePath);
            Error := CheckMyFile(SavedFile, FilePath, IsToWriteToFile);
        Except
            Error := FILE_ASSIGN_ERROR;
        End;

        If Error = NO_ERRORS Then
        Begin
            Error := WriteDataToFile(SavedFile);
        End;

        If Error <> NO_ERRORS Then
            Application.MessageBox(PWideChar(ERROR_TEXT[Error]), 'Ошибка', MB_OK + MB_ICONERROR)
        Else
        Begin
            Application.MessageBox(PWideChar('Данные успешно сохранены.'), 'Успешно', MB_OK + MB_ICONINFORMATION);
            IsDataSaved := True;
        End;

    End
    Else
    Begin
        Error := FILE_DATA_NOT_SAVED;
    End;

    SaveDataToFile := Error;
End;

Function WriteDataToFile(Var SavedFile: TextFile): ERROR_CODES;
Var
    Error: ERROR_CODES;
    ArrLength, ArrHigh, I: Integer;
    ArrayOfMersenneNumbers: TArrayOS;
Begin
    Error := NO_ERRORS;
    ArrLength := 0;
    ArrayOfMersenneNumbers := Nil;

    ArrayOfMersenneNumbers := GetStringArrayFromGrid(MainForm.StringGridA);
    ArrHigh := High(ArrayOfMersenneNumbers);

    Try
        Rewrite(SavedFile);
        WriteLn(SavedFile, MainForm.NumberOneEdit.Text);

        For I := 0 To ArrHigh Do
        Begin
            Write(SavedFile, ArrayOfMersenneNumbers[I], ' ');
        End;
        WriteLn(SavedFile);

        CloseFile(SavedFile);
    Except
        Error := FILE_CLOSE_TO_WRITE;
    End;

    WriteDataToFile := Error;
End;

Function  ReadAndWriteOutFileData(Var ReadedFile: TextFile): ERROR_CODES;
Const
    MIN_LENGTH: Integer  = 1;
    MAX_LENGTH: Integer  = 999_999;
    MAX_ELEMENT: Integer = 999_999;
    MIN_ELEMENT: Integer = 3;
Var
    Error: ERROR_CODES;
    NumberN, ArrHigh, I, AnswerNumber: Integer;
    NumberNStr, FinalString: String;
    AnswerArray: TArrayOI;
Begin
    Error := NO_ERRORS;

    Try
        Reset(ReadedFile);
    Except
        Error := FILE_CLOSE_TO_READ;
    End;

    Try
        ReadLn(ReadedFile, NumberNStr);
        If EOF(ReadedFile) Then
            Error := (FILE_DATA_NOT_CORRECT);
        NumberN := StrToInt(NumberNStr);
    Except
        Error := FILE_DATA_NOT_CORRECT;
    End;

    If Error = NO_ERRORS Then
    Begin
        If (NumberN < MIN_LENGTH) Or (NumberN > MAX_LENGTH) Then
        Begin
            Error := FILE_DATA_NOT_CORRECT;
        End;
    End;

//    If Not(GridAArray = Nil) And (Error = NO_ERRORS) Then
//    Begin
//        For I := 0 To ArrHigh Do
//        Begin
//            If Error = NO_ERRORS Then
//            Begin
//
//                If EOF(ReadedFile) Then
//                Begin
//                    GridAArray := Nil;
//                    Error := FILE_DATA_NOT_CORRECT;
//                End;
//
//                Try
//                    Read(ReadedFile, GridAArray[I]);
//                    If (GridAArray[I] > MAX_ELEMENT) Or (GridAArray[I] < MIN_ELEMENT) Then
//                        Error := FILE_DATA_NOT_CORRECT;
//                Except
//                    GridAArray := Nil;
//                    Error := FILE_DATA_NOT_CORRECT;
//                End;
//
//            End;
//        End;
//
//
//    End;

    CloseFile(ReadedFile);

    If (Error = NO_ERRORS) Then
    Begin
        MainForm.NumberOneEdit.Text := IntToStr(NumberN);

        MainForm.LabelResult.Visible := True;
        AnswerArray := GetMersenneNumbers(NumberN);

        If AnswerArray = Nil Then
            MainForm.LabelResult.Caption := 'Чисел Мерсенна меньших за 3 не существует.'
        Else
        Begin
            MainForm.LabelResult.Caption := 'Все числа Мерсенна, меньшие за ' + IntToStr(NumberN) + ':';
            MainForm.StringGridA.Visible := True;
            FillGridByArrayData(AnswerArray, MainForm.StringGridA);
        End;
    End;

    ReadAndWriteOutFileData := Error;
End;

Procedure TMainForm.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
Begin
    CanClose := LeaveFromProgram(CanClose);
End;

Procedure TMainForm.LeaveTabClick(Sender: TObject);
Begin
    Close;
End;

Function LeaveFromProgram(CanClose: Boolean): Boolean;
Var
    IsFormShouldClose: Integer;
    Error: ERROR_CODES;

Begin
    Error := NO_ERRORS;
    CanClose := False;

    If (IsDataSaved) Or Not(CheckEditStringOnValidity(MainForm.NumberOneEdit.Text)) Then
    Begin
        IsFormShouldClose := Application.MessageBox(PChar('Вы хотите выйти?'), PChar('Выход'), MB_YESNO + MB_ICONQUESTION);

        If IsFormShouldClose = mrYes Then
        Begin
            CanClose := True;
        End;
    End
    Else
    Begin
        IsFormShouldClose := Application.MessageBox(PChar('Данные не были сохранены, вы точно хотите выйти?'), PChar('Выход'), MB_YESNOCANCEL + MB_ICONQUESTION);

        If IsFormShouldClose = MrYes Then
            CanClose := True
        Else
            If IsFormShouldClose = MrNo Then
            Begin
                Error := SaveDataToFile();
                If Error = NO_ERRORS Then
                    CanClose := True;
            End;

    End;

    LeaveFromProgram := CanClose;
End;

End.
