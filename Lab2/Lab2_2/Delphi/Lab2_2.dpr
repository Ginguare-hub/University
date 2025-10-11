Program Lab2_2;

Uses
    System.SysUtils;

Function GetPrimeNumber(Number: Integer): Integer;
Begin

    Var
        IsNumberOdd: Boolean;
    Var
        Count, I: Integer;
    Var
        CountOfPN: Integer;
    Var
        IsFound: Boolean;


    IsFound := False;
    Count := 2;
    CountOfPN := 2;
    IsNumberOdd := Odd(Number);

    If Number = 1 Then
        GetPrimeNumber := 2
    Else
        If Number = 2 Then
            GetPrimeNumber := 3;

    If Number > 2 Then
    Begin

        While (CountOfPN < Number) Do
        Begin

            IsFound := False;
            Count := 2;

            For I := 2 To Count Do
            Begin

                If ((Not IsFound) And ((Count Mod I) = 0)) Then
                Begin
                    IsFound := True
                End
                Else
                If Not IsFound Then
                    CountOfPN := CountOfPN + 1;

            End;

            Count := Count + 1;
        End;

        GetPrimeNumber := Count - 1;

    End;

End;

Var
    N: Integer;
    IsCorrect: Boolean;

Begin

    WriteLn(GetPrimeNumber(3));

    ReadLn;
End.
