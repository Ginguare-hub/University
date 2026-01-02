Program Lab3_3;

uses
  System.SysUtils;

Type
    TArray = Array Of Integer;

Procedure WritePurpose;

Begin
    WriteLn('Sorts an array using natural merge sorting.');
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

Function ReadArrayFromFile(Const MIN_NUMBER, MAX_NUMBER: Integer; Var InputFile: TextFile): TArray;

Const
    MIN_LENGTH: Integer = 1;
    MAX_LENGTH: Integer = 100;

Var
    I, ArrayLength, ArrayElement: Integer;
    Array1: TArray;
    IsErrorNotFound: Boolean;

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
        For I := 0 To High(Array1) Do
            If IsErrorNotFound Then
            Begin

                If EOF(InputFile) Then
                Begin
                    WriteLn('Error, not enough data in file.');
                    Array1 := Nil;
                    IsErrorNotFound := False;
                End;

                Try
                    Read(InputFile, Array1[I]);
                Except
                    WriteLn('Incorrect numeric data: array element.');
                    Array1 := Nil;
                    IsErrorNotFound := False;
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
    I, ArrayLength, ArrayElement: Integer;

Begin
    I := 0;
    ArrayLength := 0;
    ArrayElement := 0;

    ArrayLength := ReadAndVerify(MIN_LENGTH, MAX_LENGTH, 'Write array length: ');
    SetLength(Array1, ArrayLength);

    For I := 0 To High(Array1) Do
    Begin
        Write('Write element [', I, '] of array: ');
        ArrayElement := ReadAndVerify(MIN_NUMBER, MAX_NUMBER, '');
        Array1[I] := ArrayElement;
    End;

    ReadArrayFromConsole := Array1;
End;

Procedure WriteArrayIntoFile(Var OutputFile: TextFile; Array1: TArray);

Var
    I: Integer;
    IsReady: Boolean;

Begin
    I := 0;
    IsReady := True;

    Try
        Rewrite(OutputFile);
    Except
        IsReady := False;
    End;

    If IsReady Then
    Begin
        WriteLn(OutputFile, 'The result array is: ');

        For I := 0 To High(Array1) Do
            Write(OutputFile, Array1[I], ' ');

        WriteLn(OutputFile);
    End
    Else
        WriteLn('The unexpected error is found.');

    CloseFile(OutputFile);
End;

Procedure WriteArrayIntoConsole(Array1: TArray);

Var
    I: Integer;

Begin
    I := 0;

    WriteLn('The result array is: ');

    For I := 0 To High(Array1) Do
    Begin
        Write(Array1[I], ' ');
    End;

    WriteLn;
End;

Function Merge(Array1: TArray; Array2: TArray): TArray;

Var
    I, J, Index, NewIndex: Integer;
    AnswerArray: TArray;

Begin
    I := 0;
    J := 0;
    Index := 0;
    NewIndex := 0;
    AnswerArray := [];

    SetLength(AnswerArray, Length(Array1) + Length(Array2));

    While ((Index < High(AnswerArray)) Or (Index = High(AnswerArray))) And ((I < High(Array1)) Or (I = High(Array1))) And ((J <= High(Array2)) Or (J <= High(Array2))) Do
    Begin

        If ((J < Length(Array2)) And (I < Length(Array1)) And (Array1[I] > Array2[J])) Then
        Begin
            AnswerArray[Index] := Array2[J];
            Inc(J);
        End
        Else
            If ((I < Length(Array1)) And (J < Length(Array2))) Then
            Begin
                AnswerArray[Index] := Array1[I];
                Inc(I);
            End;

        Inc(Index);
    End;

    If (I = Length(Array1)) And (J < Length(Array2)) Then
    Begin
        For NewIndex := Index To High(AnswerArray) Do
        Begin
            AnswerArray[NewIndex] := Array2[J];
            Inc(J);
        End;
    End
    Else
        If ((I < Length(Array1)) And (J = Length(Array2))) Then
        Begin
            For NewIndex := Index To High(AnswerArray) Do
            Begin
                AnswerArray[NewIndex] := Array1[I];
                Inc(I);
            End;
        End;

    Merge := AnswerArray;
End;

Procedure SortArray(Var GivenArray: TArray);

Var
    I, J, K, L, ArrayLength, AmountOfMerges, AmountOfMergesM1: Integer;
    Array1, Array2, Array3, ArrayOfLabelIndices, NewArray, MergedArray: TArray;

Begin
    I := Low(GivenArray);
    J := 0;
    K := 0;
    ArrayLength := 0;
    AmountOfMerges := 0;
    AmountOfMergesM1 := 0;
    Array1 := [];
    Array2 := [];
    Array3 := [];
    ArrayOfLabelIndices := [];
    NewArray := [];
    MergedArray := [];

    NewArray := Copy(GivenArray);

    Repeat
        I := Low(GivenArray);
        J := 0;
        K := 0;
        L := 0;
        ArrayLength := 0;

        While I < High(GivenArray) Do
        Begin

            If GivenArray[I] > GivenArray[I + 1] Then
            Begin
                Inc(ArrayLength);
            End;

            Inc(I);
        End;

        SetLength(ArrayOfLabelIndices, ArrayLength);
        I := Low(GivenArray);

        While I < High(GivenArray) Do
        Begin

            If GivenArray[I] > GivenArray[I + 1] Then
            Begin
                ArrayOfLabelIndices[J] := I;
                Inc(J);
            End;

            Inc(I);
        End;

        AmountOfMerges := (ArrayLength + 1) Div 2;
        AmountOfMergesM1 := AmountOfMerges - 1;

        For I := 0 To AmountOfMergesM1 Do
        Begin

            If I = 0 Then
            Begin
                Array1 := Copy(GivenArray, 0, ArrayOfLabelIndices[I] + 1);
                Array2 := Copy(GivenArray, ArrayOfLabelIndices[High(ArrayOfLabelIndices)] + 1, High(GivenArray) - ArrayOfLabelIndices[High(ArrayOfLabelIndices)]);
            End
            Else
            Begin
                Array1 := Copy(GivenArray, ArrayOfLabelIndices[I - 1] + 1, ArrayOfLabelIndices[I] - ArrayOfLabelIndices[I - 1]);
                Array2 := Copy(GivenArray, ArrayOfLabelIndices[ArrayLength - I - 1] + 1, ArrayOfLabelIndices[ArrayLength - I] - ArrayOfLabelIndices[ArrayLength - I - 1]);
            End;

            If (Odd(High(ArrayOfLabelIndices)) And (I = 0)) Then
                Array3 := Copy(GivenArray, ArrayOfLabelIndices[High(ArrayOfLabelIndices) Div 2] + 1, ArrayOfLabelIndices[(High(ArrayOfLabelIndices) Div 2) + 1] - ArrayOfLabelIndices[High(ArrayOfLabelIndices) Div 2]);

            SetLength(MergedArray, Length(Array1) + Length(Array2));
            MergedArray := Merge(Array1, Array2);

            For L := 0 To High(MergedArray) Do
            Begin
                NewArray[K] := MergedArray[L];
                Inc(K);
            End;

            If (I = AmountOfMergesM1) And (Odd(High(ArrayOfLabelIndices))) Then
            Begin

                For L := 0 To High(Array3) Do
                Begin
                    NewArray[K] := Array3[L];
                    Inc(K);
                End;

            End;

        End;

        GivenArray := NewArray;

    Until ArrayLength = 0;
End;

Procedure ReadingStage(Var Array1: TArray);

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
            Array1 := ReadArrayFromFile(MIN_NUMBER, MAX_NUMBER, MyFile);

            If Array1 = Nil Then
                IsAllDone := False;

        Until IsAllDone
    Else
        Array1 := ReadArrayFromConsole(MIN_NUMBER, MAX_NUMBER);
End;

Procedure WritingStage(Array1: TArray);

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
        WriteArrayIntoFile(MyFile, Array1);
    End
    Else
        WriteArrayIntoConsole(Array1);
End;

Var
    Array1: TArray;

Begin
    Array1 := Nil;

    WritePurpose;
    ReadingStage(Array1);
    SortArray(Array1);
    WritingStage(Array1);

    ReadLn;

End.
