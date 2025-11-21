Program Project1;

Uses
    System.SysUtils;

Type
    TArrayOI = Array Of Integer;

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

Function ReadArray: TArrayOI;

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

    ReadArray := MyArray;
End;

Begin

    ReadArray;

//    For I := 1 To 3 Do
//    Begin
//        If (I = 1) And  Then
//
//    End;


    Read;
End.
