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
    Vcl.Grids;

Type
    TMatrixOI = Array Of Array Of Integer;
    TMatrixOS = Array Of Array Of String;
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
        StringGridResult: TStringGrid;
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
    procedure StringGridAKeyPress(Sender: TObject; var Key: Char);
    procedure StringGridASelectCell(Sender: TObject; ACol, ARow: LongInt; Var CanSelect: Boolean);
    procedure StringGridAExit(Sender: TObject);
    function FormHelp(Command: Word; Data: THelpEventData; Var CallHelp: Boolean): Boolean;

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
    //Function CheckStringOnValidity(TestString: String; Var IsPointAllowed: Boolean): Boolean;
    Function SaveDataToFile(): ERROR_CODES;
    Function LeaveFromProgram(CanClose: Boolean): Boolean;
    Function WriteDataToFile(Var SavedFile: TextFile): ERROR_CODES;
    Function ReadAndWriteOutFileData(Var ReadedFile: TextFile): ERROR_CODES;
    Function CheckLengthStringOnValidity(TestString: String): Boolean;
    Procedure SetStringGridACorrect();
    Procedure PrepareGrid(StringGrid: TStringGrid);
    Function CheckGridOnValidity(StringGrid: TStringGrid): Boolean;
    Function GetSMatrixFromGrid(StringGrid: TStringGrid): TMatrixOS;
    Procedure OnGridAChange();
    Function GetIMatrixFromSMatrix(SMatrix: TMatrixOS): TMatrixOI;
    Procedure FixStringGridOnIncorrecValue();
    Procedure FixStringOnInvalidValue();

Const
    MAX_ARRAY_LENGTH: Integer = 99;
    MIN_ARRAY_LENGTH: Integer = 1;
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
    StrGridACol: LongInt = 1;
    StrGridARow: LongInt = 1;

    //TODO Поменять инструкцию

Implementation

{$R *.dfm}

Function SortConditional(Matrix: TMatrixOI): TMatrixOI;

Var
    I, J, K, Limiter, BoubleSortLimiter: Integer;

Begin
    I := 0;
    J := 0;
    Limiter := High(Matrix);
    BoubleSortLimiter := Length(Matrix) * (Length(Matrix) Div 2);

    For K := 1 To BoubleSortLimiter Do
    Begin

        Limiter := High(Matrix);

        For I := 0 To High(Matrix) Do
            If Odd(I) Then
            Begin

                If I = 2 * (Length(Matrix) Div 2) Then
                    Limiter := High(Matrix) - 1;

                For J := 0 To Limiter Do
                Begin

                    If (J + 1 < High(Matrix[I])) Or (J + 1 = High(Matrix[I])) Then
                    Begin

                        If Matrix[I, J] < Matrix[I, J + 1] Then
                        Begin
                            Matrix[I, J] := Matrix[I, J] + Matrix[I, J + 1];
                            Matrix[I, J + 1] := Matrix[I, J] - Matrix[I, J + 1];
                            Matrix[I, J] := Matrix[I, J] - Matrix[I, J + 1];
                        End;

                    End
                    Else
                        If (I + 2 < High(Matrix)) Or (I + 2 = High(Matrix)) Then
                        Begin

                            If Matrix[I, J] < Matrix[I + 2, 0] Then
                            Begin
                                Matrix[I, J] := Matrix[I, J] + Matrix[I + 2, 0];
                                Matrix[I + 2, 0] := Matrix[I, J] - Matrix[I + 2, 0];
                                Matrix[I, J] := Matrix[I, J] - Matrix[I + 2, 0];
                            End;

                        End;

                End;

            End;
    End;

    SortConditional := Matrix;
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
    I, J, CountOfPoints, Index, MatrixLength, MatrixHigh: Integer;
    TestString: String;
    StringGridArray: TMatrixOS;
Begin
    IsCellReadible        := False;
    IsFirstAndLastCharFine  := False;
    IsAllGridCorrect        := True;
    IsNumber                := True;

    CountOfPoints := 0;
    Index         := 0;
    MatrixLength  := 0;
    MatrixHigh    := 0;
    TestString := #0;
    FirstChar := #0;
    LastChar := #0;

    StringGridArray := Nil;

    StringGridArray := GetSMatrixFromGrid(StringGrid);

    MatrixLength := StrToInt(MainForm.NumberOneEdit.Text);
    MatrixHigh := MatrixLength - 1;

    For I := 0 To MatrixHigh Do
    Begin
        For J := 0 To MatrixHigh Do
        Begin
            TestString := StringGridArray[I, J];
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
                        For Index := 2 To High(TestString) Do
                        Begin
                            IsNumber := IsNumber And (TestString[Index] In DIGITS) And Not(TestString[2] = '0');
                        End;
                    End
                    Else
                    Begin
                        For Index := 1 To High(TestString) Do
                        Begin
                            IsNumber := IsNumber And (TestString[Index] In DIGITS);
                        End;
                    End;

                    If (FirstChar = '0') Then
                        IsFirstAndLastCharFine := False;
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

Function GetSMatrixFromGrid(StringGrid: TStringGrid): TMatrixOS;
Var
    Matrix: TMatrixOS;
    I, J, MatrixLength, MatrixHigh: Integer;
    NumberOneText: String;
Begin
    NumberOneText := '';
    NumberOneText := MainForm.NumberOneEdit.Text;

    MatrixLength := StrToInt(NumberOneText);
    MatrixHigh := MatrixLength - 1;

    SetLength(Matrix, MatrixLength, MatrixLength);

    For I := 0 To MatrixHigh Do
    Begin
        For J := 0 To MatrixHigh Do
        Begin
            Matrix[J, I] := StringGrid.Cells[I+1, J+1];
        End;
    End;

    GetSMatrixFromGrid := Matrix;
End;

Function GetIMatrixFromSMatrix(SMatrix: TMatrixOS): TMatrixOI;
Var
    IMatrix: TMatrixOI;
    I, J: Integer;
    IsGood: Boolean;
Begin
    IsGood := True;
    IMatrix := Nil;

    SetLength(IMatrix, Length(SMatrix), Length(SMatrix));

    For I := Low(SMatrix) To High(SMatrix) Do
        For J := Low(SMatrix[0]) To High(SMatrix[0]) Do
            If IsGood Then
                Try
                    IMatrix[I, J] := StrToInt(SMatrix[I, J]);
                Except
                    Application.MessageBox(PWideChar('Ошибка преобразование массива из строчного в целочисленный.'), 'Ошибка', MB_OK + MB_ICONERROR);
                    IsGood := False;
                End;

    GetIMatrixFromSMatrix := IMatrix;
End;

Function CheckLengthStringOnValidity(TestString: String): Boolean;
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
            If (TestInteger >= MIN_ARRAY_LENGTH) And (TestInteger <= MAX_ARRAY_LENGTH) Then
                IsStringReadible := True;
        Except
            IsStringReadible := False;
        End;
    End;

    CheckLengthStringOnValidity := IsStringReadible;
End;

Procedure PrepareGrid(StringGrid: TStringGrid);
Var
    I, J: Integer;
Begin
    For I := 0 To StringGrid.ColCount Do
    Begin
        For J := 0 To StringGrid.ColCount Do
        Begin
            StringGrid.Cells[J, I] := '';
            If (I = 0) And (J <> 0) Then
                StringGrid.Cells[J, 0] := '№ ' + IntToStr(J);

            If (J = 0) And (I <> 0) Then
                StringGrid.Cells[0, I] := '№ ' + IntToStr(I);
        End;
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

    If (Length(WrittenString) > 0) And (Length(WrittenString) < 2) Then
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

Procedure TMainForm.NumberOneEditChange(Sender: TObject);
Begin
    IsFirstNumberCorrect := CheckLengthStringOnValidity(NumberOneEdit.Text);
    ResultButton.Enabled := IsFirstNumberCorrect And CheckGridOnValidity(StringGridA);
    SaveTab.Enabled := IsFirstNumberCorrect And CheckGridOnValidity(StringGridA);
    IsDataSaved := Not(IsFirstNumberCorrect);
    SetStringGridACorrect;
    LabelResult.Visible := False;
    StringGridResult.Visible := False;
    FixStringOnInvalidValue()
End;

Procedure OnGridAChange();
Var
    ArrayStringGridA: TMatrixOS;
    IsGridValid: Boolean;
Begin
    IsGridValid := False;
    ArrayStringGridA := Nil;

    IsGridValid := CheckGridOnValidity(MainForm.StringGridA);
    FixStringGridOnIncorrecValue();

    MainForm.ResultButton.Enabled := IsGridValid And IsFirstNumberCorrect;
    MainForm.SaveTab.Enabled := False;
    MainForm.LabelResult.Visible := False;
    MainForm.StringGridResult.Visible := False;
End;

Procedure SetStringGridACorrect();
Begin
    If IsFirstNumberCorrect Then
    Begin
        MainForm.StringGridA.ColCount := StrToInt(MainForm.NumberOneEdit.Text) + 1;
        MainForm.StringGridA.RowCount := StrToInt(MainForm.NumberOneEdit.Text) + 1;
        PrepareGrid(MainForm.StringGridA);
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

        If Error = NO_ERRORS Then
        Begin
            Error := ReadAndWriteOutFileData(OpenedFile);
            IsDataSaved := True;
        End;
        If Error <> NO_ERRORS Then
            Application.MessageBox(PWideChar(ERROR_TEXT[Error]), 'Ошибка', MB_OK + MB_ICONERROR);

    End;
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

Procedure TMainForm.ResultButtonClick(Sender: TObject);
Var
    SMatrix: TMatrixOS;
    IMatrix: TMatrixOI;
    I, J, MatrixLength, MatrixHigh: Integer;
    NumberOneText: String;
Begin
    LabelResult.Visible := True;
    StringGridResult.Visible := True;

    NumberOneText := '';
    NumberOneText := MainForm.NumberOneEdit.Text;

    MatrixLength := StrToInt(NumberOneText);
    MatrixHigh := MatrixLength - 1;

    SMatrix := GetSMatrixFromGrid(StringGridA);

    MainForm.StringGridResult.ColCount := StrToInt(MainForm.NumberOneEdit.Text) + 1;
    MainForm.StringGridResult.RowCount := StrToInt(MainForm.NumberOneEdit.Text) + 1;
    PrepareGrid(MainForm.StringGridResult);

    IMatrix := GetIMatrixFromSMatrix(SMatrix);

    // Выполняем преобразование матрицы
    IMatrix := SortConditional(IMatrix);

    MainForm.SaveTab.Enabled := True;

    For I := 0 To MatrixHigh Do
    Begin
        For J := 0 To MatrixHigh Do
            MainForm.StringGridResult.Cells[J+1, I+1] := IntToStr(IMatrix[I, J]);
    End;

End;

procedure TMainForm.SaveTabClick(Sender: TObject);
Begin
    SaveDataToFile();
End;

Procedure TMainForm.StringGridAExit(Sender: TObject);
Begin
    OnGridAChange();
End;

Procedure TMainForm.StringGridAKeyPress(Sender: TObject; var Key: Char);
Var
    WrittenString: String;
    IsKeyAllowed: Boolean;

Begin
    IsKeyAllowed := False;
    WrittenString := StringGridA.Cells[StringGridA.Col, StringGridA.Row];

    //Проверяем ПЕРВЫЙ символ будущей строки
    If ( (Length(WrittenString) = 0) And ((Key In DIGITS) {And Not(Key = '0')} Or (Key = '-')) ) Then
        IsKeyAllowed := True;

    If (Length(WrittenString) > 0) And (Length(WrittenString) < 4) And Not(WrittenString[1] = '-') Then
    Begin
        If Key in DIGITS Then
        Begin
            IsKeyAllowed := True;
        End;
    End;

    If ( (Length(WrittenString) > 0) And (WrittenString[1] = '-') And (Length(WrittenString) < 5) )Then
    Begin
        If ( ((Length(WrittenString) = 1) And (Key in DIGITS) And Not(Key = '0')) ) Then
        Begin
            IsKeyAllowed := True;
        End;

        If ((Length(WrittenString) > 1) And (Key in DIGITS)) Then
        Begin
            IsKeyAllowed := True;
        End;
    End;

    If Key = BACKSPACE Then
        IsKeyAllowed := True;

    If Not IsKeyAllowed Then
        Key := #0;
End;

Procedure FillGridByArrayData(FromMatrix: TMatrixOI; ToGrid: TStringGrid);
Var
    Error: ERROR_CODES;
    I, J, GridLength, GridHigh: Integer;
Begin
    GridLength := 0;

    GridHigh := High(FromMatrix);

    ToGrid.ColCount := StrToInt(MainForm.NumberOneEdit.Text) + 1;
    ToGrid.RowCount := StrToInt(MainForm.NumberOneEdit.Text) + 1;
    PrepareGrid(ToGrid);

    For I := 0 To GridHigh Do
    Begin
        For J := 0 To GridHigh Do
            ToGrid.Cells[I+1, J+1] := IntToStr(FromMatrix[I, J]);
    End;
End;

Procedure TMainForm.StringGridASelectCell(Sender: TObject; ACol, ARow: LongInt; Var CanSelect: Boolean);
Begin
    FixStringGridOnIncorrecValue();
    StrGridACol := ACol;
    StrGridARow := ARow;
    OnGridAChange();
    FixStringGridOnIncorrecValue();
    MainForm.ResultButton.Enabled := CheckGridOnValidity(MainForm.StringGridA);
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
        '1) За длинну массива принимается целое число от 1 до 99.'#13#10 +
        '2) Элемент массива представляет собой целое число в диапазоне от -9999 до 9999.'#13#10 +
        '3) Для возможности вывода результатов нужно заполнить корректными значениями все ячейки массива и убрать фокус мыши с него.'#13#10;

    InstructionForm.GuideLabel.Font.Size := 11;
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
    MatrixLength, MatrixHigh, I, J: Integer;
    FromMatrix, ResultMatrix: TMatrixOS;
Begin
    Error := NO_ERRORS;
    MatrixLength := 0;
    MatrixHigh := 0;
    FromMatrix := Nil;
    ResultMatrix := Nil;

    MatrixLength := StrToInt(MainForm.NumberOneEdit.Text);
    MatrixHigh := MatrixLength - 1;
    FromMatrix := GetSMatrixFromGrid(MainForm.StringGridA);
    ResultMatrix := GetSMatrixFromGrid(MainForm.StringGridResult);

    Try
        Rewrite(SavedFile);
        WriteLn(SavedFile, MainForm.NumberOneEdit.Text);

        For I := 0 To MatrixHigh Do
        Begin
            For J := 0 To MatrixHigh Do
            Begin
                If Not((J = High(FromMatrix)) And (I = High(FromMatrix))) Then
                    Write(SavedFile, FromMatrix[I, J], ' ')
                Else
                    Write(SavedFile, FromMatrix[I, J]);
            End;
            If I <> MatrixHigh Then
                WriteLn(SavedFile);
        End;
        Write(SavedFile, #13#10#13#10);

        For I := 0 To MatrixHigh Do
        Begin
            For J := 0 To MatrixHigh Do
            Begin
                If Not((J = High(ResultMatrix)) And (I = High(ResultMatrix))) Then
                    Write(SavedFile, ResultMatrix[I, J], ' ')
                Else
                    Write(SavedFile, ResultMatrix[I, J]);
            End;
            If I <> MatrixHigh Then
                WriteLn(SavedFile);
        End;

        CloseFile(SavedFile);
    Except
        Error := FILE_CLOSE_TO_WRITE;
    End;

    WriteDataToFile := Error;
End;

Function  ReadAndWriteOutFileData(Var ReadedFile: TextFile): ERROR_CODES;
Const
    MIN_LENGTH: Integer  = 1;
    MAX_LENGTH: Integer  = 99;
    MAX_ELEMENT: Integer = 9999;
    MIN_ELEMENT: Integer = -9999;
Var
    Error: ERROR_CODES;
    MAtrixLength, MatrixHigh, I, J: Integer;
    MatrixLengthStr, AnswerNumberStr, FinalString: String;
    FromMatrix, ResultMatrix: TMatrixOI;
Begin
    Error := NO_ERRORS;
    MatrixLength := 0;
    MatrixHigh := 0;
    MatrixLengthStr := '';
    AnswerNumberStr := '';
    FinalString := '';
    FromMatrix := Nil;
    ResultMatrix := Nil;

    Try
        Reset(ReadedFile);
    Except
        Error := FILE_CLOSE_TO_READ;
    End;

    Try
        If EOF(ReadedFile) Then
            Error := (FILE_DATA_NOT_CORRECT);
        ReadLn(ReadedFile, MatrixLengthStr);

        MatrixLength := StrToInt(MatrixLengthStr);
        MatrixHigh := MatrixLength - 1;
    Except
        Error := FILE_DATA_NOT_CORRECT;
    End;

    If Error = NO_ERRORS Then
    Begin
        If (MatrixLength < MIN_LENGTH) Or (MatrixLength > MAX_LENGTH) Then
        Begin
            FromMatrix := Nil;
            Error := FILE_DATA_NOT_CORRECT;
        End
        Else
        Begin
            SetLength(FromMatrix, MatrixLength, MatrixLength);
            SetLength(ResultMatrix, MatrixLength, MatrixLength);
        End;
    End;

    If (Error = NO_ERRORS) Then
    Begin
        For I := 0 To MatrixHigh Do
        Begin
            For J := 0 To MatrixHigh Do
            Begin
                If Error = NO_ERRORS Then
                Begin

                    If EOF(ReadedFile) Then
                    Begin
                        FromMatrix := Nil;
                        Error := FILE_DATA_NOT_CORRECT;
                    End;

                    Try
                        Read(ReadedFile, FromMatrix[I, J]);
                        If (FromMatrix[I, J] > MAX_ELEMENT) Or (FromMatrix[I, J] < MIN_ELEMENT) Then
                            Error := FILE_DATA_NOT_CORRECT;
                    Except
                        FromMatrix := Nil;
                        Error := FILE_DATA_NOT_CORRECT;
                    End;

                End;
            End;
        End;
    End;

    If Not(EOF(ReadedFile)) Then
        Begin
            FromMatrix := Nil;
            Error := FILE_DATA_NOT_CORRECT;
        End;

    CloseFile(ReadedFile);

    If (Error = NO_ERRORS) Then
    Begin
        MainForm.NumberOneEdit.Text := IntToStr(MatrixLength);

        ResultMatrix := SortConditional(FromMatrix);

        MainForm.LabelResult.Visible := True;
        MainForm.StringGridResult.Visible := True;

        FillGridByArrayData(FromMatrix, MainForm.StringGridA);
        FillGridByArrayData(ResultMatrix, MainForm.StringGridResult);
    End;

    ReadAndWriteOutFileData := Error;
End;

Procedure TMainForm.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
Begin
    CanClose := LeaveFromProgram(CanClose);
End;

Function TMainForm.FormHelp(Command: Word; Data: THelpEventData; Var CallHelp: Boolean): Boolean;
Begin
    CallHelp := False;
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

    If (IsDataSaved) Or Not(CheckGridOnValidity(MainForm.StringGridA)) Then
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
