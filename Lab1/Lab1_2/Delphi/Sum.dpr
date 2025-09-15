Program Sum;

Uses
    System.SysUtils;

Var
    N, I, SumOfNumbers, Number: Integer;
    IsAllCorrect: Boolean;

Const
    MAX: Integer = 29;
    MIN: Integer = 1;

Begin
    N := 1;
    I := 1;
    SumOfNumbers := 0;
    Number := 1;
    IsAllCorrect := True;

    WriteLn('Программа считает сумму заданную в условии задачи №2 варианта №20');

    Repeat
    Begin
        Try
            Write('Введите верхнюю границу суммирования: ');
            ReadLn(N);
            IsAllCorrect := True;
            If (N < MIN) Or (N > MAX) Then
            Begin
                WriteLn('Степенью может являться только целое положительное число, которое принадлежит диапазону [', MIN, ';', MAX, '].');
                IsAllCorrect := False;
            End;
        Except
            WriteLn('Неправильный ввод, повторите попытку снова.');
            IsAllCorrect := False;
        End;
    End;
    Until IsAllCorrect;

    For I := 1 To N Do
    Begin
        Number := Number * -2;
        SumOfNumbers := SumOfNumbers + Number;
    End;

    Write('Сумма равна ');
    WriteLn(SumOfNumbers);
    ReadLn;

End.
