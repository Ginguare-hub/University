Program Lab2_1;

Uses
    System.SysUtils;

Type
    TArr = Array Of Real;

Const
    MAX_LENGTH: Integer = 20;
    MIN_LENGTH: Integer = 1;
    MAX_NUM: Real = 12345.0;
    MIN_NUM: Real = -12345.0;

Var
    ArrLength, I: Integer;
    IsCorrect: Boolean;
    Num, MinDiff, CurrDiff, SumOfNums, ArithmMean: Real;
    Arr: TArr;

Begin

    ArrLength := 1;
    I := 0;
    Num := 0;
    ArithmMean := 0;
    MinDiff := 0;
    CurrDiff := 0;
    SumOfNums := 0;
    IsCorrect := True;

    WriteLn('Programm finds the element(s) in the list, that most fits with the arithmetic mean of the series.');

    Repeat

        Write('Enter the number of numbers in the list: ');
        IsCorrect := True;

        Try
            ReadLn(ArrLength);
        Except
            WriteLn('Incorrect input, try again.');
            IsCorrect := False;
        End;

        If IsCorrect And ((ArrLength < MIN_LENGTH) Or (ArrLength > MAX_LENGTH)) Then
        Begin
            WriteLn('The number must fit the range [', MIN_LENGTH, ',', MAX_LENGTH, '].');
            IsCorrect := False;
        End;

    Until IsCorrect;

    Setlength(Arr, ArrLength);

    For I := 0 To High(Arr) Do
    Begin

        Repeat

            Write('Element ', I + 1, ' = ');
            IsCorrect := True;

            Try
                ReadLn(Num);
            Except
                WriteLn('Incorrect input, try again.');
                IsCorrect := False;
            End;

            If IsCorrect And ((Num < MIN_Num) Or (Num > MAX_Num)) Then
            Begin
                WriteLn('The number must fit the range [', MIN_NUM:8:0, ',', MAX_NUM:8:0, '].');
                IsCorrect := False;
            End;

        Until IsCorrect;

        Arr[I] := Num;
        SumOfNums := SumOfNums + Num;
    End;

    ArithmMean := SumOfNums / ArrLength;
    MinDiff := Abs(ArithmMean - Arr[0]);

    For I := 0 To High(Arr) Do
    Begin
        CurrDiff := Abs(ArithmMean - Arr[I]);

        If MinDiff > CurrDiff Then
            MinDiff := CurrDiff;
    End;

    Write('The element(s) ');

    For I := 0 To High(Arr) Do
    Begin
        CurrDiff := Abs(ArithmMean - Arr[I]);

        If MinDiff = CurrDiff Then
            Write(I + 1, ' ');
    End;

    WriteLn('in the list is the number(s), that most fits with the arithmetic mean of the series.');
    ReadLn;

End.
