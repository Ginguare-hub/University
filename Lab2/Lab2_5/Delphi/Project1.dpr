Program Project1;

Uses
    System.SysUtils;

Type
    TArrayOI = Array Of Integer;

Procedure WritePurpose;

Begin
    WriteLn('Programm modify sequence so that all zero elements appear first, followed by the negative elements, and then the positive elements.');
End;

Function ReadAndVerify(Const MIN_NUMBER, MAX_NUMBER: Integer; MyString: String): Integer;

Var
    IsCorrect: Boolean;
    Number: Integer;

Begin

    Number := 0;
    IsCorrect := True;

    Repeat

        WriteLn(MyString);
        Write('> ');
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

Function CreateArray: TArrayOI;

Const
    MIN_LENGTH: Integer = 1;
    MAX_LENGTH: Integer = 30;
    MIN_NUMBER: Integer = -100000;
    MAX_NUMBER: Integer = 100000;

Var
    MyArray: TArrayOI;
    I, Number, ArrLength: Integer;
    IsCorrect: Boolean;

Begin
    I := 0;
    Number := 0;
    ArrLength := 0;
    IsCorrect := False;

    ArrLength := ReadAndVerify(MIN_LENGTH, MAX_LENGTH, 'Write length of array: ');
    SetLength(MyArray, ArrLength);

    For I := 0 To High(MyArray) Do
    Begin

        Repeat

            Write('Element of array[', I, '] = ');
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

        MyArray[I] := Number;
    End;

    CreateArray := MyArray;
End;

Procedure WriteArray(MyArray: TArrayOI);

Var
    I: Integer;

Begin
    I := 0;
    For I := 0 To High(MyArray) Do
        WriteLn(MyArray[I], ' ');
End;

Procedure ChangeArray(Var MyArray: TArrayOI);

Var
    I, J: Integer;

Begin
    I := 0;
    J := 0;

    For I := 0 To High(MyArray) Do
        For J := 0 To High(MyArray) Do
            If (MyArray[J] = 0) And (MyArray[I] <> 0) And (I < J) Then
            Begin
                MyArray[J] := MyArray[J] + MyArray[I];
                MyArray[I] := MyArray[J] - MyArray[I];
                MyArray[J] := MyArray[J] - MyArray[I];
            End;

    For I := 0 To High(MyArray) Do
        For J := 0 To High(MyArray) Do
            If (MyArray[J] < 0) And (MyArray[I] <> 0) And (Not(MyArray[I] < 0)) And (I < J) Then
            Begin
                MyArray[J] := MyArray[J] + MyArray[I];
                MyArray[I] := MyArray[J] - MyArray[I];
                MyArray[J] := MyArray[J] - MyArray[I];
            End;
End;

Var
    ArrayA: TArrayOI;

Begin
    WritePurpose;
    ArrayA := CreateArray;
    ChangeArray(ArrayA);
    WriteArray(ArrayA);

    ReadLn;
End.
