Program Sum;

Uses
    System.SysUtils;

Var
    N, I, SumOfNumbers, Number: Integer;

Begin
    N := 1;
    I := 1;
    SumOfNumbers := 0;
    Number := 1;

    Repeat
    Begin
        Try
            ReadLn(N);
            If N < 1 Then
                WriteLn('Степенью может являться только целое положительное число');
        Except
            WriteLn('Неправильный ввод, повторите попытку снова.');
        End;
    End;
    Until (N > 0) And (N < 30);

    If (N > 1) Or (N = 1) Then
    Begin
        For I := 1 To N Do
        Begin
            Number := Number * -2;
            SumOfNumbers := SumOfNumbers + Number;
        End;
    End
    Else
        WriteLn(SumOfNumbers);

    WriteLn(SumOfNumbers);
    ReadLn;

End.
