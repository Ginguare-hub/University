Program Lab1_3;

{$APPTYPE CONSOLE}
{$R *.res}

Uses
    System.SysUtils;

Type
    UnidirNode = ^UniElement;

    UniElement = Record
        PhoneNumber: Integer;
        FirstName: String;
        LastName: String;
        Surname: String;
        Next: UnidirNode;
    End;

    TArrayOI = Array Of Integer;

Function ReadAndVerify(Const MIN_NUMBER, MAX_NUMBER: Integer; MyString: String): Integer;
Var
    IsCorrect: Boolean;
    Number: Integer;
Begin
    IsCorrect := True;
    Number := 0;

    Repeat

        Write(MyString);
        IsCorrect := True;

        Try
            ReadLn(Number);
        Except
            WriteLn('Некорректный ввод, повторите снова.');
            IsCorrect := False;
        End;

        If IsCorrect And (Not((Number >= MIN_NUMBER) And (Number <= MAX_NUMBER))) Then
        Begin
            WriteLn('Число должно входить в диапазон [', MIN_NUMBER, ',', MAX_NUMBER, '] либо равняться 0.');
            IsCorrect := False;
        End;

    Until IsCorrect;

    ReadAndVerify := Number;
End;

//Procedure Make(var Head: UnidirNode);
//Var
//I: Integer;
//Current: UnidirNode;
//Begin
//New(Head);
//Current := Head;
//
//While Current^.Next.Next <> Nil Do
//Begin
//Readln(Current^.Data);
//New(Current^.Next);
//Current := Current^.Next;
//End;
//
//New(Current^.Next);
//Current := Current^.Next;
//Current^.Next := Nil;
//End;

Procedure Print(X: UnidirNode);
Begin
    X := X^.Next;
    While X <> Nil Do
    Begin
        WriteLn;
        WriteLn('ФИО: ', X^.LastName, ' ', X^.FirstName, ' ', X^.Surname);
        WriteLn('Номер телефона: ', X^.PhoneNumber);
        X := X^.Next;
    End;
End;

//Функция сравнения двух ФИО
Function CompareFIO(Const FirstName1, LastName1, Surname1: String; Const FirstName2, LastName2, Surname2: String): Integer;
Var
    FIO1, FIO2: String;
Begin
    FIO1 := AnsiUpperCase(LastName1 + FirstName1 + Surname1);
    FIO2 := AnsiUpperCase(LastName2 + FirstName2 + Surname2);

    If FIO1 < FIO2 Then
        Result := -1
    Else
        If FIO1 > FIO2 Then
            Result := 1
        Else
            Result := 0;
End;

Procedure Insert(Const FirstName, LastName, Surname: String; PhoneNumber: Integer; Var Head: UnidirNode);
Var
    NewNode, Current, Previous: UnidirNode;
Begin
    New(NewNode);
    NewNode^.FirstName := FirstName;
    NewNode^.LastName := LastName;
    NewNode^.Surname := Surname;
    NewNode^.PhoneNumber := PhoneNumber;
    NewNode^.Next := Nil;

    If Head^.Next = Nil Then
    Begin
        Head^.Next := NewNode;
    End
    Else
    Begin
        Current := Head^.Next;
        Previous := Head;

        While (Current <> Nil) And (CompareFIO(Current^.FirstName, Current^.LastName, Current^.Surname, FirstName, LastName,
            Surname) < 0) Do
        Begin
            Previous := Current;
            Current := Current^.Next;
        End;

        NewNode^.Next := Current;
        Previous^.Next := NewNode;
    End;
End;

Procedure FindLastNameByPhoneNumber(Head: UnidirNode);
Var
    Temp: UnidirNode;
    PhoneNumber: Integer;
    IsAnyone: Boolean;
Begin
    Temp := Head^.Next;
    PhoneNumber := 0;
    IsAnyone := False;

    PhoneNumber := ReadAndVerify(1_000_000, 9_999_999, 'Введите номер телефона абонента, фамилию которого хотите найти: '#13#10'> ');

    While Temp <> Nil Do
    Begin
        If PhoneNumber = Temp^.PhoneNumber Then
        Begin
            WriteLn('Фамилия владельца номера телефона: ', Temp^.LastName);
            IsAnyOne := True;
        End;
        Temp := Temp^.Next;
    End;

    If Not(IsAnyone) Then
        WriteLn('Нет абонента с таким номером --- ', PhoneNumber);
End;

Procedure FindPhoneNumberByLastName(Head: UnidirNode);
Var
    Temp: UnidirNode;
    LastName: String;
    IsAnyone: Boolean;
Begin
    Temp := Head^.Next;
    LastName := '';
    IsAnyone := False;

    Write('Введите фамилию абонента, номер телефона котрого хотите найти: '#13#10'> ');
    ReadLn(LastName);

    While Temp <> Nil Do
    Begin
        If LastName = Temp^.LastName Then
        Begin
            WriteLn('Номер телефона абонента: ', Temp^.PhoneNumber, '  ---  ', Temp^.LastName, ' ', Temp^.FirstName, ' ', Temp^.Surname);
            IsAnyone := True;
        End;
        Temp := Temp^.Next;
    End;

    If Not(IsAnyone) Then
        WriteLn('Нет абонента с такой фамилией --- ', LastName);
End;

Procedure Append(Const FirstName, LastName, Surname: String; PhoneNumber: Integer; Var Head: UnidirNode);
Var
    Temp: UnidirNode;
    FIO: String;
Begin
    Temp := Head;

    While Temp^.Next <> Nil Do
        Temp := Temp^.Next;

    New(Temp^.Next);
    Temp^.Next.PhoneNumber := PhoneNumber;
    Temp^.Next.FirstName := FirstName;
    Temp^.Next.LastName := LastName;
    Temp^.Next.Surname := Surname;
    Temp^.Next^.Next := Nil;
End;

Procedure Find(Var Arr: TArrayOI);
Var
    NewArr: TArrayOI;
    I, ArrLength: Integer;
Begin
    NewArr := Nil;
    ArrLength := 0;

    For I := 0 To High(Arr) Do
    Begin
        If (Arr[I] >= 1_000_000) And (Arr[I] <= 9_999_999) Then
        Begin
            ArrLength := ArrLength + 1;
            SetLength(NewArr, ArrLength);
            NewArr[High(NewArr)] := Arr[I];
        End;
    End;

    Arr := Copy(NewArr);
End;

Var
    UniHead: UnidirNode;
    Number: Integer;
    Surname, FirstName, LastName: String;
    Arr: TArrayOI;

Begin
    UniHead := Nil;
    New(UniHead);
    UniHead^.Next := Nil;
    Surname := '';
    FirstName := '';
    LastName := '';
    Number := 0;

    LastName := '0';

    Writeln('Введите число 0 вместо фамилии если закончили ввод абонентов.');

    WriteLn;
    Write('Введите фамилию: '#13#10'> ');
    ReadLn(LastName);

    While LastName <> '0' Do
    Begin
        Write('Введите имя: '#13#10'> ');
        ReadLn(FirstName);
        Write('Введите отчество: '#13#10'> ');
        ReadLn(Surname);
        Number := ReadAndVerify(1_000_000, 9_999_999, 'Введите номер телефона: '#13#10'> ');
        Insert(FirstName, LastName, Surname, Number, UniHead);
        WriteLn;
        Write('Введите фамилию: '#13#10'> ');
        ReadLn(LastName);
    End;

    WriteLn(#13#10'Воспроизведение упорядоченного однонаправленного списка абонентов: ');
    Print(UniHead);

    WriteLn;
    FindLastNameByPhoneNumber(UniHead);

    WriteLn;
    FindPhoneNumberByLastName(UniHead);

    ReadLn;

End.
