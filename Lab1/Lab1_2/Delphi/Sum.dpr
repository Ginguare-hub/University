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

    Repeat
    Begin
        Try
            Write('Ââåäèòå âåðõíþþ ãðàíèöó ñóììèðîâàíèÿ: ');
            ReadLn(N);
            IsAllCorrect := True;
            If (N < MIN) Or (N > MAX) Then
            Begin
                WriteLn('Ñòåïåíüþ ìîæåò ÿâëÿòüñÿ òîëüêî öåëîå ïîëîæèòåëüíîå ÷èñëî, êîòîðîå ïðèíàäëåæèò äèàïàçîíó [', MIN, ';', MAX, '].');
                IsAllCorrect := False;
            End;
        Except
            WriteLn('Íåïðàâèëüíûé ââîä, ïîâòîðèòå ïîïûòêó ñíîâà.');
            IsAllCorrect := False;
        End;
    End;
    Until IsAllCorrect;

    For I := 1 To N Do
    Begin
        Number := Number * -2;
        SumOfNumbers := SumOfNumbers + Number;
    End;

    WriteLn(SumOfNumbers);
    ReadLn;

End.
