Program Lab3_5_D;

Uses
    System.SysUtils;

Type
    TArray = Array Of String;

Procedure WritePurpose;

Begin
    WriteLn('The program replaces separators with "+" and calculates the sum of numbers in the string.');
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

Function SplitString(Const Str: String): TArray;

Var
    StartPos, Pos, Count: Integer;
    AnswerArray: TArray;

Begin
    Count := 0;
    Pos := 1;

    While (Pos < Length(Str)) Or (Pos = Length(Str)) Do
    Begin

        While ((Pos < Length(Str)) Or (Pos = Length(Str))) And (Str[Pos] = ' ') Do
            Inc(Pos);

        If ((Pos < Length(Str)) Or (Pos = Length(Str))) Then
        Begin
            Inc(Count);
            While ((Pos < Length(Str)) Or (Pos = Length(Str))) And (Str[Pos] <> ' ') Do
                Inc(Pos);
        End;

    End;

    SetLength(AnswerArray, Count);

    Count := 0;
    Pos := 1;

    While ((Pos < Length(Str)) Or (Pos = Length(Str))) Do
    Begin
        While ((Pos < Length(Str)) Or (Pos = Length(Str))) And (Str[Pos] = ' ') Do
            Inc(Pos);
        If Pos <= Length(Str) Then
        Begin
            StartPos := Pos;
            While ((Pos < Length(Str)) Or (Pos = Length(Str))) And (Str[Pos] <> ' ') Do
                Inc(Pos);
            AnswerArray[Count] := Copy(Str, StartPos, Pos - StartPos);
            Inc(Count);
        End;
    End;

    SplitString := AnswerArray;
End;

Function ReadArrayFromFile(Const MIN_NUMBER, MAX_NUMBER: Integer; Var InputFile: TextFile; Var GivenString: String): TArray;

Const
    MIN_LENGTH: Integer = 1;
    MAX_LENGTH: Integer = 100;

Var
    I, ArrayLength, ArrayElement: Integer;
    Array1: TArray;
    IsErrorNotFound: Boolean;
    SeparatorString: String;

Begin
    ArrayLength := 0;
    I := 0;
    ArrayElement := 0;
    IsErrorNotFound := True;

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
    Begin

        Try
            ReadLn(InputFile, SeparatorString);
        Except
            WriteLn('Incorrect numeric data: array element.');
            Array1 := Nil;
            IsErrorNotFound := False;
        End;

        Array1 := SplitString(SeparatorString);

        If IsErrorNotFound Then
        Begin
            Try
                Read(InputFile, GivenString);
            Except
                WriteLn('Incorrect data: string.');
                GivenString := '';
                IsErrorNotFound := False;
            End;
        End;

    End;

    CloseFile(InputFile);

    ReadArrayFromFile := Array1;
End;

Function ReadArrayFromConsole(Const MIN_NUMBER: Integer; Const MAX_NUMBER: Integer): TArray;

Const
    MIN_LENGTH: Integer = 1;
    MAX_LENGTH: Integer = 100;

Var
    Array1: TArray;
    I, ArrayLength: Integer;
    ArrayElement: String;

Begin
    I := 0;
    ArrayLength := 0;
    ArrayElement := '';

    WriteLn('The length of the separators should decrease with increasing order.');
    ArrayLength := ReadAndVerify(MIN_LENGTH, MAX_LENGTH, 'Write amount of separators: ');
    SetLength(Array1, ArrayLength);

    For I := 0 To High(Array1) Do
    Begin
        Write('Write separator with index [', I, '] : ');
        ReadLn(ArrayElement);
        Array1[I] := ArrayElement;
    End;

    ReadArrayFromConsole := Array1;
End;

Procedure WriteStringIntoFile(Var OutputFile: TextFile; AnswerString: String);

Var
    IsReady: Boolean;

Begin
    IsReady := True;

    Try
        Rewrite(OutputFile);
    Except
        IsReady := False;
    End;

    If IsReady Then
    Begin
        WriteLn(OutputFile, AnswerString);
        WriteLn(OutputFile);
    End
    Else
        WriteLn('The unexpected error is found.');

    CloseFile(OutputFile);
End;

Procedure WriteStringIntoConsole(AnswerString: String);

Begin
    WriteLn(AnswerString);
    WriteLn;
End;

Function CheckIsStringValid(GivenString: String): Boolean;

Var
    I: Integer;
    IsValid: Boolean;

Begin
    I := 1;
    IsValid := True;

    If Not((((GivenString[1] > '0') Or (GivenString[1] = '0')) And ((GivenString[1] < '9') Or (GivenString[1] = '9'))) And (((GivenString[Length(GivenString)] > '0') Or (GivenString[Length(GivenString)] = '0')) And
        ((GivenString[Length(GivenString)] < '9') Or (GivenString[Length(GivenString)] = '9')))) Then
        IsValid := False;

    If IsValid Then
    Begin
        For I := 1 To Length(GivenString) Do
        Begin

            If (I + 1 < Length(GivenString)) And ((GivenString[I] = '+') And (GivenString[I + 1] = '+')) Then
                IsValid := False;

            If Not(GivenString[I] In ['0' .. '9', ',', '+']) Then
                IsValid := False;

        End;
    End;

//    If Not IsValid Then
//    Begin
//        WriteLn('The string contains invalid characters or their position is incorrect.');
//    End;

    CheckIsStringValid := IsValid;
End;

Function FindSumFromString(GivenString: String): String;

Var
    SumOfNumbers, Number: Double;
    I, PartLength, PartIndex: Integer;
    StringPart, AnswerString: String;
    IsFine, IsThereNumbers, IsNumberFull: Boolean;

Begin
    SumOfNumbers := 0.0;
    Number := 0.0;
    I := 0;
    PartLength := 0;
    PartIndex := 1;
    StringPart := '';
    IsFine := True;
    IsThereNumbers := False;
    IsNumberFull := False;

    IsFine := CheckIsStringValid(GivenString);

    If IsFine Then
    Begin
        For I := 1 To Length(GivenString) Do
        Begin

            If (GivenString[I] = '+') Or (I = Length(GivenString)) Then
            Begin
                PartLength := I - PartIndex;

                If I = Length(GivenString) Then
                    PartLength := I - PartIndex + 1;

                StringPart := Copy(GivenString, PartIndex, PartLength);
                PartIndex := I + 1;
                IsNumberFull := True;
            End;

            If IsNumberFull Then
            Begin
                Try
                    Number := StrToFloat(StringPart);
                    IsThereNumbers := True;
                Except
                    WriteLn('Error with StrToFloat transformation.');
                    IsFine := False;
                End;
            End;

            IsNumberFull := False;

            SumOfNumbers := SumOfNumbers + Number;
            Number := 0;
            StringPart := '';
        End;
    End;

    If Not IsFine Then
        AnswerString := 'The string contains invalid characters or their position is incorrect.'
    Else
        AnswerString := GivenString + '=' + FloatToStr(SumOfNumbers);

    If Not IsThereNumbers Then
        AnswerString := 'There are no correct numbers in the line.';

    FindSumFromString := AnswerString;
End;

Function FindAnswerString(ArrayOfSeparators: TArray; GivenString: String): String;

Var
    Separator, Substring, AnswerString: String;
    I, J, K, SpecialLength, LengthOfSeparator: Integer;

Begin
    Separator := '';
    Substring := '';
    AnswerString := '';
    I := 0;
    J := 0;
    K := 0;
    SpecialLength := 0;
    LengthOfSeparator := 0;

    For I := 0 To High(ArrayOfSeparators) Do
    Begin

        Separator := ArrayOfSeparators[I];
        LengthOfSeparator := Length(Separator);
        SpecialLength := Length(GivenString) - LengthOfSeparator + 1;
        J := 1;

        While (J < SpecialLength) Or (J = SpecialLength) Do
        Begin

            Substring := Copy(GivenString, J, LengthOfSeparator);

            If Substring = Separator Then
            Begin
                Delete(GivenString, J, LengthOfSeparator - 1);
                GivenString[J] := '+';
            End;

            SpecialLength := Length(GivenString) - LengthOfSeparator + 1;
            Inc(J);
        End;

    End;

    AnswerString := FindSumFromString(GivenString);

    FindAnswerString := AnswerString;
End;

Procedure ReadingStage(Var Array1: TArray; Var GivenString: String);

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
            Array1 := ReadArrayFromFile(MIN_NUMBER, MAX_NUMBER, MyFile, GivenString);

            If Array1 = Nil Then
                IsAllDone := False;

        Until IsAllDone
    Else
    Begin
        Array1 := ReadArrayFromConsole(MIN_NUMBER, MAX_NUMBER);
        WriteLn('Write the string of numbers between separators.');
        ReadLn(GivenString);
    End;
End;

Procedure WritingStage(AnswerString: String);

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
        WriteStringIntoFile(MyFile, AnswerString);
    End
    Else
        WriteStringIntoConsole(AnswerString);
End;

Var
    ArrayOfSeparators: TArray;
    GivenString, AnswerString: String;

Begin
    ArrayOfSeparators := Nil;
    GivenString := '';

    WritePurpose;
    ReadingStage(ArrayOfSeparators, GivenString);
    AnswerString := FindAnswerString(ArrayOfSeparators, GivenString);
    WritingStage(AnswerString);

    ReadLn;

End.
