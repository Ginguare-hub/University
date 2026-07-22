Program List;

{$APPTYPE CONSOLE}
{$R *.res}

Uses
    System.SysUtils;

Type
    UnidirNode = ^UniElement;

    UniElement = Record
        Data: Int64;
        Power: Int64;
        Next: UnidirNode;
    End;

    TArrayOI = Array Of Int64;

Function ReadAndVerify(Const MIN_NUMBER, MAX_NUMBER: Int64; MyString: String; Var IsStop: Boolean): Int64;
Var
    IsCorrect: Boolean;
    Number: Int64;
    NumberStr: String;
Begin
    IsCorrect := True;
    Number := 0;

    Repeat

        Write(MyString);
        IsCorrect := True;

        If Not IsStop Then
        Begin
            Try
                ReadLn(NumberStr);
                If (UpperCase(NumberStr) = UpperCase('стоп')) Or (UpperCase(NumberStr) = UpperCase('stop')) Then
                Begin
                    IsStop := True;
                    IsCorrect := False;
                End
                Else
                    Number := StrToInt(NumberStr);
            Except
                WriteLn('Некорректный ввод, повторите снова.');
                IsCorrect := False;
            End;

            If IsCorrect And (Not((Number >= MIN_NUMBER) And (Number <= MAX_NUMBER)) And Not(Number = 0)) Then
            Begin
                WriteLn('Число должно входить в диапазон [', MIN_NUMBER, ',', MAX_NUMBER, '] или равняться 0.');
                IsCorrect := False;
            End;
        End;

    Until IsCorrect Or IsStop;

    ReadAndVerify := Number;
End;

Procedure Print(X: UnidirNode; Polynome: String);
Begin
    X := X^.Next;

    Write(Polynome);

    If X <> Nil Then
    Begin
        If X^.Data > 0 Then
            Write(IntToStr(X^.Data) + 'x^' + IntToStr(X^.Power) + ' ')
        Else
            Write('-' + IntToStr(Abs(X^.Data)) + 'x^' + IntToStr(X^.Power) + ' ');
        X := X^.Next;
    End;

    While X <> Nil Do
    Begin
        If X^.Data > 0 Then
            Write('+' + IntToStr(X^.Data) + 'x^' + IntToStr(X^.Power) + ' ')
        Else
            Write('-' + IntToStr(Abs(X^.Data)) + 'x^' + IntToStr(X^.Power) + ' ');
        X := X^.Next;
    End;
End;

Procedure Append(Numb, Pow: Int64; Head: UnidirNode);
Var
    Temp: UnidirNode;
Begin
    Temp := Head;
    While Temp^.Next <> Nil Do
    Begin
        Temp := Temp^.Next;
    End;

    New(Temp^.Next);
    Temp^.Next.Data := Numb;
    Temp^.Next.Power := Pow;
    Temp^.Next^.Next := Nil;
End;

Function Equality(HeadP, HeadS: UnidirNode): Boolean;
Var
    TempP, TempS: UnidirNode;
    IsEqual: Boolean;
Begin
    IsEqual := True;

    TempP := HeadP;
    TempS := HeadS;
    While (TempP^.Next <> Nil) And (TempS^.Next <> Nil) Do
    Begin
        TempP := TempP^.Next;
        TempS := TempS^.Next;

        If (TempP^.Data <> TempS^.Data) Or (TempP^.Power <> TempS^.Power) Then
            IsEqual := False;
    End;

    If IsEqual Then
        WriteLn('Многочлены равны.')
    Else
        WriteLn('Многочлены НЕ равны.');

    Equality := IsEqual;
End;

Function Power(Number, Pow: Int64): Int64;
Var
    I, Answer: Int64;
Begin
    Power := -1;
    Answer := Number;

    If Pow = 1 Then
        Answer := Number
    Else
        If (Pow = 0) And (Number <> 0) Then
            Answer := 1;

    For I := 2 To Pow Do
        Answer := Answer * Number;

    Power := Answer;
End;

Function Meaning(Head: UnidirNode; Number: Int64): Int64;
Var
    Answer: Int64;
    Temp: UnidirNode;
Begin
    Answer := 0;

    Temp := Head;
    While (Temp^.Next <> Nil) Do
    Begin
        Temp := Temp^.Next;

        Answer := Answer + Temp^.Data * Power(Number, Temp^.Power);
    End;

    WriteLn('Значение в точке ' + IntToStr(Number) + ' равно ' + IntToStr(Answer));
    Meaning := Answer;
End;

Procedure Add(Var HeadAnswer: UnidirNode; HeadQ, HeadR: UnidirNode);
Var
    TempQ, TempR, TempAnswer: UnidirNode;
    IsEqual: Boolean;
Begin
    IsEqual := True;

    TempQ := HeadQ;
    TempR := HeadR;

    TempAnswer := HeadAnswer;

    TempQ := TempQ^.Next;
    TempR := TempR^.Next;

    While Not((TempQ = Nil) And (TempR = Nil)) Do
    Begin

        If ((TempR = Nil) And (TempQ <> Nil) Or ((TempR <> Nil) And (TempQ <> Nil) And (TempQ^.Power < TempR^.Power))) Then
        Begin
            Append(TempQ^.Data, TempQ^.Power, TempAnswer);
            TempQ := TempQ^.Next;
        End
        Else
            If ((TempR <> Nil) And (TempQ = Nil) Or ((TempR <> Nil) And (TempQ <> Nil) And (TempQ^.Power > TempR^.Power))) Then
            Begin
                Append(TempR^.Data, TempR^.Power, TempAnswer);
                TempR := TempR^.Next
            End
            Else
                If (TempR <> Nil) And (TempQ <> Nil) And (TempQ^.Power = TempR^.Power) Then
                Begin
                    Append((TempR^.Data + TempQ^.Data), TempR^.Power, TempAnswer);
                    TempQ := TempQ^.Next;
                    TempR := TempR^.Next;
                End;

    End;

    Print(HeadAnswer, 'Результат суммирования: ');
End;

Var
    UniHeadP, UniHeadS, UniHeadAnswer: UnidirNode;
    Number, Pow, X: Int64;
    Arr: TArrayOI;
    IsStop: Boolean;

Begin
    UniHeadP := Nil;
    New(UniHeadP);
    UniHeadP^.Next := Nil;

    UniHeadS := Nil;
    New(UniHeadS);
    UniHeadS^.Next := Nil;

    UniHeadAnswer := Nil;
    New(UniHeadAnswer);
    UniHeadAnswer^.Next := Nil;

    Number := 0;
    X := 0;
    Pow := 0;
    IsStop := False;

    Writeln('Введите ''Стоп'' если закончили вводить номера телефонов.'#13#10);

    WriteLn('Введите многочлен P: ');
    Repeat
        Number := ReadAndVerify(-999, 999, ('Коэффициент при x^' + IntToStr(Pow) + ': '), IsStop);
        If (Not IsStop) And (Number <> 0) Then
            Append(Number, Pow, UniHeadP);
        Pow := Pow + 1;
    Until IsStop;

    Pow := 0;
    IsStop := False;

    Writeln('Введите многочлен S: ');
    Repeat
        Number := ReadAndVerify(-999, 999, ('Коэффициент при x^' + IntToStr(Pow) + ': '), IsStop);
        If (Not IsStop) And (Number <> 0) Then
            Append(Number, Pow, UniHeadS);
        Pow := Pow + 1;
    Until IsStop;

    IsStop := False;

    Writeln(power(5, 5));

    WriteLn(#13#10'Воспроизведение многочлена P: '#13#10);
    Print(UniHeadP, 'P(x) = ');

    WriteLn(#13#10'Воспроизведение многочлена S: ');
    Print(UniHeadS, 'S(x) = ');

    WriteLn(#13#10#13#10'Реализация функции сравнения многочленов: ');
    Equality(UniHeadP, UniHeadS);

    WriteLn(#13#10'Реализация функции вычисления значения многочлена в точке: ');
    X := ReadAndVerify(-100, 100, 'Введите число x: ', IsStop);
    Meaning(UniHeadP, X);
    Meaning(UniHeadS, X);

    WriteLn(#13#10'Воспроизведение функции суммирования многочленов: ');
    Add(UniHeadAnswer, UniHeadP, UniHeadS);
    WriteLn;

    ReadLn;
End.
