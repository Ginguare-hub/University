Program FilesArray;

uses
  System.SysUtils;

Type
    TArray = Array Of Integer;

Procedure WritePurpose;

Begin
    WriteLn('ProgramPurpose');
End;

Function ReadAndVerify(Const MIN_NUMBER, MAX_NUMBER: Integer; MyString: String): Integer;

Var
    IsCorrect: Boolean;
    Number: Integer;

Begin
    IsCorrect := True;
    Number := 0;

    Repeat

        Write(MyString);
        IsCorrect := True;

        Try
            ReadLn(Number);
        Except
            WriteLn('Incorrect input, try again.');
            IsCorrect := False;
        End;

        If IsCorrect And ((Number < MIN_NUMBER) Or (Number > MAX_NUMBER)) Then
        Begin
            WriteLn('The number must fit the range [', MIN_NUMBER, ',', MAX_NUMBER, '].');
            IsCorrect := False;
        End;

    Until IsCorrect;

    ReadAndVerify := Number;
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

Function CheckMyFile(Var InputFile: TextFile; FilePath: String; IsFileOutput: Boolean): Boolean;

Var
    CheckInput: Boolean;

Begin
    CheckInput := False;

    If Not FileExists(FilePath) Then
        Writeln('Error, file with path <', FilePath, '> is not exists.')
    Else
        If Not IsFileText(FilePath) Then
            Writeln('Error, filename is not .txt')
        Else
            If (Not IsFileOutput) And (Not CanRead(InputFile)) Then
                Writeln('Error, no access to read the file.')
            Else
                If IsFileOutput And (Not CanWrite(InputFile)) Then
                    Writeln('Error, no access to write into the file.')
                Else
                    If Not IsFileNotEmpty(InputFile) Then
                        Writeln('Error, file is empty.')
                    Else
                    Begin
                        CheckInput := True;
                        WriteLn('Assigning is completed successfully.');
                    End;

    CheckMyFile := CheckInput;
End;

Function WorkWithConsoleOrFile(IsOutput: Boolean): Boolean;

Var
    Number: Integer;
    IsFromFile: Boolean;

Begin
    Number := 0;

    If IsOutput Then
        WriteLn('If data is output to the console write 0, if from file write 1.')
    Else
        WriteLn('If data is entered from the console write 0, if from file write 1.');

    Number := ReadAndVerify(0, 1, '> ');

    If Number = 0 Then
    Begin
        IsFromFile := False;
        If IsOutput Then
            WriteLn('The data is output to the console.')
        Else
            WriteLn('The data is entered from the console.');
    End
    Else
    Begin
        IsFromFile := True;
        If IsOutput Then
            WriteLn('The data is output to a file.')
        Else
            WriteLn('The data is entered from a file.');
    End;

    WorkWithConsoleOrFile := IsFromFile;
End;

Function ReadArrayFromFile(Const MIN_NUMBER, MAX_NUMBER: Integer; Var InputFile: TextFile): TArray;

Const
    MIN_LENGTH: Integer = 1;
    MAX_LENGTH: Integer = 100;

Var
    I, ArrayLength, ArrayElement: Integer;
    Array1: TArray;

Begin
    ArrayLength := 0;
    I := 0;
    ArrayElement := 0;

    Try
        Reset(InputFile);
        ReadLn(InputFile, ArrayLength);
    Except
        Array1 := Nil;
    End;

    SetLength(Array1, ArrayLength);

    If Not(Array1 = Nil) Then
        If (ArrayLength < MIN_NUMBER) Or (ArrayLength > MAX_NUMBER) Then
        Begin
            WriteLn('Incorrect length, the number must fit the range [', MIN_LENGTH, ',', MAX_LENGTH, '].');
            Array1 := Nil;
        End;

    If Not(Array1 = Nil) Then
        For I := 0 To High(Array1) Do
        Begin
            Try
                Read(InputFile, Array1[I]);
            Except
                Array1 := Nil;
                WriteLn('Incorrect numeric data: array element.');
            End;
        End;

    CloseFile(InputFile);

    If Array1 = Nil Then
    Begin
        WriteLn('Error, incorrect array data.');
        Array1 := Nil;
    End;

    ReadMatrixFromFile := Matrix;
End;

Function ReadMatrixFromConsole(Const MIN_NUMBER: Integer; Const MAX_NUMBER: Integer): TMatrix;

Const
    MIN_LENGTH: Integer = 1;
    MAX_LENGTH: Integer = 20;

Var
    Matrix: TMatrix;
    I, J, MatrixLength, Element: Integer;

Begin
    I := 0;
    J := 0;
    MatrixLength := 0;
    Element := 0;

    MatrixLength := ReadAndVerify(MIN_LENGTH, MAX_LENGTH, 'Write matrix length: ');
    SetLength(Matrix, MatrixLength, MatrixLength);

    For I := 0 To High(Matrix) Do
        For J := 0 To High(Matrix[I]) Do
        Begin
            Write('Write element [', I, ',', J, '] of matrix: ');
            Element := ReadAndVerify(MIN_NUMBER, MAX_NUMBER, '');
            Matrix[I, J] := Element;
        End;

    ReadMatrixFromConsole := Matrix;
End;

Procedure WriteMatrixIntoFile(Var OutputFile: TextFile; Matrix: TMatrix);

Var
    I, J: Integer;
    IsReady: Boolean;

Begin
    I := 0;
    J := 0;
    IsReady := True;

    Try
        Rewrite(OutputFile);
    Except
        IsReady := False;
    End;

    If IsReady Then
    Begin
        WriteLn(OutputFile, 'The result matrix is: ');
        For I := 0 To High(Matrix) Do
        Begin
            For J := 0 To High(Matrix[I]) Do
                Write(OutputFile, Matrix[I, J], ' ');
            WriteLn(OutputFile);
        End;
    End
    Else
        WriteLn('The unexpected error is found.');

    CloseFile(OutputFile);
End;

Procedure WriteMatrixIntoConsole(Matrix: TMatrix);

Var
    I, J: Integer;

Begin
    I := 0;
    J := 0;

    For I := 0 To High(Matrix) Do
    Begin
        For J := 0 To High(Matrix[I]) Do
            Write(Matrix[I, J], ' ');
        WriteLn;
    End;
End;

Function AskTheFilePath(): String;

Var
    FilePath: String;

Begin
    Write('Write the existing file path: ');

    Try
        ReadLn(FilePath);
    Finally
        AskTheFilePath := FilePath;
    End;
End;

Procedure AssignMyFile(Var InputFile: TextFile; IsFileOutput: Boolean);

Var
    IsCorrect: Boolean;
    FilePath: String;

Begin
    IsCorrect := True;
    FilePath := '';

    Repeat
        FilePath := AskTheFilePath();

        Try
            AssignFile(InputFile, FilePath);
        Except
            WriteLn('Error with assigning.');
            FilePath := AskTheFilePath();
            IsCorrect := False;
        End;

        IsCorrect := CheckMyFile(InputFile, FilePath, IsFileOutput);

    Until IsCorrect;
End;

Procedure ReadingStage(Var Matrix: TMatrix);

Const
    MIN_NUMBER: Integer = -100000;
    MAX_NUMBER: Integer = 100000;

Var
    MyFile: TextFile;
    IsFromFile: Boolean;
    IsOutput: Boolean;
    IsAllDone: Boolean;

Begin
    IsOutput := False;
    IsAllDone := True;
    IsFromFile := WorkWithConsoleOrFile(IsOutput);

    If IsFromFile Then
        Repeat

            IsAllDone := True;
            AssignMyFile(MyFile, IsOutput);
            Matrix := ReadMatrixFromFile(MIN_NUMBER, MAX_NUMBER, MyFile);

            If Matrix = Nil Then
                IsAllDone := False;

        Until IsAllDone
    Else
        Matrix := ReadMatrixFromConsole(MIN_NUMBER, MAX_NUMBER);
End;

Procedure WritingStage(Matrix: TMatrix);

Var
    MyFile: TextFile;
    IsToFile: Boolean;
    IsOutput: Boolean;

Begin
    IsOutput := True;

    IsToFile := WorkWithConsoleOrFile(IsOutput);

    If IsToFile Then
    Begin
        AssignMyFile(MyFile, IsOutput);
        WriteMatrixIntoFile(MyFile, Matrix);
    End
    Else
        WriteMatrixIntoConsole(Matrix);
End;

Var
    Matrix: TMatrix;

Begin
    Matrix := Nil;

    WritePurpose;
    ReadingStage(Matrix);
    WritingStage(Matrix);

    ReadLn;

End.
