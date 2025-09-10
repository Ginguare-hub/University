Program Project1;

Uses
    System.SysUtils;

Var
    A, B, ArithmMean, GeomMean: Double;
    IsIncorrect, IsAllCorrect: Boolean;
    Checker: Integer;

Const
    MIN: Integer = 0;
    MAX: Integer = 999;

Begin
    WriteLn('Программа считает среднее арифметическое и среднее геометрическое для чисел A и B, и показывает, что среднее арифметическое этих чисел не меньше их среднего геометрического.');

    A := 1.0;
    B := 1.0;
    ArithmMean := 1.0;
    GeomMean := 1.0;
    Checker := 0;
    IsIncorrect := True;
    IsAllCorrect := True;

    While IsAllCorrect Do
    Begin

        While IsIncorrect Do
        Begin
            Write('Введите число A: ');
            Try
                ReadLn(A);
                If ((A > MIN) Or (A = MIN)) And ((A < MAX) Or (A = MAX)) Then
                    IsIncorrect := False
                Else
                Begin
                    WriteLn('Число A должно быть положительным и лежать в диапазоне (', MIN, ';', MAX, '), попробуйте ещё раз.');
                    IsIncorrect := True;
                End;
            Except
                WriteLn('Ошибка в записи числа А, повториет попытку.');
            End;
        End;

        IsIncorrect := True;

        While IsIncorrect Do
        Begin
            Write('Введите число B: ');
            Try
                ReadLn(B);
                If ((B > MIN) Or (B = MIN)) And ((B < MAX) Or (B = MAX)) Then
                    IsIncorrect := False
                Else
                Begin
                    WriteLn('Число B должно быть положительным и лежать в диапазоне (', MIN, ';', MAX, '), попробуйте ещё раз.');
                    IsIncorrect := True;
                End;
            Except
                WriteLn('Ошибка в записи числа B, повториет попытку.');
            End;
        End;

        IsIncorrect := True;

        ArithmMean := (A + B) / 2;
        GeomMean := Sqrt(A * B);

        If (ArithmMean < GeomMean) Then
            WriteLn('Среднее арифметическое меньше чем среднее геометрическое заданных чисел.')
        Else
            WriteLn('Cреднее арифметическое заданных чисел не меньше их среднего геометрического.');

        WriteLn('Если хотите продолжить, введите число 1, если нет, то число 2');

        Try
            ReadLn(Checker);
            If Checker = 1 Then
            Begin
                WriteLn('');
                WriteLn('Давайте заново');
            End
            Else
                IsAllCorrect := False;
        Except
            IsAllCorrect := False
        End;

    End;

End.
