Program Homework1_1;

uses
  System.SysUtils;

Var
    NumOne, NumTwo, NumThree, First, Second, Third: Integer;
    IsAllCorrect: Boolean;

Begin
    NumOne := 0;
    NumTwo := 0;
    NumThree := 0;
    First := 0;
    Second := 0;
    Third := 0;

    WriteLn('Программа сравнивает три целых заданных числа, введите числа.');

    While True Do
    Begin

        Write('Введите первое число: ');
        ReadLn(NumOne);
        Write('Введите второе число: ');
        ReadLn(NumTwo);
        Write('Введите третье число: ');
        ReadLn(NumThree);

        If ((NumOne < NumTwo) And (NumOne < NumThree)) Or ((NumOne < NumTwo) And (NumOne = NumThree)) Or ((NumOne = NumTwo) And (NumOne < NumThree)) Then
        Begin
            First := NumOne;
            If NumTwo > NumThree Then
            Begin
                Second := NumThree;
                Third := NumTwo;
            End
            Else
            Begin
                Second := NumTwo;
                Third := NumThree;
            End;
        End
        Else
        Begin
            If (NumTwo < NumThree) Or (NumTwo = NumThree) Then
            Begin
                First := NumTwo;
                If NumOne > NumThree Then
                Begin
                    Second := NumThree;
                    Third := NumOne;
                End
                Else
                Begin
                    Second := NumOne;
                    Third := NumThree;
                End;
            End
            Else
            Begin
                First := NumThree;
                If NumOne > NumTwo Then
                Begin
                    Second := NumTwo;
                    Third := NumOne;
                End
                Else
                Begin
                    Second := NumOne;
                    Third := NumTwo;
                End;
            End;
        End;

        If (NumOne = NumTwo) And (NumOne = NumThree) Then
        Begin
            First := NumOne;
            Second := NumOne;
            Third := NumOne;
        End;

        Write(First);
        If First = Second Then
            Write(' = ')
        Else
            Write(' < ');
        Write(Second);
        If Third = Second Then
            Write(' = ')
        Else
            Write(' < ');
        WriteLn(Third);
        WriteLn('Давайте сравним новые числа.');
    End;

End.
