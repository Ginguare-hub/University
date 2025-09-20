Program ArrayOfNumbers;

Uses
    System.SysUtils;

Const
    MAX_NUMBER: Real = 1024.0;
    MIN_NUMBER: Real = -1024.0;
    MAX_LENGHT: Integer = 10;
    MIN_LENGHT: Integer = 1;


Var
    A: Array Of Real;
    B: Array Of Real;
    Lenght: Integer;
    I: Integer;
    N: Real;
    IsIncorrect: Boolean;

Begin

    Lenght := 0;
    I := 0;
    N := 0.0;
    IsIncorrect := False;

    Repeat
        Try
            Write('Введите число элементов массива A: ');
            ReadLn(Lenght);
            IsIncorrect := False;
            If (Lenght < MIN_LENGHT) Or (Lenght > MAX_LENGHT) Then
            Begin
                WriteLn('Число элементов массива должно лежать в диапазоне [', MIN_LENGHT, ';', MAX_LENGHT, '], попробуйте ещё раз.');
                IsIncorrect := True;
            End;
        Except
            WriteLn('Ошибка ввода, повторите попытку.');
            IsIncorrect := True;
        End;
    Until IsIncorrect = False;

    SetLength(A, Lenght);
    SetLength(B, Lenght);

    For I := 0 To High(A) Do
    Begin

        Repeat
        Try
            IsIncorrect := False;
            Write('Введите N', I + 1, ' элемент массива: ');
            ReadLn(N);
            If (N < MIN_NUMBER) Or (N > MAX_NUMBER) Then
            Begin
                WriteLn('Значение элемента массива должно лежать в диапазоне [', MIN_NUMBER, ';', MAX_NUMBER, '], попробуйте ещё раз.');
                IsIncorrect := True;
            End;
        Except
            WriteLn('Ошибка ввода, повторите попытку.');
            IsIncorrect := True;
        End;
        Until IsIncorrect = False;

        A[I] := N;
    End;

    For I := 0 To High(A) Do
        B[I] := 2 * A[I] + I + 1;

    For I := 0 To (Lenght - 1) Do
        WriteLn('B[', I, '] = ', B[I]:4:4);

    ReadLn;

End.
