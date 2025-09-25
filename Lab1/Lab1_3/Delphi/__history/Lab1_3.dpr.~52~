Program Lab1_3;

Uses
    System.SysUtils;

Const
    A: Double = 7.622;
    B: Double = 8.59;
    C: Double = 5.0;
    UPPER_LIMIT: Double = 0.5;
    LOWER_LIMIT: Double = 1.0;
    MAX_ITERATIONS: Integer = 20;

Var
    X0, X1, Derivative, EquivEquation, Epsilon, Diff: Real;
    Count: Integer;
    IsCorrect: Boolean;

Begin

    X0 := 0.0;
    X1 := 0.0;
    Derivative := 0.0;
    EquivEquation := 0.0;
    Epsilon := 1;
    Diff := 0.0;
    Count := 0;
    IsCorrect := True;

    WriteLn('Программа находит корень уравнения ln(', A:7:4, 'x) – ', B:7:4, 'х + ', C:7:4,' = 0 с точностью эпсилон методом простой итерации.');

    Repeat
        WriteLn('Введите положительное число эпсилон, рекомендуемое значение менее 0.1');
        IsCorrect := True;

        Try
            ReadLn(Epsilon);
        Except
            WriteLn('Неправильный ввод, повторите попытку снова.');
            IsCorrect := False;
        End;

        If IsCorrect And ((Epsilon < 0) Or (Epsilon = 0)) Then
        Begin
            WriteLn('Эпсилон - положительное сколь угодно малое вещественное число, эпсилон должен быть больше 0');
            IsCorrect := False;
        End;

    Until IsCorrect;

    X1 := (LOWER_LIMIT + UPPER_LIMIT) / 2;
    X0 := X1;

    EquivEquation := (Ln(A * X0) + C) / B;
    Derivative := 1 / (B * X0);

    If Abs(Derivative) < 1 Then
    Begin
        Repeat
            Count := Count + 1;
            X0 := X1;
            EquivEquation := (Ln(A * X0) + C) / B;
            X1 := EquivEquation;
            Diff := Abs(X1 - X0);
        Until ((Diff < Epsilon) Or (Count > MAX_ITERATIONS));
        WriteLn('X = ', X1:7:15);
    End
    Else
        WriteLn('Корней методом простой итерации на данном промежутке найти не удалось');

    ReadLn;

End.
