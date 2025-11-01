Program Project1;

Uses
    System.SysUtils;

Var
    I, J, Number, InputNum: Integer;
    IsShouldStop, IsMustStop: Boolean;

Begin
    InputNum := 1;
    IsMustStop := False;
    IsShouldStop := False;
    J := 2;
    Number := 0;

    ReadLn(InputNum);

    I := 2;

    If InputNum = 1 Then
        WriteLn('2')
    Else
        If InputNum = 2 Then
            WriteLn('3')
        Else
        Begin

            While (Not IsMustStop) Do
            Begin

                IsShouldStop := False;

                For J := 2 To (I - 1) Do
                Begin

                    If (I Mod J = 0) And (Not IsShouldStop) Then
                    Begin
                        IsShouldStop := True;
                    End
                    Else
                        If (Not IsShouldStop) Then
                            IsShouldStop := False;

                End;

                If Not IsShouldStop Then
                Begin
                    //Write(I, ' ');
                    Number := Number + 1;
                End;

                If Number = InputNum Then
                Begin
                    IsMustStop := True;
                    Write(I);
                End;

                I := I + 1;

            End;
        End;
    ReadLn;

End.
